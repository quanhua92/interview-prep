# Day 2 — Building an SFT Dataset (The Real Work)

> The single biggest determinant of a fine-tune's quality is the dataset. Master chat templates, formats, masking, and synthetic generation.

## Objectives
- Understand why data quality >> quantity and >> framework choice.
- Master **chat templates** — the #1 cause of broken fine-tunes.
- Know the standard SFT data formats and when each applies.
- Produce a clean, validated conversational dataset.
- Learn the synthetic-generation loop (generate → judge → dedup).

## Concepts

### Why data is the real work

Two truths that every production team relearns the expensive way:

1. **A few hundred expert-curated pairs beat thousands of noisy synthetic ones.** Quality dominates quantity in SFT. The model learns the *distribution* of your data — if the data is shallow, repetitive, or off-format, the fine-tune is too.
2. **The framework is not the differentiator.** Unsloth vs raw TRL vs DeepSpeed all produce equivalent models on equivalent data. What separates a good fine-tune from a bad one is the *dataset* and the *eval*, not the trainer.

Spend your time accordingly. Most practitioners underinvest in data and overinvest in hyperparameter tuning. Invert that.

| Lever | Impact on final quality | Time cost |
|---|---|---|
| Dataset quality (curation, dedup, balance) | Very high | High |
| Dataset size (past a floor) | Moderate, diminishing | High |
| Eval rigor (gold set + judge) | High (it tells you the truth) | Medium |
| Trainer / framework choice | Low | Low |
| Hyperparameter tuning | Low–moderate | Medium |

### SFT loss & masking

SFT trains the model to maximize the probability of the *response* tokens given the *prompt* tokens. The mechanism is token-level cross-entropy — but **which tokens you compute loss on is the critical knob**.

**The wrong default:** loss on every token. The model then also learns to imitate the *user's* turns, which wastes capacity and degrades instruction-following. Don't do this.

**The right behavior:** mask the prompt so gradients flow only on the tokens you want the model to *produce*. Two flavors:

| Masking mode | What gets loss | TRL knob | When |
|---|---|---|---|
| **Completion-only loss** | Only the final response in a prompt→completion pair | `completion_only_loss=True` | Single-turn instruction/response (Alpaca-style) |
| **Assistant-only loss** | Only assistant turns across a multi-turn conversation | `assistant_only_loss=True` | Multi-turn ChatML conversations |

TRL's `SFTTrainer` handles both. The masking works by setting prompt-token labels to `-100` (PyTorch's ignore index), so cross-entropy skips them.

> **2026 TRL gotcha:** `assistant_only_loss=True` requires the model's chat template to include `{% generation %}` / `{% endgeneration %}` keywords. TRL auto-patches templates for most Qwen and Llama families, but verify it works. It's also incompatible with `use_liger_kernel=True`. When in doubt, use Unsloth's `train_on_responses_only` helper (see Day 3) — it is more robust.

```python
from trl import SFTConfig

# Single-turn (prompt + completion), compute loss on completion only
cfg = SFTConfig(completion_only_loss=True, ...)

# Multi-turn conversations, compute loss on every assistant turn
cfg = SFTConfig(assistant_only_loss=True, ...)
```

If you skip this knob your fine-tune still runs and the loss still drops — but the model learns to generate user turns too, which shows up as worse instruction-following at inference. It is a silent bug. Always set the mask.

### Chat templates — THE critical concept

A chat template is a **Jinja2 template in the tokenizer** that serializes a list of `{"role", "content"}` messages into a single string with the right special tokens. The model is trained on that serialized string; at inference you must produce the *exact same* serialization or the model sees out-of-distribution input.

> **Golden rule:** train and infer with the SAME template. A mismatched template is the most common cause of "the fine-tune produces garbage."

Every model family ships its own template baked into the tokenizer. You almost never write one — you call `tokenizer.apply_chat_template(messages, tokenize=False)` and inspect the output.

| Family | Serialized format | EOS token |
|---|---|---|
| **ChatML** (Qwen, old OpenAI) | `<\|im_start\|>role\n...content...<\|im_end\|>` | `<\|im_end\|>` |
| **Qwen 2.5 / 3** | ChatML | `<\|im_end\|>` |
| **Llama 3** | `<\|begin_of_text\|><\|start_header_id\|>user<\|end_header_id\|>\n\n...<\|eot_id\|>` | `<\|eot_id\|>` |
| **Gemma** | `<start_of_turn>user\n...<end_of_turn>\n` | `<end_of_turn>` |
| **Mistral** | `[INST] ...[/INST]...` | `</s>` |

A concrete ChatML example after `apply_chat_template`:

```
<|im_start|>system
You are a precise financial analyst.<|im_end|>
<|im_start|>user
What is the Wyckoff Spring pattern?<|im_end|>
<|im_start|>assistant
A Wyckoff Spring is a false breakdown below a support level...
```

How to inspect your template (do this before every fine-tune):

```python
from transformers import AutoTokenizer

tok = AutoTokenizer.from_pretrained("Qwen/Qwen3-7B")
msgs = [
    {"role": "system", "content": "You are a precise financial analyst."},
    {"role": "user", "content": "What is the Wyckoff Spring pattern?"},
    {"role": "assistant", "content": "A Wyckoff Spring is a false breakdown..."},
]

print(tok.apply_chat_template(msgs, tokenize=False))
print("EOS:", repr(tok.eos_token), tok.eos_token_id)
```

If the printed string looks wrong, stop and fix the template before training. Common mistakes:

- **Forgetting the `system` role** when the template expects one.
- **Concatenating messages with `"\n".join`** instead of using `apply_chat_template` (drops special tokens entirely).
- **Mismatched EOS** between the dataset format and what generation looks for (causes runaway output).
- **Adding a BOS token twice** when the template already prepends one.

### Data formats

Three formats you will see. TRL's `SFTTrainer` accepts all three and auto-applies the chat template where appropriate.

**1. Alpaca** — single-turn, instruction-style. Oldest, simplest, still common.

```json
{
  "instruction": "Explain the difference between accumulation and distribution in Wyckoff theory.",
  "input": "",
  "output": "Accumulation is the phase where smart money buys..."
}
```

**2. ShareGPT** — multi-turn conversations with explicit role labels.

```json
{
  "conversations": [
    {"from": "human", "value": "Analyze the volume spike on VCB today."},
    {"from": "gpt", "value": "The volume spike on VCB suggests..."},
    {"from": "human", "value": "Should I enter a long position?"},
    {"from": "gpt", "value": "Based on the price action and volume..."}
  ]
}
```

**3. ChatML / native conversational JSONL** — the modern default. TRL's `SFTTrainer` consumes this directly with zero preprocessing.

```json
{
  "messages": [
    {"role": "system", "content": "You are a precise financial analyst."},
    {"role": "user", "content": "Analyze the volume spike on VCB today."},
    {"role": "assistant", "content": "The volume spike on VCB suggests..."}
  ]
}
```

| Format | Best for | Notes |
|---|---|---|
| Alpaca | Single-turn QA, simple tasks | `completion_only_loss=True` |
| ShareGPT | Multi-turn chat logs scraped from real convos | Convert to messages for cleanliness |
| ChatML JSONL | Modern default, anything multi-turn | `assistant_only_loss=True`; TRL auto-applies template |

**Default to ChatML JSONL.** It is the format TRL, vLLM, Ollama, and most eval harnesses natively read, and it sidesteps the role-mapping quirks of ShareGPT.

### Minimum viable dataset size

| Goal | Pairs | Example |
|---|---|---|
| Tone / style shift | **100–500** | "Answer in Vietnamese, be terse, cite the chart" |
| Task specialization | **1,000–10,000** | "Always structure analysis as: trend → volume → S/R → verdict" |
| Continued pretraining / big domain shift | **tens of thousands+** | Adding deep equity-research vocabulary to a base that lacks it |

The lower bound matters more than the upper. Past ~10k pairs, marginal quality gains plateau unless you are doing a real domain injection. The biggest mistake is to scrape 50k noisy pairs when 1k clean ones would do better.

### Quality rules (run this checklist before training)

- [ ] **Format consistency** — every example matches the chat template exactly. Print 5 random examples with `apply_chat_template(tokenize=False)` and read them.
- [ ] **Diversity** — vary phrasing, length, topic, and difficulty. If 30% of your pairs share an opening phrase, the model will parrot it.
- [ ] **Correctness** — vet a random sample (≥30 examples) by hand. Bad labels = bad model.
- [ ] **Deduplication** — exact-match dedup plus near-dup (MinHash on the assistant turn). Duplicates leak the test signal.
- [ ] **Balance** — no single subtopic > ~25% of the set. Trim overrepresented classes.
- [ ] **Length sanity** — filter empty responses and absurdly long ones (> context budget / 2).
- [ ] **Hold out eval** — carve out **10–20%** as a frozen gold set before any fine-tune touches the data. Never train on it.
- [ ] **No benchmark contamination** — search for near-duplicates of MMLU/GSM8K/HumanEval in your data. Remove them.

The eval split is non-negotiable. Without it you cannot measure whether the fine-tune actually helped (Day 5).

### Synthetic data generation

When you do not have enough expert-labeled pairs, generate them with a strong model and then auto-clean. This is now a standard production workflow.

**The loop:**

```
   seed docs / analyst notes / transcripts
                  │
                  ▼
   strong model (GPT-4-class / Qwen3-Max / DeepSeek) generates QA pairs
                  │
                  ▼
   judge model scores each pair (correctness, clarity, answerability)
                  │
                  ▼
   drop low-scoring pairs → dedup → format to ChatML JSONL
                  │
                  ▼
   hold out eval → fine-tune
```

**Tools:**

| Tool | What it does |
|---|---|
| **Unsloth Synthetic Data notebook** | PDFs / videos → QA pairs, notebook-first, free on Colab |
| **`distilabel`** (Argilla) | Pipelines for generate → judge → filter at scale; pluggable models |
| Raw API loop | Roll your own with any strong model + a judge prompt; most flexible |

**Two failure modes to avoid:**

1. **Contamination.** If your source documents contain benchmark questions (or near-paraphrases), the model memorizes them and your eval numbers lie. Always grep your dataset against public benchmarks before training.
2. **Model collapse by proxy.** If you generate with model A and the data is mediocre, your fine-tune inherits A's weaknesses. The judge step exists to filter this — do not skip it.

Synthetic data is powerful but it is not free quality. Treat it as *candidate* data that must pass the same quality checklist as human-labeled data.

## Hands-on exercise

**Goal: produce a ~1,000-example conversational ChatML JSONL in a domain you know — financial market analysis (AIPriceAction context: Vietnamese and global stocks, crypto).**

This dataset feeds Day 3's fine-tune, so do it properly.

### Step 1 — Collect seeds

Gather 50–150 seed items from your domain. Sources that work for the financial-analysis context:

- Your own analyst notes / chart write-ups / newsletters.
- Real Q&A from support channels, Discord, or comments.
- Past analyses on tickers you cover (VIC, VCB, FPT, BTC, ETH).
- Public analyst reports — rephrase into QA form.

Each seed is either a finished QA pair or a document you will turn into QA pairs.

### Step 2 — Generate / expand

Use a strong model (Qwen3-Max, DeepSeek, GPT-4-class) to expand seeds into diverse QA pairs. Vary the user phrasing, the depth of the answer, and the asset class. Target ~5–10 generated pairs per seed.

A prompt skeleton:

```
Given this analyst note: "<note>"

Generate 5 diverse question/answer pairs about it.
Vary: question phrasing, length, and which concept each focuses on
(trend, volume, support/resistance, verdict).
Format each as:
{"role": "user", "content": "..."}
{"role": "assistant", "content": "..."}
```

### Step 3 — Format to ChatML JSONL

One JSON object per line, each a `{"messages": [...]}` conversation. Use `datasets` to load, then validate with `apply_chat_template`.

```python
import json
import random
from datasets import Dataset
from transformers import AutoTokenizer

random.seed(42)

# Assume `rows` is a list of dicts: {"user": str, "assistant": str}
rows = [...]  # your generated pairs

SYSTEM = "You are a precise financial analyst covering Vietnamese and global equities and crypto. Use price-action reasoning: trend, volume, support/resistance, then a clear verdict."

records = []
for r in rows:
    records.append({
        "messages": [
            {"role": "system", "content": SYSTEM},
            {"role": "user", "content": r["user"]},
            {"role": "assistant", "content": r["assistant"]},
        ]
    })

# Dedup on the assistant turn (exact match)
seen, deduped = set(), []
for rec in records:
    key = rec["messages"][-1]["content"].strip().lower()
    if key in seen:
        continue
    seen.add(key)
    deduped.append(rec)
records = deduped
print(f"After dedup: {len(records)}")

# Shuffle and split: 90% train, 10% eval gold set
random.shuffle(records)
n_eval = max(100, len(records) // 10)
eval_set, train_set = records[:n_eval], records[n_eval:]

def write_jsonl(path, data):
    with open(path, "w") as f:
        for rec in data:
            f.write(json.dumps(rec, ensure_ascii=False) + "\n")

write_jsonl("fin_train.jsonl", train_set)
write_jsonl("fin_eval.jsonl", eval_set)   # FROZEN gold set — never train on this
print(f"train: {len(train_set)}  eval: {len(eval_set)}")
```

### Step 4 — Sanity-check the template

Before fine-tuning, print 3 formatted examples through the model's actual chat template and read them. This catches 90% of broken-fine-tune bugs.

```python
tok = AutoTokenizer.from_pretrained("Qwen/Qwen3-7B")

ds = Dataset.from_json("fin_train.jsonl")
for i in random.sample(range(len(ds)), 3):
    example = ds[i]
    rendered = tok.apply_chat_template(example["messages"], tokenize=False)
    print(f"--- example {i} ---")
    print(rendered)
    print(f"EOS: {repr(tok.eos_token)} (id={tok.eos_token_id})")
    print()
```

What to look for:

- The `<|im_start|>role\n...<|im_end|>` structure is intact for every turn.
- The assistant turn ends with the EOS token (`<|im_end|>` for Qwen).
- No BOS token is duplicated; no orphan special tokens.
- The system message is present and consistent across examples.
- Vietnamese diacritics and ticker symbols render correctly (byte-level BPE handles this; just verify).

If all three examples look clean, you are ready for Day 3. If not, fix the template / format before going further.

## Checklist
- [ ] I can explain why completion-only / assistant-only loss matters and the TRL knobs that enable it.
- [ ] I can name the chat template formats for ChatML, Llama 3, Gemma, and Mistral.
- [ ] I have called `tokenizer.apply_chat_template(tokenize=False)` and read the raw string output.
- [ ] I can produce Alpaca, ShareGPT, and ChatML JSONL examples from memory.
- [ ] I know the minimum-viable sizes: 100–500 (style), 1k–10k (task), tens of thousands+ (CPT).
- [ ] I ran every item on the quality-rules checklist on my dataset.
- [ ] I built a ~1,000-example ChatML JSONL with a frozen ~100-example eval gold set.
- [ ] I printed 3 formatted examples and they look correct.
- [ ] I checked for benchmark contamination in my synthetic data.

## What to explain in interview

**Q: What makes or breaks an SFT fine-tune — the model, the framework, or the data?**
The data. A few hundred expert-curated pairs will outperform thousands of noisy synthetic ones, and the framework choice (Unsloth vs raw TRL vs DeepSpeed) has minimal impact on final quality given equivalent data. I invest most of my time in dataset curation, dedup, balance, and a frozen eval gold set, then a rigorous judge — and treat the trainer as a solved problem.

**Q: What is completion-only loss and why does it matter?**
By default, cross-entropy loss is computed on every token, which means the model also learns to imitate the user's turns — wasting capacity and degrading instruction-following. Completion-only (or assistant-only for multi-turn) loss masks prompt tokens by setting their labels to `-100`, so gradients flow only on the tokens I want the model to produce. In TRL this is `completion_only_loss=True` or `assistant_only_loss=True`. Skipping it is a silent bug: loss still drops, but the fine-tune is worse.

**Q: What is a chat template and what goes wrong if you misuse it?**
A chat template is the Jinja2 template in the tokenizer that serializes `{"role","content"}` messages into the exact string the model was trained on, including special tokens like `<|im_start|>` or `<|eot_id|>`. The golden rule is to train and infer with the SAME template. Mismatches — forgetting the system role, joining messages with newlines, wrong EOS, double BOS — are the most common cause of a fine-tune that produces garbage at inference, and they are silent because training loss still looks fine.

**Q: How big does an SFT dataset need to be?**
It depends on the goal: 100–500 pairs for a tone or style shift, 1,000–10,000 for task specialization, and tens of thousands plus for a real continued-pretraining domain shift. Past about 10k clean pairs, marginal gains plateau unless I am injecting deep new vocabulary. The bigger mistake is scraping 50k noisy pairs when 1k clean ones would do better — quality dominates quantity.

**Q: How do you generate synthetic SFT data without contaminating your eval?**
I run a generate → judge → dedup loop: a strong model produces candidate QA pairs from my source documents, a judge model scores them for correctness and clarity, I drop low-scoring pairs, and I dedup. Critically, I grep the final dataset against public benchmarks (MMLU, GSM8K, HumanEval, finance-specific benchmarks) to remove near-paraphrases before training, and I hold out a frozen 10–20% gold set that no fine-tune ever touches — that is the only number I trust for "did this help."
