# Day 1 — The LLM Lifecycle & What to Grok (Not Build)

> Map the full LLM lifecycle, understand which stages you own vs only grok, and run your first end-to-end fine-tune.

## Objectives
- Internalize the 5-stage LLM lifecycle as a single mental model.
- Know which stages you **do** vs which you only **understand** (and why).
- Grok transformers, MoE, tokenization, and scaling laws without reimplementing them.
- Map the mature OSS stack you will actually use at each stage.
- Leave with a working fine-tune behind you (Unsloth notebook on free Colab).

## Concepts

### The 5-stage lifecycle

Every modern LLM is produced by the same pipeline. The boundaries between stages are real and they determine who does what.

```
                      STAGE 0 (pre-train)  — YOU DON'T DO
   trillions of tokens → next-token loss → base model weights
   cost: $10M–$100M+, thousands of GPUs, months of compute
                              │
                              ▼
                      STAGE 1 (mid-training)  — YOU DON'T DO (but understand)
   capability shaping: reasoning / code / math / long-CoT data
   blends the raw base toward "useful" before alignment
                              │
                              ▼
       ┌──────────────────────────────────────────────────┐
       │  STAGE 2 (SFT)  ─────────────────── YOU DO       │
       │  supervised pairs (instruction → response)        │
       │  Unsloth + TRL SFTTrainer + QLoRA                │
       └──────────────────────────────────────────────────┘
                              │
                              ▼
       ┌──────────────────────────────────────────────────┐
       │  STAGE 3 (post-train / alignment) ── YOU DO      │
       │  DPO (preferences) / GRPO + RLVR (reasoning)     │
       └──────────────────────────────────────────────────┘
                              │
                              ▼
       ┌──────────────────────────────────────────────────┐
       │  STAGE 4 (eval + serve) ──────────── YOU DO      │
       │  lm-eval-harness + judge + gold set → vLLM       │
       └──────────────────────────────────────────────────┘
```

| Stage | Input | Output | Who | Why |
|---|---|---|---|---|
| Pre-train | Web-scale text (5T–50T tokens) | Base model (raw next-token predictor) | Big labs | $10M+; one company amortizes across everyone |
| Mid-training | Curated reasoning/code/math/long-CoT corpora | Capability-shaped base | Big labs | The step that separates "raw" from "useful" bases |
| **SFT** | Instruction pairs (few hundred → tens of thousands) | Instruction-following model | **You** | This is where domain knowledge and tone get baked in |
| **Post-train** | Preference pairs / verifiable-reward rollouts | Aligned, reasoning-tuned model | **You** | DPO for style/safety; GRPO+RLVR for reasoning |
| **Eval + Serve** | Benchmarks + gold set + judge | Shipped model behind an endpoint | **You** | Without eval you cannot claim improvement; without serving nobody uses it |

The key insight for a pivoting senior engineer: **you start at stage 2, always.** Everything you ship is some combination of *open base → SFT → optional post-train → eval → serve*. Pre-training is purely intellectual context.

### Architectures — grok, don't build

You will never hand-write a transformer. You will absolutely need to reason about one when picking a model, debugging a fine-tune, or sizing a serving budget. Here is what matters for a practitioner.

**The decoder-only causal transformer is still dominant.** Every modern open base (Qwen3, Llama 4, DeepSeek V3/V4, Mistral, Gemma, Phi-4) is autoregressive: predict token *t+1* given *t...t*. The modernized internals are uniform enough to treat as a recipe:

| Component | What it is (one line) | Why a practitioner cares |
|---|---|---|
| **Pre-norm + RMSNorm** | Normalize inputs (not outputs); RMSNorm drops the mean term | Standard; BF16 stability; you do not touch it |
| **RoPE** (rotary positional embedding) | Injects position via rotations, not learned absolute IDs | Extends context cheaply; you may set `rope_scaling` to lengthen context at fine-tune time |
| **SwiGLU MLP** | Gated feed-forward (GLU variant); ~the universal MLP now | Affects parameter accounting; MoE experts are SwiGLU blocks |
| **KV cache** | Cache keys/values of past tokens so generation is O(1) per step | Single biggest serving throughput knob; vLLM/SGLang are KV-cache engines |
| **GQA** (grouped-query attention) | Share K/V heads across Q heads | Reduces KV-cache size → more concurrent requests; universal on new models |

**MoE is now mainstream for big models.** Mixture-of-Experts replaces the dense MLP with N experts and routes each token to the top-k (usually 2) experts. The two numbers that matter:

```
total params        = all experts + shared layers  (memory footprint)
active params/token = only the routed experts      (FLOPs / token)
```

| Model | Total / Active | Note |
|---|---|---|
| DeepSeek V3 / V4 | 671B / 37B | Fine-grained experts + shared expert |
| Llama 4 Scout | 109B / 17B | 16 experts, 10M token context window |
| Llama 4 Maverick | 400B / 17B | 128 experts, 1M token context |
| Qwen3 (235B MoE) | 235B / 22B | Apache 2.0; Qwen3.6/3.7 sub-series extend this |
| Qwen3.6 / 3.7 (MoE) | 36B–480B / small active | "Agent Frontier" series released April–May 2026 |
| GLM-5 | large total / small active | Strong open MoE |

Why this matters to you: an MoE model's *active* params decide its fine-tune cost and inference latency; its *total* params decide the VRAM you need to load it. A 671B/37B model is roughly as cheap to *run* per token as a 40B dense model — but you still need ~700B params worth of memory (or quantization) to host it.

**Hybrid SSM+attention is emerging for long context.** Pure attention scales O(n²) in sequence length; state-space models (SSMs) scale O(n) by carrying a compressed state. The 2026 frontier blends them: **Mamba-3, Gated DeltaNet, Nemotron 3 Super** interleave SSM layers (cheap long context) with attention layers (precise recall). For most fine-tuning jobs in the near term you will still be on attention-only or MoE models, but hybrid architectures increasingly appear in the base models you consume.

**The practitioner takeaway:** you do not build any of this. You do need to understand it because architecture dictates **context length, throughput, quantization behavior, and serving cost** — the four numbers that decide whether your fine-tune ships.

### Tokenization

A tokenizer maps text → integer token IDs (and back). The model never sees text. Everything you ship is gated by token economics.

**Byte-level BPE is universal.** No serious challenger algorithm exists in 2026.

| Tool | Used by | Notes |
|---|---|---|
| HF `tokenizers` (Rust core) | Qwen, Llama, Mistral, Gemma, Phi | The de-facto open standard; `PreTrainedTokenizerFast` |
| `tiktoken` | OpenAI, many derivative APIs | Fast, byte-level BPE, plain library |
| `SentencePiece` | older Llama, T5, some Asian-language models | Still around; newer models mostly moved to byte-level BPE |

Why byte-level: it eliminates out-of-vocabulary tokens entirely. Any UTF-8 byte (Vietnamese diacritics, emoji, code, mixed scripts) decomposes to a known byte sequence even before BPE merges learn it. Vocabulary sizes in 2026 sit at **65k–250k**; larger vocabularies compress common text into fewer tokens (cheaper inference) at the cost of a bigger embedding matrix.

Why tokenization matters to a fine-tuning engineer:

1. **Cost is denominated in tokens.** Training FLOPs and inference $ are both per-token. A tokenizer that uses 1.3× more tokens for your language means 1.3× the bill.
2. **Edge cases live at the tokenizer.** Trailing spaces, code indentation, CJK tokenization, leading whitespace — all classic sources of "the model works on my prompt but not in prod."
3. **The tokenizer is part of the model.** You cannot fine-tune a base with one tokenizer and serve it with another. Same checkpoint = same tokenizer = same chat template (Day 2).

You will *use* tokenizers via `tokenizer = AutoTokenizer.from_pretrained(...)`. You will never train one from scratch in this role.

### Scaling laws (theory vs practice)

**Chinchilla (2022):** for compute-optimal training, scale tokens and parameters roughly equally — about **20 tokens per parameter**. A 70B model would be "optimal" at ~1.4T tokens.

**What everyone actually does in 2026:** massively overtrain. Llama 3 70B trained on ~15T tokens (~200 tokens/param, ~10× Chinchilla). Qwen3, Gemma, Phi families all do the same.

Why the deliberate "inefficiency"? **Inference cost dominates.** A model is trained once but served billions of times. A smaller, heavily overtrained model is cheaper to host per token while matching a Chinchilla-optimal larger model on quality. The economics flipped the rule:

| Theory (Chinchilla) | Practice (2026) |
|---|---|
| ~20 tokens / param | ~100–300 tokens / param |
| Scale params + data together | Fix param budget, pump tokens |
| Optimize for training compute | Optimize for *lifetime* compute (train + serve) |
| Bigger = better for fixed compute | Smaller + more data = cheaper to serve at same quality |

**Practitioner implication:** pick model size for **serving budget and latency target**, not for training optimality. You will choose between, say, a 1.5B, 7B, and 14B Qwen3 variant by looking at your deployment VRAM and required tokens/sec — *not* by chasing the "compute-optimal" point.

### What you MUST understand but NEVER execute

A clean split between context-that-makes-you-useful and skills-you-actually-ship.

| You must UNDERSTAND | Why | You DO this | How |
|---|---|---|---|
| Transformer internals (attention, MLP, norms) | Reason about VRAM, context, quant | Start from open base | `AutoModelForCausalLM.from_pretrained` |
| MoE routing | Pick dense vs MoE for cost | CPT or SFT | Unsloth + TRL `SFTTrainer` |
| Tokenizer behavior (byte BPE, merges) | Debug edge cases, count cost | Apply chat template | `tokenizer.apply_chat_template` |
| The pre-train data pipeline (MinHash dedup, quality filter, mixing) | Know what makes a base good or bad | Curate SFT pairs | Day 2 work |
| Scaling laws / overtraining | Pick model size rationally | Pick size for serve cost | Per-deployment math |
| AdamW, LR schedules, BF16/FP8 stability | Read trainer logs; survive mixed-precision training | Use TRL defaults + Unsloth | `TrainingArguments` |

If an interviewer asks "how is a base model trained," you answer fluently. If they ask "what did *you* ship," you point at SFT → post-train → eval → serve. Both answers matter; only the second one is your job.

### The OSS stack map (expanded)

What you reach for at each stage. Memorize this; it is the spine of the rest of this path.

| Stage | Tool(s) | Role | Docs |
|---|---|---|---|
| **Base model** | Qwen3, Llama 4, DeepSeek-R1-Distill, Mistral, Gemma, Phi-4 | Starting checkpoint; pick by size + license + language fit | huggingface.co/models |
| **Data load** | `datasets`, `distilabel`, Unsloth synthetic-data notebook | Load, filter, format, synthesize pairs | huggingface.co/docs/datasets |
| **SFT + PEFT** | **Unsloth** (hero) + TRL `SFTTrainer` + `peft` | Single-GPU fast, low-VRAM fine-tune; LoRA / DoRA / PiSSA | docs.unsloth.ai · huggingface.co/docs/trl |
| **Post-train** | TRL `DPOTrainer` / `GRPOTrainer`, Unsloth DPO, `verl`, OpenRLHF | Preference alignment + RL with verifiable rewards | huggingface.co/docs/trl |
| **Eval** | `lm-evaluation-harness`, LLM-as-judge, Promptfoo / Braintrust | Public benchmarks + product gold set | github.com/EleutherAI/lm-evaluation-harness |
| **Serve** | **vLLM** (prod default), **SGLang** (prefix cache), **Ollama** (local), GGUF / AWQ quant | From laptop to multi-GPU prod | docs.vllm.ai · sglang.dev |
| **Observe** | **Langfuse**, Arize Phoenix | Trace calls, live eval, cost/latency | langfuse.com |

The single tool to internalize first: **Unsloth**. It is a drop-in accelerator for TRL/HF training on a single GPU — ~2× faster and ~70% less VRAM, free on Colab. Every hands-on in days 3, 4, and 7 builds on it.

## Hands-on exercise

**Goal: by the end of today you have fine-tuned an LLM, start to finish, at least once.** No new concepts — just run an existing notebook as-is to build muscle memory.

1. Open **https://docs.unsloth.ai/get-started/unsloth-notebooks** in a browser.
2. Pick the **Qwen3 (or Llama 3.1) SFT notebook** — the standard `Alpaca`/Llama-style starter. Click "Open in Colab."
3. In Colab: set runtime to **T4 GPU** (free tier is fine for 1.5B–7B QLoRA).
4. **Run All.** Steps the notebook does for you:
   - `pip install unsloth` (pulls TRL, peft, bitsandbytes)
   - `FastModel.from_pretrained(...)` with 4-bit QLoRA
   - Loads the bundled sample dataset and applies the chat template
   - Calls `SFTTrainer(...).train()`
   - Saves LoRA adapters and runs a tiny inference check
5. While it trains, watch the loss curve. Note:
   - Initial loss (usually 1–2 range on instruction data)
   - Whether loss drops monotonically over a few steps
   - VRAM usage in the top-right (T4 = 16GB; QLoRA on 7B should fit comfortably)
6. When the inference cell runs, read the sample output. It should look coherent and on-format for the dataset.

You do not need to understand every line yet. Days 2–4 unpack the dataset, the trainer, and the post-training. Today is about removing the "I've never fine-tuned an LLM" line from your CV.

## Checklist
- [ ] I can draw the 5-stage lifecycle and label which stages I own.
- [ ] I can explain, in one sentence each, RoPE, KV cache, SwiGLU, and GQA.
- [ ] I can explain the difference between an MoE model's total and active params, and why both matter.
- [ ] I know byte-level BPE is universal and why (no OOV).
- [ ] I can state Chinchilla (≈20 tok/param) and why everyone overtrains in practice (inference dominates cost).
- [ ] I can name the OSS tool at each stage: base, data, SFT+PEFT, post-train, eval, serve, observe.
- [ ] I ran an Unsloth SFT notebook end-to-end on free Colab and watched loss decrease.
- [ ] I can honestly say "I have fine-tuned an LLM" and point at the notebook output.

## What to explain in interview

**Q: Walk me through the LLM lifecycle from scratch to production.**
Pre-train on trillions of web tokens (next-token loss; $10M+, big labs only), optionally mid-train on curated reasoning/code/math data to shape capabilities, then SFT on instruction pairs to teach format and domain behavior, then post-train with DPO for preferences or GRPO+RLVR for reasoning, then eval (benchmarks + LLM-as-judge + gold set) and serve behind vLLM. In my role I start at SFT — I never pre-train.

**Q: Why do companies overtrain models past Chinchilla-optimal?**
Chinchilla says ~20 tokens per parameter is compute-optimal for *training*, but inference dominates lifetime compute because a model is served billions of times. A smaller, heavily overtrained model matches the quality of a larger Chinchilla-optimal one while being cheaper to host, so the economics push everyone (Llama 3, Qwen3, Gemma) to fix the parameter budget and pump tokens — often 100–300 tokens per parameter.

**Q: What is MoE and why does it matter for my fine-tune?**
Mixture-of-Experts replaces the dense MLP with N experts and routes each token to top-k (usually 2). *Total* params decide VRAM needed to load the model; *active* params decide per-token FLOPs and latency. A 671B/37B MoE is roughly as cheap per token as a 40B dense model but still needs ~700B params of memory (or quantization) to host — so it changes both the serving bill and the fine-tune memory math.

**Q: Why does tokenization matter if I'm just fine-tuning?**
The model never sees text — only token IDs — so tokens are the unit of both training cost and inference cost. Byte-level BPE is universal because it has no out-of-vocabulary tokens. The tokenizer is part of the model: I cannot fine-tune with one tokenizer and serve with another, and most "it works in my prompt but breaks in prod" bugs trace back to tokenization edge cases (trailing whitespace, code indentation, CJK merges) or a mismatched chat template.

**Q: What's your tool stack for a single-GPU fine-tune?**
I start from an open base (Qwen3 or Llama 4), curate data with `datasets` and synthetic generation, fine-tune with **Unsloth + TRL `SFTTrainer`** using QLoRA (4-bit) on all linear modules, post-train with TRL `DPOTrainer` or `GRPOTrainer`, evaluate with `lm-evaluation-harness` plus a domain gold set and an LLM-as-judge, and serve with vLLM in prod or Ollama locally, with Langfuse for tracing.
