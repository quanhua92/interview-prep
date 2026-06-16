# LLM Training, Fine-Tuning & Post-Training Engineer — Multi-Day Learning Path

> State of the art as of **June 2026**. Researched via multi-agent web survey (pre-training, fine-tuning, post-training, eval/serving).

## Who this is for

Senior engineers pivoting into an **LLM training role** — e.g. *Fullstack LLM Engineer (Pre-training & Post-training)*. The author's context: Senior AI Engineer (10+ yrs CV / production ML), strong Python/Rust/fullstack, **light direct experience training LLMs**. This path closes that gap fast.

## Core philosophy — OFF-THE-SHELF FIRST

> **We do NOT pre-train models from scratch.** Pre-training a frontier base costs $10M–$100M+ and thousands of GPUs. At any realistic startup budget ($3.5k/mo roles included), nobody pre-trains.

Instead we **stand on open base models + the mature OSS training/serving stack**:

```
                ┌─────────────────────────────────────────────────┐
   DON'T DO →   │  Pre-train from scratch                          │
                └─────────────────────────────────────────────────┘
                ┌─────────────────────────────────────────────────┐
   START HERE → │  Open base model (Qwen3 / Llama 4 / DeepSeek)    │
                └─────────────────────────────────────────────────┘
                       │
            ┌──────────┴───────────┐
            ▼                      ▼
     Continued Pre-train        SFT  ←── the skill you ship
     (optional, rare)           (Unsloth + QLoRA)
                                       │
                                       ▼
                          Post-train: DPO / GRPO / RLVR
                                       │
                                       ▼
                          Eval (judge + gold set) → Serve (vLLM)
```

**The skill that pays = data curation + fine-tuning + eval + serving**, executed with mature tools. Framework internals are *not* the differentiator — **data quality and eval rigor are.**

---

## 2026 SOTA snapshot (what's current)

| Area | What's dominant in mid-2026 |
|---|---|
| **Architecture** | Decoder-only transformer still king. **MoE is mainstream** for big models (DeepSeek V3/V4, Llama 4 Scout/Maverick, Qwen3, GLM-5). Hybrid **SSM+attention** (Mamba-3, Gated DeltaNet) emerging for long context. |
| **Tokenizer** | **Byte-level BPE** universal (`tokenizers`, `tiktoken`). No challenger algorithm. |
| **Pre-train objective** | Next-token prediction, now followed by a distinct **"mid-training"** capability-shaping stage. |
| **Scaling** | Chinchilla holds in theory; **everyone overtrains** (smaller model, more tokens) for cheaper inference. |
| **Fine-tuning default** | **QLoRA (4-bit) + LoRA** on all 7 linear modules. **DoRA / PiSSA** for a quality bump. |
| **Hero tool (single GPU)** | **Unsloth** — 2× faster, ~70% less VRAM, notebook-first, free on Colab. Unsloth Studio is now an open-source local web UI. |
| **Post-training** | **DPO displaced RLHF** for preferences; **GRPO + RLVR** power the reasoning-model revolution (DeepSeek-R1, Qwen3-thinking). **REINFORCE++/RLOO** are stable GRPO variants; **AsyncGRPO** solves scale stalls. |
| **Eval** | Public benchmarks saturating; **LLM-as-judge + domain gold set** is what production teams actually run. New 2026 frontier benchmarks: **HLE, APEX-Agents, τ²-bench**. |
| **Serving** | **vLLM v0.23+** (default), **SGLang** (prefix-cache), **Ollama/llama.cpp** (local), 4-bit quant standard. **P-EAGLE** (parallel drafting) stacks up to 1.69× on top of EAGLE-3. |

---

## The off-the-shelf stack (what you use at each stage)

| Stage | Tool(s) | Why |
|---|---|---|
| **Base model** | Qwen3 / Llama 4 / DeepSeek-R1-Distill / Mistral / Gemma | Best open-weight starting points; broad size range |
| **Data** | `datasets`, `distilabel`, Unsloth synthetic-data notebook | Build/curate instruction pairs |
| **SFT + PEFT** | **Unsloth** (hero) + TRL `SFTTrainer` + `peft` (LoRA/DoRA/PiSSA) | Fast, low-VRAM, single-GPU |
| **Post-train** | TRL (`DPOTrainer`/`GRPOTrainer`), Unsloth (DPO), `verl`/OpenRLHF (scale) | DPO for prefs, GRPO+RLVR for reasoning |
| **Eval** | `lm-evaluation-harness`, LLM-as-judge (strong model), domain gold set, Promptfoo/Braintrust | Benchmarks + product eval |
| **Serve** | **vLLM** (prod), **SGLang**, **Ollama** (local), quantize GGUF/AWQ | From local dev to multi-GPU prod |
| **Observe** | **Langfuse** / Arize Phoenix | Tracing + live eval + cost/latency |

---

## 7-day learning path

Read top-to-bottom. Each day: **objectives → concepts (SOTA-aware) → hands-on exercise → checklist → "what to explain in interview."** Time-boxed; assumes you already know Python + PyTorch basics + ML/DL fundamentals.

| Day | File | Objective | Time | Hands-on |
|:--:|---|---|:--:|---|
| 1 | [day1_foundations.md](day1_foundations.md) | The LLM lifecycle mental model; what to *grok, not build*; the OSS stack map; tokenization | ~3h | Run an Unsloth notebook as-is on free Colab |
| 2 | [day2_data_engineering.md](day2_data_engineering.md) | Build an SFT dataset: chat templates, formats, synthetic generation, quality rules | ~4h | Format ~1k aipriceaction QA pairs into ChatML JSONL |
| 3 | [day3_finetuning_unsloth.md](day3_finetuning_unsloth.md) | **HERO:** SFT + QLoRA with Unsloth; LoRA family (DoRA/PiSSA/rsLoRA); hyperparams | ~6h | Fine-tune Qwen3 on your Day-2 data |
| 4 | [day4_posttraining.md](day4_posttraining.md) | DPO / GRPO / RLVR; preference data; the reasoning-model revolution | ~4h | Run a DPO via TRL on preference pairs |
| 5 | [day5_evaluation.md](day5_evaluation.md) | Benchmarks, LLM-as-judge, domain gold set, eval-driven dev | ~4h | Build a 100-example gold set; before/after eval |
| 6 | [day6_serving.md](day6_serving.md) | Quantization, vLLM/SGLang/Ollama, deployment, observability | ~3h | Export GGUF → Ollama; serve with vLLM |
| 7 | [day7_capstone.md](day7_capstone.md) | **End-to-end:** SFT + eval + serve a domain model | ~6h | Ship a financial-analysis fine-tune w/ eval + endpoint |

**Companion files:** [resources.md](resources.md) · [interview_qa.md](interview_qa.md) · [tools_cheatsheet.md](tools_cheatsheet.md)

---

## How this maps: JD requirement → day → your CV

| JD requirement | Covered in | Your CV evidence | Verdict |
|---|---|---|---|
| 3+ yrs Python SWE | (given) | 10+ yrs; SDK, CLI, Lambda | ✅ Strong |
| **LLM training/fine-tuning/eval** | Days 1,3,4,5 | None yet → **Days 3+7 produce the proof** | ❌→✅ Bridge |
| ML/DL fundamentals | Day 1 | DL book co-author, 3D recon, patent | ✅ Strong |
| PyTorch / HuggingFace | Days 1,3 | PyTorch listed → add HF | ⚠️ Add HF |
| Production-grade apps | Day 6 | Rust backend, AWS Lambda/S3/ECS | ✅ Strong |
| Cloud + scalable infra | Day 6 | AWS, Docker, CI/CD | ✅ Strong |
| Distributed training (nice) | Day 3 ref | — | Optional |
| RLHF/DPO/alignment (nice) | Day 4 | — → Day 4 + capstone | ❌→✅ |
| RAG / agents / multimodal (nice) | (existing) | Multi-agent pipeline, tool-LLMs, CV | ✅ Strong |

**The single highest-ROI move:** finish Day 3 + Day 7 → you can honestly say *"I fine-tuned Qwen3 with QLoRA via Unsloth on domain data and evaluated it with an LLM-as-judge gold set, improving domain accuracy from X% to Y%."*

---

## Prerequisites

- **Python** (strong), **PyTorch** basics, **ML/DL fundamentals** — you already have these.
- A single GPU for hands-on: **free Colab T4/L4** works for 7B QLoRA, or a local RTX (12GB+).
- HF account (free) for `push_to_hub`.

## How to use

1. Skim this README fully (the mental model + stack map).
2. Do Day 1 → 7 in order; each builds on the last and feeds the Day 7 capstone.
3. Keep [interview_qa.md](interview_qa.md) open and answer questions **out loud** after each day.
4. The Day 7 capstone becomes your portfolio artifact + interview talking point.
