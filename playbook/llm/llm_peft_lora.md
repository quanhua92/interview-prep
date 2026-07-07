# Parameter-Efficient Fine-Tuning: LoRA & QLoRA

- **Category**: LLM Systems
- **Difficulty**: Hard
- **Target Role**: LLM Systems Engineer / ML Platform Engineer
- **Source**: PEFT_LORA.md + peft_lora_output.txt (Hu et al. 2021, Dettmers et al. 2023, Chen et al. 2023, Sheng et al. 2023)
- **Flashcards**: [LLM Systems deck](../flash_cards/llm/llm_systems.md)

---

## Concept Overview

Think of pre-trained LLM weights as a massive marble statue, and fine-tuning as carving modifications into it. Instead of chipping away at the original marble (which would require making a separate copy of the heavy statue for every single task), LoRA bolts a small, adjustable wireframe skeleton onto the outside. This skeleton takes the input signals, processes them through a pair of lightweight, low-rank matrices, and adds the adjustment back to the statue's output.

Specifically, LoRA freezes the pre-trained weight matrix $W_0 \in \mathbb{R}^{d \times k}$ and approximates the task-specific update matrix $\Delta W \in \mathbb{R}^{d \times k}$ as the product of two low-rank matrices $B \in \mathbb{R}^{d \times r}$ and $A \in \mathbb{R}^{r \times k}$, where the rank $r \ll \min(d, k)$. By training only $A$ and $B$, we reduce the number of trainable parameters by orders of magnitude (e.g., $10,000\times$ fewer parameters for GPT-3). QLoRA goes a step further by compressing the frozen base weights to a specialized 4-bit NormalFloat (NF4) representation to slash the base model VRAM footprint, while maintaining fp16 adapters. In multi-adapter serving, we can run multiple independent task-specific adapters concurrently on a single shared base model, routing different tokens in a batch to different adapters via grouped GEMMs.

### The Problem It Solves

Full fine-tuning requires updating and saving all $d \times k$ weights for each task. For a model like GPT-3 175B, each fine-tuned variant requires saving a separate 350 GB checkpoint (in FP16). Serving $N = 100$ independent personalized versions would require storing and hosting $\sim 35\text{ TB}$ of weights, which is financially and operationally prohibitive. At a micro-level, for a single layer of Qwen3-0.5B with hidden dimension $d = k = 896$, full fine-tuning must track and store $d \cdot k = 802,816$ trainable parameters for just one layer of one task. 

Additionally, training memory footprint is dominated by optimizer states (momentum and variance) in Adam. For each trainable parameter, we store 16 bytes of optimizer states (4 bytes master parameter, 4 bytes grad copy, 4 bytes momentum, 4 bytes variance). Full parameter updates thus consume massive memory. LoRA limits training to only the low-rank path $r(d+k)$, which represents $\sim 0.1\% - 1\%$ of the base model weights, dropping optimizer memory overhead to negligible levels.

### How It Works

LoRA structures the forward pass of a linear projection layer as:
$$y = W_0 x + \Delta W x = W_0 x + \frac{\alpha}{r} B (A x)$$

Where:
- $W_0 \in \mathbb{R}^{d \times k}$ is the frozen pre-trained weight matrix.
- $x \in \mathbb{R}^k$ is the input vector.
- $A \in \mathbb{R}^{r \times k}$ is the down-projection matrix, initialized using a random Gaussian distribution: $A \sim \mathcal{N}(0, \sigma^2)$.
- $B \in \mathbb{R}^{d \times r}$ is the up-projection matrix, initialized to all zeros ($B = 0$).
- $\alpha$ is a constant scaling hyperparameter.
- $r$ is the inner rank.

Since $B = 0$ at the start of training, the update $\Delta W = \frac{\alpha}{r} BA = 0$, meaning the adapter starts as a pure no-op, preserving base model behavior exactly.

```text
                     Input x (shape: [k])
                              │
             ┌────────────────┴────────────────┐
             ▼                                 ▼
   ┌───────────────────┐             ┌───────────────────┐
   │  Frozen Base W₀   │             │ Down-projection A │
   │  (shape: [d, k])  │             │  (shape: [r, k])  │
   └─────────┬─────────┘             └─────────┬─────────┘
             │                                 │ A·x
             │                                 ▼
             │                       ┌───────────────────┐
             │                       │  Up-projection B  │
             │                       │  (shape: [d, r])  │
             │                       └─────────┬─────────┘
             │                                 │ B·A·x
             │                                 ▼
             │                       ┌───────────────────┐
             │                       │   Scale Factor    │
             │                       │      (α / r)      │
             │                       └─────────┬─────────┘
             │ W₀·x                            │ (α/r)·B·A·x
             ▼                                 ▼
           ┌─────────────────────────────────────┐
           │               Sum (+)               │
           └──────────────────┬──────────────────┘
                              │
                              ▼
                     Output y (shape: [d])
```

During inference, if only a single adapter is deployed, we can pre-compute $W_{\text{merged}} = W_0 + \frac{\alpha}{r} BA$ and run a normal linear layer ($y = W_{\text{merged}} x$), introducing **zero** additional inference latency.

For multi-adapter serving, we avoid merging and instead run:
1. A shared, frozen base forward pass ($W_0 x$) once for all tokens in a batch.
2. A specialized grouped GEMM kernel (such as Punica's SGMV/BGMV) to batch the low-rank paths for different tokens that target different adapters in a single GPU pass.
3. S-LoRA style paged adapter memory management, mapping non-contiguous blocks of adapter weights to GPU memory dynamically (analogous to PagedAttention for KV cache).

---

## Worked Example

### 1. Zero at Initialization (Step 0)
Using $d = 8, k = 8, r = 2, \alpha = 16$ (scaling factor $\alpha/r = 8.0$), we initialize $A$ randomly and set $B = 0$. 
Given input:
$$x = [0.5, -0.3, 0.8, -0.1, 0.4, -0.6, 0.2, 0.7]$$

From `peft_lora_output.txt`:
```
y_init = [0.2, -0.205, 0.96, -0.45, 0.5, 0.045, 0.085, 0.27]
W₀·x   = [0.2, -0.205, 0.96, -0.45, 0.5, 0.045, 0.085, 0.27]
```
Since $B = 0$, $y_{\text{init}} = W_0 x$ exactly.

### 2. After Training (Step 1)
After training, $B$ is updated with learned values. The forward pass outputs:
- **Base Path ($W_0 x$):** `[0.2, -0.205, 0.96, -0.45, 0.5, 0.045, 0.085, 0.27]`
- **Adapter Path ($\frac{\alpha}{r} B (A x)$):** `[-0.0192, 0.0446, 0.0456, 0.0643, -0.0221, 0.0765, 0.0045, 0.0379]`
- **Total Output ($y = W_0 x + \frac{\alpha}{r} B (A x)$):** `[0.1808, -0.1604, 1.0056, -0.3857, 0.4779, 0.1215, 0.0895, 0.3079]`

The gold validation pin is $y[0] = 0.180800$.

### 3. Parameter Savings Across Ranks (Layer $d = k = 8$)
Full fine-tuning requires $d \cdot k = 64$ parameters.

| Rank ($r$) | LoRA Params $r(d+k)$ | Ratio $r(d+k)/dk$ | Savings |
|---|---|---|---|
| 1 | 16 | 0.2500 | $4.00\times$ |
| 2 | 32 | 0.5000 | $2.00\times$ |
| 4 | 64 | 1.0000 | $1.00\times$ (Break-even) |
| 8 | 128 | 2.0000 | $0.50\times$ (LoRA is larger) |

*Note: For a real-world attention layer with $d = k = 12288$ and $r = 4$, full fine-tuning requires $150,994,944$ parameters, whereas LoRA requires only $98,304$ parameters (a $1536\times$ reduction).*

### 4. QLoRA: NF4 Base + FP16 Adapters
For a Qwen3-0.5B layer ($d = k = 896$), the memory footprints are:
- **FP16 Base:** $802,816 \times 2 = 1,605,632\text{ bytes} \approx 1.606\text{ MB}$
- **NF4 4-bit Base:** $802,816 / 2 = 401,408\text{ bytes} \approx 0.401\text{ MB}$ ($4.0\times$ smaller)

The NF4 codebook values normalized to $[-1, 1]$:
```
[-1.0, -0.6962, -0.5251, -0.3949, -0.2844, -0.1848, -0.0911, 0.0,
  0.0796,  0.1609,  0.2461,  0.3379,  0.4407,  0.5626,  0.7230,  1.0]
```
Comparing outputs for QLoRA forward pass:
- **FP16 Base (Exact):** `[0.1808, -0.1604, 1.0056, -0.3857, 0.4779, 0.1215, 0.0895, 0.3079]`
- **QLoRA (NF4 quantized base):** `[0.1572, -0.1323, 1.0179, -0.3589, 0.4801, 0.1080, 0.0769, 0.2974]`
- **Max Absolute Difference:** `0.0281` (arising purely from base rounding error; the adapter path is exact).

### 5. Multi-Adapter Serving Math
To serve $N = 1000$ personalized tasks with $d = k = 12288$ (GPT-3 attention layer) and $r = 64$:

| Strategy | Weights in VRAM | Notes |
|---|---|---|
| **$N$ Full Replicas (Full FT)** | $1000 \times 150,994,944 = 151.0\text{ B}$ weights | Unscalable |
| **1 FP16 Base + $N$ LoRA** | $150,994,944 + 1000 \times 1,572,864 = 1.72\text{ B}$ weights | $87.8\times$ savings |
| **1 NF4 Base + $N$ QLoRA** | $37,748,736\text{ (NF4)} + 1000 \times 1,572,864 = 1.61\text{ B}$ weights | $93.8\times$ savings |

---

## Complexity & Trade-offs

| Metric | Value | Notes |
|---|---|---|
| **Trainable Parameter Count** | $O(r(d + k))$ | Reduction by $1000\times$ to $10,000\times$ compared to full fine-tuning. |
| **Memory Footprint (Training)** | Base Model + $O(r(d+k))$ | QLoRA allows base model to be quantized to 4-bit (NF4), reducing base footprint by $4\times$. |
| **Serving Overhead per Task** | $r(d + k)$ weights | $\sim 1.04\%$ of a base layer per task for $r=64$, $d=k=12288$. |
| **Inference Latency** | $0$ (if merged) \| Grouped GEMM Overhead (if serving multi-adapters) | Merge is only possible if serving a single task. Multi-adapter serving requires running $W_0 x$ once + token-specific $B(Ax)$ paths. |
| **Batching Efficiency** | Reduced if naive loops are used | Naive loops process adapters sequentially. Punica grouped GEMM or S-LoRA paged adapter memory restores batched GPU execution. |

---

## Common Interview Questions & How to Answer

### Q1: Why do we initialize $B$ to zero and $A$ to a random Gaussian in LoRA? What happens if both are initialized to zero, or if both are initialized randomly?
- **Answer**: 
  We initialize $A \sim \mathcal{N}(0, \sigma^2)$ and $B = 0$ so that the initial update matrix is $\Delta W = \frac{\alpha}{r} BA = 0$. This ensures that at step 0 of training, the model behaves exactly like the pre-trained base model. 
  - If both $A$ and $B$ were initialized to zero, the gradients for both matrices would be zero during backpropagation, preventing the model from learning anything (symmetry break failure).
  - If both were initialized to non-zero random values, the initial output would be distorted by the untrained adapter path ($\Delta W \neq 0$), causing optimization instability at the start of training and degrading the base model's zero-shot capabilities.

### Q2: How does QLoRA achieve 4-bit training without losing accuracy compared to 16-bit? Explain the role of NF4 and Double Quantization.
- **Answer**: 
  QLoRA achieves this via three core techniques:
  1. **NF4 (NormalFloat4) Data Type**: It is an information-theoretically optimal quantization scheme for normally distributed data. Since neural network weights typically follow a zero-mean normal distribution, NF4 spaces its 16 quantization levels on the quantiles of a normal distribution. This packs levels more densely around zero where most weights reside, reducing quantization error.
  2. **Double Quantization (DQ)**: It quantizes the quantization constants (scales) themselves. For instance, quantizing block-level scales from 32-bit floats to 8-bit floats reduces memory overhead from 32 bits per block of 64 weights to 8 bits, saving roughly 0.37 bits/parameter ($\sim 3$ GB for a 65B model).
  3. **FP16/BF16 Computation**: During forward and backward passes, the NF4 weights are dequantized on-the-fly to 16-bit floats. Gradients are computed and backpropagated only through the fp16/bf16 adapter weights ($A$ and $B$). The base model remains frozen in 4-bit storage.

### Q3: When serving thousands of adapters on a single GPU in multi-tenant serving, how do Punica and S-LoRA optimize memory and compute?
- **Answer**: 
  Multi-tenant serving faces two primary issues: execution serialization (GPU starvation) and VRAM capacity limitations.
  - **Punica (Grouped GEMM)**: A naive batching approach runs sequential matrix multiplications for different adapters in a batch, which wastes GPU parallelism. Punica utilizes a specialized grouped GEMM kernel (such as SGMV/BGMV) that performs all adapter matmuls for their respective token slices in a single batched GPU kernel execution (modeled as `einsum("tdr,tr->td")`).
  - **S-LoRA (Paged Adapter Memory)**: Since loading all adapters into VRAM causes out-of-memory (OOM) errors, S-LoRA implements a unified page-based memory manager for adapters, mimicking PagedAttention. It shards adapter weights into non-contiguous physical pages in GPU memory. Only the adapters needed for the current active batch are swapped in, allowing thousands of adapters to be served concurrently with sub-millisecond swap times.

---

## Pro-Tip: How to Impress the Interviewer

- **Demonstrate deep hardware intuition by discussing the "Grouped GEMM" kernel mechanics.** Explain that when batching requests across different adapters, the batch cannot be processed by a single standard GEMM since different rows need different weight matrices ($A_i, B_i$). Mention **Punica's SGMV** (Segmented Gather Matrix-Vector multiplication) which enables a single kernel to compute $Y_i = B_i (A_i X_i)$ for variable-sized sequences without padding, avoiding CPU-GPU launch overheads and fully saturating GPU tensor cores.
