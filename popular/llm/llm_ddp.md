# Distributed Data Parallel (DDP)

- **Category**: LLM Systems
- **Difficulty**: Hard
- **Target Role**: LLM Systems Engineer / ML Platform Engineer
- **Source**: DDP.md + ddp_output.txt (Goyal et al. 2017, Micikevicius et al. 2017)
- **Flashcards**: [LLM Systems deck](../flash_cards/llm/llm_systems.md)

---

## Concept Overview

Think of Distributed Data Parallel (DDP) like a chorus line of identical dancers. Each dancer watches a different part of the stage (a different slice of the mini-batch) and makes moves. After every step, the dancers whisper their corrections to everyone else and compute the average adjustment (AllReduce). Because they start with identical moves and always apply the exact same averaged adjustment, they can never drift out of sync, no matter how long the show runs. In system terms, DDP replicates the entire model and optimizer states on every GPU. Each GPU executes a forward and backward pass on its local data slice to compute local gradients. An AllReduce operation then averages these gradients across all ranks, ensuring that all GPUs take the exact same gradient step and their parameters remain bit-identical forever.

### The Problem It Solves

A single GPU hits hard limits in throughput and memory capacity. Modern training requires large effective batch sizes to stabilize optimization. DDP implements data-parallel execution to scale training throughput linearly with the number of GPUs. 

However, replicas will drift if gradients differ. If we do not synchronize, rank-specific data batches ($X_0 \neq X_1$) will generate differing local gradients ($g_0 \neq g_1$). Taking independent SGD steps would cause the parameter sets to diverge immediately. Additionally, training consumes massive memory: the model and optimizer states require a redundant **$20\text{ bytes per parameter}$** on every GPU (including master weights and Adam states in mixed-precision training). DDP manages this redundancy by ensuring perfect synchronization of gradients across the communication fabric.

### How It Works

1. **Initialization**: The weights are initialized on a coordinator GPU (Rank 0) and broadcast to all other GPUs, guaranteeing identical starting parameters. Ranks set unique seed offsets based on their rank (e.g., `seed = 1337 + rank`) to ensure they load non-overlapping mini-batches.
2. **Forward and Backward Passes**: Each GPU runs the forward pass on its local batch $X_k$ and executes the backward pass to compute a local gradient $g_k$.
3. **Autograd Hook Synchronization**: PyTorch DDP installs backward hooks on all parameters. As soon as the autograd engine finishes computing the gradient for a parameter, the hook triggers an immediate `AllReduce-average` operation. This overlaps communication time with the computation of remaining gradients in the backward pass.
4. **Optimizer Step**: Once backward finishes and all gradients are averaged across all ranks, every GPU performs the identical optimizer update:
   $$W \leftarrow W - \eta \cdot g_{\text{averaged}}$$
   Because the starting weights $W$ and the gradients $g_{\text{averaged}}$ are identical, the updated weights remain bit-identical on all nodes.

```mermaid
graph TD
    subgraph Rank 0 (GPU 0)
        X0["Batch X0"] --> Fwd0["Forward Pass"]
        Fwd0 --> Bwd0["Backward Pass"]
        Bwd0 --> G0["Local Gradient g0"]
    end
    subgraph Rank 1 (GPU 1)
        X1["Batch X1"] --> Fwd1["Forward Pass"]
        Fwd1 --> Bwd1["Backward Pass"]
        Bwd1 --> G1["Local Gradient g1"]
    end
    
    G0 --> AR["AllReduce (Average)"]
    G1 --> AR
    
    AR -->|Identical Avg Grad| Step0["SGD Step (W_new)"]
    AR -->|Identical Avg Grad| Step1["SGD Step (W_new)"]
```

---

## Worked Example

### 1. Simulated 2-Rank Step
We simulate $K = 2$ ranks with a single linear layer $y = xW$ (W shape $[4, 3]$ = 12 parameters) and MSE loss.
Ranks start with identical initialized weights $W$:
```
W = [+0.154100, -0.029343, -0.217879, +0.056843, -0.108452, -0.139860, 
     +0.040335, +0.083803, -0.071926, -0.040334, -0.059664, +0.018204]
```
Ranks process different batch rows (e.g., $X_0 \neq X_1$):
- $X_0[0, :] = [+0.336690, +0.128809, +0.234462, +0.230333]$
- $X_1[0, :] = [-0.988960, +0.957972, +1.322135, +0.817190]$

Local gradients computed in backward:
- $g_0[0, :] = [+0.283542, +0.280142, -0.741705]$
- $g_1[0, :] = [-0.033977, +0.354733, -0.016214]$
*(These differ because the training inputs differ).*

AllReduce computes the average gradient across both ranks:
- $g_{\text{avg}} = (g_0 + g_1)/2$:
  ```
  avg[0, :] = [+0.124783, +0.317437, -0.378959]
  ```
- Both ranks end up with this exact average gradient. (Gold `avg_grad[0,0] = +0.124783`, `avg_grad[1,2] = -0.167272`).

Taking an SGD step with learning rate $\eta = 0.1$:
- $W_{\text{new}} = W - \eta \cdot g_{\text{avg}}$:
  ```
  W_new[0, :] = [+0.154100, -0.029343, -0.217879] - 0.1 * [+0.124783, +0.317437, -0.378959]
              = [+0.141621, -0.061087, -0.179983]
  ```
- Weights are bit-identical on both ranks (Gold `W_after_step[0,0] = +0.141621`, `W_after_step[1,2] = -0.123132`).
- A single GPU running on the concatenated batch $X = [X_0; X_1]$ produces the exact same gradient (`max|diff| = 5.96e-08`), proving that DDP on $K$ GPUs is mathematically identical to single-GPU training with a $K\times$ larger batch.

### 2. Gradient Accumulation
Gradient accumulation runs multiple micro-batches sequentially on each GPU before updating weights. In a 2-GPU setup ($K = 2$) with batch size $B=2$ and gradient accumulation steps $\text{accum} = 2$:
- Effective Batch Size = $B \times \text{accum} \times K = 2 \times 2 \times 2 = 8\text{ samples}$
- To avoid redundant communications, we disable AllReduce on early micro-steps using PyTorch's `require_backward_grad_sync = False`. 
- On the last micro-step, we enable synchronization (`require_backward_grad_sync = True`).
- Micro-losses are scaled down: $\text{Loss}_{\text{micro}} = \text{Loss} / \text{accum}$.
- The accumulated and synced gradient matches the single-GPU gradient on all 8 samples exactly:
  $$g_{\text{accum}} = [+0.399230, -0.563779, -0.283541, \dots]$$

### 3. Mixed Precision & Underflow
In FP16 mixed precision training, small gradients underflow to zero due to FP16's narrow range $[6 \cdot 10^{-5}, 65504]$.
- Underflow example: $10^{-8}$ rounds to `0.0` in FP16, whereas it survives in BF16 (which matches FP32's exponent range).
- **GradScaler Solution**:
  1. Multiply the loss by a scaling factor $S = 2^{16} = 65536$:
     $$\text{scaled\_grad} = 10^{-8} \times 65536 = 0.00065536\text{ (survives in FP16)}$$
  2. Perform backward pass to propagate scaled gradients in FP16.
  3. Divide gradients by $S$ (unscale) back to FP32 before the optimizer step:
     $$\text{unscaled\_grad} = 0.00065536 / 65536 \approx 9.997 \cdot 10^{-9}\text{ (recovered!)}$$

### 4. Memory Bill (Mixed Precision + Adam)
Under mixed precision training, the memory overhead per parameter is **$20\text{ bytes}$**:

| Component | Bytes / Parameter | Rationale |
|---|---|---|
| FP16 parameters | 2 | Weights used in forward pass computation |
| FP16 gradients | 2 | Computed during backward pass |
| FP32 master parameters | 4 | High-precision copy updated by optimizer |
| FP32 gradients | 4 | Upcast gradients for optimizer calculations |
| FP32 Adam momentum | 4 | First moment running average |
| FP32 Adam variance | 4 | Second moment running average |
| **Total per param** | **20** | Redundantly replicated on every GPU |

For LLaMA-3 8B, DDP requires **$160\text{ GB}$** of memory per GPU just for the parameters, gradients, and optimizer states, which is why ZeRO sharding is necessary at scale.

### 5. Cosine LR Schedule with Warmup
To train stable large batches (Goyal et al. 2017), the learning rate is scaled linearly with batch size, warmed up from 0 to peak over the first $W$ steps, and then decayed to $\text{min\_lr}$ using a cosine function over $T$ steps.
With Peak LR = 1.0, min_lr = 0.1, warmup = 10 steps, decay = 50 steps:
- Iter 0: $0.0909$ (Warmup)
- Iter 6: $0.6364$ (Warmup)
- Iter 10: $1.0000$ (Peak)
- Iter 25: $0.7222$ (Cosine Decay)
- Iter 50: $0.1000$ (min_lr)
- Iter 55: $0.1000$ (Hold)

---

## Complexity & Trade-offs

| Metric | Value / Cost | Notes |
|---|---|---|
| **Memory Footprint** | $20N\text{ bytes per param}$ | Redundant replication of all weights, gradients, and optimizer states on every node. |
| **Communication Volume** | $2 \frac{K-1}{K} N \approx 2N\text{ bytes per step}$ | Independent of $K$ when using Ring-AllReduce. |
| **Communication Overlap** | High | Gradients are synced layer-by-layer during backward, hiding communication behind computation. |
| **Mathematical Equivalence** | $1.00\text{ (Exact)}$ | DDP on $K$ nodes is mathematically identical to training on a single GPU with batch size $K \times B$. |
| **Scaling Efficiency** | High | Scales linearly with GPU count, assuming communication is hidden by compute. |

---

## Common Interview Questions & How to Answer

### Q1: Why must the loss function be a batch mean (not a sum) for DDP's AllReduce gradient averaging to be mathematically equivalent to single-GPU training?
- **Answer**: 
  The single-GPU training loss on a concatenated batch $X = [X_0; X_1]$ is defined as the mean over all samples in the combined batch:
  $$\mathcal{L}(X) = \frac{1}{2B} \sum_{i=1}^{2B} \ell_i = \frac{1}{2} \left[ \frac{1}{B} \sum_{i=1}^{B} \ell_i + \frac{1}{B} \sum_{i=B+1}^{2B} \ell_i \right] = \frac{\mathcal{L}(X_0) + \mathcal{L}(X_1)}{2}$$
  Taking the gradient of the loss with respect to parameters $W$:
  $$\nabla_W \mathcal{L}(X) = \frac{\nabla_W \mathcal{L}(X_0) + \nabla_W \mathcal{L}(X_1)}{2}$$
  Because the combined loss is the average of the individual losses, the combined gradient is the **average** of the individual local gradients ($g_0$ and $g_1$). 
  Thus, running an `AllReduce-average` on local gradients perfectly reconstructs the global gradient. If we used a sum loss, the combined gradient would be the sum of local gradients ($\nabla_W \mathcal{L}_{\text{sum}} = g_0 + g_1$), and AllReduce-averaging would make the gradients $2\times$ too small.

### Q2: How does DDP overlap communication with computation, and why is this critical for scaling?
- **Answer**: 
  DDP does not wait for the backward pass to finish entirely before communicating gradients. PyTorch DDP registers an autograd hook on each parameter. 
  - During the backward pass, gradients are computed in reverse order (from the output layer back to the input layer). 
  - As soon as the gradient for a parameter is calculated, its autograd hook triggers. 
  - DDP organizes parameters into "buckets" (typically $25\text{ MB}$ in size). When all parameters in a bucket have finished computing their gradients, DDP initiates an asynchronous `AllReduce` for that bucket.
  - This allows the GPU to communicate gradient buckets for the late layers over the network (using NCCL) while simultaneously calculating gradients for the early layers. This overlap hides communication latency behind backward pass computation.

### Q3: Why is loss scaling necessary for FP16 training, but not for BF16 training?
- **Answer**: 
  - **FP16 (Half Precision)** allocating 5 bits for the exponent and 10 bits for the mantissa. Its minimum positive representable value (underflow limit) is $\approx 6 \cdot 10^{-5}$ (or $6 \cdot 10^{-8}$ for subnormals). Since gradients in deep networks are often smaller than $10^{-5}$, they underflow to `0.0` in FP16, halting training. A `GradScaler` scales the loss up by $2^{16}$ to shift the gradient values into the representable range of FP16, and divides them back to FP32 before updating.
  - **BF16 (Brain Float 16)** allocates 8 bits for the exponent (matching FP32) and 7 bits for the mantissa. Its minimum positive representable value is $\approx 1.2 \cdot 10^{-38}$. This massive range ensures that gradients never underflow in BF16, rendering loss scaling unnecessary.

---

## Pro-Tip: How to Impress the Interviewer

- **Discuss the DDP "Bucket Tuning" strategy.** Mention that DDP's default bucket size ($25\text{ MB}$) is tuned for standard workloads, but can bottleneck training. For small models or slow fabrics, larger buckets reduce the number of small NCCL calls, saturating bandwidth. For giant models, smaller buckets allow synchronization to start earlier in the backward pass, maximizing the overlap between communication and computation. Explain that bucket sizes can be tuned in PyTorch via the `bucket_cap_mb` parameter in the `DistributedDataParallel` constructor.
