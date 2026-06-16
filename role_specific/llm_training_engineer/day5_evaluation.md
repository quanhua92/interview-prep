# Day 5 — Evaluation: Benchmarks, LLM-as-Judge & Domain Gold Sets

> The single hardest part of the LLM lifecycle: did your fine-tune actually make the model better — and did it silently break something else?

## Objectives

- Internalize **why eval is the hardest part** of shipping an LLM (Goodhart, contamination, alignment tax) and the discipline that follows: triangulate, never trust one number.
- Know the 2026 benchmark landscape — what's **saturated vs current** — well enough to pick the right handful and dismiss the dead ones in an interview.
- Master **LLM-as-judge**: scoring modes (pointwise / pairwise / listwise), the bias family (position, length, self-preference), and the mitigations that make judges trustworthy.
- Build a **domain gold set** and a **before/after regression loop** — the actual practice at startups that ship LLM features.
- Pick an **eval harness** for public benchmarks vs a **product-eval platform** for gold sets + judges, and know when to involve humans.

## Concepts

### Why eval is hard

Three forces make LLM evaluation unlike classic ML metrics:

| Force | What it is | What goes wrong |
|---|---|---|
| **Goodhart's law** | "When a measure becomes a target, it ceases to be a good measure." | Once a benchmark is a target, models (and data) get optimized for it; scores inflate while real ability lags. |
| **Data contamination** | Benchmark items leak into pretraining/SFT corpora. | The most insidious failure: a high score that measures **memorization, not capability**. Frontier models are widely suspected (sometimes shown) to be contaminated on MMLU, GSM8K, HumanEval. |
| **Alignment tax / catastrophic forgetting** | Fine-tuning improves the target domain while eroding general ability. | Your domain win is real, but MMLU/IFEval/coding quietly drop. A "better" model ships and a release later you discover regression. |

**The discipline:** treat any single number as a *hypothesis*, not a verdict. Triangulate across three signals:

```
   Public benchmarks  ──┐
                        ├──→  ship / no-ship gate
   Private gold set   ──┤      (regression threshold)
                        ├──→  release sign-off
   Live-traffic eval  ──┘      (sampled + judged)
```

No one of these is sufficient. Startups that ship reliably lean hardest on the **private gold set** because it is uncontaminated, domain-aligned, and the only signal the competition can't game.

### Public benchmarks — 2026 status

| Benchmark | Tests | Status mid-2026 |
|---|---|---|
| **MMLU / MMLU-Pro** | broad academic knowledge | saturated (frontier 88–93%); MMLU-Pro preferred but climbing |
| **GSM8K** | grade-school math | saturated & contaminated; largely abandoned for frontier |
| **MATH / AIME** | competition / Olympiad math | respected & current; **AIME is a headline reasoning metric** |
| **HumanEval / MBPP** | single-function code | saturated / contaminated |
| **LiveCodeBench** | code, continuously refreshed, anti-contamination | respected |
| **SWE-bench / SWE-bench Verified** | end-to-end repo bug fixing | dominant but strained coding standard |
| **GPQA Diamond** | PhD-level STEM reasoning | respected (Google-proof) but nearing ceiling |
| **HellaSwag / ARC** | commonsense / science | dated & saturated; largely retired |
| **IFEval** | instruction-following (verifiable formatting) | respected & cheap; **contamination-resistant** (verifiable) |
| **ARC-AGI-2** | abstract pattern generalization | hard frontier separator |
| **LiveBench** | continuously refreshed, contamination-proof | respected for honest tracking |
| **Humanity's Last Exam (HLE)** | expert-level multi-domain reasoning | new 2026 "frontier ceiling" — resists saturation by design |
| **τ²-bench** | multi-step agentic tool use + shared world state | **headline agentic metric in 2026** |
| **APEX-Agents** | long-horizon professional tasks (legal, consulting, finance) | closest to real business automation |
| **SWE-bench Verified** | end-to-end repo bug fixing (agentic coding) | gold standard for coding agents |

**The new center of gravity = reasoning + agentic + coding:** AIME, HLE, LiveCodeBench, SWE-bench Verified, GPQA Diamond, ARC-AGI-2, τ²-bench, APEX-Agents. When a JD or paper quotes MMLU + GSM8K + HumanEval as headline numbers, that's a 2023 signal; quote the modern set instead.

Two structural defenses against contamination are worth naming:

- **Continuously-refreshed benchmarks** (LiveCodeBench, LiveBench) roll new items on a cadence — anything trained before the cutoff can't have seen them.
- **Verifiable / Google-proof benchmarks** (IFEval formatting rules, GPQA Diamond PhD-level items, ARC-AGI abstract puzzles) resist lookup and paraphrase.

### LLM-as-judge — the dominant practical method for open-ended eval

For open-ended outputs there is no regex. Reference answers exist only sometimes. So the production method is: **ask a strong model to grade a weaker one against a rubric.**

Three scoring modes:

| Mode | What it does | Robustness |
|---|---|---|
| **Pointwise** | Score one response in isolation (1–5 per rubric criterion). | **Most robust** — preferences flip ~9% under prompt perturbation. |
| **Pairwise** | Compare A vs B, pick winner. | ~3.5× more bias-prone — flip rate ~35% under perturbation. |
| **Listwise** | Rank N candidates. | Cheap ranking signal; same bias family as pairwise. |

Default to **rubric-anchored pointwise** for any decision you'll defend in a release review.

**Bias pitfalls + mitigations** (these come up in interviews):

| Bias | Symptom | Mitigation |
|---|---|---|
| **Position bias** | Pairwise judge prefers whichever is first. | Swap A/B order, run twice, average. |
| **Length / verbosity bias** | Judge conflates longer with better. | Normalize per-criterion; instruct judge explicitly; use **length-controlled** prompts. |
| **Self-preference (narcissism)** | Judge favors outputs in its own style / family. | **Use a DIFFERENT, STRONGER model family as judge.** Never let a model grade itself or its twin. |
| **Format / authority bias** | Judge rewards confident tone, lists, markdown regardless of correctness. | Anchor on a rubric; require evidence quotes; penalize unjustified confidence. |

**Rule of thumb:** a judge should be **strictly stronger than** the model being judged. Grade a 7B fine-tune with GPT-class / Claude-class / frontier-Qwen — never the other way around.

**Cheap tactics that scale judges**:

- **Cache + batch** identical prompts; judge calls are the cost center.
- **Rubric-anchored pointwise** gives you per-criterion signal, not just a winner.
- **"LLM juries"** — ensemble a few weaker judges (majority vote) approximates one strong judge at lower cost; useful when you can't call frontier models at scale.
- **Sample aggressively**: run the full battery only on the held-out gold set + a sample of live traffic, not on every request.

### Domain / custom eval — what startups actually do

This is the single most important practice in this whole module. Public benchmarks are general-purpose and saturated; **your product lives or dies on a private gold set you own.**

| Gold-set size | Use case |
|---|---|
| 50–200 | Focused single-feature eval (one capability) |
| 200–500 | Vertical / domain coverage |
| 500–2000 `(query, gold chunks, gold answer)` triples | RAG eval |

**How to curate:**

1. Pull from **real traffic** (de-identified) — the cases your users actually hit.
2. Add **edge cases** explicitly: long context, ambiguous query, adversarial phrasing, out-of-scope.
3. Add **adversarial / red-team** items (jailbreak attempts, prompt injection, PII leakage probes).
4. Write **reference answers** (or gold chunks for RAG).
5. Define a **fixed rubric** — typically 4–5 criteria on a fixed scale:

   | Criterion | Question | Scale |
   |---|---|---|
   | Correctness | Is the answer factually right vs reference? | 1–5 |
   | Grounding | Is every claim supported (RAG) / no hallucination? | 1–5 |
   | Clarity / tone | Reads well, right register? | 1–5 |
   | Safety | No harmful/PII/toxic output? | 1–5 |
   | Format | Follows required schema/style? | 1–5 |

6. **NEVER train on the gold set.** Not SFT, not DPO, not prompt-tuning. The instant the gold set is in training data, it stops measuring generalization.

**The core loop — before/after A/B regression on the same gold set:**

```
   BASE model   ──┐
                  ├── run on gold set ── judge ── per-criterion scores
   FINE-TUNE   ──┘                                       │
                                                         ▼
                              win/loss/tie per item + mean per criterion
                                                         │
                                                         ▼
                          gate candidate on regression threshold:
                          "ship if overall win-rate > 55% AND no criterion regresses > X%"
```

This is **eval-driven development**, wired into CI via **Braintrust / Galtea / Promptfoo / DeepEval**. Golden datasets beat vibes: log real traces, label the interesting ones into the gold set, grow it continuously. Your gold set is a compounding asset; benchmarks are a depreciating one.

### Eval harnesses

| Harness | Sweet spot |
|---|---|
| **lm-evaluation-harness** (EleutherAI) | **Dominant open standard**; backs the Open LLM Leaderboard; largest benchmark coverage. Workhorse for public benchmarks. |
| **lighteval** (HuggingFace) | HF-native, leaderboard-aligned metric definitions. |
| **Inspect** (UK AISI) | Safety / eval research; flexible task DSL. |
| **OpenAI evals** | Reference framework; useful for OpenAI-model-specific tasks. |

**Reality on the ground:**

- **Public benchmarks → `lm-evaluation-harness`** is the default. One CLI, every standard benchmark, reproducible.
- **Product eval (gold sets + judges) → increasingly owned by** **Braintrust** (eval-first), **Promptfoo** (CLI-first, great for regression gates), **DeepEval** (Pytest-native), **RAGAS** (RAG-specific), **Galtea** (test-driven LLM dev).
- **Observability tie-in:** **Langfuse** / **Arize Phoenix** log traces from production; you sample those traces back into your gold set.

### Human eval — when and how

Automated judges are cheap and consistent but they inherit judge-model blind spots. Humans still own:

- **Gold-set creation** (the labels everything else is measured against).
- **Judge calibration** — measure judge–human agreement, e.g. **Cohen's κ**; if κ drops, your judge drifted.
- **High-stakes / safety sign-off** before release.
- **Release gating** on a small human-rated sample per release.

How to make it tractable (don't human-rate everything):

- Label a **small high-quality set** once, thoroughly.
- **Calibrate the judge** against it; track κ over time.
- **Sample a few human-rated items per release** — not the whole battery.
- Track **inter-annotator agreement** so you know when the rubric itself is ambiguous.

Platforms: **Braintrust**, **Surge AI**, **Toloka**, **Scale AI**, **Prolific**.

### Agentic / tool-use eval

Single-turn benchmarks under-measure the 2026 center of gravity — **agents that call tools and act in environments.**

| Benchmark | What it measures |
|---|---|
| **τ-bench / τ²-bench** (Sierra) | User + agent + tools + **shared world state**. τ²-bench is the **headline agentic metric** in 2026. |
| **SWE-bench / Verified** | End-to-end repo bug fixing (agentic coding). |
| **GAIA / WebArena** | General assistant / web navigation agents. |

**2026 insight:** don't just report pass@1. Measure the **trade-off frontier**:

```
   success rate   vs   cost ($)   vs   latency (p95)   vs   tool-call count
```

A model that's 3% more accurate but 5× the tool calls and 2× the latency is usually **not** the right pick for production. Plot the Pareto frontier, decide with the product owner.

## Hands-on exercise

**Build a 100-example domain gold set and run a before/after eval.** ~4h.

You will hold out 100 financial-analysis Q&A from your Day-2 dataset, score the **base model** vs your **Day-3 fine-tune** with an LLM-as-judge, compute per-criterion means + overall win-rate, and decide ship/no-ship.

### Step 1 — Hold out 100 examples as the gold set

From the Day-2 SFT JSONL, move **100 items** into a separate `gold_set.jsonl` **before** any training split. Each record:

```json
{"id": "g-0001", "query": "...", "reference_answer": "..."}
```

Remove these 100 from the training data — re-run Day-3 fine-tuning if you must. **The gold set must never appear in training.**

### Step 2 — Write the rubric

Adopt the 5-criteria rubric from the Concepts section (correctness, grounding, clarity, safety, format), each 1–5. Pin it in a constant string every judge call uses — rubric drift is real.

### Step 3 — Generate completions from both models

For each gold item, produce two completions: `base_completion` (base model via the same chat template) and `ft_completion` (your Day-3 fine-tune). Same decoding defaults (temp 0.0 / greedy) for both — eval must be reproducible.

### Step 4 — Score with a stronger LLM-as-judge

Pointwise, rubric-anchored. Call a **frontier model** (stronger than the 7B you fine-tuned) via API. Parse a strict JSON schema.

```python
# eval_gold.py — ~40-line skeleton
import json, os, statistics
from openai import OpenAI

client = OpenAI()  # point at your frontier-judge provider

RUBRIC = """Score the answer on 5 criteria, each 1-5 (integer).
- correctness: factually right vs the reference answer
- grounding:   no hallucination; claims are supported
- clarity:     readable, right tone for financial analysis
- safety:      no harmful/PII/toxic content
- format:      follows the required markdown style
Respond ONLY with JSON: {"correctness":int,"grounding":int,
"clarity":int,"safety":int,"format":int}
"""

def judge(query, reference, answer):
    msg = f"QUESTION:\n{query}\n\nREFERENCE:\n{reference}\n\nANSWER:\n{answer}\n\n{RUBRIC}"
    r = client.chat.completions.create(
        model="gpt-4o-mini",  # use a frontier-class model you have access to
        messages=[{"role": "user", "content": msg}],
        response_format={"type": "json_object"}, temperature=0,
    )
    return json.loads(r.choices[0].message.content)

def run(label, gen_fn, gold):
    per = {c: [] for c in ["correctness","grounding","clarity","safety","format"]}
    for item in gold:
        s = judge(item["query"], item["reference_answer"], gen_fn(item["query"]))
        for c in per: per[c].append(s[c])
    means = {c: round(statistics.mean(v), 2) for c, v in per.items()}
    means["overall"] = round(statistics.mean(list(means.values())), 2)
    return means

if __name__ == "__main__":
    gold = [json.loads(l) for l in open("gold_set.jsonl")]
    # gen_fn_base / gen_fn_ft call your base / fine-tuned model (Day 3 / Day 6)
    print("BASE :", run("base", gen_fn_base, gold))
    print("FT   :", run("ft",   gen_fn_ft,   gold))
```

### Step 5 — Compute means + overall win-rate

Per-criterion means for base vs fine-tune. Then overall **win-rate**: for each item, did the fine-tune score higher (win), lower (loss), or equal (tie) on overall? Report `wins / (wins+losses)` ignoring ties (or count ties as 0.5).

### Step 6 — Check general-ability regression

Before declaring victory, run **1–2 public benchmarks** on both models via `lm-evaluation-harness` — **IFEval** (cheap, contamination-resistant) and one more (e.g. a slice of MMLU-Pro or HumanEval) — to confirm the fine-tune didn't quietly erode general ability:

```bash
# https://github.com/EleutherAI/lm-evaluation-harness
lm_eval --model hf --model_args pretrained=<your-ft-repo> --tasks ifs,leaderboard_mmlu_pro \
        --batch_size auto
```

### Step 7 — Decide ship / no-ship

Apply an explicit gate. Example:

> *Ship if overall win-rate ≥ 55% AND no criterion regresses more than 0.2 mean points AND IFEval drops ≤ 1%.*

Record the decision + numbers in a changelog. This is the artifact you show in interviews: "I built a 100-item gold set, ran a blind before/after with a frontier LLM judge, and gated release on a regression threshold including public-benchmark regression checks."

## Checklist

- [ ] I can explain Goodhart's law, data contamination, and alignment tax in one sentence each.
- [ ] I can name the 2026 headline set (AIME, LiveCodeBench, SWE-bench Verified, GPQA Diamond, ARC-AGI-2, IFEval) and which older benchmarks are saturated.
- [ ] I know pointwise vs pairwise vs listwise and why pointwise is the default.
- [ ] I can list the four judge biases and the mitigation for each (esp. **use a different, stronger model**).
- [ ] I have a 100-item held-out gold set that is **not** in any training split.
- [ ] I have a fixed 5-criterion rubric pinned as a constant.
- [ ] I ran base vs fine-tune through a frontier judge and computed per-criterion means + win-rate.
- [ ] I checked at least IFEval (public benchmark) before/after for general regression.
- [ ] I wrote down an explicit ship/no-ship gate and recorded the decision.
- [ ] I can name the harness split: `lm-evaluation-harness` for public benchmarks; Braintrust/Promptfoo/DeepEval/RAGAS/Galtea for product eval.

## What to explain in interview

**Q: How do you evaluate a fine-tuned LLM in production?**
Triangulate three signals: a few uncontaminated public benchmarks via `lm-evaluation-harness` (IFEval + a reasoning set) for general-ability regression; a private domain gold set (50–5000 examples, never trained on) scored by a stronger LLM-as-judge against a fixed rubric; and sampled live-traffic judged in production. Gate releases on a regression threshold across all three.

**Q: Public benchmarks feel gamed — what do you actually trust in 2026?**
I trust continuously-refreshed or verifiable benchmarks (LiveCodeBench, LiveBench, IFEval, GPQA Diamond, ARC-AGI-2) over saturated/contaminated ones (MMLU, GSM8K, HumanEval). But for product decisions the private gold set is the load-bearing signal, because it's uncontaminated and domain-aligned.

**Q: How do you make an LLM-as-judge reliable?**
Default to rubric-anchored **pointwise** scoring (it's ~3.5× more stable than pairwise). Mitigate the four biases: swap A/B order for pairwise, normalize for length, and crucially **use a different, stronger model family as judge** to kill self-preference. Calibrate against a human-labeled set with Cohen's κ and track κ over time.

**Q: What's a domain gold set and how big should it be?**
A held-out, never-trained-on set of `(query, reference answer)` pairs with a fixed rubric, curated from real traffic + edge cases + adversarial items. 50–200 for a focused feature, 200–500 for a vertical, 500–2000 triples for RAG. It's a compounding asset — you grow it continuously from production traces.

**Q: How do you catch catastrophic forgetting after fine-tuning?**
Run the same before/after A/B on a small set of public benchmarks (IFEval + one reasoning set) alongside the gold set, and gate the candidate on a max-allowed regression per benchmark. Forgetting shows up as a quiet drop on general ability even when domain win-rate goes up.

**Q: When do you involve humans?**
For gold-set creation, judge calibration (measuring judge–human agreement / κ), high-stakes or safety sign-off, and a small human-rated sample per release. You don't human-rate everything — you human-rate a high-quality set and let the calibrated judge scale.
