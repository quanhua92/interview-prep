# Day 7 — Capstone: Ship a Domain Fine-Tune End-to-End

> Tie Days 1–6 into one shippable artifact: a fine-tuned, evaluated, served domain model — and the portfolio piece that proves you can do this job.

## Objectives
- Execute the **full lifecycle on real data**: data → SFT → (optional DPO) → eval → serve.
- Produce a **portfolio repo** you can link on your CV and discuss in interviews.
- Generate the **before/after numbers** that convert your CV's biggest gap into a strength.
- Rehearse the **end-to-end narrative** for "have you fine-tuned a model?" and "how do you ship an LLM feature?"

## The project

Fine-tune an open instruct model to be a better **financial-market analyst assistant** for the AIPriceAction domain (Vietnamese / global stocks, crypto, commodities). This leverages your existing edge (you own the data and the domain) so the fine-tune is genuinely useful, not a toy.

| Choice | Value | Why |
|---|---|---|
| **Base model** | Qwen2.5-7B-Instruct (or Qwen3-8B) | Strong multilingual (VN + EN), permissive, Unsloth-supported, fits a free Colab L4 at 4-bit |
| **Method** | QLoRA (4-bit) + LoRA r=16, α=16, all 7 linear modules | Single-GPU default (Day 3) |
| **Tool** | **Unsloth** | 2× faster, ~70% less VRAM (Day 3) |
| **Data** | Distill from your analysis agents via [`capstone_dataset/`](capstone_dataset/) — questions (OHLCV features) + multi-teacher outputs + realized outcomes | Domain you own → real, contributable, unbounded |
| **Eval** | 100-example held-out gold set + LLM-as-judge (rubric) + 1 public benchmark regression check (Day 5) | Honest before/after |
| **Serve** | GGUF Q4_K_M in Ollama (demo) + vLLM endpoint (prod) (Day 6) | Local demo + real serving |
| **Optional** | A light DPO pass on ~200–500 preference pairs (Day 4) | Bonus: show post-training depth |

## Build plan (maps to the week)

1. **Data** — use [`capstone_dataset/`](capstone_dataset/): fetch aipa OHLCV+MA per ticker, run `make_real_questions.py` to emit real questions (evidence = MA values + MA scores; the realized future outcome is stored separately as the reward/label, never in the prompt). Hold out whole tickers/periods as the eval set.
2. **Baseline eval (Day 5)** — score the **base** Qwen model on the gold set with an LLM-as-judge (5-criterion rubric: correctness, grounding, clarity, safety, format). Record numbers. Also run `lm-eval-harness` IFEval on the base model for a general-ability reference.
3. **SFT (Day 3)** — Unsloth + QLoRA, 1 epoch, lr=2e-4, cosine, completion-only loss. Save the LoRA adapter.
4. **(Optional) DPO (Day 4)** — from the harness: for each question with ≥2 teachers, emit `(prompt, chosen, rejected)` where the teacher whose verdict matched the realized future = chosen, the one that missed = rejected. Run `DPOTrainer` (lr=5e-6, β=0.1, 1 epoch).
5. **Candidate eval (Day 5)** — score the fine-tuned model on the **same** gold set + same judge. Compute per-criterion deltas + overall win-rate vs base. Re-run IFEval to check for **general-ability regression**.
6. **Serve (Day 6)** — export GGUF Q4_K_M → Ollama (local demo); serve the merged model with vLLM for a prod-like endpoint. Record VRAM / TTFT / tokens-per-sec.
7. **Write up + ship** — the portfolio repo below.

## Deliverables — the portfolio repo

Create a public GitHub repo, e.g. `quanhua92/qwen-finance-sft`. Structure:

```
qwen-finance-sft/
  README.md            ← the money document (see template below)
  data/
    train.jsonl        ← SFT data (messages format)
    eval_gold.jsonl    ← 100-example held-out set
    dpo_pairs.jsonl    ← (optional) preference pairs
  configs/
    sft_unsloth.py     ← the Unsloth training script (from Day 3)
    dpo_trl.py         ← (optional) DPO script (from Day 4)
  eval/
    judge.py           ← LLM-as-judge scorer (from Day 5)
    results_base.csv
    results_sft.csv    ← (and results_dpo.csv)
  serve/
    modelfile          ← Ollama Modelfile
    vllm_start.sh      ← vllm serve command
  adapter/             ← (or link to HF Hub) the LoRA adapter
```

### README.md template (fill the `[BRACKETS]`)

```markdown
# Qwen-Finance-SFT — Domain fine-tune for market analysis

Fine-tuned Qwen2.5-7B-Instruct (QLoRA via Unsloth) for financial-market Q&A,
grounded in [AIPriceAction] analyst data. Evaluated with an LLM-as-judge
gold set against the base model.

## Results
| Model | Correctness | Grounding | Clarity | Overall | Win-rate vs base |
|-------|------------:|----------:|--------:|--------:|-----------------:|
| Base Qwen2.5-7B  | [X]% | [X]% | [X]% | [X]% | — |
| + SFT (this)     | [Y]% | [Y]% | [Y]% | [Y]% | [Z]% |
| + DPO (optional) | [Y]% | [Y]% | [Y]% | [Y]% | [Z]% |

General-ability regression check (IFEval): base [X]% → fine-tuned [Y]% (Δ within tolerance).

## Method
- **Data:** [N] conversational QA pairs, ChatML format, [source]. 100-example held-out gold set.
- **SFT:** QLoRA (4-bit), LoRA r=16/α=16 on all 7 linear modules, 1 epoch, lr=2e-4, cosine, completion-only loss, via Unsloth on a single Colab L4.
- **(DPO):** [N] preference pairs, TRL DPOTrainer, lr=5e-6, β=0.1, 1 epoch.
- **Eval:** LLM-as-judge ([judge model]) on a 5-criterion rubric; win-rate by pairwise comparison.
- **Serve:** GGUF Q4_K_M (Ollama) for local; vLLM for the endpoint.

## Reproduce
1. `pip install unsloth`  2. `python configs/sft_unsloth.py`  3. `python eval/judge.py`
```

## Interview talking points this produces

- *"I fine-tuned Qwen2.5-7B with QLoRA via Unsloth on ~[N]k domain QA pairs, using a 100-example held-out gold set and an LLM-as-judge, and improved domain correctness from [X]% to [Y]% while staying within tolerance on IFEval."*
- *"I used completion-only loss with the correct ChatML template — getting the template wrong is the #1 way fine-tunes break."*
- *"Before serving I checked for catastrophic forgetting by re-running a public benchmark alongside my domain eval."*
- Be ready to answer: **what failed**, **what you'd do with more compute** (DoRA/PiSSA, GRPO+RLVR if you had verifiable rewards, distillation from a reasoner), and **why QLoRA not full FT** (single GPU, small data, preserve general capability).

> **Data pipeline:** use [`capstone_dataset/`](capstone_dataset/) — a live, markdown-only
> distillation harness. You generate **questions** from aipa OHLCV+MA (evidence = MA
> values + MA scores); to gather teacher outputs you **copy the `data/COPY_AND_RENAME/`
> template folder** to `data/<model>/` and let subagents (in opencode / Claude Code /
> any subscription CLI) fill each file's `# Answer` section — no API code, no per-token
> cost. Realized forward outcomes live separately in `outcomes.jsonl` and power SFT
> rejection-sampling, DPO pairs, and the final **RLVR** stage where the teacher becomes
> irrelevant (the student is graded only against what the market actually did). See
> its [README](capstone_dataset/README.md#stage-3-rlvr-the-teacher-is-irrelevant) for
> the teacher-vs-reality contract.

## Definition of done
- [ ] Gold set frozen (100 examples, never trained on)
- [ ] Base vs fine-tuned numbers in the README table
- [ ] General-ability regression checked (IFEval or similar)
- [ ] Adapter saved + pushed to HF Hub (or in repo)
- [ ] Runs in Ollama locally AND via vLLM
- [ ] Public repo with a clean README + reproduce steps
- [ ] Rehearsed the 60-second "I fine-tuned a model" story out loud

> This single artifact is what makes the JD's *"hands-on experience with LLM training, fine-tuning, or evaluation"* true. Don't skip it.
