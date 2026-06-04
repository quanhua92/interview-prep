# LLMOps & Deployment Playbook

## 1. GPU Sizing Math & Memory Bottlenecks

**Total VRAM = Model Weights + KV Cache**

**Model Weights (Fixed):**
- Formula: `Parameters (in billions) × Bytes per parameter`
- FP16/BF16: 2 bytes/param (70B model = 140 GB)
- INT8: 1 byte/param (70B model = 70 GB)
- INT4: 0.5 bytes/param (70B model = 35 GB)

**KV Cache (Dynamic):**
- The KV cache scales linearly with batch size and sequence length. For long-context workloads (e.g., 32k+ tokens), the KV cache can easily dwarf the model weights.
- **KV Cache Formula (bytes per token):** `2 (for K & V) × Number of Layers × Number of Attention Heads × Head Dimension × Bytes per parameter`
- Always budget for your *maximum* expected concurrent tokens across all active requests.
- **Overhead:** Always reserve a buffer (e.g., 2-4GB) for CUDA context and forward pass activations.

## 2. Inference Optimization

- **Continuous Batching:** Treats inference as an iterative process. As soon as one request finishes, the scheduler injects a new one into that slot. Increases throughput 2-4x over static batching.
- **PagedAttention (vLLM):** Manages KV cache memory like an OS manages RAM, reducing memory fragmentation from ~60-80% to <4%. Allows fitting much larger batches.

## 3. Deployment Strategies

- **Canary Deployments:** Route a small percentage (e.g., 5%) of production traffic to a new LLM version or prompt. Monitor token usage, latency, and error rates before full rollout.
- **Shadow Deployments:** Route a copy of production traffic to both the existing "stable" model and the "challenger" model. Only the stable model returns a response to the user. Compare outputs to validate the challenger safely.

## 4. Observability & Tracing

- **OpenTelemetry (OTel):** The universal standard for distributed tracing.
- **OpenInference:** Provides semantic conventions (standardized attributes) for AI-specific workloads on top of OTel.
  - Span kinds: `LLM`, `RETRIEVER`, `TOOL`, `GUARDRAIL`.
  - Captures token usage, model names, and retrieval similarity scores.
- **Data Governance:** Capturing full prompts helps debugging but creates PII risks. Implement redaction and sampling policies at the OTel Collector level.
- **Context Management:** Explicitly pass session-level context in agentic workflows so multi-turn conversations form a single logical trace.
