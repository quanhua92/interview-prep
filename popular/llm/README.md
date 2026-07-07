# LLM Systems — Interview Preparation Roadmap

Welcome to the **LLM Systems study guide**. This directory contains 34 deep-dive interview-preparation guides covering Transformer fundamentals, serving optimization, distributed training, and voice/speech pipelines.

---

## 🗺️ Progression Roadmap

To build solid LLM systems intuition, progress through the modules in sequence:

```text
┌────────────────────────────────────────────────────────┐
│           Module 1: Transformer Foundations            │
│                 (Math & Layer Basics)                  │
└───────────────────────────┬────────────────────────────┘
                            │
                            ▼
┌────────────────────────────────────────────────────────┐
│         Module 2: Memory & Attention Efficiency        │
│                 (FlashAttention & GQA)                 │
└───────────────────────────┬────────────────────────────┘
                            │
                            ▼
┌────────────────────────────────────────────────────────┐
│           Module 3: Inference & Serving Stack          │
│              (PagedAttention & Schedulers)             │
└───────────────────────────┬────────────────────────────┘
                            │
                            ▼
┌────────────────────────────────────────────────────────┐
│    Module 4 & 5: Adaptations & Distributed Training    │
│                  (LoRA, TP, PP, ZeRO)                  │
└───────────────────────────┬────────────────────────────┘
                            │
                            ▼
┌────────────────────────────────────────────────────────┐
│           Module 6: Advanced Scale & Serving           │
│          (MoE, Speculative Dec, Disaggregated)         │
└───────────────────────────┬────────────────────────────┘
                            │
                            ▼
┌────────────────────────────────────────────────────────┐
│          Module 7: Conversational & Voice AI           │
│             (VAD, Streaming ASR/TTS, ALMs)             │
└────────────────────────────────────────────────────────┘
```

---

## 📈 Learning Modules & File Index

### Module 1: Transformer Foundations
*Goal: Understand layer-by-layer mathematics, normalization stability, and subword tokenization mechanics.*

| Topic | Guide Link | Key Focus Area |
| :--- | :--- | :--- |
| **Layer Normalization** | [Normalization](llm_normalization.md) | LayerNorm vs. RMSNorm, BF16 underflow, and FP32 upcast |
| **Tokenization** | [Tokenization](llm_tokenization.md) | BPE rank-greedy merges, WordPiece, and SentencePiece CJK rules |
| **Position Encoding** | [Rotary Position Embedding (RoPE)](llm_rope.md) | Absolute PE vs. RoPE, norm-preservation, and context scaling |
| **MLP Activation** | SwiGLU Activation | Swish gating, parameter footprint, and validation benefits |
| **Causal Masking** | [Causal Mask](llm_causal_mask.md) | Prefill vs. decode attention, lower-triangular masking, and QK-Norm |

### Module 2: Memory & Attention Efficiency
*Goal: Overcome memory bandwidth bottlenecks and minimize KV Cache footprints.*

| Topic | Guide Link | Key Focus Area |
| :--- | :--- | :--- |
| **KV Cache Basics** | [KV Cache (Dense vs Paged)](llm_kv_cache.md) | Autoregressive prefill/decode phases, and sequence waste math |
| **FlashAttention** | [FlashAttention](llm_flash_attention.md) | SRAM tiling, online softmax normalization, and HBM memory walls |
| **Grouped Attention** | [Grouped-Query Attention (GQA)](llm_gqa.md) | MHA vs. MQA vs. GQA, sharding layouts, and tensor contiguous steps |
| **Quantization** | [Quantization (INT8, FP8, AWQ, GPTQ)](llm_quantization.md) | Outliers, weight-only vs. activation quantization, SmoothQuant, and AWQ |

### Module 3: Inference & Serving Stack
*Goal: Design high-throughput serving systems and optimize kernels for GPU execution.*

| Topic | Guide Link | Key Focus Area |
| :--- | :--- | :--- |
| **Sampling** | [Sampling Strategies](llm_sampling.md) | Temperature scaling, top-k/top-p nucleus cutoff, and entropy |
| **PagedAttention** | [PagedAttention Kernel](llm_paged_attention.md) | Logical-to-physical block tables, address gather math, and page sizes |
| **Block Manager** | [Block Manager](llm_block_manager.md) | Dynamic allocation, free list tracking, reference count sharing, and preemption |
| **LLM Scheduler** | [Scheduler](llm_scheduler.md) | Continuous batching, prefill/decode slot allocation, and FCFS scheduling |
| **Prefix Caching** | [Prefix Cache](llm_prefix_cache.md) | Radix-tree prefix sharing, hit rate numbers, and LRU eviction |
| **CUDA Graphs** | [CUDA Graphs](llm_cuda_graphs.md) | Decode launch overhead, eager mode vs. captured graph execution, and dynamic padding |

### Module 4: Fine-Tuning & Adaptation
*Goal: Scale down model updates and optimize memory overhead during training.*

| Topic | Guide Link | Key Focus Area |
| :--- | :--- | :--- |
| **LoRA** | [Low-Rank Adaptation (LoRA)](llm_peft_lora.md) | Frozen parameters, $\Delta W = B \cdot A$ rank-reduction, and S-LoRA multi-adapter serving |
| **Recomputation** | [Gradient Checkpointing](llm_gradient_checkpointing.md) | Activation storing vs. selective recomputation, and $O(\sqrt{L})$ memory scaling |

### Module 5: Distributed Training & Large-Scale Systems
*Goal: Train giant models across multi-node GPU clusters, partitioning memory and compute.*

| Topic | Guide Link | Key Focus Area |
| :--- | :--- | :--- |
| **Collectives** | [NCCL Collectives](llm_nccl_collectives.md) | Broadcast, Reduce, AllReduce, Ring-AllReduce step mechanics, and network bounds |
| **Data Parallelism** | [DDP](llm_ddp.md) | Weight replication, Ring-AllReduce gradient sync, and Amp mixed precision |
| **Tensor Parallelism** | [Tensor Parallelism](llm_tensor_parallel.md) | Megatron Column/Row projections, activation cancellation, and NVLink limits |
| **Pipeline Parallelism** | [Pipeline Parallelism](llm_pipeline_parallel.md) | GPipe bubbles, 1F1B scheduling, and virtual stages |
| **ZeRO Optimizer** | [ZeRO Optimizer](llm_zero.md) | Partitioning optimizer states, gradients, and parameters; communication overhead |
| **Distributed Scale** | [Distributed GPU Training](llm_distributed_gpu_training.md) | 1-Trillion parameter model cluster layout, GPUDirect RDMA, and fault tolerance |

### Module 6: Advanced Serving & Scale
*Goal: Deploy massive expert models and coordinate high-speed GPU-to-CPU offloading.*

| Topic | Guide Link | Key Focus Area |
| :--- | :--- | :--- |
| **MoE Routing** | [MoE Routing](llm_moe_routing.md) | Sparse gating, top-k routing, load balancing, and DeepSeek aux-free routing |
| **Speculative Decoding** | [Speculative Decoding](llm_speculative_decoding.md) | Draft-target synchronization, and parallel target validation |
| **Global Prefix Cache** | [LMCache](llm_lmcache.md) | GPU-CPU-NVMe-S3 storage hierarchy, and RDMA block transfers |
| **Prefill-Decode Split** | [Disaggregated Serving](llm_disaggregated_serving.md) | Dedicated prefill and decode nodes, and KV cache transfer latencies |
| **CPU Offloading** | [KTransformers Offload](llm_ktransformers_offload.md) | CPU expert offloading, activation-only transfers, and AVX/AMX GEMMs |
| **TPU Compilation** | [JAX / XLA / TPU](llm_jax_xla_tpu.md) | Jaxpr tracing, XLA kernel fusion, and Pallas low-level TPU code |

### Module 7: Conversational & Voice AI Systems
*Goal: Build sub-500ms voice agents with streaming audio pipelines and robust guardrails.*

| Topic | Guide Link | Key Focus Area |
| :--- | :--- | :--- |
| **NVIDIA Riva Stack** | [NVIDIA Conversational AI](llm_nemo_riva_stack.md) | FastConformer downsampling, Riva NIM Triton deployments, and guardrails |
| **Voice Agent Design** | [Voice Agent Architecture](llm_voice_agent_architecture.md) | Decoupled queues, streaming VAD, state synchronization, and barge-in |
| **Voice Profiling** | [Voice Latency Optimization](llm_latency_optimization.md) | Real-time factor (RTF), memory-bound vocoders, and batch latency tradeoffs |
| **Audio ALMs** | [Multimodal Audio-Language Models](llm_multimodal_audio.md) | Codec audio tokenizers, Residual Vector Quantization (RVQ), and vocoders |
| **Voice Evaluation** | [Voice Agent Evaluation](llm_agent_benchmarking.md) | PESQ, POLQA, ViSQOL, and simulated acoustic noise testing |

---

## 💡 LLM Systems Interview Strategy

1. **Be Exact on Roofline Analysis**: When discussing inference latency, distinguish between the **compute-bound prefill phase** (high batch size, parallel context processing) and the **memory-bound decode phase** (batch size 1, reading model weights from High-Bandwidth Memory (HBM) for every single token).
2. **Explain Paged Memory and DSU Analogy**: Connect PagedAttention back to operating system virtual memory concepts. Explain how the block table acts as page-table mapping, and how references are updated during preemption or swapping.
3. **Know the Quantization outlier math**: Explain that activations have vertical outliers (specific channels with $100\times$ larger magnitudes). Explain how SmoothQuant and AWQ preserve these channels while quantizing the rest.
