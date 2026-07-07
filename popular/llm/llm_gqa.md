# Grouped-Query Attention (GQA)

- **Category**: LLM Systems
- **Difficulty**: Hard
- **Target Role**: LLM Inference Engineer / ML Systems Engineer
- **Source**: GQA (Ainslie et al. 2023) + MQA (Shazeer 2019)

---

## Concept Overview

Imagine a corporate office with 14 researchers (**Query heads**) who need to compile a report. In **Multi-Head Attention (MHA)**, each researcher has their own personal filing assistant (**KV head**) managing a separate filing cabinet of past data. This offers maximum accuracy, but maintaining 14 cabinets wastes a massive amount of office space and makes retrieval slow. In **Multi-Query Attention (MQA)**, the office downsizes to just 1 filing cabinet shared by all 14 researchers. This saves massive space, but because everyone is queuing up for the same cabinet, the researchers' notes get cluttered and quality drops. **Grouped-Query Attention (GQA)** is the sweet spot: the researchers are divided into groups (e.g., 2 groups of 7 researchers), and each group shares 1 filing cabinet (2 cabinets total). This recovers almost all the accuracy of having individual cabinets while running nearly as fast as the single-cabinet setup.

```mermaid
graph TD
    subgraph MHA["1. Multi-Head Attention (MHA)"]
        Q0_MHA["Q0"] ---> KV0_MHA["KV0"]
        Q1_MHA["Q1"] ---> KV1_MHA["KV1"]
        Q2_MHA["Q2"] ---> KV2_MHA["KV2"]
        Q3_MHA["Q3"] ---> KV3_MHA["KV3"]
    end

    subgraph GQA["2. Grouped-Query Attention (GQA) - 2 Groups"]
        Q0_GQA["Q0"] ---\ Group 0 /---> KV0_GQA["KV0"]
        Q1_GQA["Q1"] ---/             \
        Q2_GQA["Q2"] ---\ Group 1 /---> KV1_GQA["KV1"]
        Q3_GQA["Q3"] ---/             /
    end

    subgraph MQA["3. Multi-Query Attention (MQA)"]
        Q0_MQA["Q0"] ---\             
        Q1_MQA["Q1"] ----\ All Share /---> KV0_MQA["KV0"]
        Q2_MQA["Q2"] ----/           \
        Q3_MQA["Q3"] ---/             
    end

    style MHA fill:#eaf2f8,stroke:#2980b9
    style GQA fill:#eafaf1,stroke:#27ae60,stroke-width:2px
    style MQA fill:#fdecea,stroke:#c0392b
```

### The Problem It Solves

- **The KV Cache Bottleneck**: During the autoregressive generation (decode) phase of LLM serving, the model produces text one token at a time. To generate each new token, the GPU must reload the key-value matrices (the **KV Cache**) of *all previous tokens* from High-Bandwidth Memory (HBM) into SRAM.
- **Memory Bandwidth Bottleneck**: In MHA, the KV cache size is proportional to the number of query heads $H_q$. The memory bandwidth required per layer at sequence length $S$ with head dimension $D$ is:
  $$\text{KV Cache Elements} = 2 \times H_{kv} \times S \times D \quad (\text{where } H_{kv} = H_q)$$
  For long context lengths (e.g., $S = 4096$), fetching this cache for every decode step saturates the memory bus, slowing down generation speed (rendering the chip bandwidth-bound).
- **Quality-Memory Trade-off**: MQA ($H_{kv} = 1$) reduces this cache footprint by $H_q \times$, but causes accuracy degradation. GQA groups query heads to share KV heads, cutting the KV cache size by a factor of $H_q / H_{kv}$ while matching the performance of MHA.

### How It Works

GQA interpolates between MHA and MQA by grouping $H_q$ query heads into $H_{kv}$ groups. Each group contains $n_{\text{repeats}} = H_q / H_{kv}$ query heads that share a single KV head.

To implement this efficiently in hardware *without* physically duplicating the key and value vectors in memory (which would erase the memory savings), we use the **broadcast reshape trick**:

1. **Expose Group Structure**: Reshape the query tensor $q$ of shape $[B, H_q, L, D]$ into $q_g$ of shape $[B, H_{kv}, n_{\text{repeats}}, L, D]$.
2. **Inject Singleton Dimension**: Reshape key $k$ and value $v$ tensors of shape $[B, H_{kv}, S, D]$ into shape $[B, H_{kv}, 1, S, D]$.
3. **Implicit Broadcasting**: Perform attention score calculation. The $1$ in the key tensor's shape is implicitly broadcast across the $n_{\text{repeats}}$ dimension of the query tensor during matrix multiplication:
   $$\text{scores} = \frac{q_g k_g^T}{\sqrt{D}} \quad \text{of shape} \quad [B, H_{\text{kv}}, n_{\text{repeats}}, L, S]$$
4. **Aggregate Output**: Compute softmax over the sequence length axis $S$ and multiply by the value tensor $v_g$ (which also broadcasts over $n_{\text{repeats}}$), producing an output shape of $[B, H_{kv}, n_{\text{repeats}}, L, D]$.
5. **Flatten Back**: Reshape the output back to $[B, H_q, L, D]$.

---

## Worked Example

Consider a model with batch size $B=1$, query heads $H_q = 4$, KV heads $H_{kv} = 2$, sequence length $L=S=4$, head dimension $D=8$, and $n_{\text{repeats}} = 2$.

### KV Cache Memory Footprint Comparison
Let's look at the memory savings for a real-world scale model based on the Qwen2.5-0.5B config ($H_q = 14$, $H_{kv} = 2$, $D=64$, 28 layers) at context length $S = 4096$ using FP16 (2 bytes per element):

| Config | $H_{kv}$ | Elements per Layer ($2 \cdot H_{kv} \cdot S \cdot D$) | Bytes per Layer (FP16) | Total Cache (28 Layers) | Cache Savings vs MHA |
|---|---|---|---|---|---|
| **MHA** | $14$ | $7,340,032$ | $14.00\text{ MiB}$ | $392.00\text{ MiB}$ | $1.0\times$ (Baseline) |
| **GQA** | **$2$** | **$1,048,576$** | **$2.00\text{ MiB}$** | **$56.00\text{ MiB}$** | **$7.0\times$ smaller** |
| **MQA** | $1$ | $524,288$ | $1.00\text{ MiB}$ | $28.00\text{ MiB}$ | $14.0\times$ smaller |

### Exposing the Reshape Broadcast Shapes
During the forward pass of GQA, the tensors are reshaped as follows:
- **Input Query $q$**: $[1, 4, 4, 8]$ $\rightarrow$ **Reshaped $q_g$**: $[1, 2, 2, 4, 8]$ (where the dimensions represent $[B, H_{kv}, n_{\text{repeats}}, L, D]$)
- **Input Key $k$**: $[1, 2, 4, 8]$ $\rightarrow$ **Reshaped $k_g$**: $[1, 2, 1, 4, 8]$ (where the dimensions represent $[B, H_{kv}, 1, S, D]$)
- **Input Value $v$**: $[1, 2, 4, 8]$ $\rightarrow$ **Reshaped $v_g$**: $[1, 2, 1, 4, 8]$

During $\text{scores} = q_g k_g^T$, the $n_{\text{repeats}}=2$ queries in group 0 both multiply the *same* KV head 0, while the queries in group 1 multiply KV head 1.

### Verified Golden Output (Group 0, Head 0)
The exact attention output for the first query head ($h=0$) across all sequence positions is:

| Position | $d=0$ | $d=1$ | $d=2$ | $d=3$ | $d=4$ | $d=5$ | $d=6$ | $d=7$ |
|---|---|---|---|---|---|---|---|---|
| **Pos 0** | $+0.1477$ | $+0.1235$ | $+0.1470$ | $+0.2909$ | $-0.0165$ | $+0.1233$ | $-0.1583$ | $-0.0593$ |
| **Pos 1** | $+0.1701$ | $+0.1540$ | $+0.1353$ | $+0.2926$ | $-0.0287$ | $+0.1402$ | $-0.1822$ | $-0.0644$ |
| **Pos 2** | $+0.1984$ | $+0.0860$ | $+0.1432$ | $+0.3035$ | $-0.0228$ | $+0.0652$ | $-0.1475$ | $-0.1401$ |
| **Pos 3** | $+0.1580$ | $+0.1518$ | $+0.1443$ | $+0.2910$ | $-0.0318$ | $+0.1529$ | $-0.1785$ | $-0.0530$ |

- **Golden Scalar**: $\text{out}[h=0, pos=0, d=0] = \mathbf{+0.147747}$

### The Reshape Order Pitfall (The #1 GQA Implementation Bug)
Since query heads are contiguous in memory, they are grouped as $[Q_0, Q_1 \mid Q_2, Q_3]$.
- **Correct Reshape**: `[H_kv, n_repeats]` $\rightarrow$ row-major partition splits contiguous blocks: $[[Q_0, Q_1], [Q_2, Q_3]]$. Heads $Q_0, Q_1$ pair with $KV_0$ (Correct).
- **Wrong Reshape**: `[n_repeats, H_kv]` $\rightarrow$ row-major partition splits into striped blocks: $[[Q_0, Q_2], [Q_1, Q_3]]$. This maps $Q_1$ to $KV_1$ and $Q_2$ to $KV_0$.

Because the shapes still align ($2 \times 2$ in both cases), **no code crash occurs**. However, the output is silently corrupted:

| Variant | Value of $\text{out}[h=1, pos=0, d=0]$ | Result |
|---|---|---|
| **Correct Reshape** (`H_kv, n_repeats`) | $\mathbf{+0.1724}$ (Pairs $Q_1 \rightarrow KV_0$) | **Correct** |
| **Wrong Reshape** (`n_repeats, H_kv`) | $\mathbf{-0.2905}$ (Pairs $Q_1 \rightarrow KV_1$) | **Scrambled (Error = 0.6535)** |

---

## Complexity & Trade-offs

| Metric | Multi-Head Attention (MHA) | Grouped-Query Attention (GQA) | Multi-Query Attention (MQA) |
|---|---|---|---|
| **KV Cache Bytes** | $\mathcal{O}(H_q \cdot S \cdot D)$ | $\mathcal{O}(H_{kv} \cdot S \cdot D)$ | $\mathcal{O}(1 \cdot S \cdot D)$ |
| **HBM Read Bandwidth** | High (Slowest Decode) | **Low (Fast Decode)** | Lowest (Fastest Decode) |
| **Forward FLOPs** | $\mathcal{O}(H_q \cdot S \cdot D)$ | $\mathcal{O}(H_q \cdot S \cdot D)$ | $\mathcal{O}(H_q \cdot S \cdot D)$ |
| **Downstream Accuracy** | Upper Bound | **Near-MHA quality** | Noticeable accuracy drop |
| **Key Advantage** | Maximum expressivity | **Optimal throughput/quality** | Minimum memory usage |

---

## Common Interview Questions & How to Answer

### Q1: Why is GQA considered a crucial optimization for serving long-context LLMs, and why does MHA fail at scale?
- **Answer**: LLM generation (decoding) is memory-bandwidth bound because the GPU must load the entire history of key-value vectors (the KV Cache) from HBM for every token generated. In MHA, the KV Cache grows quadratically with sequence length and linearly with the number of attention heads. For long context lengths (e.g., $S \ge 32\text{k}$), the cache becomes too large to fit in fast memory, causing severe latency bottlenecks or Out-of-Memory (OOM) errors. GQA addresses this by allowing groups of query heads to share KV heads. This reduces the KV Cache footprint and HBM read traffic by a factor of $H_q / H_{kv}$ (e.g., $8\times$ in Llama 3), directly accelerating decoding speed while maintaining near-MHA-level quality.

### Q2: What is the broadcast reshape trick, and why is it used instead of copying key-value tensors?
- **Answer**: The broadcast reshape trick is a tensor manipulation technique that implements GQA without duplicating KV cache memory. Instead of copying the KV heads $n_{\text{repeats}}$ times to match the shape of the queries (which would waste memory and CPU/GPU cache space), we reshape the query tensor to $[B, H_{kv}, n_{\text{repeats}}, L, D]$ and insert a singleton dimension of $1$ into the KV tensors: $[B, H_{kv}, 1, S, D]$. During the subsequent matrix multiplication, the hardware-level matrix engine automatically broadcasts the key/value data across the $n_{\text{repeats}}$ axis in place. This avoids physical memory duplication and keeps the KV cache footprint small.

### Q3: Why does changing the query reshape order from `[H_kv, n_repeats]` to `[n_repeats, H_kv]` corrupt the output, and why is it hard to debug?
- **Answer**: In the query tensor, the attention heads are arranged contiguously in memory. For example, with 4 heads and 2 groups, the layout is $[Q_0, Q_1 \mid Q_2, Q_3]$. Reshaping to `[H_kv, n_repeats]` ($2 \times 2$) splits the heads into contiguous groups: group 0 gets $[Q_0, Q_1]$ and group 1 gets $[Q_2, Q_3]$. Reshaping to `[n_repeats, H_kv]` ($2 \times 2$) splits them row-major into striped groups: group 0 gets $[Q_0, Q_2]$ and group 1 gets $[Q_1, Q_3]$. This routes the queries of $Q_1$ and $Q_2$ to the wrong KV cabinets. It is difficult to debug because the tensor shapes still match perfectly, meaning the code runs without error but outputs silent, garbled garbage.

---

## Pro-Tip: How to Impress the Interviewer

- **The GQA Split Limit (Tensor Parallelism)**: In large-scale deployments, models are split across multiple GPUs using Tensor Parallelism (TP). The query, key, and value heads are divided evenly among the GPUs. For example, if a model has $H_{kv} = 8$ KV heads and is split across $\text{TP} = 8$ GPUs, each GPU holds exactly $1$ KV head. If you attempt to scale this setup to $\text{TP} = 16$ GPUs, the KV heads cannot be split further because you cannot have a fraction of a head. To scale past this limit, you must either replicate KV heads across GPUs (which increases memory usage) or transition to Pipeline Parallelism (PP), which introduces latency bubble overheads.
