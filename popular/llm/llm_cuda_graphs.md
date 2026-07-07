# CUDA Graphs for LLM Decode Acceleration

- **Category**: LLM Systems
- **Difficulty**: Expert
- **Target Role**: LLM Inference Engineer / LLM Serving Engineer
- **Source**: NVIDIA CUDA Programming Guide / vLLM paper

---

## Concept Overview

LLM autoregressive generation (the decode phase) is memory-bandwidth bound. Every step, the GPU runs the **same** sequence of kernels (RMSNorm, projections, attention, MLP) at the **same** shapes, reading and writing to the KV cache one token at a time. In eager PyTorch, every kernel is launched from the Python interpreter on the host CPU one by one. Each launch costs $\sim 5\text{--}14\ \mu\text{s}$ of CPU-to-GPU driver overhead.

A **CUDA Graph** addresses this overhead by capturing the entire kernel sequence once as a static Directed Acyclic Graph (DAG). Instead of launching 70+ kernels individually, the engine replays the entire sequence with a **single** host call, collapsing host launch latency and maximizing GPU occupancy.

### The Problem It Solves

During the decode step, a typical LLM executes $\sim 50\text{--}100$ individual GPU kernels. At an average of $10\ \mu\text{s}$ of launch overhead per kernel, this creates **$720\ \mu\text{s}$ of pure CPU host-side overhead** per step. 

For small models or small batch sizes, this host latency accounts for **over 50% of the entire decode step time**. CUDA Graphs eliminate this overhead by packaging all kernels into a single unit, reducing launch tax to a single graph launch of $\sim 5\ \mu\text{s}$.

### How It Works

1. **Warmup Run**: The engine runs the model once with dummy data. This primes PyTorch's lazy allocator pools, cuBLAS handles, and cuDNN algorithm selections.
2. **Graph Capture**: The engine runs the model inside a capture context manager (`torch.cuda.graph(g)`). During this run, kernels are appended to the graph DAG rather than executed on the GPU.
3. **Graph Storage**: Graphs are captured for a discrete set of batch sizes (e.g., `graph_bs = [1, 2, 4, 8, 16, 32]`).
4. **Replay**: At runtime, the engine rounds the active batch size up to the nearest captured bucket, writes input data in-place to pre-allocated tensors, and invokes `graph.replay()`.
5. **Sentinel Padding**: Unused slots in the rounded batch size are padded with a `-1` sentinel. The attention kernel reads this sentinel and skips VRAM writes for those slots, preventing memory corruption.

```mermaid
graph TD
    subgraph Eager Mode (72 Launches)
        CPU1["CPU: Launch Kernel 1"] -->|10us tax| GPU1["GPU: Execute RMSNorm"]
        CPU2["CPU: Launch Kernel 2"] -->|10us tax| GPU2["GPU: Execute QKV Proj"]
        CPU3["CPU: Launch Kernel 3"] -->|10us tax| GPU3["GPU: Execute Attention"]
        CPU4["CPU: Launch Kernel 72"] -->|10us tax| GPU4["GPU: Execute Softmax"]
    end

    subgraph CUDA Graph Mode (1 Launch)
        CPUG["CPU: graph.replay()"] -->|5us tax| GPUG["GPU: Run Frozen DAG (72 kernels)"]
    end

    style CPU1 fill:#fdecea,stroke:#c0392b
    style CPU2 fill:#fdecea,stroke:#c0392b
    style CPU4 fill:#fdecea,stroke:#c0392b
    style CPUG fill:#eafaf1,stroke:#27ae60,stroke-width:2px
```

---

## Worked Example

This example uses verified numbers from the simulation code for a model with 24 layers and 3 kernels per layer ($N_{\text{kernels}} = 72$).

### 1. Eager vs. Graphed Latency (Batch = 1)
* **Kernel Launch Overhead**: $10\ \mu\text{s}$ per kernel.
* **Kernel Compute Time**: $8\ \mu\text{s}$ per kernel.
* **Graphed Launch Overhead**: $5\ \mu\text{s}$ total.

$$\text{Eager Step Total} = (72 \times 10\ \mu\text{s}) + (72 \times 8\ \mu\text{s}) = 720\ \mu\text{s} + 576\ \mu\text{s} = 1296\ \mu\text{s}$$
$$\text{Graphed Step Total} = 5\ \mu\text{s} + 576\ \mu\text{s} = 581\ \mu\text{s}$$

* **Launch-Overhead Speedup**: $\frac{720\ \mu\text{s}}{5\ \mu\text{s}} = \mathbf{144\times}$
* **Total Step Speedup**: $\frac{1296\ \mu\text{s}}{5\ \mu\text{s} + 576\ \mu\text{s}} = \mathbf{2.23\times}$

### 2. Batch-Size Scaling
Because launch overhead is fixed while compute scales linearly with batch size, CUDA Graphs help most at small batch sizes:

| Batch Size | Compute Time ($\mu\text{s}$) | Eager Launch Tax ($\mu\text{s}$) | Launch Fraction (Eager) | Total Speedup |
|---|---|---|---|---|
| **1** | 576 | 720 | 55.6% | **2.231×** |
| **2** | 1152 | 720 | 38.5% | 1.618× |
| **4** | 2304 | 720 | 23.8% | 1.310× |
| **8** | 4608 | 720 | 13.5% | 1.155× |
| **16** | 9216 | 720 | 7.2% | 1.078× |
| **32** | 18432 | 720 | 3.8% | 1.039× |
| **64** | 36864 | 720 | 1.9% | 1.019× |

*At batch size 64, compute dominates, making the launch tax negligible ($1.9\%$).*

### 3. Replay and Padding Sentinels
Active batch size is $3$. The engine selects the smallest captured graph size $\ge 3$, which is **$4$**.
The graph runs with 4 slots, meaning slot 3 is padding. To prevent writing garbage data into VRAM, the engine pads inputs and uses a sentinel:
* **Real KV Cache Slot Mapping**: `[4, 17, 9]`
* **Graph Slot Mapping Input**: `[4, 17, 9, -1]`

**GPU Kernel Execution Behavior**:

| Slot Index | `slot_mapping` value | Target Token | GPU Attention Kernel Action |
|---|---|---|---|
| 0 | 4 | Token 0 | Write KV to Physical Slot 4 |
| 1 | 17 | Token 1 | Write KV to Physical Slot 17 |
| 2 | 9 | Token 2 | Write KV to Physical Slot 9 |
| **3** | **-1** | Padding | **SKIP (sentinel detected)** |

> [!CAUTION]
> If slot 3 was not padded with the `-1` sentinel, the GPU would write garbage KV data to a random memory address, silently corrupting the cache of other active requests.

---

## Complexity & Trade-offs

| Metric | Eager | Graphed | Notes |
|---|---|---|---|
| **Launch Latency** | $\mathcal{O}(N_{\text{kernels}})$ | $\mathcal{O}(1)$ | Collapses $N \times 10\ \mu\text{s}$ down to a single $\sim 5\ \mu\text{s}$ call. |
| **VRAM Footprint** | Dynamic | Static + Pre-allocated | Input, output, and intermediate activation tensors must be pre-allocated for every graph batch size. |
| **Warmup Cost** | 0 | High (seconds) | Compiles kernels and instantiates memory pools during engine initialization. |
| **Control Flow** | Dynamic | Static (no CPU branching) | No CPU-side conditional branching is allowed inside the graph. |

---

## Common Interview Questions & How to Answer

### Q1: Why are CUDA Graphs used for the decode phase of LLM serving but not the prefill phase?
- **Answer**: CUDA Graphs require strictly fixed tensor shapes, sizes, and memory strides because memory offsets are frozen during capture. In the prefill phase, prompt lengths vary across requests (e.g., one request has 10 tokens, another has 500). This causes dynamic tensor shapes, preventing graph capture. In contrast, the decode phase processes exactly 1 token per sequence per step. The tensor shapes depend only on the batch size, which is bounded and predictable. We can pre-capture graphs for common batch sizes (T-shirt sizing) and run the decode loop using CUDA Graphs.

### Q2: Explain the requirement of a "warmup run" before capturing a CUDA Graph and what happens if you skip it.
- **Answer**: PyTorch, cuBLAS, and cuDNN use lazy initialization: they allocate internal workspace pools, choose algorithms, and JIT-compile PTX kernels on their first execution. If we capture a graph without a warmup run, these initialization operations are recorded inside the graph. On replay, the graph will crash or run into invalid pointer states because these host-side setups cannot be repeated in a device-side replay. A warmup run executes the model once with dummy data to force initialization before capture begins.

---

## Pro-Tip: How to Impress the Interviewer

- **In-place Copy Contract**: Explain that because the input tensor addresses are frozen during graph capture, you cannot swap input tensor objects at runtime (e.g., `x = fresh_tensor`). Instead, you must copy data **in-place** to pre-allocated tensors mapped to the graph (e.g., `graph_input.copy_(runtime_input)`).
- **Scale Impact in Large Models**: Acknowledge that while CUDA Graphs achieve $144\times$ launch speedups, the total decode step speedup for production models (like Llama-3-70B) is closer to $10\text{--}20\%$ because weight-reading compute dominates. However, this is a critical win for interactive latency and TTFT.
