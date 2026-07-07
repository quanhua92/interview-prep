# Causal Masking & QK-Norm

- **Category**: LLM Systems
- **Difficulty**: Easy
- **Target Role**: LLM Inference Engineer / ML Systems Engineer
- **Source**: CAUSAL_MASK.md + causal_mask_output.txt (Vaswani et al. 2017, Dehghani et al. 2023)
- **Flashcards**: [LLM Systems deck](../flash_cards/llm/llm_systems.md)

---

## Concept Overview

Think of causal masking as a **bouncer** at a VIP club who ensures that during language model training, each token can only read messages written **before** it, preventing it from peeking into the future. It accomplishes this by adding a value of $-\infty$ to future attention logits before the softmax step, which converts those probabilities to exactly $0\%$. In multi-token prefilling and single-token decoding phases, the attention mask boundary shifts using a diagonal offset index $k = S - L$ to keep the past-future dividing line aligned with the actual generated history. To prevent the attention logits from growing too large and saturating the softmax function, modern architectures introduce **QK-Norm**, which normalizes the query and key vectors using RMSNorm prior to the dot product.

### The Problem It Solves

Without these attention stabilization and causal guarding mechanics:
- **Information Leakage**: An autoregressive language model must not see tokens to the right of the current position during training. Without a causal mask, the model would simply memorize the future tokens, failing to generalize at inference time.
- **The Decode Off-by-One Bug**: During generation (decode phase), we compute attention for one new query token ($L=1$) against all cached keys ($S=N$). Without the diagonal offset $k=S-L$, the mask blocks the token from seeing its own history. As shown in `causal_mask_output.txt`, it forces the new token to attend **100%** to the very first token ($s=0$) and **0%** to the rest, resulting in immediate silent generation failure.
- **Softmax Saturation**: In deep models, the query-key dot products can grow extremely large (e.g., reaching scores of **61.7954**). If the scores spread widely, softmax saturates, producing a one-hot probability distribution with near-zero gradients, stalling training.

### How It Works

Causal self-attention operates using three primary mechanisms working together.

```text
┌────────────────────────────────────────────────────────────────────────┐
│                      1. Query-Key Normalization                        │
│                                                                        │
│        ┌──────────────────────┐        ┌──────────────────────┐        │
│        │ Raw Q: [B, L, H, D]  │        │ Raw K: [B, L, H, D]  │        │
│        └───────────┬──────────┘        └───────────┬──────────┘        │
│                    │                               │                   │
│                    ▼                               ▼                   │
│        ┌──────────────────────┐        ┌──────────────────────┐        │
│        │      RMSNorm(Q)      │        │      RMSNorm(K)      │        │
│        └───────────┬──────────┘        └───────────┬──────────┘        │
└────────────────────┼───────────────────────────────┼───────────────────┘
                     │                               │
                     ▼                               ▼
┌────────────────────────────────────────────────────────────────────────┐
│                   2. Shape Choreography & RoPE                         │
│                                                                        │
│        ┌──────────────────────┐        ┌──────────────────────┐        │
│        │ Apply RoPE (L-axis)  │        │ Apply RoPE (L-axis)  │        │
│        └───────────┬──────────┘        └───────────┬──────────┘        │
│                    │                               │                   │
│                    ▼                               ▼                   │
│        ┌──────────────────────┐        ┌──────────────────────┐        │
│        │ Transpose: [B,H,L,D] │        │ Transpose: [B,H,S,D] │        │
│        └───────────┬──────────┘        └───────────┬──────────┘        │
└────────────────────┼───────────────────────────────┼───────────────────┘
                     │                               │
                     └───────────────┬───────────────┘
                                     │
                                     ▼
┌────────────────────────────────────────────────────────────────────────┐
│                         3. Masked Dot Product                          │
│                                                                        │
│                    ┌────────────────────────────────┐                  │
│                    │   Scores = (Q' @ K'^T) / √D    │                  │
│                    │          [B, H, L, S]          │                  │
│                    └───────────────┬────────────────┘                  │
│                                    │                                   │
│  ┌───────────────────────┐         │                                   │
│  │      Mask[L, S]       │────────►┼ (Add Mask)                        │
│  │       k = S - L       │         │                                   │
│  └───────────────────────┘         │                                   │
│                                    ▼                                   │
│                    ┌────────────────────────────────┐                  │
│                    │  probs = softmax(Scores, dim)  │                  │
│                    └───────────────┬────────────────┘                  │
│                                    │                                   │
│                                    ▼                                   │
│                    ┌────────────────────────────────┐                  │
│                    │        Out = probs @ V         │                  │
│                    └────────────────────────────────┘                  │
└────────────────────────────────────────────────────────────────────────┘
```

#### Step-by-Step Execution:
1. **QK-Norm**: Apply RMSNorm to the projected query and key states along the head-dim axis $D$.
   - $Q' = \text{RMSNorm}(Q) \odot W_q$
   - $K' = \text{RMSNorm}(K) \odot W_k$
2. **Positional Encoding & Transpose**: Apply RoPE to $Q'$ and $K'$ along the position axis $L$, then transpose the states to shape `[B, H, L, D]`.
3. **Scaled Dot Product**: Compute raw scores: $\text{scores} = \frac{Q' K'^T}{\sqrt{D}}$.
4. **Causal Mask Application**: Shift the mask diagonal based on the difference between key length ($S$) and query length ($L$):
   - $k = S - L$
   - $\text{mask}_{l, s} = \begin{cases} 0 & s \le l + k \\ -\infty & \text{otherwise} \end{cases}$
   - Add the mask to the scores: $\text{scores} = \text{scores} + \text{mask}$.
5. **Softmax & Value Mixing**: Run softmax to get probabilities (masked values become $0.0$) and multiply by $V$:
   - $\text{probs} = \text{softmax}(\text{scores}, \text{dim}=-1)$
   - $\text{output} = \text{probs} V$

---

## Worked Example

### Prefill vs. Decode Causal Mask (L vs. S)
Here is how the mask matrix changes depending on the execution phase (sourced from `causal_mask_output.txt`):

#### Prefill Phase ($L=4, S=4, k = S-L = 0$):
Every query token $l$ attends to past and current keys $s \le l$:

| $l \backslash s$ | s=0 | s=1 | s=2 | s=3 |
|---|---|---|---|---|
| **l=0** | 0.0 | $-\infty$ | $-\infty$ | $-\infty$ |
| **l=1** | 0.0 | 0.0 | $-\infty$ | $-\infty$ |
| **l=2** | 0.0 | 0.0 | 0.0 | $-\infty$ |
| **l=3** | 0.0 | 0.0 | 0.0 | 0.0 |

After softmax, the resulting probabilities show a strictly lower-triangular profile (upper triangle is exactly `0.0000`):

| $l \backslash s$ | s=0 | s=1 | s=2 | s=3 |
|---|---|---|---|---|
| **l=0** | **1.0000** | 0.0000 | 0.0000 | 0.0000 |
| **l=1** | 0.5624 | **0.4376** | 0.0000 | 0.0000 |
| **l=2** | 0.3139 | 0.3309 | **0.3552** | 0.0000 |
| **l=3** | 0.2429 | 0.2788 | 0.2336 | **0.2446** |

The gold pin output vector for $l=3$ is exactly `[0.2429, 0.2788, 0.2336, 0.2446, 0.0, 0.0, 0.0, 0.0]`.

#### Decode Phase ($L=1, S=4, k = S-L = 3$):
The single query token represents the last position and attends to the entire history:

| $l \backslash s$ | s=0 | s=1 | s=2 | s=3 |
|---|---|---|---|---|
| **l=0** | 0.0 | 0.0 | 0.0 | 0.0 |

#### The Decode Mask Bug ($k=0$ instead of $k=3$):
If the offset is neglected, the mask incorrectly defaults to:

| $l \backslash s$ | s=0 | s=1 | s=2 | s=3 |
|---|---|---|---|---|
| **l=0** | 0.0 | $-\infty$ | $-\infty$ | $-\infty$ |

Below is the resulting probability distribution comparison:

| Mask used | probs[s=0] | probs[s=1] | probs[s=2] | probs[s=3] |
|---|---|---|---|---|
| **Correct ($k=3$)** | 0.4195 | 0.1553 | 0.3751 | 0.0501 |
| **Wrong ($k=0$)** | **1.0000** | **0.0000** | **0.0000** | **0.0000** |

The wrong mask forces the model to ignore tokens $1..3$ entirely, attending only to the very first token.

### QK-Norm Performance (Seeded x5 Inputs)
Comparing attention stats with and without QK-Norm (from `causal_mask_output.txt`):

| Metric | Without QK-Norm | With QK-Norm |
|---|---|---|
| **Max $\|q\|$** | 20.0820 | **2.8284** ($\sqrt{D}$) |
| **Max $\|k\|$** | 20.8228 | **2.8284** ($\sqrt{D}$) |
| **Max RMS(q)** | 7.1001 | **1.0000** |
| **Max Abs Score ($Q \cdot K / \sqrt{D}$)** | 61.7954 | **1.6563** |
| **Std of Scores** | 23.9671 | **0.8721** |

QK-Norm bounds the dot products to $\approx \pm 1.6$, preventing logits from saturating softmax and stabilizing gradient flow.

### Shape Choreography Step-by-Step
For tensor sizes $B=1, L=4, H=2, D=8$, the dimensions flow as follows:

| Step | Operation | Result Shape |
|---|---|---|
| **1. Project** | `q = linear(x, wq).reshape(B, L, H, D)` | `(1, 4, 2, 8)` |
| **2. QK-Norm** | `q = rms_norm(q)` (on $D$ axis, before RoPE) | `(1, 4, 2, 8)` |
| **3. RoPE** | `q = apply_rope(q)` (over sequence axis $L$) | `(1, 4, 2, 8)` |
| **4. Transpose** | `q = q.transpose(1, 2)` | `(1, 2, 4, 8)` |
| **5. Attention** | `scores = q @ k.T * scale + mask` | `(1, 2, 4, 4)` |
| **6. Transpose back**| `out = out.transpose(1, 2)` | `(1, 4, 2, 8)` |
| **7. Reassemble** | `out = out.reshape(B, L, H * D)` | `(1, 4, 16)` |

---

## Complexity & Trade-offs

| Metric | Value | Notes |
|---|---|---|
| **Attention Mask Space** | $O(L \cdot S)$ per head | Typically generated on the fly to save memory bandwidth |
| **Attention Flops** | $O(B \cdot H \cdot L \cdot S \cdot D)$ | Dominates computation at long contexts |
| **QK-Norm Parameter Count**| $2 \cdot H \cdot D$ parameters | One learned scale parameter per head per dimension for $Q$ and $K$ |
| **QK-Norm Computation** | $O(B \cdot L \cdot H \cdot D)$ FLOPs | Extremely cheap; requires only one division pass per head vector |
| **Memory Bandwidth** | High | Mask additions and softmax require element-wise GPU memory operations |

---

## Common Interview Questions & How to Answer

### Q1: Why do we add $-\infty$ to the future tokens instead of setting their values to $0$ before softmax?
- **Answer**: Softmax exponentiates its input: $\text{softmax}(x)_i = \frac{e^{x_i}}{\sum_j e^{x_j}}$. If we set a masked score to $0$, $e^0 = 1$, which still assigns a positive probability mass to that token. By adding $-\infty$, we ensure that $e^{-\infty} = 0$, giving the masked position exactly $0\%$ probability after softmax and guaranteeing that future tokens cannot leak information to the past.

### Q2: What is the $k = S - L$ offset in causal masking, and what happens if you forget it during decode?
- **Answer**: The offset $k = S - L$ shifts the causal diagonal boundary of the mask. In the prefill phase, sequence lengths are equal ($L=S$), so $k=0$, yielding a standard lower-triangular mask. In the decode phase, we process one new query token ($L=1$) against all cached keys ($S=N$). The new token is the last token in the sequence, so it must attend to all keys ($0..N-1$). The offset shifts the triangle boundary right by $N-1$, making the mask row all zeros (fully allowed). If you forget the offset ($k=0$), the mask row becomes `[0, -inf, -inf, -inf]`, forcing the new token to attend **100%** to the first token ($s=0$) and ignore the rest of the sequence, corrupting outputs.

### Q3: What training issue does QK-Norm solve, and how does it work?
- **Answer**: As models grow deeper, query and key activations can grow in scale, making their dot products blow up (e.g., above $60$). This spreads the logits widely, saturating the softmax function, which drives gradients to zero and halts learning. QK-Norm applies an RMSNorm or LayerNorm to the $Q$ and $K$ states independently along the head dimension $D$ before computing the dot product. Because it pins the RMS of each head vector to $1.0$ (constraining the vector's $L_2$ norm to $\sqrt{D}$), the maximum dot product is mathematically bounded (reducing scores from $\approx \pm 60$ to $\approx \pm 1.6$), preventing softmax saturation and keeping training stable.

### Q4: Why must QK-Norm and RoPE be applied before the transpose to `[B, H, L, D]`?
- **Answer**: In attention projections, the sequence position axis is the second dimension ($L$). Both QK-Norm and RoPE are position-aware: RoPE rotates queries and keys based on their sequence index, and QK-Norm scales vectors per token position. Thus, they must be applied while the tensor is still in `[B, L, H, D]`. If you transpose to `[B, H, L, D]` first, the sequence dimension shifts to the third axis, meaning any naive position lookup or head-dimension reduction will index along the wrong axis, silently scrambling position embeddings and scaling factors.

---

## Pro-Tip: How to Impress the Interviewer

- **Coordinate RoPE and Causal Mask Offsets**: Point out that the causal mask offset $k = S - L$ and RoPE's position offset are mathematically linked. During decode, the new query has sequence position $M = S - 1$. Explain that both the causal mask offset ($k = S-1$) and the RoPE offset ($M$) represent the same physical property: the current logical position of the token in the sequence. 
- **QK-Norm as Cheap Insurance**: Highlight that QK-Norm is "cheap training insurance". It introduces a tiny parameter overhead ($2 \cdot H \cdot D$ params) and negligible FLOPs ($O(B \cdot L \cdot H \cdot D)$) but prevents catastrophic loss spikes in large models. Mention its adoption in production models like Qwen3, Gemma 2, and OLMo 2.
- **Triton FlashAttention Mask Optimization**: Mention that in highly optimized serving systems (like vLLM using FlashAttention), the causal mask is almost never instantiated as a physical tensor in HBM. Instead, the boundary checks $s \le l + (S - L)$ are compiled directly into the Triton GPU kernel's loop conditions, completely eliminating the $O(L \cdot S)$ memory allocation and bandwidth overhead.
- **Reference Gold Verification Values**: Cite exact values to show hands-on experience: for instance, with QK-Norm using weight=1, the L2 norm of the query vector is pinned exactly to $\sqrt{D}$ (e.g., $\sqrt{8} = \mathbf{2.8284}$), and the final token attention output row under prefill is `out[0,0,3,:] = [0.2429, 0.2788, 0.2336, 0.2446, 0, 0, 0, 0]`.
