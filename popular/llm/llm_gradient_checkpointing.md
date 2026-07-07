# Gradient Checkpointing (Activation Recomputation)

- **Category**: LLM Systems
- **Difficulty**: Hard
- **Target Role**: LLM Systems Engineer / ML Platform Engineer
- **Source**: GRADIENT_CHECKPOINTING.md + gradient_checkpointing_output.txt (Chen et al. 2016, Gruslys et al. 2016, Korthikanti et al. 2022)
- **Flashcards**: [LLM Systems deck](../flash_cards/llm/llm_systems.md)

---

## Concept Overview

Think of training a deep neural network like embarking on a long hike where you must carry snacks (intermediate activations) to eat on the way back (backward pass) to compute gradients. In vanilla backpropagation, you carry all $L$ snacks at once, which requires a heavy, linearly growing backpack. In full recomputation, you carry no snacks at all, but every time you need one, you have to hike all the way back to the trailhead (network input) to fetch it, resulting in a slow, quadratic $O(L^2)$ time penalty. Gradient checkpointing offers the optimal middle path: you carry a snack only at every $\sqrt{L}$-th layer, keeping only $\sqrt{L}$ checkpoints. On the way back, when you need a missing snack, you only detour at most $\sqrt{L}$ steps from the nearest checkpoint to recompute it. This drops activation memory from $O(L)$ to $O(\sqrt{L})$ at the cost of running a single extra forward pass (roughly $33\%$ compute overhead).

### The Problem It Solves

Training a modern LLM stores three primary pools of memory: model weights + optimizer states (which scale as $20N$ bytes per parameter for DDP), gradients, and intermediate activations.
The activation memory scales linearly with depth, batch size, sequence length, and hidden dimension:
$$\text{Activation Memory} = L \times B \times S \times D \times \text{dtype\_bytes}$$

At a standard LLaMA-3 8B configuration (depth $L = 32$, batch size $B = 32$, sequence length $S = 4096$, hidden dimension $D = 4096$), a single layer’s intermediate activation is:
$$1 \times 32 \times 4096 \times 4096 \times 2\text{ bytes (in fp16/bf16)} = 1073.74\text{ MB} \approx 1.07\text{ GB}$$
Across all $32$ layers, the total activation memory peaks at **$34.36\text{ GB}$**, which is more than double the memory needed to store the model weights themselves ($16\text{ GB}$ in FP16). As sequence lengths or batch sizes grow, activations quickly bottleneck the system and cause Out-of-Memory (OOM) errors.

### How It Works

Gradient checkpointing splits the $L$ layers of a network into $\approx \sqrt{L}$ segments of length $\approx \sqrt{L}$. 
1. **Forward Pass**: It computes the full forward pass, but saves (checkpoints) only the boundary inputs at every $\sqrt{L}$-th layer. All intermediate activations within the segments are immediately thrown away.
2. **Backward Pass**: When backpropagation enters a segment of length $\sqrt{L}$, it takes the saved segment boundary input, runs a local forward pass across the $\sqrt{L}$ layers in that segment to recompute the missing intermediate activations, and then performs the backward pass for that segment. Once the segment's gradients are computed, the recomputed activations are discarded.

```text
=== Vanilla Backpropagation ===
┌───────────┐     ┌───────────┐     ┌───────────┐     ┌───────────┐
│  Layer 0  │ ──► │  Layer 1  │ ──► │  Layer 2  │ ──► │  Layer 3  │
│  (Store)  │     │  (Store)  │     │  (Store)  │     │  (Store)  │
└───────────┘     └───────────┘     └───────────┘     └───────────┘

=== Gradient Checkpointing (√L = 2) ===
┌───────────┐     ┌───────────┐     ┌───────────┐     ┌───────────┐
│  Layer 0  │ ──► │  Layer 1  │ ──► │  Layer 2  │ ──► │  Layer 3  │
│[CHECKPT]  │     │ [Discard] │     │ [CHECKPT] │     │ [Discard] │
└───────────┘     └───────────┘     └───────────┘     └───────────┘
      │                 ▲                 │                 ▲
      └─ recompute ─────┘                 └─ recompute ─────┘
```

During training, this recomputation runs exactly one extra forward pass for each non-checkpointed layer, introducing a predictable $\sim 33\%$ compute overhead, because a typical training step already costs roughly 3 forward-pass equivalents (1 forward + 1 backward, where the backward pass costs $\approx 2\times$ the forward pass due to calculating gradients for both weights and activations). Adding 1 extra forward pass represents $\frac{1}{3} \approx 33.3\%$ overhead.

---

## Worked Example

### 1. Verification of Activation Memory Math
For a batch size $B = 32$, sequence length $S = 4096$, hidden dimension $D = 4096$, and dtype size of 2 bytes (FP16/BF16), the activation size of a single layer $A$ is:
$$A = 32 \times 4096 \times 4096 \times 2 = 1,073,741,824\text{ bytes} = 1.0737\text{ GB}$$
If we train a 32-layer model:
$$\text{Vanilla Activation Memory} = 32 \times 1.0737\text{ GB} = 34.36\text{ GB}$$

### 2. Comparison of the Three Strategies ($L = 32$)
From the verified execution statistics in `gradient_checkpointing_output.txt`:

| Strategy | Stored Activations | Memory Multiplier | Recomputed Layers | Total Compute Units (Fwd+Recompute+Bwd) | Compute vs. Vanilla |
|---|---|---|---|---|---|
| **Store-All (Vanilla)** | $32$ | $32\times$ ($34.36$ GB) | 0 | $32 + 0 + 64 = 96$ | $1.00\times$ |
| **Full Recompute** | $1$ (input only) | $1\times$ ($1.07$ GB) | $\frac{L(L+1)}{2} = 528$ | $32 + 528 + 64 = 624$ | $6.50\times$ |
| **Selective $\sqrt{L}$** | $\lceil\sqrt{32}\rceil = 6$ | **$6\times$ ($6.44$ GB)** | $32$ | $32 + 32 + 64 = 128$ | **$1.33\times$** ($+33.3\%$) |

The checkpoints for $L=32$ are located at indices: `[0, 6, 12, 19, 25, 31]`.

### 3. Scaling Checkpoints with Depth
The benefit of $\sqrt{L}$ scaling increases with model depth:

| Depth ($L$) | Store-All Memory ($L$) | Selective $\sqrt{L}$ Memory ($\lceil\sqrt{L}\rceil$) | Savings Factor |
|---|---|---|---|
| 4 | $4\times$ | $2\times$ | $2.0\times$ |
| 16 | $16\times$ | $4\times$ | $4.0\times$ |
| 32 | $32\times$ | $6\times$ | $5.3\times$ |
| 64 | $64\times$ | $8\times$ | $8.0\times$ |
| 128 | $128\times$ | $12\times$ | $10.7\times$ |
| 1000 | $1000\times$ | $32\times$ | $31.2\times$ |

### 4. Gradient Correctness Proof
Gradient checkpointing does not approximate gradients. As verified in `gradient_checkpointing_output.txt` on a real 4-layer MLP network (with layers 1-2 checkpointed, `use_reentrant=False`):
- `forward output match? max|h_ref - h_ckp| = 0.00e+00`
- `loss match? |loss_ref - loss_ckp| = 0.00e+00`
- `input-grad match? max|dx_ref - dx_ckp| = 0.00e+00`

---

## Complexity & Trade-offs

| Metric | Value | Notes |
|---|---|---|
| **Activation Memory** | $O(\sqrt{L})$ | Reduces activation footprint from $O(L)$ to $O(\sqrt{L})$. For $L = 1000$, drops from $1000\times$ to $32\times$. |
| **Compute Overhead** | $+33.3\%$ | Requires exactly one extra forward pass per step. |
| **Gradient Accuracy** | Bit-identical ($0.00\text{ difference}$) | The backward pass operates on recomputed activations that match the original forward outputs exactly. |
| **Optimizer Memory** | Unaffected | Checkpointing only reduces activation memory. Model parameters and optimizer states remain sharded by DDP/ZeRO. |
| **RNG State Tracking** | Requires re-saving seeds | Operations like dropout rely on random states. PyTorch's checkpoint API saves and restores RNG states during recomputation to preserve determinism. |

---

## Common Interview Questions & How to Answer

### Q1: Why is the compute overhead of gradient checkpointing $\approx 33\%$ and not $100\%$, even though we run the forward pass twice?
- **Answer**: 
  A standard training iteration consists of one forward pass and one backward pass. Calculating the gradients during the backward pass requires twice the amount of floating-point operations (FLOPs) of a forward pass (since we compute gradients with respect to both the weights and the inputs of each layer). Therefore:
  $$\text{Vanilla Iteration Cost} = 1 \text{ Fwd} + 1 \text{ Bwd} \approx 3 \text{ Fwd Units}$$
  When gradient checkpointing is enabled, we run the initial forward pass ($1 \text{ Fwd}$), discard intermediate activations, and then during the backward pass we recompute the forward pass layer-by-layer ($1 \text{ Fwd}$) in segments before executing the backward step ($1 \text{ Bwd}$):
  $$\text{Checkpointed Iteration Cost} = 1 \text{ Fwd} + 1 \text{ Recompute Fwd} + 1 \text{ Bwd} \approx 4 \text{ Fwd Units}$$
  The additional cost is $\frac{4 - 3}{3} = \frac{1}{3} \approx 33.3\%$.

### Q2: What is the difference between PyTorch's `use_reentrant=True` and `use_reentrant=False` in the checkpoint API? Why does this matter for DDP/FSDP?
- **Answer**: 
  - **Reentrant Checkpointing (`use_reentrant=True`)**: This is the legacy implementation. It runs the forward pass under a `no_grad` block and manually constructs a nested autograd graph using custom `Function` blocks. It does not support standard autograd hooks properly and fails when mixing checkpointed blocks with DDP/FSDP (causing incorrect gradient sync hooks, hanging, or crashes during backward passes).
  - **Non-reentrant Checkpointing (`use_reentrant=False`)**: This is the modern implementation (introduced in PyTorch 2.0). It uses PyTorch’s standard autograd engine to trace the backward pass, utilizing hook mechanisms. It fully supports double backward passes, works seamlessly with DDP/FSDP gradient synchronization hooks, and handles modules with unused inputs. It is the recommended setting and must be passed explicitly.

### Q3: Explain Megatron-LM's "selective activation recomputation" and how it differs from Chen et al.'s standard $\sqrt{L}$ checkpointing.
- **Answer**: 
  - Standard $\sqrt{L}$ checkpointing (Chen et al. 2016) checkpoints the boundary inputs of every $\sqrt{L}$-th *entire layer* (attention + MLP blocks) and recomputes the entire layer's forward pass.
  - Megatron-LM's selective activation recomputation (Korthikanti et al. 2022) focuses on checkpointing only the parts of a layer that consume massive memory but are cheap to compute. Specifically, the attention head activations (e.g., attention scores $S = \text{Softmax}(\frac{QK^T}{\sqrt{d_k}})$ of shape $[B, H, S, S]$) and dropout masks are highly memory-intensive but computationally cheap. By checkpointing only these specific intermediates and storing the rest of the layer normally, it recovers most of the memory savings with significantly lower compute overhead (often $< 10\%$).

---

## Pro-Tip: How to Impress the Interviewer

- **Address the RNG state preservation problem under checkpointing.** Explain that since operations like Dropout or stochastic depth rely on random number generators (RNG), simply re-running the forward pass during backward would yield different random masks, resulting in incorrect gradients. Explain that `torch.utils.checkpoint` handles this by caching the current GPU RNG state (`torch.cuda.get_rng_state()`) at the checkpoint boundaries during the forward pass and restoring it before running the recomputation, ensuring mathematical determinism and gradient correctness.
