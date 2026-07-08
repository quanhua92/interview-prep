# Disaggregated Serving (DistServe / Mooncake)

- **Category**: LLM Systems
- **Difficulty**: Expert
- **Target Role**: LLM Inference Architect / ML Platform Engineer
- **Source**: DistServe (Zhong et al., 2024) / Mooncake (Qin et al., 2025) / Splitwise (Microsoft, 2023)
- **Flashcards**: [LLM Systems deck](../flash_cards/llm/llm_systems.md)

---

## Concept Overview

An LLM request consists of two phases with opposite computational profiles: the **prefill** phase (which processes the prompt and is compute-bound) and the **decode** phase (which generates tokens one by one and is memory-bandwidth-bound). In standard co-located serving engines (like vLLM or Orca), these two phases run on the same GPU. 

**Disaggregated serving** separates the prefill and decode phases onto **distinct GPU pools** connected by high-speed networks. The prefill pool processes the prompt, generates the Key-Value (KV) cache, and transmits the KV cache bytes over RDMA to the decode pool, which handles token generation.

```text
Co-located (1 GPU): prefill blocks decode → ITL spikes
[ Decode Batch (20ms) ] → [ Prefill (80ms) ] → [ Decode Batch (stalled!) ] → ITL = 100ms (5x spike)

Disaggregated (2 pools): parallel execution → flat ITL
Prefill Pool: [ Prefill (80ms) ] ──(KV Transfer: 1.3ms)──> Decode Pool: [ Decode Batch (20ms) ] (flat ITL)
```

### The Problem It Solves

Co-located serving causes severe **phase interference**. Eager schedulers prioritize the prefill phase to keep the Time-To-First-Token (TTFT) low. However, if a long prefill request (e.g., 512 tokens, taking **80 ms**) enters the execution queue, the active decode batch must stall. This causes the Inter-Token Latency (ITL) to spike from a baseline of **20 ms** to **100 ms** (a **5.0× spike**), violating user-facing latency SLAs.

Disaggregated serving resolves this by separating the compute resources. The prefill pool is configured with Tensor Parallelism (TP) for fast matrix multiplication to minimize TTFT, while the decode pool uses Data Parallelism (DP) and large batching to maximize throughput and keep ITL low and flat. The only overhead is the network transfer of the KV cache.

For a Llama-3-8B model ($\text{layers}=32, \text{nQHeads}=32, \text{nKvHeads}=8, \text{headDim}=128$, prompt length $S=512$ tokens), the KV cache size is:
$$\text{Size}_{\text{KV}} = 2 \cdot \text{layers} \cdot \text{n}_{\text{kvHeads}} \cdot \text{headDim} \cdot S \cdot \text{bytes} = 2 \cdot 32 \cdot 8 \cdot 128 \cdot 512 \cdot 2 = 67,108,864\text{ bytes } (\approx 64.0\text{ MiB})$$

We compare the network transfer latency of this 64.0 MiB KV cache against the prefill roofline floor on an NVIDIA A100 GPU (peak FP16 TFLOPS = 312, crossover = 156 FLOP/B):

| Transfer Path / Operation | Bandwidth | Transfer Latency | vs. Prefill Floor |
|---|---|---|---|
| **Prefill Recomputation** (A100 Floor) | — | **22.91 ms** | Baseline |
| **Intra-node NVLink** (GPU $\leftrightarrow$ GPU) | 600.0 GB/s | **0.112 ms** | **204.8× faster** |
| **Remote RoCEv2 / IB** (400 Gbps network) | 50.0 GB/s | **1.342 ms** | **17.1× faster** |
| **Remote RoCEv2 / IB** (200 Gbps network) | 25.0 GB/s | **2.684 ms** | **8.5× faster** |
| **100 GbE network** | 12.5 GB/s | **5.369 ms** | **4.3× faster** |

At 400 Gbps RoCEv2, the transfer takes only **1.34 ms**. This is negligible compared to the prefill roofline floor of **22.91 ms** (and empirical prefill times of **~80 ms**). Disaggregation adds only a **1.68%** overhead to TTFT (80 ms $\rightarrow$ 81.34 ms) but completely eliminates the 5.0× ITL spikes, allowing engines to serve **7.4× more requests** under strict latency SLAs.

### How It Works

1. **Request Routing**: An incoming query goes to the request router. In advanced systems (like Mooncake), the router uses **KV-centric prefix-aware routing** to route requests to the prefill node holding the longest matching prefix of the prompt.
2. **Prefill Execution**: The chosen prefill node computes the KV cache for the prompt (or only the suffix on a prefix hit) and generates the first output token.
3. **KV Cache Transfer**: The prefill GPU streams the KV cache over RDMA (RoCEv2 or NVLink) into the target decode GPU's VRAM.
4. **Decode Execution**: The decode GPU appends the pages to its local block table (under PagedAttention). It continues generating subsequent tokens autoregressively at low, flat ITL.
5. **Dynamic Co-optimization**: The platform searches for the optimal ratio of prefill-to-decode GPUs (e.g., 2P:1D) based on traffic profiles to maximize overall system goodput.

```text
          ┌────────────────┐       ┌──────────────────────┐
Request ─►│ Request Router │       │     Prefill Pool     │
          │   (Mooncake:   │──────►│    (TP, low TTFT)    │
          │ Prefix-aware)  │       │     Produces KV      │
          └────────────────┘       └──────────┬───────────┘
                                              │
                                              │ RDMA Transfer
                                              │ Size_KV / BW (~1.34 ms)
                                              ▼
          ┌────────────────┐       ┌──────────┴───────────┐
          │     Client     │◄──────│     Decode Pool      │
          │    (Tokens)    │       │    (DP, low ITL)     │
          │                │       │     Consumes KV      │
          └────────────────┘       └──────────────────────┘
```

---

## Worked Example

This example demonstrates how Mooncake's KV-centric routing and disaggregated serving collaborate to minimize compute and eliminate latency spikes.

### 1. Unified KV Cache Catalog Setup
Suppose we have 3 prefill nodes caching the following prefixes:
- **System Prompt**: 8 tokens `[100..107]`
- **Node 0**: Caches `system_prompt` + `query_a` (`[200, 201, 202]`, total 11 tokens)
- **Node 1**: Caches `system_prompt` only (total 8 tokens)
- **Node 2**: Caches `system_prompt` + `query_b` (`[203, 204, 205]`, total 11 tokens)

### 2. KV-Centric Routing & Prefill
A new request arrives: `system_prompt` + `query_a` + `new_question` (13 tokens total).
- The router queries the global catalog:

| Node | Longest Cached Prefix Match | Match Length | Remaining Suffix to Prefill |
|---|---|---|---|
| **Node 0** | `system_prompt + query_a` | **11 tokens** | **2 tokens** |
| **Node 1** | `system_prompt` | 8 tokens | 5 tokens |
| **Node 2** | `system_prompt` | 8 tokens | 5 tokens |

The router selects **Node 0**. 
- Node 0 only computes the KV cache for the **2 suffix tokens** (skipping 11 tokens, an **85% prefix compute saving**).
- Node 0 generates the first output token.

### 3. KV Transfer & Decode Execution
Node 0 transfers the KV cache to the decode pool:
- The decode pool node maps the received KV pages into its block table:
  - `logical 0` $\rightarrow$ `physical page 0`
  - `logical 1` $\rightarrow$ `physical page 1`
  - `logical 2` $\rightarrow$ `physical page 2`
- The transfer is byte-equal to the original precomputed tensors. The decode pool begins generating output tokens.

### 4. End-to-End Latency Comparison

| Metric | Co-Located (1 GPU) | Disaggregated (2 Pools) | Advantage of Disaggregation |
|---|---|---|---|
| **TTFT (No Contention)** | 80 ms | 81.34 ms | Slight 1.68% network overhead |
| **TTFT (Under Load)** | 80+ ms (stalled by active decodes) | ~81.34 ms | Predictable first-token latency |
| **ITL Baseline** | 20 ms | 20 ms | Identical speed |
| **ITL (Under Prefill Load)** | **100 ms (SPIKE)** | **20 ms (FLAT)** | **Eliminates 5× tail latency spikes** |
| **Goodput (SLO-bound)** | Lower (broken by ITL spikes) | **7.4× higher** | Predictable throughput under load |

---

## Complexity & Trade-offs

| Metric | Complexity / Value | Notes |
|---|---|---|
| **Routing Overhead** | $\mathcal{O}(L \cdot \text{RTT}_{index})$ | Router checks prefix catalog before dispatching. |
| **KV Transfer Complexity** | $\mathcal{O}(\text{SizeKV})$ | Linear with prompt length and layer dimension. |
| **SLO Goodput Ratio** | Up to 7.4× improvement | Eliminating ITL variance increases overall compliant throughput. |
| **GPU Hardware Overhead** | High (decoupled pool) | Requires setting aside separate clusters. If prefill:decode ratio is misconfigured, one pool idles. |

---

## Common Interview Questions & How to Answer

### Q1: Why do prefill and decode phases benefit from different parallelization strategies, and how does disaggregated serving exploit this?
- **Answer**: The prefill and decode phases have different hardware bottlenecks:
  1. **Prefill**: Processes all prompt tokens in parallel, resulting in large matrix multiplications with high arithmetic intensity. It is highly **compute-bound**. To minimize user-perceived TTFT, we want to split the computation of this single prompt across multiple GPUs. Thus, the prefill pool is configured with **Tensor Parallelism (TP)**, which splits weights within a layer across GPUs, reducing matmul latency at the cost of intra-layer communication.
  2. **Decode**: Generates one token at a time, performing small matrix-vector multiplications that read all model weights. It is highly **memory-bandwidth-bound**. Tensor Parallelism is inefficient here because it introduces frequent synchronization barriers for tiny computations. Instead, the decode pool is configured with **Data Parallelism (DP)** or **Pipeline Parallelism (PP)**. This allows the system to process thousands of concurrent, independent generation streams in large batches, maximizing weight reuse and throughput without synchronization overheads.
  Disaggregated serving allows us to tune these parallelization strategies **independently** on their respective pools. In a co-located engine, we are forced to use the same parallelism strategy (usually TP) for both phases, compromising the efficiency of the decode step.

### Q2: What is Mooncake's "prediction-based early rejection policy," and why is it needed in disaggregated serving?
- **Answer**: In a disaggregated serving cluster, the prefill and decode pools have finite capacities. Under high traffic, the decode pool can become saturated with active generation streams. If we continue to accept new requests, the prefill pool will compute them, transfer the KV cache, and flood the decode pool. This would force the decode pool to increase its batch sizes beyond its hardware threshold, leading to queuing delays and causing active streams to miss their ITL/TPOT SLOs.
  Mooncake implements a **prediction-based early rejection policy**. When a new request arrives, the scheduler estimates its generation length and calculates the future resource load on the decode pool. If the scheduler predicts that the decode pool cannot serve the new request without causing existing streams to violate their ITL SLOs, it rejects the request *before* performing prefill. This prevents wasting prefill compute and protects active users from latency degradation, maintaining high **goodput** under overload conditions.

---

## Pro-Tip: How to Impress the Interviewer

- **Disaggregated Cache Tiering**: Suggest caching KV pages on the **CPU DRAM of the decode nodes** rather than on the prefill nodes. When the prefill pool finishes, it transfers the KV cache straight to the destination decode node's CPU DRAM. When the decode node's scheduler allocates a slot, the KV cache is copied locally from CPU DRAM $\rightarrow$ GPU VRAM over PCIe Gen5. This offloads VRAM capacity pressure from both GPU pools and hides transfer latency behind execution.
- **Prefix-Aware Routing Overlap**: Point out that the router should route requests to prefill nodes based not only on prefix match length but also on **network topology**. Routing to a prefill node on the same rack as the destination decode node allows the KV cache transfer to use intra-rack RoCEv2, avoiding inter-rack network congestion.
