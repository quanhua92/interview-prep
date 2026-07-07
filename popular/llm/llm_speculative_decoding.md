# Speculative Decoding

- **Category**: LLM Systems
- **Difficulty**: Expert
- **Target Role**: LLM Inference Architect / ML Platform Engineer
- **Source**: Fast Inference from Transformers via Speculative Decoding (Leviathan et al., 2023) / Speculative Sampling (Chen et al., 2023)
- **Flashcards**: [LLM Systems deck](../flash_cards/llm/llm_systems.md)

---

## Concept Overview

Autoregressive decoding in Large Language Models is severely memory-bound: generating one token requires loading the entire model's weights (often tens of gigabytes) from High-Bandwidth Memory (HBM) to the GPU's registers, performing only 2 FLOPs per parameter. 

**Speculative decoding** shifts the workload from memory-bound to compute-bound. It employs a fast, cheap **draft model** (e.g., 0.5B parameters) to autoregressively sketch $K$ candidate tokens ahead. A large, expensive **target model** (e.g., 70B parameters) then verifies all $K$ candidates in a *single parallel forward pass*. A **rejection sampling** step decides which candidates to keep. When a candidate is rejected, the target model's KV cache is rolled back, and the correct token is resampled. Crucially, the mathematical formulation of rejection sampling guarantees that the final output distribution is *exactly identical* to what the target model would have produced alone, resulting in zero quality degradation.

### The Problem It Solves

During standard autoregressive decode, the arithmetic intensity is extremely low:
$$\text{Arithmetic Intensity} = \frac{\text{FLOPs}}{\text{Bytes Loaded}} = \frac{2 \cdot P \cdot 1}{P \cdot 2} = 1 \text{ FLOP/byte}$$
On an NVIDIA A100 GPU (312 TFLOPS FP16 peak / 2.0 TB/s HBM bandwidth), the system's execution crossover is **156 FLOP/byte**. An intensity of 1 FLOP/byte means the GPU math units run at only **0.6% of peak**, stalled 99.4% of the time waiting for weights. 

By verifying $K$ tokens in a single target pass, speculative decoding loads the target model weights once but performs $2 \cdot P \cdot K$ FLOPs, scaling the intensity:

| K | Target FLOPs | Weights Loaded (ONCE) | Arithmetic Intensity | GPU Peak Capacity % |
|---|---|---|---|---|
| **1** (Baseline) | $1.40 \times 10^{11}$ | $1.40 \times 10^{11}$ bytes | **1 FLOP/B** | 0.6% |
| **2** | $2.80 \times 10^{11}$ | $1.40 \times 10^{11}$ bytes | **2 FLOP/B** | 1.3% |
| **4** | $5.60 \times 10^{11}$ | $1.40 \times 10^{11}$ bytes | **4 FLOP/B** | 2.6% |
| **8** | $1.12 \times 10^{12}$ | $1.40 \times 10^{11}$ bytes | **8 FLOP/B** | 5.1% |
| **16** | $2.24 \times 10^{12}$ | $1.40 \times 10^{11}$ bytes | **16 FLOP/B** | 10.3% |

By increasing $K$, speculative decoding amortizes weight loading, boosting GPU utilization and resulting in **2×–3× latency speedups** in practice.

### How It Works

1. **Drafting Step**: The draft model runs $K$ sequential forward steps to produce draft tokens $t_0, t_1, \dots, t_{K-1}$ and their corresponding draft probabilities $q_0, q_1, \dots, q_{K-1}$.
2. **Parallel Verification**: The target model runs a single forward pass over the block $[t_0, t_1, \dots, t_{K-1}]$ using a standard lower-triangular causal mask:
   $$\text{Causal Mask} = \begin{pmatrix} 
   \text{att} & . & . & . \\ 
   \text{att} & \text{att} & . & . \\ 
   \text{att} & \text{att} & \text{att} & . \\ 
   \text{att} & \text{att} & \text{att} & \text{att} 
   \end{pmatrix}$$
   This computes the true target probabilities $p_i(x \mid t_0 \dots t_{i-1})$ for each token position $i$ in parallel.
3. **Rejection Sampling**: For each token position $i$ from $0$ to $K-1$:
   - Draw a uniform random variable $u \sim U(0,1)$.
   - **Accept** $t_i$ if $u \le \min\left(1, \frac{p_i(t_i)}{q_i(t_i)}\right)$.
   - If **rejected** at index $R$: discard $t_R \dots t_{K-1}$. Resample the corrected token $t'_R$ from the adjusted distribution:
     $$P_{adj}(x) = \frac{\max(0, p_R(x) - q_R(x))}{Z} \quad \text{where } Z = \sum_y \max(0, p_R(y) - q_R(y))$$
     Terminate the verification round.
4. **KV Cache Rollback**: On rejection at index $R$, the last $K - R$ tokens appended to the target model's KV cache are invalid and must be removed using a `rewind(K - R)` operation.

```text
┌──────────────────────────────────────────────────────────┐
│              1. DRAFT MODEL (Serial, Cheap)              │
│                                                          │
│  ┌─────────────────┐     ┌─────────────────┐             │
│  │ draft(t_0) ──►  │ ──► │ draft(t_1) ──►  │ ──► ...     │
│  │   proposes t_0  │     │   proposes t_1  │             │
│  └─────────────────┘     └─────────────────┘             │
│                                                          │
│  ... ──► ┌───────────────────┐                           │
│          │ draft(t_K-1) ──►  │                           │
│          │   proposes t_K-1  │                           │
│          └─────────┬─────────┘                           │
└────────────────────┼─────────────────────────────────────┘
                     │ Proposals: t_0, t_1, ..., t_K-1
                     ▼
┌──────────────────────────────────────────────────────────┐
│        2. TARGET MODEL (1 Parallel Forward Pass)         │
│                                                          │
│  ┌────────────────────────────────────────────────────┐  │
│  │   target([t_0 ... t_K-1]) ──► p_0, p_1, ..., p_K-1 │  │
│  └─────────────────┬──────────────────────────────────┘  │
└────────────────────┼─────────────────────────────────────┘
                     │ Verification Probabilities
                     ▼
┌──────────────────────────────────────────────────────────┐
│                 3. REJECTION & RESAMPLING                │
│                                                          │
│                  ┌───────────────────┐                   │
│                  │  u ≤ min(1, p/q)? │                   │
│                  └─┬────────────────┬┘                   │
│                    │                │                    │
│      Accept (i < R)│                │ Reject (at index R)│
│                    ▼                ▼                    │
│              ┌──────────┐     ┌───────────────────┐      │
│              │Output t_i│     │Discard t_R..t_K-1 │      │
│              └──────────┘     └─────────┬─────────┘      │
│                                         │                │
│                                         ▼                │
│                               ┌───────────────────┐      │
│                               │Resample t'_R~P_adj│      │
│                               └─────────┬─────────┘      │
│                                         │                │
│                                         ▼                │
│                               ┌───────────────────┐      │
│                               │ KV rewind(K - R)  │      │
│                               └───────────────────┘      │
└──────────────────────────────────────────────────────────┘
```

---

## Worked Example

This example uses verified numbers from a simulated speculative decoding run with vocabulary size $V=8$ and draft length $K=4$.

### 1. Probability Distributions

Let the draft probabilities ($q$) and target probabilities ($p$) be:
- $q = [0.0938, 0.2550, 0.0569, 0.1547, 0.0466, 0.2088, 0.0695, 0.1146]$
- $p = [0.2377, 0.1761, 0.0356, 0.1068, 0.0263, 0.2903, 0.0480, 0.0791]$

The acceptance ratios $\min(1, \frac{p_i}{q_i})$ for all tokens in the vocabulary are:

| Token Idx | Word | Draft $q(x)$ | Target $p(x)$ | $p/q$ | $\min(1, \frac{p}{q})$ | Always Accept? |
|---|---|---|---|---|---|---|
| **0** | the | 0.0938 | 0.2377 | 2.534 | **1.0000** | **YES** ($p \ge q$) |
| **1** | cat | 0.2550 | 0.1761 | 0.690 | 0.6905 | No (accept w.p. 0.69) |
| **2** | xyz | 0.0569 | 0.0356 | 0.625 | 0.6248 | No (accept w.p. 0.62) |
| **3** | sat | 0.1547 | 0.1068 | 0.690 | 0.6905 | No (accept w.p. 0.69) |
| **4** | qqq | 0.0466 | 0.0263 | 0.565 | 0.5653 | No (accept w.p. 0.56) |
| **5** | on | 0.2088 | 0.2903 | 1.390 | **1.0000** | **YES** ($p \ge q$) |
| **6** | a | 0.0695 | 0.0480 | 0.690 | 0.6905 | No (accept w.p. 0.69) |
| **7** | mat | 0.1146 | 0.0791 | 0.690 | 0.6905 | No (accept w.p. 0.69) |

### 2. The Verification Trace
The draft model proposes tokens: `['a', 'sat', 'cat', 'on']` (token indices `[6, 3, 1, 5]`).

- **Step 0**: Verify $t_0 = 6$ ("a").
  - $q(t_0) = 0.0695$, $p(t_0) = 0.0480$.
  - Acceptance threshold: $\min(1, \frac{p}{q}) = 0.6905$.
  - Draw $u = 0.4963$.
  - **Decision**: **ACCEPT** (since $0.4963 \le 0.6905$).
- **Step 1**: Verify $t_1 = 3$ ("sat").
  - $q(t_1) = 0.1547$, $p(t_1) = 0.1068$.
  - Acceptance threshold: $\min(1, \frac{p}{q}) = 0.6905$.
  - Draw $u = 0.7682$.
  - **Decision**: **REJECT** (since $0.7682 > 0.6905$). 

Because index $R = 1$ is rejected, draft tokens $t_1, t_2, t_3$ are discarded.

### 3. Resampling at Rejection Index $R=1$
We construct $P_{adj}$ using the normalizer $Z = \sum \max(0, p-q) = 0.2254$:
$$P_{adj} = [0.6383, 0.0, 0.0, 0.0, 0.0, 0.3617, 0.0, 0.0]$$
Only tokens `0` ("the") and `5` ("on") have mass (where $p > q$). Drawing from $P_{adj}$ yields token **5** ("on").
- **Final Output**: `['a', 'on']` (indices `[6, 5]`).
- **Committed Tokens**: **2** (1 accepted from draft + 1 resampled).
- **KV Cache Rollback**: During verification, $K=4$ tokens were appended to the KV cache, moving the cache length from 3 (prefill) to 7. Upon rejection at $R=1$, the engine performs `rewind(K - R) = rewind(3)` to restore the cache length to 4 (representing 3 prefill + 1 accepted token).

---

## Complexity & Trade-offs

| Metric | Complexity / Value | Notes |
|---|---|---|
| **Draft Latency** | $K \cdot \text{Cost}_{draft}$ | $K$ serial forward steps on the cheap draft model. |
| **Verify Latency** | $1 \cdot \text{Cost}_{target}$ | $1$ parallel forward step on the large target model. |
| **KV Cache Truncation** | $\mathcal{O}(1)$ (dense) / $\mathcal{O}(\text{pages})$ (paged) | Tearing out rejected tokens. Paged cache blocks must be freed. |
| **Expected Speedup $S$** | $\frac{1 - \alpha^{K+1}}{(1 - \alpha)(1 + K\gamma)}$ | Where $\alpha$ is acceptance rate, $\gamma = \frac{\text{Cost}_{draft}}{\text{Cost}_{target}}$. |

---

## Common Interview Questions & How to Answer

### Q1: Prove that the output distribution of speculative decoding exactly matches that of the target model alone.
- **Answer**: The probability of outputting a token $x$ at step $i$ is the sum of two mutually exclusive events: accepting $x$ if proposed by the draft model, or rejecting the draft proposal and sampling $x$ from the adjusted distribution $P_{adj}$:
  $$P(\text{output} = x) = P(\text{draft proposes } x \text{ and is accepted}) + P(\text{reject}) \cdot P_{adj}(x)$$
  $$P(\text{output} = x) = q(x) \cdot \min\left(1, \frac{p(x)}{q(x)}\right) + Z \cdot \frac{\max(0, p(x) - q(x))}{Z}$$
  $$P(\text{output} = x) = \min(q(x), p(x)) + \max(0, p(x) - q(x))$$
  - **Case 1**: If $p(x) \ge q(x)$, then $\min(q(x), p(x)) = q(x)$ and $\max(0, p(x) - q(x)) = p(x) - q(x)$. The sum is:
    $$q(x) + p(x) - q(x) = p(x)$$
  - **Case 2**: If $p(x) < q(x)$, then $\min(q(x), p(x)) = p(x)$ and $\max(0, p(x) - q(x)) = 0$. The sum is:
    $$p(x) + 0 = p(x)$$
  Thus, in both cases, the probability of generating $x$ is exactly $p(x)$, matching the target model's output distribution.

### Q2: Under what conditions does speculative decoding result in a slowdown ($S < 1$), and how do we optimize the draft length $K$?
- **Answer**: Speculative decoding slows down inference when the cost of drafting plus the cost of target verification exceeds the cost of standard autoregressive decoding. This happens when:
  1. The draft model is too large, meaning the cost ratio $\gamma = \text{Cost}_{draft}/\text{Cost}_{target}$ is too high.
  2. The draft model is inaccurate, leading to a low acceptance rate $\alpha$, which causes most draft tokens to be rejected. For instance, with $\alpha = 0.2, K=4, \gamma=0.5$, the speedup $S$ falls to **0.42×** (a major slowdown).
  To optimize $K$, we analyze the derivative of the speedup equation:
  $$S = \frac{1 - \alpha^{K+1}}{(1 - \alpha)(1 + K\gamma)}$$
  - When $\alpha$ is high (e.g., $0.9$), increasing $K$ maximizes speedup (e.g., optimal $K \approx 10$ at $\gamma=0.1$ yielding $3.40\times$).
  - When $\alpha$ is low (e.g., $0.3$), the optimal $K$ is $1$ (yielding $1.02\times$), and any larger $K$ degrades performance due to wasted target computations.

---

## Pro-Tip: How to Impress the Interviewer

- **Tree Attention Verification (Medusa/EAGLE)**: Standard speculative decoding proposes a single linear chain of tokens. Impress the interviewer by suggesting **Tree Attention**. Instead of a single sequence, the draft mechanism (like Medusa's heads or EAGLE) proposes a branching tree of multiple candidate sequences. The target model verifies all branches of the tree in parallel using a tree-structured causal mask. This raises the effective acceptance rate $\alpha$ by checking multiple high-probability paths simultaneously, achieving speedups of **2.7×–3.5×** without needing a separate draft model.
- **Off-by-One Paged KV Cache Trapping**: In PagedAttention serving engines, rolling back the KV cache during rejection requires freeing page blocks. Warn the interviewer of the **ceil-division page boundary trap**: if cache indices are zero-indexed and page size is $16$, rolling back from cache length 33 to 32 must release the page block hosting indices 32-47. If the index subtraction is not block-aligned, memory leaks or pointer corruption will occur.
