# Capstone Dataset — Live, Markdown-First Distillation Set

A **markdown-only**, file-based dataset for distilling market-analysis capability
from many teacher LLMs into one student model. No API code, no per-token billing —
you gather teacher outputs by **copying a template folder and letting subagents
fill it** inside any subscription CLI (opencode / Claude Code / Gemini CLI / Cursor).

## The data-vs-future contract (read first)

Trading is probabilistic; a teacher is rarely cleanly right/wrong and a single
outcome is noisy. So each question splits time:

```
        data range [t0 .. as_of]                future range [as_of .. as_of+N]
 (what the analyst saw -> the .md Question)     (what happened -> outcomes.jsonl)
```

- The teacher's `# Question` section is **data-window only**. The realized outcome
  lives in **`outcomes.jsonl`**, never inside the `.md` the teacher sees — that
  would be look-ahead leakage.
- Subagents are **forbidden from using tools** (no web/bash/aipa) so they can't
  look up what the ticker did. The teacher must be genuinely blind.

## Layout

```
capstone_dataset/
  data/
    COPY_AND_RENAME/        TEMPLATE folder — copy it, don't fill it directly
      README.md             orchestrator instructions (rename to your model)
      SUBAGENT_PROMPT.md    the task each spawned subagent reads + follows
      q_NNNNNN.md           question on top, empty # Answer (NO outcome inside)
    <model>/                a teacher run = a renamed COPY of COPY_AND_RENAME,
                            filled by subagents (may use batch_*/ subfolders)
  outcomes.jsonl            realized future outcome per id (scoring index; NEVER copied into teacher folders)
  manifest.json             system prompt, holdout, scoring config
  scripts/
    make_real_questions.py  build data/COPY_AND_RENAME/*.md + outcomes.jsonl from aipa
    score.py                grade teacher verdicts vs outcomes.jsonl
    build_dataset.py        assemble build/sft_*.jsonl / build/dpo_*.jsonl
    status.py               coverage (done/todo per teacher)
    _mdutil.py              shared markdown parser
  build/                    built SFT/DPO JSONL (gitignored)
```

## Pipeline

```bash
cd capstone_dataset

# 1) You: fetch aipa OHLCV (per ticker) and build the template + outcomes index
for T in VCB FPT BTCUSDT; do
  uvx aipa-cli get-ohlcv-data $T --start-date 2025-06-01 --end-date 2026-06-16 \
    --no-system-prompt >> ohlcv.txt
done
python scripts/make_real_questions.py ohlcv.txt

# 2) Copy the template to a teacher folder, then fill it with subagents
cp -r data/COPY_AND_RENAME data/claude-opus-4.8
#   in your CLI: see data/claude-opus-4.8/README.md  (spawn subagents reading SUBAGENT_PROMPT.md)
#   repeat, copying to data/<other-model>/ for more teachers

# 3) Score + build
python scripts/status.py
python scripts/score.py
python scripts/build_dataset.py --mode sft     # -> build/sft_train.jsonl
python scripts/build_dataset.py --mode dpo     # -> build/dpo_train.jsonl
```

## How the student "learns from teacher mistakes"

The teacher is **not treated as gold**; outcomes are used as a label/reward:

| Stage | Mechanism | Teacher's role |
|---|---|---|
| **SFT (cold start)** | Rejection-sample: keep answers whose verdict matched the realized direction; student imitates the *form*, mostly from teachers who were right. | High — imitated |
| **DPO** | Same question, multiple teachers: `chosen` matched the future, `rejected` missed. | Medium — relative ranking |
| **RLVR (final stage)** | Reward the *student's* own call vs the realized return, aggregated over thousands. | **None — see below** |

### Stage 3 (RLVR): the teacher is irrelevant

In the **final** stage the teacher plays no role. The student is the *policy*
(emits a call); the *verifier* is the realized historical return you already know
because it's the past. The reward is **external and ground-truth, NOT
self-generated** — if the student "rewarded itself" it would collapse into a
self-confirming loop. "Unlimited" = sampling random `(ticker, as_of)` windows from
history whose future is already known (offline RLVR). This is why a noisy/overconfident
teacher cannot corrupt the final student — reality corrects it. (Same recipe as
DeepSeek-R1: SFT to imitate → RLVR to optimize.)

> Caveat: markets are ~52/48, not math. RLVR yields a *small calibrated edge +
> consistency + cost savings*, not alpha.

## Fields & glossary

Every question carries two records — an **opinion** (verdict, in the markdown) and a
**fact** (outcome, in `outcomes.jsonl`).

**Verdict** — the model's opinion (in each `q_*.md`, parsed from the fenced block):

| field | values | meaning |
|---|---|---|
| `bias` | `bullish` / `bearish` / `neutral` | expected direction |
| `conviction` | `0.0` – `1.0` | self-reported confidence |
| `target` | a price | take-profit level the model thinks is reachable |
| `invalidation` | a price | thesis-wrong level — "I'm wrong if price crosses this" |

> **Why `invalidation`, not `stop loss`?** A *stop loss* is an **execution** concept
> (the price where you exit a trade to cap a loss). *Invalidation* is an **analytical**
> concept (the price where the **thesis** is proven wrong). This model *analyzes* — it
> doesn't place orders — so "where my read breaks down" is the precise framing. In
> practice the two levels are usually the same price.

**Outcome** — the fact (in `outcomes.jsonl`, computed from the real future 20 bars):

| field | meaning |
|---|---|
| `realized_dir` | `up` / `down` / `flat` — noise-gated 20-day direction |
| `ret_5d` / `ret_10d` / `ret_20d` | realized return at 5 / 10 / 20 **trading days** — the **endpoint** move (`future_close / entry − 1`). `ret_20d` sets `realized_dir` and the reward's move strength |
| `max_favorable` (**MFE**) | peak upside reached during the window |
| `max_adverse` (**MAE**) | worst dip reached during the window |
| `vol_20d` | 20-day return volatility (the noise level) |
| `entry` | close at `as_of` — the reference price for direction-aware checks |
| `max_high` / `min_low` | absolute peak / trough price reached (for target & invalidation) |

> **Why a 20-day horizon?** 20 trading days ≈ 1 calendar month — a **swing-trading**
> window that matches the Wyckoff / price-action style of these analyses (a phase
> plays out over weeks, not minutes or quarters). It's the single fixed horizon for
> `ret_20d`, `realized_dir`, and the MFE/MAE window. Shorter is too choppy; longer
> drifts from what a near-term chart thesis actually claims.

**MFE / MAE** = Maximum Favorable / Adverse Excursion (John Sweeney, 1990s; standard
in quant backtesting — `backtrader`, `vectorbt`, `QuantStats`). They measure the
**path** extremes, as opposed to `ret_20d` which is the **endpoint**: `ret_20d` =
where price *ended*; MFE/MAE = the best/worst it *touched en route*. Don't confuse
MAE with **max drawdown**: drawdown is portfolio-level (peak-to-trough of cumulative
equity across many trades), while MAE is per-trade (entry-to-trough of one position).

**Reward coverage** — what `score.py` uses now vs. collects for later:

| field | scored now? | role |
|---|:--:|---|
| `bias` ↔ `realized_dir` | ✅ | core: direction right? |
| `conviction` | ✅ | core: confidence weight (confident-wrong penalized most) |
| `ret_20d`, `vol_20d` | ✅ | core: signal-rich gate + move strength |
| `target` ↔ `max_high` (MFE) | ✅ | path: take-profit reachable? (direction-aware) |
| `invalidation` ↔ `min_low` (MAE) | ✅ | path: stop breached? (direction-aware) |

**Path-aware layer** (wired in `score.py`): direction-aware checks using `entry` +
`max_high`/`min_low` (stored in `outcomes.jsonl`). A `target` on the correct side
counts as reached if the peak/trough touched it → small `+0.2 × conviction` bonus;
an `invalidation` breach → small `-0.3 × conviction` penalty. The combined
`reward = signed + path`. Path weights are deliberately small relative to the core
direction reward, because the path can conflict with the endpoint (a call right on
direction yet stopped out first). `target`/`invalidation` are also *imitated* by the
student during SFT (part of the teacher prose).

## Wiring your real data

`scripts/make_real_questions.py` reads an aipa OHLCV+MA dump (fetch **per ticker**),
splits each at `as_of`, builds the evidence from aipa's MA values + **MA scores**
(% distance of close from each MA — the key trend signal), and computes the
realized outcome from the real future 20 bars. To scale: edit its `TARGETS` list
`(ticker, as_of, tags)` and re-run. The 3 seed questions (FPT / VCB / BTCUSDT) are real.
