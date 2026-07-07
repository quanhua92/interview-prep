# Handling GPU Bottlenecks in Microservice Architectures

- **Category**: System Design
- **Difficulty**: Hard
- **Target Role**: Systems Engineer / DevOps Architect / Backend Engineer / AI Infrastructure Engineer
- **Source**: NVIDIA Core Infrastructure & Cloud Team Interview Experience, Glassdoor
- **Flashcards**: [System Design deck](flash_cards/design/system_design.md)

---

## 1. Question Description

Design an API gateway and microservice architecture where downstream services rely on GPU-accelerated workloads (e.g., Speech-to-Text, Object Recognition, OCR). The system must handle high-volume traffic while resolving common GPU bottlenecks, such as CPU-to-GPU memory transfer latency, GPU memory exhaustion (OOM), queueing delays, and multi-tenant GPU sharing.

---

## 2. High-Level System Architecture

A standard microservice mesh that treats a GPU worker like a CPU-bound service fails immediately under load due to queue congestion and PCIe bottlenecks. We propose a decoupled architecture utilizing an **Asynchronous Event-Driven Buffer**, **NUMA-Aware Scheduling**, **Hardware GPU Sharing (MIG/MPS)**, and **Host-Device Stream Overlapping**.

### System Architecture & Hardware Topologies

```text
  ┌────────────┐    HTTPS / gRPC    ┌──────────────────────┐
  │ Clients /  │ ─────────────────> │  API Gateway - Envoy │
  │ Users      │                    └──────────┬───────────┘
  └────────────┘                               │ 1. Enqueue Task
                                               ▼
┌─ Async Buffer & Scaling Layer ──────────────────────────────────────┐
│   ┌──────────────────────────┐   Monitor    ┌──────────────────┐    │
│   │ (Redis Streams / Kafka)  │ <─ Queue ─── │ KEDA Autoscaler  │    │
│   │        Queue             │    Depth     └────────┬─────────┘    │
│   └──────────┬───────────────┘                       │              │
│              │ 2. Dequeue Task                       │ 3. Scale Pods│
└──────────────┼───────────────────────────────────────┼──────────────┘
               │                                       │
               ▼ (dequeue)                             ▼ (scale pods)
┌─ GPU Compute Host (NUMA Node 0) ────────────────────────────────────┐
│                                                                     │
│  ┌─ NVIDIA H100 Physical GPU ─────────────────────────────────────┐ │
│  │                                                                 │ │
│  │  ┌─ MIG Instance 0 (3g.40gb) ───────────────────────────────┐  │ │
│  │  │  ┌─ MPS Daemon ────────────────────────────────────────┐  │  │ │
│  │  │  │  ┌────────────────┐        ┌────────────────────┐   │  │  │ │
│  │  │  │  │ OCR Worker     │        │ OCR Worker         │   │  │  │ │
│  │  │  │  │ Process 1      │        │ Process 2          │   │  │  │ │
│  │  │  │  │ (dequeue task) │        │ (scaled by KEDA)   │   │  │  │ │
│  │  │  │  └────────────────┘        └────────────────────┘   │  │  │ │
│  │  │  └──────────────────────────────────────────────────────┘  │  │ │
│  │  │                                                            │  │ │
│  │  │  ┌─ MIG Instance 1 (2g.20gb) ───────────────────────────┐ │  │ │
│  │  │  │  ┌────────────────────┐                               │ │  │ │
│  │  │  │  │ Speech-to-Text     │ (dequeue task)                │ │  │ │
│  │  │  │  │ Worker             │                               │ │  │ │
│  │  │  │  └────────────────────┘                               │ │  │ │
│  │  │  └───────────────────────────────────────────────────────┘ │  │ │
│  │  └────────────────────────────────────────────────────────────┘ │
│                                                                    │
│  ┌────────────┐   NUMA-Locality   ┌──────────────────┐            │
│  │ CPU Socket │ <───────────────> │ Pinned Host CPU  │            │
│  │ 0          │                   │ Memory           │            │
│  └────────────┘                   └────────┬─────────┘            │
│                                             │ 4. Pinned DMA over  │
│                                             │    PCIe Gen5        │
│                                             ▼                     │
│                                    ┌────────────────────┐         │
│                                    │ PCIe Gen5 Switch   │         │
│                                    └─────────┬──────────┘         │
│                                              │ 5. H2D Copy to VRAM│
│                                              ▼                    │
│                                    (feeds Physical GPU above)     │
└────────────────────────────────────────────────────────────────────┘
```

---

## 3. Resolving Core GPU Bottlenecks

### 3.1 Host-to-Device (H2D) Memory Transfer Latency
Transferring raw data (e.g. image frames, audio segments) from Host CPU RAM to GPU High Bandwidth Memory (HBM) over the PCIe bus is slow and blocks CPU execution.

* **Pinned (Page-Locked) Memory**: We allocate host memory using `cudaHostAlloc` instead of standard `malloc`. Pinned memory is mapped into the GPU's virtual address space, allowing the GPU's DMA (Direct Memory Access) engine to copy the memory asynchronously without CPU intervention.
* **CUDA Stream Overlapping**: We create multiple CUDA streams (`cudaStreamCreate`) to overlap the asynchronous H2D memory copies (`cudaMemcpyAsync`) of Batch $K+1$ with the active GPU execution of Batch $K$.

```
Time ───>
Stream 1:  [ H2D Copy Batch K ] [ CUDA Compute Batch K ]
Stream 2:                       [ H2D Copy Batch K+1  ] [ CUDA Compute Batch K+1 ]
```

### 3.2 Dynamic Memory Allocations & OOMs
* **The Bottleneck**: Dynamic allocations (`cudaMalloc` / `cudaFree`) in the critical loop are synchronous blocking operations that stall the GPU pipeline. Furthermore, exceeding VRAM limits causes an unrecoverable CUDA Out-of-Memory (OOM) error that crashes the container.
* **The Solution**: 
  1. We enforce strict **static memory allocation** at boot time. The worker pre-allocates a fixed memory pool (e.g., using Triton's memory pool allocator or PyTorch's caching allocator).
  2. The service refuses requests that exceed the pre-allocated batch bounds, returning a clean rate-limit message to the gateway rather than attempting dynamic allocations that risk OOM.

---

## 4. Sizing & Ingestion Math (PCIe Gen4 vs. Gen5)

Let's compute the transfer and processing latency for an OCR service handling a batch of images.
* **Batch Size ($B$)**: $64$ images.
* **Image Properties**: $1080\text{p RGB}$ ($1920 \times 1080$ resolution, $3\text{ bytes per pixel}$).
* **Total Batch Size**:
  $$\text{Batch Data} = 64 \times (1920 \times 1080 \times 3) \text{ bytes} \approx \mathbf{398.13\text{ MB}}$$

### 4.1 Latency with Pageable Memory vs. Pinned Memory (PCIe Gen4)
* **Pageable Memory (`malloc`)**: Limited by OS paging. Real-world transfer speed is restricted to $\approx 6\text{ GB/s}$.
  $$\text{H2D Transfer Time} = \frac{398.13\text{ MB}}{6\text{ GB/s}} \approx \mathbf{66.35\text{ ms}}$$
* **Pinned Memory (`cudaHostAlloc`)**: Allows full DMA saturation. Real-world transfer speed is $\approx 26\text{ GB/s}$.
  $$\text{H2D Transfer Time} = \frac{398.13\text{ MB}}{26\text{ GB/s}} \approx \mathbf{15.31\text{ ms}}$$
* **Analysis**: Assuming a GPU model inference time of $12\text{ ms}$:
  * *Without Pinned Memory/Streams*: Total execution is sequential: $66.35\text{ ms} + 12\text{ ms} = \mathbf{78.35\text{ ms}}$.
  * *With Pinned Memory & Streams*: The $15.31\text{ ms}$ copy is overlapped with the preceding batch's $12\text{ ms}$ execution. After the initial preheat step, the effective processing interval drops to $\max(15.31\text{ ms}, 12\text{ ms}) = \mathbf{15.31\text{ ms}}$ (a **$5.1\times$** throughput improvement).

### 4.2 Latency on PCIe Gen5
* PCIe Gen5 x16 provides a real-world transfer speed of $\approx 52\text{ GB/s}$.
  $$\text{H2D Transfer Time (Gen5)} = \frac{398.13\text{ MB}}{52\text{ GB/s}} \approx \mathbf{7.65\text{ ms}}$$
  * *Result*: Since $7.65\text{ ms} < 12\text{ ms}$ (inference time), upgrading to PCIe Gen5 completely hides the H2D transfer time behind execution, shifting the system bottleneck entirely to the GPU Tensor Cores.

---

## 5. Multi-Tenant GPU Sharing: MIG vs. MPS

To optimize costs, we split physical GPUs across multiple microservices. We select the sharing mechanism based on isolation requirements:

| Feature | NVIDIA MIG (Multi-Instance GPU) | NVIDIA MPS (Multi-Process Service) |
| :--- | :--- | :--- |
| **Partitioning Level** | Hardware-level (Silicon-level partitioning of SMs, memory, and path). | Software-level (CUDA driver layer task multiplexing). |
| **Failure Isolation** | **Complete**. A crash/memory leak in Service A has zero impact on Service B. | **None**. A memory crash in one process can crash the shared MPS daemon. |
| **VRAM Limits** | Rigid (e.g., $20\text{ GB}$ or $40\text{ GB}$ partitions). | Dynamic/Configurable (percentage allocations). |
| **Context Switch Overhead**| Zero (Instances execute concurrently). | Low (MPS groups kernels into a single hardware context). |
| **Best Used For** | Multi-tenant isolation of **different microservices** (e.g., ASR and OCR). | Running **multiple replicas of the same service** to saturate compute. |

---

## 6. Failure Mode and Effects Analysis (FMEA)

| Failure Mode | Root Cause | Impact | Mitigation Strategy |
| :--- | :--- | :--- | :--- |
| **GPU OOM Cascade** | One worker crashes due to OOM; traffic fails over to remaining workers, causing them to OOM sequentially. | Entire GPU microservice cluster goes offline; service outage. | Implement **Static Memory Pools** and **Load-Gate Sinks**. Workers reject tasks exceeding their batch queue capacity. Deploy **Circuit Breakers** on the API Gateway to return HTTP 503 early instead of routing to overloaded workers. |
| **MPS Crash Propagation** | A memory access violation in one worker process crashes the shared MPS daemon. | All worker processes sharing that GPU partition are terminated. | 1. Limit MPS usage to processes running identical, validated containers (homogenous workload).<br>2. Use **MIG** to partition different services, preventing ASR failures from affecting OCR. |
| **Cold Start Latency** | Large models ($>5\text{ GB}$) and libraries (PyTorch) take time to load onto new pods during scaling. | Microservice fails to handle sudden traffic spikes; queue times explode. | 1. Implement **Warm Pooling** (maintain spare idle instances).<br>2. Cache model weights locally on node NVMe drives using Kubernetes HostPath mounts to avoid downloading weights from registries over the network during scaling. |
| **GPU Hang / Freeze** | Hardware fault, kernel lockup, or memory bus error. | Pod appears healthy to Kubernetes (port is open) but calls to the GPU hang indefinitely. | Implement a **Non-Blocking GPU Heartbeat Check** in the pod liveness probe. The probe runs a lightweight CUDA kernel (e.g., a simple vector addition) via `cudaDeviceSynchronize` with a $100\text{ ms}$ timeout watchdog. If the timeout is hit, the pod restarts. |

---

## 7. Pro-Tip: How to Impress the Interviewer

* **Propose NUMA-Aware Scheduling**:
  * Explain that in multi-socket systems, a GPU is physically wired to a specific CPU socket via PCIe lanes. If a worker thread runs on CPU Socket 1 but accesses a GPU wired to CPU Socket 0, all data must cross the inter-socket UPI link. This degrades H2D bandwidth by up to **$50\%$** and introduces high latency jitter.
  * To fix this, bind worker containers using core affinity:
    ```bash
    numactl --physcpubind=0-7 --membind=0 my_gpu_worker
    ```
* **Leverage KEDA for Autoscaling**:
  * Standard Kubernetes Horizontal Pod Autoscalers (HPA) rely on CPU or GPU metrics scraped by Prometheus. This introduces a $30\text{--}60\text{ second}$ latency, which is too slow for real-time traffic spikes.
  * Propose **KEDA (Kubernetes Event-driven Autoscaling)** hooked directly into the Redis Stream queue length or Kafka consumer lag. If the queue length exceeds $50$, KEDA triggers scaling *instantly*, bypassing Prometheus scrape delays.
* **Integrate CUDA Graphs**:
  * For microservices with small batches, the CPU overhead of launching multiple small CUDA kernels can exceed the actual execution time on the GPU.
  * Explain how you would record the kernel execution sequence once using **CUDA Graphs** (`cudaGraphLaunch`), allowing the microservice to launch the entire network sequence in a single operation, eliminating CPU kernel dispatch latency.

---

## 8. Common Follow-Up Questions & How to Answer

### Q1: How do you handle rate-limiting and backpressure at the API Gateway for GPU services?
**Answer**: We implement a two-tier strategy:
1. **Asynchronous Processing (Redis Streams)**: For non-blocking endpoints, the gateway writes the request to a Redis Stream and returns an HTTP 202 (Accepted) with a job ID. Workers pull jobs at their peak processing speed, shielding the GPU from traffic surges.
2. **Synchronous Processing (Token Bucket + Circuit Breakers)**: For real-time blocking tasks, the gateway runs a Token Bucket rate limiter matched to the maximum throughput of the GPU cluster. If the queue exceeds a threshold, the gateway opens the circuit breaker, fallbacking to CPU-based inference or returning an HTTP 429 rate limit.

### Q2: What is the impact of NVLink bandwidth contention in multi-GPU nodes?
**Answer**: If multiple microservices run on the same server, they may execute collective communication (e.g., `AllReduce`) or host transfers simultaneously. If they share PCIe switches, they will compete for bandwidth. We mitigate this by configuring **Device Affinity**, pinning specific services to dedicated GPUs and NUMA nodes, and configuring PCIe Switch partitioning where available.

### Q3: When should you choose MPS over MIG?
**Answer**: 
* **Choose MIG** when you need strict security, resource, and fault isolation between different services (e.g., sharing a GPU between a production model and a staging model, or between two completely different microservices).
* **Choose MPS** when you have a single service that needs high concurrency (e.g., 4 instances of the same OCR model worker processing items from a shared queue). MPS allows them to share the GPU resources dynamically, saturating the Tensor Cores without the rigid memory boundaries of MIG.
