# LLM Systems — Flashcards

34 cards. Click the bold text to reveal the answer. Click the file link for the full deep dive.

---

<details><summary><b>Compare LayerNorm vs RMSNorm — why is RMSNorm standard?</b></summary>

Topic: Layer Normalization (LayerNorm → RMSNorm)
Key concepts:
- LayerNorm centers the input vector at zero (subtracts mean) and rescales to unit variance (divides by standard deviation).
- RMSNorm simplifies this by skipping the centering step and dividing only by the root-mean-square (loudness) of the vector, saving 7–64% compute time.
- All modern models (Llama, Gemma, Qwen) use RMSNorm for faster execution. Upcasting to FP32 during division is mandatory to avoid underflow/NaNs in BF16/FP16.
File: [llm_normalization.md](../../llm/llm_normalization.md)
</details>

<details><summary><b>BPE vs WordPiece — what is the key difference in encoding?</b></summary>

Topic: Tokenization Pipelines
Key concepts:
- BPE uses rank-greedy merge logic (applies merges in the exact order they were learned during training).
- WordPiece uses greedy longest-prefix match (looks up the longest possible matching prefix from the dictionary, appending `##` to suffixes).
- Byte-level BPE maps raw bytes instead of Unicode characters, preventing `[UNK]` tokens entirely.
File: [llm_tokenization.md](../../llm/llm_tokenization.md)
</details>

<details><summary><b>How does Rotary Position Embedding (RoPE) achieve relative position?</b></summary>

Topic: Positional Encoding (Absolute PE vs RoPE)
Key concepts:
- RoPE rotates query/key vectors in 2D coordinate slices by angles proportional to their absolute positions.
- During query-key dot product, the trigonometric identity $\cos(A)\cos(B) + \sin(A)\sin(B) = \cos(A-B)$ collapses the coordinates, preserving relative distance while absolute positions cancel out.
- RoPE preserves vector norms ($L_2$ norm), unlike absolute positional addition which alters vector lengths.
File: [llm_rope.md](../../llm/llm_rope.md)
</details>

<details><summary><b>Why do modern models use SwiGLU instead of standard MLP? SwiGLU formulation?</b></summary>

Topic: MLP & Activation Functions
Key concepts:
SwiGLU splits the hidden layer projection into two parallel linear passes: a gate branch activated by Swish ($\text{Swish}(x) = x \cdot \sigma(\beta x)$) and an up-projection branch, multiplied element-wise. SwiGLU eliminates flat zero-gradient regions, improving gradient flow and validation loss.
- Equation: $\text{SwiGLU}(x) = \left(\text{Swish}(x W_{\text{gate}}) \odot (x W_{\text{up}})\right) W_{\text{down}}$. SwiGLU requires 1.5× more parameters than Swish, which is offset by scaling down the intermediate dimension to $\sim 8/3 \cdot D_{\text{model}}$.
File: [llm_mlp_activation.md](../../llm/llm_mlp_activation.md)
</details>

<details><summary><b>Why does prefill use an attention mask, but decode does not?</b></summary>

Topic: Causal Masking (Prefill vs Decode)
Key concepts:
- Prefill processes the whole prompt at once, requiring a lower-triangular causal mask to prevent tokens from attending to future tokens.
- Decode processes exactly one token at a time, looking back at the KV cache of past tokens. Because the past is already computed, no mask is needed for decode attention (query attends to all keys).
- QK-Norm (applying LayerNorm to queries and keys) stabilizes attention score variance in low-precision FP8/BF16 training.
File: [llm_causal_mask.md](../../llm/llm_causal_mask.md)
</details>

<details><summary><b>Compare dense vs paged KV Cache — where does the waste come from?</b></summary>

Topic: KV Cache (Dense vs Paged)
Key concepts:
- Dense cache pre-allocates memory for the maximum sequence length (`max_seq_len`) for every request, wasting up to 93% of HBM on unused slots.
- Paged cache (vLLM) allocates memory dynamically in fixed-size blocks (pages), mapping logical pages to physical pages using a block table.
- This dynamic allocation reduces HBM waste to <4%, enabling a 2–4× increase in batch size and system throughput.
File: [llm_kv_cache.md](../../llm/llm_kv_cache.md)
</details>

<details><summary><b>How does FlashAttention avoid the memory wall?</b></summary>

Topic: FlashAttention (Tiling & Online Softmax)
Key concepts:
- Standard attention materializes the $S \times S$ scores matrix in high-bandwidth memory (HBM), creating an $O(S^2)$ memory bottleneck.
- FlashAttention tiles Q, K, and V into small blocks that fit in GPU SRAM, computing attention block-by-block.
- It uses online softmax tracking (rescaling intermediate sum and max values) to compute exact attention without saving the full attention matrix to HBM.
File: [llm_flash_attention.md](../../llm/llm_flash_attention.md)
</details>

<details><summary><b>Explain MHA, MQA, and GQA — head count math?</b></summary>

Topic: Grouped-Query Attention (GQA)
Key concepts:
- Multi-Head Attention (MHA): $H$ query heads, $H$ key/value heads. High HBM overhead during decode.
- Multi-Query Attention (MQA): $H$ query heads, $1$ key/value head. Reduces KV cache size to $1/H$, but hurts quality.
- Grouped-Query Attention (GQA): $H$ query heads grouped into $G$ key/value heads (ratio $H/G$ queries per group). Balance between speed and accuracy.
- GQA requires correct contiguous vs striped reshaping to avoid mixing attention keys across heads during tensor operations.
File: [llm_gqa.md](../../llm/llm_gqa.md)
</details>

<details><summary><b>What is the difference between AWQ, GPTQ, and SmoothQuant?</b></summary>

Topic: Quantization (INT8, FP8, AWQ, GPTQ)
Key concepts:
- SmoothQuant: Weight-activation co-quantization that migrates outliers from activations to weights, enabling INT8 quantization on both.
- GPTQ: Second-order optimization (using the inverse Hessian matrix) that compensates for quantization errors by adjusting remaining weights.
- AWQ (Activation-aware Weight Quantization): Keeps the top 1% salient weights in FP16/FP8 while quantizing the rest, avoiding outliers without Hessian compute.
File: [llm_quantization.md](../../llm/llm_quantization.md)
</details>

<details><summary><b>How do top-k, top-p, and temperature shape sampling output?</b></summary>

Topic: Sampling Strategies
Key concepts:
- Temperature ($T$) rescales logits ($z_i/T$). $T \to 0$ collapses probability to greedy search; $T > 1$ flattens the distribution, raising entropy.
- Top-k restricts sampling to the $k$ highest-probability tokens.
- Top-p (nucleus sampling) dynamically restricts sampling to the smallest set of tokens whose cumulative probability exceeds threshold $p$, adapting to model confidence.
File: [llm_sampling.md](../../llm/llm_sampling.md)
</details>

<details><summary><b>Explain how PagedAttention is implemented at the kernel level</b></summary>

Topic: PagedAttention Kernel Mechanics
Key concepts:
- Logical tokens are grouped into pages (default 16 tokens).
- The kernel uses a physical-to-logical block table to find K and V page addresses in HBM.
- In the CUDA kernel, threads gather scattered blocks, compute attention values, and write the output back, achieving identical results to dense attention at a fraction of the HBM footprint.
File: [llm_paged_attention.md](../../llm/llm_paged_attention.md)
</details>

<details><summary><b>What does the Block Manager do, and how does it handle allocation/preemption?</b></summary>

Topic: Block Manager Mechanics
Key concepts:
- The Block Manager acts as the virtual memory manager, tracking page allocations, reference counts, and the free list pool.
- It allocates new blocks on-demand during decode. If HBM runs out, it preempts running requests (either by recomputing their prompts later or swapping their pages to CPU memory).
- Reference counting enables sharing parent blocks during parallel sampling and beam search.
File: [llm_block_manager.md](../../llm/llm_block_manager.md)
</details>

<details><summary><b>Static vs Continuous Batching — how does the scheduler work?</b></summary>

Topic: Scheduler & Continuous Batching
Key concepts:
- Static batching runs requests in lockstep, holding up the entire batch until the longest request finishes (causing idle GPU slots).
- Continuous batching (iteration-level scheduling) inserts new prompts (prefill) and steps existing decodes at each iteration boundary.
- The scheduler balances prefill and decode budgets to maximize throughput while avoiding preemption.
File: [llm_scheduler.md](../../llm/llm_scheduler.md)
</details>

<details><summary><b>How does Radix-Tree Prefix Caching work?</b></summary>

Topic: Radix-Tree Prefix Cache
Key concepts:
- Prompts with identical prefixes (system prompts, chat history) share KV cache blocks to save memory.
- The cache organizes blocks in a Radix Tree. Matching keys hit the cache, avoiding recomputation.
- When memory is full, the manager evicts blocks using a Least Recently Used (LRU) policy, reclaiming pages with a reference count of zero.
File: [llm_prefix_cache.md](../../llm/llm_prefix_cache.md)
</details>

<details><summary><b>Why do CUDA Graphs speed up decode steps but not prefill?</b></summary>

Topic: CUDA Graphs
Key concepts:
- LLM decode is memory-bound with tiny kernel execution times. CPU launch overhead (submitting kernels to GPU) becomes the primary latency driver.
- CUDA Graphs capture the entire decode execution flow (kernels, memory addresses) during a warm-up step, launching them with a single CPU call.
- Prefill shapes change dynamically (sequence length varies), making static graph capture impractical, whereas decode shapes are fixed ($L=1$).
File: [llm_cuda_graphs.md](../../llm/llm_cuda_graphs.md)
</details>

<details><summary><b>How does LoRA perform low-rank updates?</b></summary>

Topic: Low-Rank Adaptation (LoRA)
Key concepts:
- LoRA freezes base weights $W_0$ and updates weights via a low-rank decomposition $\Delta W = B \cdot A$ (where $A \in \mathbb{R}^{r \times d}$ and $B \in \mathbb{R}^{d \times r}$ with rank $r \ll d$).
- This reduces trainable parameters by up to 99% and saves optimizer memory.
- During inference, multi-adapter serving frameworks (e.g. S-LoRA, Punica) run base weights jointly and use grouped GEMMs to execute adapter paths in-flight.
File: [llm_peft_lora.md](../../llm/llm_peft_lora.md)
</details>

<details><summary><b>Explain the compute/memory tradeoffs in Gradient Checkpointing</b></summary>

Topic: Activation Recomputation (Gradient Checkpointing)
Key concepts:
- Instead of storing all intermediate activation tensors for the backward pass (causing $O(L)$ memory scaling), checkpointing stores only boundaries.
- During backward propagation, missing activations are recomputed on-demand within segments.
- This cuts activation memory footprint to $O(\sqrt{L})$ at the cost of a 33% increase in total floating-point operations.
File: [llm_gradient_checkpointing.md](../../llm/llm_gradient_checkpointing.md)
</details>

<details><summary><b>What is the difference between Ring-AllReduce and Tree-AllReduce?</b></summary>

Topic: NCCL Collectives
Key concepts:
- Ring-AllReduce organizes $N$ GPUs in a ring. It splits tensors into $N$ chunks and runs $2(N-1)$ peer-to-peer transfers, transferring $2 \frac{N-1}{N}$ total bytes.
- Tree-AllReduce organizes GPUs into a binary tree structure.
- Ring-AllReduce scales well for large message sizes on ring topologies, whereas Tree-AllReduce achieves lower latency for small messages by minimizing step count.
File: [llm_nccl_collectives.md](../../llm/llm_nccl_collectives.md)
</details>

<details><summary><b>How does DDP scale gradients, and what is require_backward_grad_sync?</b></summary>

Topic: Distributed Data Parallel (DDP)
Key concepts:
- DDP replicates the model on $K$ GPUs, divides the batch, runs forward passes independently, and averages gradients via Ring-AllReduce during the backward pass.
- `require_backward_grad_sync` controls whether gradients are synced immediately or accumulated.
- Under gradient accumulation, syncing is disabled until the final micro-batch to prevent network bottlenecks. DDP requires $20N$ bytes of memory per parameters.
File: [llm_ddp.md](../../llm/llm_ddp.md)
</details>

<details><summary><b>Explain Column-Parallel vs Row-Parallel layers in Megatron-LM</b></summary>

Topic: Tensor Parallelism (TP)
Key concepts:
- Column-Parallel shards weight matrices column-wise, outputting sharded columns (e.g., in MLP Gate/Up projections).
- Row-Parallel shards weight matrices row-wise, multiplying sharded inputs and combining results via an AllReduce collective.
- Sharding MLP blocks (Column-Parallel followed by Row-Parallel) allows the AllReduce to be postponed until the very end, hiding network latency.
File: [llm_tensor_parallel.md](../../llm/llm_tensor_parallel.md)
</details>

<details><summary><b>Compare GPipe vs 1F1B scheduling in Pipeline Parallelism</b></summary>

Topic: Pipeline Parallelism (PP)
Key concepts:
- GPipe splits batches into micro-batches, running them sequentially through pipeline stages and causing a large bubble (idle time) at the start and end.
- 1F1B (One Forward, One Backward) schedules forward and backward steps of micro-batches concurrently.
- This caps activation memory buffer requirements to the number of pipeline stages $K$ instead of micro-batch count $M$, reducing VRAM overhead.
File: [llm_pipeline_parallel.md](../../llm/llm_pipeline_parallel.md)
</details>

<details><summary><b>How do ZeRO-1, ZeRO-2, and ZeRO-3 partition state? Memory math?</b></summary>

Topic: Zero Redundancy Optimizer (ZeRO)
Key concepts:
- ZeRO-1 shards Adam optimizer states (VRAM footprint: $2 + 2 + \frac{12}{K}$ bytes/param).
- ZeRO-2 shards both optimizer states and gradients ($2 + \frac{14}{K}$ bytes/param).
- ZeRO-3 shards optimizer states, gradients, and model parameters ($\frac{16}{K}$ bytes/param).
- ZeRO-3 increases communication volume by $1.5\times$ (requires an AllGather pass to reconstruct parameters before forward/backward steps).
File: [llm_zero.md](../../llm/llm_zero.md)
</details>

<details><summary><b>How do you train a 1-Trillion Parameter model? TPU/GPU cluster design?</b></summary>

Topic: Distributed GPU Training Scale
Key concepts:
- Scale require 3D Parallelism: Tensor Parallelism (TP=8) inside server nodes, Pipeline Parallelism (PP=16) across nodes, and Data Parallelism (DP=8) with ZeRO-1.
- Network demands GPUDirect RDMA over low-latency InfiniBand or RoCEv2 with priority flow control (PFC) to avoid packet drops.
- Failures like silent data corruption (SDC) must be mitigated by periodic checksum audits and redundant gradient validation.
File: [llm_distributed_gpu_training.md](../../llm/llm_distributed_gpu_training.md)
</details>

<details><summary><b>How do sparse MoE routers distribute tokens? DeepSeek aux-free?</b></summary>

Topic: MoE Routing Mechanics
Key concepts:
- Gating routers project token representations to expert probabilities, routing tokens to top-$k$ experts.
- Load balancing losses (auxiliary loss, z-loss) are added during training to prevent expert starvation.
- DeepSeek auxiliary-loss-free routing uses dynamic bias adjustment to balance expert loads without hurting representation quality.
File: [llm_moe_routing.md](../../llm/llm_moe_routing.md)
</details>

<details><summary><b>How does Speculative Decoding verify draft tokens in parallel?</b></summary>

Topic: Speculative Decoding
Key concepts:
- A small draft model generates $K$ tokens quickly (memory-efficient).
- The larger target model verifies all $K$ tokens in a single parallel forward pass (compute-bound).
- Rejection sampling accepts draft tokens with probability $\min(1, \frac{p(x)}{q(x)})$, recovering the exact target model probability distribution.
File: [llm_speculative_decoding.md](../../llm/llm_speculative_decoding.md)
</details>

<details><summary><b>What is LMCache, and how does it share KV caches across nodes?</b></summary>

Topic: LMCache Hierarchical KV Cache
Key concepts:
- LMCache extends local prefix caching to a global, hierarchical pool (GPU VRAM $\to$ CPU RAM $\to$ NVMe $\to$ object storage like S3).
- Nodes transfer and retrieve cached KV page blocks using RDMA to bypass local CPU/HBM copy bottlenecks.
- LMCache enables fast prefill/time-to-first-token (TTFT) for requests that hit globally cached prefixes.
File: [llm_lmcache.md](../../llm/llm_lmcache.md)
</details>

<details><summary><b>Why split prefill and decode (Disaggregated Serving)?</b></summary>

Topic: Disaggregated Serving (Prefill/Decode Split)
Key concepts:
- Prefill is compute-bound (large batch, high arithmetic intensity), while decode is memory-bound (batch size 1, low arithmetic intensity).
- Co-locating them on the same GPU causes scheduling conflicts and latency spikes.
- Disaggregated serving splits them onto dedicated prefill nodes and decode nodes, transferring intermediate KV caches via RDMA over high-speed networks.
File: [llm_disaggregated_serving.md](../../llm/llm_disaggregated_serving.md)
</details>

<details><summary><b>How does KTransformers offload weights to CPU DRAM without bottlenecks?</b></summary>

Topic: KTransformers Offload (AMX/AVX Expert Offloading)
Key concepts:
- Massive MoE models (e.g. DeepSeek-V3/671B) cannot fit in consumer GPU memory.
- KTransformers offloads sparse experts to CPU DRAM. It transfers only the activation tokens to the CPU, executing matrix multiplications locally using AVX/AMX instruction sets.
- This avoids transferring heavy expert weights to the GPU, minimizing PCIe bus bottlenecks.
File: [llm_ktransformers_offload.md](../../llm/llm_ktransformers_offload.md)
</details>

<details><summary><b>JAX vs PyTorch compilation flow? XLA compiler & Pallas?</b></summary>

Topic: JAX / XLA / TPU Compilation
Key concepts:
- PyTorch is eager by default. JAX traces python functions to construct an intermediate representation (Jaxpr), compiling it via XLA (Accelerated Linear Algebra).
- XLA performs operator fusion, eliminating memory read/write bottlenecks between adjacent layers.
- Pallas is JAX's low-level kernel language, enabling developers to write custom TPU kernels (like Splash Attention) in python.
File: [llm_jax_xla_tpu.md](../../llm/llm_jax_xla_tpu.md)
</details>

<details><summary><b>Streaming ASR/TTS optimization via Riva NIM</b></summary>

Topic: NVIDIA Conversational AI Stack
Key concepts:
- FastConformer downsamples audio 8x, speeding up streaming ASR.
- Riva NIM runs Triton Inference Server with compiled TensorRT-LLM and TensorRT-TTS pipelines, optimizing audio chunk queuing.
- Securing streaming speech requires low-latency guardrails (e.g. NeMo Guardrails) to filter PII and toxic speech in real-time.
File: [llm_nemo_riva_stack.md](../../llm/llm_nemo_riva_stack.md)
</details>

<details><summary><b>How do you design a streaming voice agent with &lt;500ms TTFA?</b></summary>

Topic: Low-Latency Voice Agent Architecture
Key concepts:
- Decouples ASR, LLM, and TTS into streaming queues. ASR streams audio chunks; the LLM streams token chunks (phrases) to the TTS.
- Voice Activity Detection (VAD) monitors user speech, triggering playback interrupts (barge-in) and clearing LLM prompt buffers in-flight.
- State synchronization uses async IPC to manage multi-turn history without blocking synthesis.
File: [llm_voice_agent_architecture.md](../../llm/llm_voice_agent_architecture.md)
</details>

<details><summary><b>Why are speech models memory-bound, and how do you calculate RTF?</b></summary>

Topic: Voice Agent Latency Profiling
Key concepts:
- Streaming TTS vocoders and LLM decode steps operate on tiny batch sizes ($L=1$), spending most time reading weight parameters from HBM (memory-bound).
- Real-Time Factor (RTF) measures throughput: $\text{RTF} = \frac{\text{Processing Time}}{\text{Audio Duration}}$. Production requires $\text{RTF} < 0.05$.
- Latency optimizations include weight-only quantization (FP8/INT4) and batching multiple streams.
File: [llm_latency_optimization.md](../../llm/llm_latency_optimization.md)
</details>

<details><summary><b>How do native Audio-Language Models differ from cascaded pipelines?</b></summary>

Topic: Multimodal Audio-Language Models
Key concepts:
- Cascaded pipelines (ASR $\to$ LLM $\to$ TTS) lose prosody, pitch, and emotion, and propagate errors across boundaries.
- Native Audio-Language Models (e.g., GPT-4o voice) ingest and output audio tokens directly using neural audio codecs.
- Residual Vector Quantization (RVQ) quantizes audio waveforms into discrete tokens for joint text-audio attention.
File: [llm_multimodal_audio.md](../../llm/llm_multimodal_audio.md)
</details>

<details><summary><b>What metrics evaluate voice agents under network jitter and packet loss?</b></summary>

Topic: Voice Agent Benchmarking & Evaluation
Key concepts:
- Speech quality metrics include PESQ (objective speech quality, -0.5 to 4.5), POLQA (successor to PESQ, 1.0 to 4.75), and ViSQOL.
- Performance under network stress is measured by tracking TTFA percentiles under simulated packet loss and jitter.
- LLM-as-a-judge models assess conversational flow and barge-in responsiveness dynamically.
File: [llm_agent_benchmarking.md](../../llm/llm_agent_benchmarking.md)
</details>

---

[Flashcard Index](../README.md)
