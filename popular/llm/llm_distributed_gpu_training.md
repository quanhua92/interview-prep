# Distributed GPU Training

- **Category**: LLM Systems
- **Difficulty**: Hard
- **Target Role**: LLM Systems Engineer / Distributed Systems Engineer / Platform Architect
- **Source**: Megatron-LM / DeepSpeed / PyTorch FSDP (NVIDIA H100 Architecture)
- **Flashcards**: [LLM Systems deck](../flash_cards/llm/llm_systems.md)

---

## Concept Overview

Think of training a trillion-parameter Large Language Model (LLM) as coordinating a massive construction project to build a skyscraper using a crew of 1,024 crane operators (GPUs). You cannot fit the entire blueprint (model parameters and optimizer states) onto a single desk (GPU memory). Instead, you split the blueprint into sections and assign them to teams of workers. To succeed, the crane operators must be connected by high-speed walkie-talkies (the network fabric) that let them communicate without delays. Furthermore, you need a conveyor belt (GPUDirect Storage) that streams concrete (datasets) directly to the site without intermediate unloading, and a system to replace any crane operator who falls ill (fault tolerance) within minutes to prevent the whole structure from collapsing.

In ML systems, **Distributed GPU Training** refers to the infrastructure and system design required to scale LLM training across multi-node, multi-GPU clusters. This involves three planes of operation:
1. **Control & Orchestration Plane**: Allocates compute resources and schedules tasks based on physical network topology.
2. **Data Ingestion Plane**: Streams training datasets directly from storage to GPU memory.
3. **Compute & Communication Plane**: Executes forward/backward math and synchronizes parameters using high-performance network collectives.

```text
┌────────────────────────────────────────────────────────────────────────┐
│                             Storage Layer                              │
│                                                                        │
│  ┌─────────────────────────────────┐   ┌────────────────────────────┐  │
│  │ Parallel Storage (Lustre/WekaFS)│──►│ GPUDirect Storage (NVMe-oF)│  │
│  └─────────────────────────────────┘   └─────────────┬──────────────┘  │
└──────────────────────────────────────────────────────┼─────────────────┘
                                                       │ Direct DMA (PCIe)
                                                       ▼
┌────────────────────────────────────────────────────────────────────────┐
│                    DGX H100 Compute Node (1 of 128)                    │
│                                                                        │
│  ┌──────────────────┐  ┌──────────────────┐      ┌──────────────────┐  │
│  │    Sapphire      │  │   ConnectX-7     │      │   ConnectX-7     │  │
│  │   Rapids CPU     │  │     HCA 0        │      │     HCA 7        │  │
│  └────────┬─────────┘  └────────┬─────────┘      └────────┬─────────┘  │
│           │                     │                         │            │
│           ▼                     ▼                         ▼            │
│  ┌──────────────────────────────────────────────────────────────────┐  │
│  │                        PCIe Gen 5 Switch                         │  │
│  └───────┬──────────────────────┬────────────────────────┬──────────┘  │
│          │                      │                        │             │
│          ▼                      ▼                        ▼             │
│  ┌───────────────┐      ┌───────────────┐        ┌───────────────┐     │
│  │  H100 GPU 0   │◄────►│NVSwitch Chips │◄──────►│  H100 GPU 7   │     │
│  └───────────────┘      │(4x, 900 GB/s) │        └───────────────┘     │
│                         └───────────────┘                              │
└──────────┬────────────────────────────────────────────────┬────────────┘
           │ 400 Gbps                                       │ 400 Gbps
           ▼                                                ▼
┌────────────────────────────────────────────────────────────────────────┐
│                       Inter-Node Network Fabric                        │
│                                                                        │
│  ┌─────────┴─────────┐                          ┌────────┴──────────┐  │
│  │ InfiniBand Leaf 1 │                          │ InfiniBand Leaf 2 │  │
│  └─────────┬─────────┘                          └────────┬──────────┘  │
│            │                                             │             │
│            └─────────────────────┬───────────────────────┘             │
│                                  ▼                                     │
│          ┌───────────────────────────────────────────────────┐         │
│          │          InfiniBand Spine Switch (SHARP)          │         │
│          └───────────────────────────────────────────────────┘         │
└────────────────────────────────────────────────────────────────────────┘
```

### The Problem It Solves

When scaling training to $1,024\times$ NVIDIA H100 GPUs ($128\times$ DGX H100 nodes), conventional training setups break down:
- **Memory Footprint**: A 1-Trillion Parameter model requires **$16\text{ TB}$** of static memory in mixed-precision training (weights: $2\text{ TB}$, gradients: $2\text{ TB}$, Adam states: $12\text{ TB}$). This is far beyond the $80\text{ GB}$ capacity of a single GPU.
- **Communication Bottlenecks**: Standard Ethernet or PCIe communication speeds are too slow to sync weights at high frequencies, leaving GPUs starved for work.
- **Storage Bottlenecks**: Standard IO pipelines copy data from NVMe storage to the host OS Page Cache, then to host CPU memory, and finally to GPU memory. This saturates host CPU cores and limits throughput.
- **Hardware Failures**: In a cluster with 1,024 GPUs, the Mean Time Between Failures (MTBF) is measured in days. A single GPU, PCIe link, or network switch failure will crash the entire synchronous training job if not mitigated.

---

## Worked Example

Let's design a distributed training platform to train a **1-Trillion Parameter Model ($N = 10^{12}$)** across **1,024 NVIDIA H100 SXM5 GPUs** ($128\times$ DGX H100 nodes).

### 1. Static Memory Budget Calculation
- **Model Parameters (FP16)**: $2 \cdot N = \mathbf{2\text{ TB}}$
- **Gradients (FP16)**: $2 \cdot N = \mathbf{2\text{ TB}}$
- **Optimizer States (FP32 Adam)**: $12 \cdot N = \mathbf{12\text{ TB}}$ (master weights: $4\text{ TB}$, momentum: $4\text{ TB}$, variance: $4\text{ TB}$)
- **Total Static Model Memory**: $\mathbf{16\text{ TB}}$ (excludes dynamic activation memory)

### 2. 3D Parallelism + ZeRO-1 Configuration
To distribute the $16\text{ TB}$ static memory, we implement a hybrid parallelism strategy:
1. **Tensor Parallelism (TP)**: Set $TP=8$. All 8 GPUs inside a single DGX H100 node form a TP group, sharding matrices over the high-speed NVLink fabric.
2. **Pipeline Parallelism (PP)**: Set $PP=16$. The model's layers are split sequentially across 16 nodes.
3. **Data Parallelism (DP) with ZeRO-1**: Set $DP=8$ (calculated as $\frac{1,024\text{ total GPUs}}{TP \cdot PP} = 8$). ZeRO-1 shards the $12\text{ TB}$ of optimizer states across the 8 data-parallel replicas.

#### Sharded Memory Math per GPU:
- **Layers per Node**: $L_{total} / PP = L / 16$.
- **Parameters per Node**: $N / PP = 10^{12} / 16 = \mathbf{62.5\text{ Billion parameters}}$ per node.
- **Parameters per GPU (after $TP=8$)**: $62.5\text{ B} / 8 = \mathbf{7.8125\text{ Billion parameters}}$.
- **Weight Memory per GPU (FP16)**: $7.8125\text{ B} \cdot 2\text{ bytes} = \mathbf{15.625\text{ GB}}$.
- **Gradient Memory per GPU (FP16)**: $7.8125\text{ B} \cdot 2\text{ bytes} = \mathbf{15.625\text{ GB}}$.
- **Optimizer States per GPU (sharded by $DP=8$ via ZeRO-1)**:
  $$\text{Optimizer State per GPU} = \frac{7.8125\text{ B} \cdot 12\text{ bytes}}{8\text{ DP ranks}} = \text{11.719 GB}$$
- **Total Static Memory per GPU**: $15.625\text{ GB} + 15.625\text{ GB} + 11.719\text{ GB} = \mathbf{42.969\text{ GB}}$.
- This easily fits inside the $80\text{ GB}$ capacity of an H100 GPU, leaving $37\text{ GB}$ for dynamic activation memory and the KV cache.

### 3. Ingestion & Storage Bandwidth
- **GPUDirect Storage (GDS)**: We bypass CPU memory and the host Page Cache by linking Mellanox ConnectX-7 network cards directly to the GPU HBM3 over the PCIe Gen5 switch.
- This achieves a read bandwidth of **$215\text{ GB/s}$** per DGX node, ensuring that data ingestion never bottlenecks the GPU compute.

---

## Complexity & Trade-offs

| Metric | Target Value | System Trade-offs & Notes |
|---|---|---|
| **Intra-Node Bandwidth** | $900\text{ GB/s}$ (bi-directional) | Delivered by 18 NVLinks per H100 SXM5. Optimal for low-latency TP. |
| **Inter-Node Bandwidth** | $400\text{ Gbps}$ (ConnectX-7) | Fat-tree topology (1 HCA per GPU). Backed by InfiniBand Quantum-2 switches. |
| **Ingestion Read Bandwidth** | $215\text{ GB/s}$ | Enabled by GPUDirect Storage (GDS). Avoids host CPU bottlenecks. |
| **Model FLOPs Utilization (MFU)** | $> 50\%$ | MFU of $\sim 52\%$ is targeted using FlashAttention-3 and FP8 precision. |
| **Fault Recovery Downtime** | $< 5\text{ minutes}$ | Automated health checks, job rescheduling, and NVMe-backed checkpointing. |

---

## Failure Mode and Effects Analysis (FMEA)

| Failure Mode | Root Cause | Impact | Mitigation Strategy |
| :--- | :--- | :--- | :--- |
| **Straggler Node** | GPU thermal throttling or PCIe lane degradation (e.g. falling from Gen5 to Gen1). | The entire cluster slows down to match the speed of the slowest node during synchronous collectives. | Host agents monitor node health (e.g. via `dcgmPMGetMetrics`). If clock speeds drop or PCIe bandwidth falls below $50\text{ GB/s}$, the scheduler marks the node as unhealthy, drains it, and replaces it. |
| **Network Link Degradation** | Loose transceivers or packet drop on inter-node fabric. | The NCCL communication ring collapses, causing training to timeout and crash. | Enable adaptive routing on the Quantum-2 switches. If error rates exceed a threshold, NCCL dynamically routes around the degraded link via alternative paths. |
| **Silent Data Corruption (SDC)** | Hardware faults in Tensor Cores or cosmic ray bit flips. | Loss values diverge to `NaN` or model weights degrade silently, wasting compute time. | Run periodic deterministic test steps. Implement real-time gradient checks: if $||\nabla w||_2 > \text{threshold}$, pause training and run hardware diagnostics. |
| **Checkpoint Storage Congestion** | 1,024 GPUs writing $16\text{ TB}$ of data to Lustre simultaneously. | Storage network becomes saturated, halting training for $30\text{--}45\text{ minutes}$. | **Double-Buffered Host Memory Staging**: Write checkpoints to local node NVMe SSDs ($\approx 2.5\text{ GB/s}$ per drive, taking $<15\text{ seconds}$). Resume training immediately while a background service streams the data to Lustre. |

---

## Common Interview Questions & How to Answer

### Q1: Explain NCCL Ring vs. Tree collective algorithms and how the library chooses between them.
- **Answer**:
  - **Ring Algorithm**: Tensors are split into chunks and circulated around a logical ring of GPUs. The data volume transferred per rank for an `AllReduce` is $2 \cdot \frac{K-1}{K} \cdot S$, where $S$ is the tensor size and $K$ is the number of GPUs. This algorithm is bandwidth-efficient, making it optimal for **large tensors**, but it has higher latency because it scales linearly with $K$.
  - **Tree Algorithm**: Tensors are reduced up a double-binary tree and then broadcast back down. The latency scales logarithmically ($\log K$), making it optimal for **small tensors** or when the node count $K$ is very large.
  - NCCL measures cluster latencies during startup and dynamically switches from Tree to Ring once the tensor size exceeds a specific threshold (typically around $16\text{ MB}$).

### Q2: What happens when packet loss occurs on a RoCE v2 cluster vs. an InfiniBand cluster?
- **Answer**:
  - **InfiniBand**: Uses credit-based flow control at the link layer. A sender only transmits packets when the receiver has buffer space. This prevents packet loss from buffer overflows.
  - **RoCE v2**: Relies on Ethernet, which is lossy. To make it lossless, you must configure **PFC (Priority Flow Control)** to send PAUSE frames when switch buffers fill, and **ECN (Explicit Congestion Notification)** to mark packets when congestion is detected, allowing senders to throttle their transmission rates. If PFC is misconfigured, packet drops will trigger Go-Back-N retransmissions at the transport layer, causing NCCL timeouts and slashing training performance to near-zero.

### Q3: How do you optimize memory consumption during LLM training without offloading to CPU?
- **Answer**:
  1. **Activation Checkpointing (Recomputation)**: Discard activations computed during the forward pass and recalculate them during the backward pass. This reduces activation memory from $\mathcal{O}(L)$ (where $L$ is the number of layers) to $\mathcal{O}(\sqrt{L})$ at the cost of $33\%$ extra compute.
  2. **FlashAttention-3**: Computes attention on-chip in GPU SRAM without materializing the intermediate $S \times S$ attention matrix to global HBM3, saving up to $80\%$ of attention activation memory.
  3. **Sequence Parallelism**: Extends Tensor Parallelism by splitting activations along the sequence length dimension for layers that are not split by standard TP (such as LayerNorm and Dropout).

---

## Pro-Tip: How to Impress the Interviewer

- **Maximize MFU with FlashAttention-3 & FP8 precision**: Show you understand hardware optimizations. Explain how you would combine **FlashAttention-3** (which overlaps softmax and matmuls inside the GPU's Tensor Cores) and **FP8 Precision Scaling** (which uses 8-bit floats for forwards and backwards while maintaining FP16 master copies) to push Model FLOPs Utilization (MFU) past the typical $35\%$ threshold up to **$52\%$**.
- **Deep-Dive into NCCL Network Tuning**: Demonstrate familiarity with network configuration by citing specific tuning parameters. Detail how setting `NCCL_CROSS_NIC=1` enables multi-HCA routing to balance traffic across cards, setting `NCCL_BUFFSIZE=4194304` (sets the ring buffer size to $4\text{ MB}$) avoids bottlenecks in high-bandwidth channels, and setting `NCCL_COLLNET_ENABLE=1` offloads collective aggregation to Quantum-2 switches using SHARP.
