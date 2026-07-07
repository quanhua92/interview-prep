# High-Performance System Design (Flashcards)

Click the bold text to reveal the answer. Click the file link for the full deep dive.

---

<details><summary><b>Design an autonomous driving perception pipeline (L3/L4, 50 ms photon-to-planning)</b></summary>

Topic: Autonomous Driving Perception Data Pipeline
Key concepts:
- Heterogeneous compute on DRIVE Orin/Thor: cameras (8x 8MP @ 30Hz), LiDAR, radar, IMU feed CPU + Ampere GPU + dual DLA under a 50 ms end-to-end latency budget and ISO 26262 ASIL-D safety.
- Zero-copy IPC via `NvSciBuf`/`NvSciSync` and PTP-based sensor synchronization (Frame-Sync) eliminate H2D copies and serialization between processes.
- BEV fusion projects all sensor features into a unified Bird's-Eye-View occupancy grid; DLAs run CNNs, the GPU handles attention/fusion, an ASIL-D safety MCU provides fail-operational fallback.
File: [system_design_autonomous_driving_perception.md](../../system_design_autonomous_driving_perception.md)
</details>

<details><summary><b>Design a distributed GPU training cluster for a trillion-parameter LLM</b></summary>

Topic: Distributed GPU Training Platform
Key concepts:
- Three planes: control/orchestration, data ingestion (GPUDirect Storage → HBM3, bypassing host RAM), compute/communication (NCCL collectives).
- Fabric: intra-node NVLink/NVSwitch (~900 GB/s), inter-node InfiniBand/RoCE with GPUDirect RDMA so gradients cross the wire without CPU copies.
- 3D parallelism combines Tensor Parallel (TP), Pipeline Parallel (PP), and Data Parallel, layered with ZeRO-3/FSDP sharding of optimizer states/gradients/params to fit models larger than one GPU's 80 GB HBM. Target MFU > 50%.
File: [system_design_distributed_gpu_training.md](../../system_design_distributed_gpu_training.md)
</details>

<details><summary><b>Design a real-time video analytics platform for 1,000 RTSP streams</b></summary>

Topic: Real-Time Video Analytics Pipeline
Key concepts:
- A naive OpenCV/Python pipeline saturates CPU decoders; use NVIDIA DeepStream (GStreamer) + Triton, with NVDEC hardware H.264 decoders handling decode offload.
- `nvstreammux` batches frames from many streams into a single batched tensor; `nvinferserver` sends the batch to Triton for dynamic-batched inference, then `nvtracker` tracks objects on GPU.
- Zero-copy memory pointers (NvBufSurface) carry the frame through the whole pipeline without CPU memcpy, hitting the 33 ms/frame real-time budget; metadata exits via `nvmsgbroker` to Kafka.
File: [system_design_realtime_video_analytics.md](../../system_design_realtime_video_analytics.md)
</details>

<details><summary><b>Design a scalable LLM inference server (Llama-3 70B, 5k concurrent users)</b></summary>

Topic: Triton Inference Server + TensorRT-LLM
Key concepts:
- Decoupled Gateway-Compute model with a prompt-caching router in front of Triton; TensorRT-LLM backend serves the model. KPIs: TTFT p99 < 100 ms, ITL p99 < 25 ms, > 100 tokens/s/GPU.
- Dynamic batching groups concurrent requests; in-flight (continuous) batching inserts/evicts requests at decode step boundaries so the GPU never idles waiting for a slow sequence to finish.
- Paged KV Cache borrows OS paging: KV state is stored in fixed-size blocks so fragmentation drops and long contexts fit, raising HBM utilization above 80%.
File: [system_design_triton_inference_server.md](../../system_design_triton_inference_server.md)
</details>

<details><summary><b>Handle GPU bottlenecks in a microservice architecture</b></summary>

Topic: GPU Microservices Bottlenecks
Key concepts:
- Treating a GPU worker like a CPU service fails under load: the H2D PCIe copy + queue congestion + OOM dominate. Use an async event-driven buffer (Redis Streams/Kafka) + KEDA autoscaler instead of synchronous calls.
- CPU-to-GPU transfer latency is the core bottleneck: pin host memory (page-locked) and overlap H2D copies with compute via CUDA streams so transfers and kernels run concurrently.
- GPU multi-tenancy: MIG hardware-partitions one GPU into isolated slices (hard isolation); MPS shares one GPU across processes with shared address space (higher throughput, weaker isolation). Add backpressure queues to shed load before OOM.
File: [system_design_gpu_microservices_bottleneck.md](../../system_design_gpu_microservices_bottleneck.md)
</details>

<details><summary><b>Design a distributed task scheduler with cooldown across M machines</b></summary>

Topic: Task Scheduler with Cooldown and Multiple Machines
Key concepts:
- Algorithm: max-heap of remaining task frequencies; poll up to M tasks per cycle, decrement, push to a cooldown wait-queue keyed by release time `t + n + 1`; fast-forward idle cycles to the earliest release.
- Distributed scale-out: each machine claims work via `SELECT ... FOR UPDATE SKIP LOCKED` on a shared DB row so workers never grab the same task without a global lock.
- Global cooldown is enforced with Redis leases carrying a TTL lock: a task type cannot be re-acquired until its lock expires, giving correctness across machines even under worker crashes.
File: [system_design_task_scheduler_multiple_machines.md](../../system_design_task_scheduler_multiple_machines.md)
</details>

---

[Flashcard Index](../README.md)
