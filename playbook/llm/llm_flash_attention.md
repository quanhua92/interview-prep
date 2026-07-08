# FlashAttention: IO-Aware Exact Attention

- **Category**: LLM Systems
- **Difficulty**: Expert
- **Target Role**: LLM Inference Engineer / ML Systems Engineer
- **Source**: FlashAttention (Dao et al. 2022) + Online Softmax (Milakov & Gimelshein 2018)
- **Flashcards**: [LLM Systems deck](../flash_cards/llm/llm_systems.md)

---

## Concept Overview

Think of the GPU as a chef working in a kitchen: the GPU's fast on-chip **SRAM** is the cutting board right in front of the chef, while the slow main memory **HBM (High-Bandwidth Memory)** is a pantry at the far end of the kitchen. Standard attention forces the chef to chop a tiny bit of ingredients, walk all the way to the pantry to store them, walk back, retrieve them, and repeat — resulting in the chef spending 95% of their time walking back and forth rather than cooking. **FlashAttention** reorganizes the work so that the chef brings small, bite-sized "tiles" of ingredients to the cutting board, completes all necessary steps (including the tricky softmax normalization) on that board, and only walks to the pantry once to deliver the final dish. By processing the attention matrix in small, local blocks instead of materializing the entire quadratic table in HBM, it eliminates memory round-trips without changing the mathematical output.

```text
┌────────────────────────────────────────────────────────────────────────┐
│                      Naive Attention (HBM Bound)                       │
│                                                                        │
│  ┌──────────────────┐  Write N² scores   ┌──────────────────────────┐  │
│  │ Compute Q @ Kᵀ   │───────────────────►│  HBM (Slow Main Memory)  │  │
│  └──────────────────┘                    └────────────┬─────────────┘  │
│                                                       │                │
│                                                       │ Read N² scores │
│                                                       ▼                │
│  ┌──────────────────┐  Write N² probs    ┌──────────────────────────┐  │
│  │ Compute Softmax  │───────────────────►│  HBM (Slow Main Memory)  │  │
│  └──────────────────┘                    └────────────┬─────────────┘  │
│                                                       │                │
│                                                       │ Read N² probs  │
│                                                       ▼                │
│                                          ┌──────────────────────────┐  │
│                                          │    Compute Probs @ V     │  │
│                                          └──────────────────────────┘  │
└────────────────────────────────────────────────────────────────────────┘

┌────────────────────────────────────────────────────────────────────────┐
│                      FlashAttention (SRAM Fused)                       │
│                                                                        │
│  ┌────────────────────────┐              ┌──────────────────────────┐  │
│  │ Load Q, K, V           │─────────────►│ Fast SRAM                │  │
│  │ tiles to SRAM          │  Compute     │ (On-chip cutting board)  │  │
│  └────────────────────────┘  scores &    └────────────┬─────────────┘  │
│                              online                   │                │
│                              softmax                  │ Write final    │
│                              locally                  │ output [N, d]  │
│                                                       ▼                │
│                                          ┌──────────────────────────┐  │
│                                          │  HBM (Final Write Only)  │  │
│                                          └──────────────────────────┘  │
└────────────────────────────────────────────────────────────────────────┘
```

### The Problem It Solves

- **Memory Bandwidth Bottleneck**: Modern GPUs have massive compute capacity (hundreds of TFLOPs) but relatively slow memory access speeds. Standard attention projects queries and keys to build a giant score table $S = Q K^T$ of shape $[N, N]$. 
- **Quadratic Scaling**: For a sequence length $N = 8192$ and head dimension $d = 64$, the score table contains $N^2 \approx 67$ million cells. Storing this table in 4-byte FP32 floats takes **256 MiB** per head, per layer ($8192 \times 8192 \times 4 \text{ bytes}$). Multiplying this across 32 heads and 80 layers yields a massive footprint.
- **Excessive Memory Traffic**: Standard attention performs $\approx 4N^2$ memory transactions (writing scores, reading scores for softmax, writing softmax probabilities, reading probabilities for value aggregation). Because LLM inference is **memory-bandwidth bound**, the GPU cores spend most of their cycles idle, waiting for these memory transactions to finish.

### How It Works

FlashAttention avoids materializing the $[N, N]$ score matrix by partitioning the inputs into blocks (tiles), loading them into SRAM, and computing attention incrementally using a technique called **online softmax**.

Standard softmax requires the maximum value of the entire row ($m$) to prevent numerical overflow during exponentiation:
$$\text{softmax}(x)_i = \frac{e^{x_i - m}}{\sum_j e^{x_j - m}} \quad \text{where} \quad m = \max_j(x_j)$$
This requirement makes tiling non-obvious, as the maximum value is not known until the entire row is read. 

To overcome this, FlashAttention uses the online softmax recurrence. For each row, it maintains three running metrics in SRAM across K/V tiles:
1. **$m$**: The running maximum score seen so far (initialized to $-\infty$).
2. **$l$**: The running normalizer sum (initialized to $0$).
3. **$o$**: The running output vector (initialized to all zeros).

When moving from a tile with running max $m_{\text{old}}$ and normalizer $l_{\text{old}}$ to a new tile with local max $m_{\text{new}} = \max(m_{\text{old}}, \text{rowmax}(s))$, we apply a **correction factor** $\text{corr} = e^{m_{\text{old}} - m_{\text{new}}}$ to our running aggregates before adding the new tile's contributions:
$$l_{\text{new}} = e^{m_{\text{old}} - m_{\text{new}}} \cdot l_{\text{old}} + \sum e^{s - m_{\text{new}}}$$
$$o_{\text{new}} = e^{m_{\text{old}} - m_{\text{new}}} \cdot o_{\text{old}} + e^{s - m_{\text{new}}} V_{\text{tile}}$$

Because $m_{\text{new}} \ge m_{\text{old}}$, the exponent is always $\le 0$, yielding a correction factor $\le 1$ that shrinks the past contributions to align with the new, larger denominator. At the end of the row, the true normalized output is simply $o / l$.

---

## Worked Example

Below are the exact values from a simulated attention forward pass with sequence length $N = 8$, head dimension $d = 8$, scale factor $1/\sqrt{d} = 0.3536$, and tile size $B_r = B_c = 4$ ($2 \times 2$ tiles).

### The Materialized Score Matrix $S$ (Naive Attention)
Standard attention writes this entire $[8, 8]$ table to slow HBM:

| $q \backslash k$ | $k=0$ | $k=1$ | $k=2$ | $k=3$ | $k=4$ | $k=5$ | $k=6$ | $k=7$ | **Row Max** |
|---|---|---|---|---|---|---|---|---|---|
| **$q=0$** | $-0.1160$ | $+0.0909$ | $-0.0998$ | $-0.4400$ | $-0.3969$ | $+0.0736$ | $+0.4049$ | $-0.1240$ | **$+0.4049$** |
| **$q=1$** | $+0.1595$ | $+0.0673$ | $-0.0434$ | $-0.4481$ | $-0.0200$ | $+0.0276$ | $+0.2197$ | $+0.2710$ | **$+0.2710$** |
| **$q=2$** | $-0.2861$ | $+0.1418$ | $-0.0041$ | $-0.2182$ | $+0.2089$ | $-0.0232$ | $+0.4081$ | $+0.2560$ | **$+0.4081$** |
| **$q=3$** | $+0.0296$ | $-0.1254$ | $+0.0781$ | $-0.4158$ | $-0.4133$ | $+0.0830$ | $+0.2035$ | $+0.0956$ | **$+0.2035$** |
| **$q=4$** | $-0.0327$ | $+0.0913$ | $+0.1463$ | $+0.0832$ | $-0.2202$ | $-0.0010$ | $-0.0073$ | $+0.0617$ | **$+0.1463$** |
| **$q=5$** | $+0.5159$ | $+0.0707$ | $-0.1574$ | $-0.1376$ | $-0.5931$ | $-0.1283$ | $+0.0715$ | $-0.1468$ | **$+0.5159$** |
| **$q=6$** | $+0.1365$ | $-0.0496$ | $+0.0134$ | $+0.0490$ | $-0.0689$ | $+0.1214$ | $-0.2589$ | $+0.1266$ | **$+0.1365$** |
| **$q=7$** | $+0.4462$ | $-0.2285$ | $+0.0145$ | $+0.1127$ | $+0.5438$ | $+0.3833$ | $-0.4868$ | $+0.0673$ | **$+0.5438$** |

### Step-by-Step Online Softmax for Row $q=0$
Row $q=0$ is processed over $T_c = 2$ tiles of keys:

#### Tile $j=0$ (keys $0, 1, 2, 3$)
- **Local Scores**: $s = [-0.1160, +0.0909, -0.0998, -0.4400]$
- **Local Max**: $\text{rowmax}(s) = +0.0909$
- **Accumulators**: $m_{\text{old}} = -\infty, \ l_{\text{old}} = 0, \ o_{\text{old}} = \mathbf{0}$
- **New Max**: $m_{\text{new}} = \max(-\infty, +0.0909) = +0.0909$
- **Correction Factor**: $\text{corr} = e^{-\infty - 0.0909} = 0.0$ (wipes out the empty history)
- **Exponentiated Shifted Scores**: $p = e^{s - m_{\text{new}}} = [0.8131, 1.0000, 0.8264, 0.5881]$
- **Update Running Normalizer**: $l_{\text{new}} = 0.0 \cdot 0 + \sum(p) = 3.2277$
- **Update Running Output**: $o_{\text{new}} = 0.0 \cdot \mathbf{0} + p V_{\text{tile}, 0} = [-0.4464, -0.2905, -1.0848, +0.1282, +0.1119, -0.0819, +0.6012, -0.2488]$
- **State after $j=0$**: $m = +0.0909, \ l = 3.2277$

#### Tile $j=1$ (keys $4, 5, 6, 7$)
- **Local Scores**: $s = [-0.3969, +0.0736, +0.4049, -0.1240]$
- **Local Max**: $\text{rowmax}(s) = +0.4049$
- **New Max**: $m_{\text{new}} = \max(+0.0909, +0.4049) = +0.4049$ (the running maximum increases!)
- **Correction Factor**: $\text{corr} = e^{0.0909 - 0.4049} = \mathbf{0.7305}$
- **Exponentiated Shifted Scores**: $p = e^{s - m_{\text{new}}} = [0.4485, 0.7180, 1.0000, 0.5893]$
- **Update Running Normalizer**: $l_{\text{new}} = \mathbf{0.7305} \cdot 3.2277 + \sum(p) = 2.3578 + 2.7558 = 5.1135$
- **Update Running Output**: $o_{\text{new}} = \mathbf{0.7305} \cdot o_{\text{old}} + p V_{\text{tile}, 1} = [-0.3441, -0.7496, -1.1122, +0.1029, +0.9256, -0.7843, +1.1381, -0.5088]$
- **State after $j=1$**: $m = +0.4049, \ l = 5.1135$

#### Final Row Normalization
$$\text{out} = \frac{o}{l} = [-0.0673, -0.1466, -0.2175, +0.0201, +0.1810, -0.1534, +0.2226, -0.0995]$$

### Running Metrics Trace (First 4 rows of Q-tile $i=0$)
The table below tracks the state transition of $(m \ / \ l \ / \ |o|_{\max})$ after each K/V tile:

| Step | $q=0$ ($m \ / \ l \ / \ |o|_{\max}$) | $q=1$ ($m \ / \ l \ / \ |o|_{\max}$) | $q=2$ ($m \ / \ l \ / \ |o|_{\max}$) | $q=3$ ($m \ / \ l \ / \ |o|_{\max}$) |
|---|---|---|---|---|
| **$j=0$** | $+0.091 \ / \ 3.228 \ / \ 1.085$ | $+0.159 \ / \ 3.273 \ / \ 1.093$ | $+0.142 \ / \ 3.214 \ / \ 1.120$ | $+0.078 \ / \ 3.379 \ / \ 1.086$ |
| **$j=1$** | $+0.405 \ / \ 5.113 \ / \ 1.138$ | $+0.271 \ / \ 6.409 \ / \ 1.260$ | $+0.408 \ / \ 5.790 \ / \ 1.151$ | $+0.204 \ / \ 6.304 \ / \ 1.235$ |

### Verification of Exact Equivalence
Comparing the output from our tiled implementation against standard attention:
- **Max Absolute Difference**: $2.98 \times 10^{-8}$ (pure floating-point rearrangement noise).
- **Broken Variant (No Rescaling)**: If we omit the $e^{m_{\text{old}} - m_{\text{new}}}$ correction, the output deviates from the baseline by $2.18 \times 10^{-2}$ (over $700,000 \times$ larger error), resulting in garbled text.

---

## Complexity & Trade-offs

| Metric | Value | Notes |
|---|---|---|
| **HBM Read/Write Complexity** | $\mathcal{O}(N d + N^2 d^2 / M)$ | Standard attention requires $\mathcal{O}(N^2)$ reads/writes. Here, $M$ is the size of on-chip SRAM, reducing traffic significantly. |
| **FLOPs (Forward Pass)** | $\mathcal{O}(N^2 d)$ | Identical to standard attention. FlashAttention is an I/O optimization, not a mathematical approximation. |
| **FLOPs (Backward Pass)** | $\mathcal{O}(N^2 d)$ | Slightly higher than standard because we recompute the attention scores on the fly to avoid storing them. |
| **Activation Memory (Training)** | $\mathcal{O}(N)$ | Standard attention stores the full $N \times N$ matrix ($\mathcal{O}(N^2)$). FlashAttention only caches $m$ and $l$ of size $N$. |
| **Numerical Accuracy** | Exact ($\approx 3 \times 10^{-8}$ diff) | Not an approximation. Differs only due to floating-point addition order. |

---

## Common Interview Questions & How to Answer

### Q1: FlashAttention claims to speed up LLM attention, yet it performs the same (or even slightly more) FLOPs than standard attention. How does this work?
- **Answer**: GPUs have two types of memory: slow, large main memory (HBM) and fast, small local memory (SRAM). In standard attention, the GPU's compute cores calculate the $N \times N$ score matrix, write it to HBM, read it back to compute the softmax, write the probabilities back to HBM, and read them again to multiply by the values. Since LLM inference is bandwidth-bound, the GPU spends most of their time waiting for these HBM transfers to complete. FlashAttention fuses these steps by keeping local tiles in SRAM and doing the calculations in place. Since the intermediate $N \times N$ matrix never leaves SRAM, HBM traffic drops from $\mathcal{O}(N^2)$ to $\mathcal{O}(N)$, letting the GPU compute at its maximum potential.

### Q2: What is the online softmax recurrence, and why is the scaling factor $\exp(m_{\text{old}} - m_{\text{new}})$ critical? What happens if you omit it?
- **Answer**: Standard softmax requires the global maximum value of a row to remain numerically stable. In a tiled setting, we do not know the global maximum beforehand. Online softmax solves this by carrying a running maximum $m$, a running normalizer sum $l$, and a running output $o$. When a new tile has a local maximum higher than $m_{\text{old}}$, the scaling factor $\exp(m_{\text{old}} - m_{\text{new}})$ is used to rescale the previously accumulated $l$ and $o$ to the new, larger scale before adding the new tile's contributions. Without this correction, the values inside the accumulator would represent mixed scales, causing silent numerical corruption and producing incorrect outputs.

### Q3: How does FlashAttention reduce the memory footprint during training?
- **Answer**: Standard attention caches the entire $N \times N$ attention matrix in HBM during the forward pass to use during backpropagation. This is the primary memory bottleneck when training long-context LLMs. FlashAttention does not store the $N \times N$ matrix. Instead, it only stores the running row maximum $m$ and the normalizer sum $l$ (which are $\mathcal{O}(N)$). During the backward pass, it loads the tiles of $Q, K, V$ back into SRAM and recomputes the $N \times N$ blocks on the fly. This increases FLOPs by about 30%, but drastically reduces memory consumption, enabling training with much larger batch sizes and sequence lengths.

---

## Pro-Tip: How to Impress the Interviewer

- **Warp-level Scheduling & Asynchronous Copies**: In interviews, stand out by discussing how FlashAttention partitions work across CUDA thread blocks and warps. SRAM tiles (like $B_r = B_c = 128$) are loaded using hardware asynchronous copy commands (e.g., `cp.async` on NVIDIA Ampere/Hopper) to bypass registers and fetch data directly from HBM to SRAM. While one warp group computes matmuls on the current tile, another warp group prefetches the next tile in the background, overlapping compute and memory access.
- **SRAM Budget Calculation**: Demonstrate system design maturity by showing how to select tile sizes based on head dimension $d$. On an NVIDIA A100 with $96\text{ KB}$ of shared memory per SM:
  $$(\text{Tile}_q \times d + \text{Tile}_k \times d) \times \text{bytesPerElement} \le \text{sharedMemoryBudget}$$
  If $d = 128$ and we use FP16 (2 bytes), a tile size of $B_r=128, B_c=64$ consumes $(128 \times 128 + 64 \times 128) \times 2 = 48\text{ KB}$, leaving plenty of space for accumulators and double-buffering. If $d$ increases, the tile size must be scaled down accordingly.
