# LLM Systems Interview Prep — TODO & Subagent Plan

## Overview

This directory (`popular/llm/`) contains **34 interview-style Markdown guides** covering
LLM internals, serving infrastructure, and distributed training — all written in the
same detailed teaching style as the tier coding guides (Metadata header, Concept
explanation, Worked examples, Complexity/tradeoffs table, Follow-up Q&A, Pro-tips).

**Sources combined:**
- `/Users/quan/workspace/tutorials/llm/` — 29 deep-dive tutorials (`.md` + `.py` with
  verified numbers)
- `/Users/quan/workspace/interview-prep/popular/speech_llm_*.md` — 5 existing voice/LLM
  system-design guides

---

## Module Structure & Learning Progression

```
Module 1: Transformer Foundations      (5 topics)  — normalization → tokenization → attention → positional encoding → MLP
Module 2: Memory & Attention Efficiency (5 topics)  — causal mask → KV cache → flash attention → GQA → quantization
Module 3: Inference & Serving Stack    (6 topics)  — sampling → paged attention → block manager → scheduler → prefix cache → CUDA graphs
Module 4: Fine-tuning & Adaptation    (2 topics)  — LoRA/PEFT → gradient checkpointing
Module 5: Distributed Training        (5 topics)  — NCCL → DDP → tensor parallel → pipeline parallel → ZeRO
Module 6: Advanced Serving & Scale    (6 topics)  — MoE routing → speculative decoding → LMCache → disaggregated serving → KTransformers offload → JAX/XLA/TPU
Module 7: Voice & Speech LLM Systems  (5 topics)  — NeMo/Riva stack → voice agent architecture → latency optimization → multimodal audio → agent benchmarking
```

**Total: 34 guides**

---

## Output File Naming Convention

Each guide is named: `llm_<topic>.md`  (lowercase, underscores, no number prefix)

| # | Output File | Source | Module |
|---|---|---|---|
| 1 | `llm_normalization.md` | `tutorials/llm/NORMALIZATION.md` + `.py` | M1 |
| 2 | `llm_tokenization.md` | `tutorials/llm/TOKENIZATION.md` + `.py` | M1 |
| 3 | `llm_rope.md` | `tutorials/llm/ROPE.md` + `ABSOLUTE_PE.md` + `.py` | M1 |
| 4 | `llm_mlp_activation.md` | `tutorials/llm/MLP_ACTIVATION.md` + `.py` | M1 |
| 5 | `llm_causal_mask.md` | `tutorials/llm/CAUSAL_MASK.md` + `.py` | M1 |
| 6 | `llm_kv_cache.md` | `tutorials/llm/KV_CACHE.md` + `.py` | M2 |
| 7 | `llm_flash_attention.md` | `tutorials/llm/FLASH_ATTENTION.md` + `.py` | M2 |
| 8 | `llm_gqa.md` | `tutorials/llm/GQA.md` + `.py` | M2 |
| 9 | `llm_quantization.md` | `tutorials/llm/QUANTIZATION.md` + `.py` | M2 |
| 10 | `llm_sampling.md` | `tutorials/llm/SAMPLING.md` + `.py` | M3 |
| 11 | `llm_paged_attention.md` | `tutorials/llm/PAGED_ATTENTION.md` + `.py` | M3 |
| 12 | `llm_block_manager.md` | `tutorials/llm/BLOCK_MANAGER.md` + `.py` | M3 |
| 13 | `llm_scheduler.md` | `tutorials/llm/SCHEDULER.md` + `.py` | M3 |
| 14 | `llm_prefix_cache.md` | `tutorials/llm/PREFIX_CACHE.md` + `.py` | M3 |
| 15 | `llm_cuda_graphs.md` | `tutorials/llm/CUDA_GRAPHS.md` + `.py` | M3 |
| 16 | `llm_peft_lora.md` | `tutorials/llm/PEFT_LORA.md` + `.py` | M4 |
| 17 | `llm_gradient_checkpointing.md` | `tutorials/llm/GRADIENT_CHECKPOINTING.md` + `.py` | M4 |
| 18 | `llm_nccl_collectives.md` | `tutorials/llm/NCCL_COLLECTIVES.md` + `.py` | M5 |
| 19 | `llm_ddp.md` | `tutorials/llm/DDP.md` + `.py` | M5 |
| 20 | `llm_tensor_parallel.md` | `tutorials/llm/TENSOR_PARALLEL.md` + `.py` | M5 |
| 21 | `llm_pipeline_parallel.md` | `tutorials/llm/PIPELINE_PARALLEL.md` + `.py` | M5 |
| 22 | `llm_zero.md` | `tutorials/llm/ZERO.md` + `.py` | M5 |
| 23 | `llm_moe_routing.md` | `tutorials/llm/MOE_ROUTING.md` + `.py` | M6 |
| 24 | `llm_speculative_decoding.md` | `tutorials/llm/SPECULATIVE_DECODING.md` + `.py` | M6 |
| 25 | `llm_lmcache.md` | `tutorials/llm/LMCACHE.md` + `.py` | M6 |
| 26 | `llm_disaggregated_serving.md` | `tutorials/llm/DISAGGREGATED_SERVING.md` + `.py` | M6 |
| 27 | `llm_ktransformers_offload.md` | `tutorials/llm/KTRANSFORMERS_OFFLOAD.md` + `.py` | M6 |
| 28 | `llm_jax_xla_tpu.md` | `tutorials/llm/JAX_XLA_TPU.md` + `.py` | M6 |
| 29 | `llm_nemo_riva_stack.md` | `popular/speech_llm_nemo_riva_stack.md` | M7 |
| 30 | `llm_voice_agent_architecture.md` | `popular/speech_llm_voice_agent_architecture.md` | M7 |
| 31 | `llm_latency_optimization.md` | `popular/speech_llm_latency_optimization.md` | M7 |
| 32 | `llm_multimodal_audio.md` | `popular/speech_llm_multimodal_audio_language_models.md` | M7 |
| 33 | `llm_agent_benchmarking.md` | `popular/speech_llm_agent_benchmarking_evaluation.md` | M7 |
| 34 | `llm_distributed_gpu_training.md` | `popular/system_design_distributed_gpu_training.md` | M5 |

---

## Output Format (per guide)

Every `.md` MUST follow this exact template — same style as the tier coding guides:

```markdown
# <Topic Full Name>

- **Category**: LLM Systems
- **Difficulty**: <Easy | Medium | Hard | Expert>
- **Target Role**: <e.g. LLM Inference Engineer / ML Systems Engineer>
- **Source**: <e.g. vLLM paper, Attention is All You Need, etc.>

---

## Concept Overview

<3–5 sentence plain-English explanation. Use analogies first, then formulas.>

### The Problem It Solves
<What breaks without this? Include concrete numbers.>

### How It Works
<Step-by-step narrative. Include mermaid diagram where helpful.>

---

## Worked Example

<Concrete numbers taken verbatim from the tutorials/llm source .py output or the speech_llm guide.>
<Include tables showing before/after.>

---

## Complexity & Trade-offs

| Metric | Value | Notes |
|---|---|---|
| ... | ... | ... |

---

## Common Interview Questions & How to Answer

### Q1: ...
- **Answer**: ...

### Q2: ...
- **Answer**: ...

---

## Pro-Tip: How to Impress the Interviewer

- ...
```

---

## Subagent Boundaries — 7 Parallel Workers

Each subagent handles exactly ONE module (clearly bounded, no overlap).
Subagents read source files, synthesize, and write output files independently.

---

### SUBAGENT 1 — Module 1: Transformer Foundations
**Files to write (5):**
- `llm_normalization.md`
- `llm_tokenization.md`
- `llm_rope.md`  ← merge ROPE.md + ABSOLUTE_PE.md
- `llm_mlp_activation.md`
- `llm_causal_mask.md`

**Sources to read:**
```
/Users/quan/workspace/tutorials/llm/NORMALIZATION.md
/Users/quan/workspace/tutorials/llm/normalization.py
/Users/quan/workspace/tutorials/llm/TOKENIZATION.md
/Users/quan/workspace/tutorials/llm/tokenization.py
/Users/quan/workspace/tutorials/llm/ROPE.md
/Users/quan/workspace/tutorials/llm/ABSOLUTE_PE.md
/Users/quan/workspace/tutorials/llm/rope.py
/Users/quan/workspace/tutorials/llm/MLP_ACTIVATION.md
/Users/quan/workspace/tutorials/llm/mlp_activation.py
/Users/quan/workspace/tutorials/llm/CAUSAL_MASK.md
/Users/quan/workspace/tutorials/llm/causal_mask.py
```
**Output dir:** `/Users/quan/workspace/interview-prep/popular/llm/`

---

### SUBAGENT 2 — Module 2: Memory & Attention Efficiency
**Files to write (4):**
- `llm_kv_cache.md`
- `llm_flash_attention.md`
- `llm_gqa.md`
- `llm_quantization.md`

**Sources to read:**
```
/Users/quan/workspace/tutorials/llm/KV_CACHE.md
/Users/quan/workspace/tutorials/llm/kv_cache.py
/Users/quan/workspace/tutorials/llm/FLASH_ATTENTION.md
/Users/quan/workspace/tutorials/llm/flash_attention.py
/Users/quan/workspace/tutorials/llm/GQA.md
/Users/quan/workspace/tutorials/llm/gqa.py
/Users/quan/workspace/tutorials/llm/QUANTIZATION.md
/Users/quan/workspace/tutorials/llm/quantization.py
```
**Output dir:** `/Users/quan/workspace/interview-prep/popular/llm/`

---

### SUBAGENT 3 — Module 3: Inference & Serving Stack
**Files to write (6):**
- `llm_sampling.md`
- `llm_paged_attention.md`
- `llm_block_manager.md`
- `llm_scheduler.md`
- `llm_prefix_cache.md`
- `llm_cuda_graphs.md`

**Sources to read:**
```
/Users/quan/workspace/tutorials/llm/SAMPLING.md
/Users/quan/workspace/tutorials/llm/sampling.py
/Users/quan/workspace/tutorials/llm/PAGED_ATTENTION.md
/Users/quan/workspace/tutorials/llm/paged_attention.py
/Users/quan/workspace/tutorials/llm/BLOCK_MANAGER.md
/Users/quan/workspace/tutorials/llm/block_manager.py
/Users/quan/workspace/tutorials/llm/SCHEDULER.md
/Users/quan/workspace/tutorials/llm/scheduler.py
/Users/quan/workspace/tutorials/llm/PREFIX_CACHE.md
/Users/quan/workspace/tutorials/llm/prefix_cache.py
/Users/quan/workspace/tutorials/llm/CUDA_GRAPHS.md
/Users/quan/workspace/tutorials/llm/cuda_graphs.py
```
**Output dir:** `/Users/quan/workspace/interview-prep/popular/llm/`

---

### SUBAGENT 4 — Module 4: Fine-tuning & Adaptation + Module 5 Part A
**Files to write (4):**
- `llm_peft_lora.md`
- `llm_gradient_checkpointing.md`
- `llm_nccl_collectives.md`
- `llm_ddp.md`

**Sources to read:**
```
/Users/quan/workspace/tutorials/llm/PEFT_LORA.md
/Users/quan/workspace/tutorials/llm/peft_lora.py
/Users/quan/workspace/tutorials/llm/GRADIENT_CHECKPOINTING.md
/Users/quan/workspace/tutorials/llm/gradient_checkpointing.py
/Users/quan/workspace/tutorials/llm/NCCL_COLLECTIVES.md
/Users/quan/workspace/tutorials/llm/nccl_collectives.py
/Users/quan/workspace/tutorials/llm/DDP.md
/Users/quan/workspace/tutorials/llm/ddp.py
```
**Output dir:** `/Users/quan/workspace/interview-prep/popular/llm/`

---

### SUBAGENT 5 — Module 5 Part B: Distributed Training
**Files to write (4):**
- `llm_tensor_parallel.md`
- `llm_pipeline_parallel.md`
- `llm_zero.md`
- `llm_distributed_gpu_training.md`

**Sources to read:**
```
/Users/quan/workspace/tutorials/llm/TENSOR_PARALLEL.md
/Users/quan/workspace/tutorials/llm/tensor_parallel.py
/Users/quan/workspace/tutorials/llm/PIPELINE_PARALLEL.md
/Users/quan/workspace/tutorials/llm/pipeline_parallel.py
/Users/quan/workspace/tutorials/llm/ZERO.md
/Users/quan/workspace/tutorials/llm/zero.py
/Users/quan/workspace/interview-prep/popular/system_design_distributed_gpu_training.md
```
**Output dir:** `/Users/quan/workspace/interview-prep/popular/llm/`

---

### SUBAGENT 6 — Module 6: Advanced Serving & Scale
**Files to write (6):**
- `llm_moe_routing.md`
- `llm_speculative_decoding.md`
- `llm_lmcache.md`
- `llm_disaggregated_serving.md`
- `llm_ktransformers_offload.md`
- `llm_jax_xla_tpu.md`

**Sources to read:**
```
/Users/quan/workspace/tutorials/llm/MOE_ROUTING.md
/Users/quan/workspace/tutorials/llm/moe_routing.py
/Users/quan/workspace/tutorials/llm/SPECULATIVE_DECODING.md
/Users/quan/workspace/tutorials/llm/speculative_decoding.py
/Users/quan/workspace/tutorials/llm/LMCACHE.md
/Users/quan/workspace/tutorials/llm/lmcache.py
/Users/quan/workspace/tutorials/llm/DISAGGREGATED_SERVING.md
/Users/quan/workspace/tutorials/llm/disaggregated_serving.py
/Users/quan/workspace/tutorials/llm/KTRANSFORMERS_OFFLOAD.md
/Users/quan/workspace/tutorials/llm/ktransformers_offload.py
/Users/quan/workspace/tutorials/llm/JAX_XLA_TPU.md
/Users/quan/workspace/tutorials/llm/jax_xla_tpu.py
```
**Output dir:** `/Users/quan/workspace/interview-prep/popular/llm/`

---

### SUBAGENT 7 — Module 7: Voice & Speech LLM Systems
**Files to write (5):**
- `llm_nemo_riva_stack.md`
- `llm_voice_agent_architecture.md`
- `llm_latency_optimization.md`
- `llm_multimodal_audio.md`
- `llm_agent_benchmarking.md`

**Sources to read:**
```
/Users/quan/workspace/interview-prep/popular/speech_llm_nemo_riva_stack.md
/Users/quan/workspace/interview-prep/popular/speech_llm_voice_agent_architecture.md
/Users/quan/workspace/interview-prep/popular/speech_llm_latency_optimization.md
/Users/quan/workspace/interview-prep/popular/speech_llm_multimodal_audio_language_models.md
/Users/quan/workspace/interview-prep/popular/speech_llm_agent_benchmarking_evaluation.md
```
**Output dir:** `/Users/quan/workspace/interview-prep/popular/llm/`

---

## Verification Checklist (after all subagents complete)

For each of the 34 output files, verify:
- [ ] Has correct metadata header (Category, Difficulty, Target Role, Source)
- [ ] Has "Concept Overview" with plain-English analogy first
- [ ] Has "The Problem It Solves" with concrete numbers
- [ ] Has "Worked Example" section with real values (not hand-waved)
- [ ] Has "Complexity & Trade-offs" table
- [ ] Has at least 2 "Interview Questions" with answers
- [ ] Has "Pro-Tip" section
- [ ] No hallucinated numbers — values sourced from `.py` outputs or source `.md`

## Status Tracking

| # | File | Subagent | Status |
|---|---|---|---|
| 1 | `llm_normalization.md` | SA-1 | ⬜ TODO |
| 2 | `llm_tokenization.md` | SA-1 | ⬜ TODO |
| 3 | `llm_rope.md` | SA-1 | ⬜ TODO |
| 4 | `llm_mlp_activation.md` | SA-1 | ⬜ TODO |
| 5 | `llm_causal_mask.md` | SA-1 | ⬜ TODO |
| 6 | `llm_kv_cache.md` | SA-2 | ⬜ TODO |
| 7 | `llm_flash_attention.md` | SA-2 | ⬜ TODO |
| 8 | `llm_gqa.md` | SA-2 | ⬜ TODO |
| 9 | `llm_quantization.md` | SA-2 | ⬜ TODO |
| 10 | `llm_sampling.md` | SA-3 | ⬜ TODO |
| 11 | `llm_paged_attention.md` | SA-3 | ⬜ TODO |
| 12 | `llm_block_manager.md` | SA-3 | ⬜ TODO |
| 13 | `llm_scheduler.md` | SA-3 | ⬜ TODO |
| 14 | `llm_prefix_cache.md` | SA-3 | ⬜ TODO |
| 15 | `llm_cuda_graphs.md` | SA-3 | ⬜ TODO |
| 16 | `llm_peft_lora.md` | SA-4 | ⬜ TODO |
| 17 | `llm_gradient_checkpointing.md` | SA-4 | ⬜ TODO |
| 18 | `llm_nccl_collectives.md` | SA-4 | ⬜ TODO |
| 19 | `llm_ddp.md` | SA-4 | ⬜ TODO |
| 20 | `llm_tensor_parallel.md` | SA-5 | ⬜ TODO |
| 21 | `llm_pipeline_parallel.md` | SA-5 | ⬜ TODO |
| 22 | `llm_zero.md` | SA-5 | ⬜ TODO |
| 23 | `llm_distributed_gpu_training.md` | SA-5 | ⬜ TODO |
| 24 | `llm_moe_routing.md` | SA-6 | ⬜ TODO |
| 25 | `llm_speculative_decoding.md` | SA-6 | ⬜ TODO |
| 26 | `llm_lmcache.md` | SA-6 | ⬜ TODO |
| 27 | `llm_disaggregated_serving.md` | SA-6 | ⬜ TODO |
| 28 | `llm_ktransformers_offload.md` | SA-6 | ⬜ TODO |
| 29 | `llm_jax_xla_tpu.md` | SA-6 | ⬜ TODO |
| 30 | `llm_nemo_riva_stack.md` | SA-7 | ⬜ TODO |
| 31 | `llm_voice_agent_architecture.md` | SA-7 | ⬜ TODO |
| 32 | `llm_latency_optimization.md` | SA-7 | ⬜ TODO |
| 33 | `llm_multimodal_audio.md` | SA-7 | ⬜ TODO |
| 34 | `llm_agent_benchmarking.md` | SA-7 | ⬜ TODO |
