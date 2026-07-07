# LLM Sampling Strategies
- **Category**: LLM Systems
- **Difficulty**: Medium
- **Target Role**: LLM Inference Engineer / LLM Serving Engineer
- **Source**: sampling.py / SAMPLING.md (tiny-llm)
- **Flashcards**: [LLM Systems deck](../flash_cards/llm/llm_systems.md)

---

## Concept Overview

Think of sampling as rolling a **loaded die with one face per vocabulary word**. The model doesn't hand you the next token directly — it gives you a *preference score* (logit) for every possible next word, and sampling is how you convert those scores into a single choice. Four strategies give you four different ways to *shape the die* before you roll it: greedy always picks the heaviest face, temperature reshapes all the weights, top-$k$ blanks out all but the highest $k$ faces, and top-$p$ (nucleus) blanks everything past a cumulative probability threshold — adapting the kept set to the distribution's actual shape.

The full token-generation pipeline: each step, the model produces a logit vector of shape `[vocab_size]`, you apply your strategy to filter/reshape it, then draw one token from the resulting distribution. That token is appended to the input and the loop repeats.

### The Problem It Solves

Without a strategy you face two failure modes:
- **Always argmax (greedy)**: the model loops and degenerates. The single most-likely next word after a repeated phrase is the phrase again ("neural text degeneration", Holtzman et al. 2019).
- **Pure sampling ($T=1$, no filtering)**: the low-probability tail gets drawn too often $\rightarrow$ incoherent outputs. On the worked example, the nonsense token "qqq" would appear 2.6% of the time.

### How It Works

```text
┌──────────────────────────┐
│ LM-head logits z : [V]   │
└────────────┬─────────────┘
             │
             ├──( temp == 0 )──▶ ┌────────────────────┐
             │                   │ greedy: argmax     │
             │                   │ (no RNG)           │
             │                   └────────────────────┘
             ▼
┌──────────────────────────┐
│ 1. divide by temp        │
└────────────┬─────────────┘
             ▼
┌──────────────────────────┐
│ 2. top-k mask            │
│    keep k highest,       │
│    rest -inf             │
└────────────┬─────────────┘
             ▼
┌──────────────────────────┐
│ 3. top-p mask            │
│    cumsum(probs) >= p,   │
│    rest -inf             │
└────────────┬─────────────┘
             ▼
┌──────────────────────────┐
│ 4. categorical draw      │
│    (ONLY random step)    │
└──────────────────────────┘
```

**Production pipeline order** (from `make_sampler`):
1. $T == 0$ $\rightarrow$ return `argmax` (greedy, skip everything else)
2. Divide logits by $T$
3. Apply top-$k$ mask (mask outside top-$k$ to $-\infty$)
4. Apply top-$p$ mask (mask outside nucleus to $-\infty$)
5. `categorical draw` — the **only** random step

---

## Worked Example

All numbers from `sampling_output.txt` (run `uv run python sampling.py`).

### Base Distribution (Section A)

**Fixed logits** (vocab size = 8):
```
LOGITS = [2.3, 2.0, 0.4, 1.5, 0.1, 2.5, 0.7, 1.2]
TOKENS = ["the", "cat", "xyz", "sat", "qqq", "on", "a", "mat"]
```

| idx | token | logit   | prob (softmax) | logprob  |
|-----|-------|---------|----------------|----------|
| 0   | the   | +2.3000 | **0.2377**     | −1.4367  |
| 1   | cat   | +2.0000 | **0.1761**     | −1.7367  |
| 2   | xyz   | +0.4000 | 0.0356         | −3.3367  |
| 3   | sat   | +1.5000 | 0.1068         | −2.2367  |
| 4   | qqq   | +0.1000 | 0.0263         | −3.6367  |
| 5   | **on** | +2.5000 | **0.2903**    | −1.2367  |
| 6   | a     | +0.7000 | 0.0480         | −3.0367  |
| 7   | mat   | +1.2000 | 0.0791         | −2.5367  |

$\sum \text{probs} = 1.000000$  ·  $\text{argmax} = \text{idx } 5 \text{ ("on")}$

---

### Temperature Scaling (Section B)

$$p_i(T) = \text{softmax}\left(\frac{z_i}{T}\right)$$

High $T$ = flatter (more random); low $T$ = sharper.

| idx | token | T=0.5  | T=1.0  | T=2.0  |
|-----|-------|--------|--------|--------|
| 0   | the   | 0.2917 | 0.2377 | 0.1858 |
| 1   | cat   | 0.1601 | 0.1761 | 0.1599 |
| 2   | xyz   | 0.0065 | 0.0356 | 0.0719 |
| 3   | sat   | 0.0589 | 0.1068 | 0.1245 |
| 4   | qqq   | 0.0036 | 0.0263 | 0.0618 |
| 5   | **on**| **0.4351** | **0.2903** | **0.2053** |
| 6   | a     | 0.0119 | 0.0480 | 0.0835 |
| 7   | mat   | 0.0323 | 0.0791 | 0.1072 |

- $\text{entropy}(T=0.5) = 1.3981 \text{ nats}$ (sharp)
- $\text{entropy}(T=1.0) = 1.8062 \text{ nats}$
- $\text{entropy}(T=2.0) = 1.9984 \text{ nats}$ (flat)

> **Rule:** $T \rightarrow 0 \Rightarrow$ greedy; $T \rightarrow \infty \Rightarrow$ uniform. $T < 1$ = confident, $T > 1$ = creative.

---

### Greedy Decoding (Section C)

```
greedy(LOGITS) = argmax = idx 5 ("on")
```

$T=0$ is a **special case**: skip softmax entirely, return argmax directly. Deterministic, zero RNG, same token every call. Use for evaluation / factual QA — never for creative generation.

---

### Top-$k = 3$ (Section D)

Blank all but the 3 highest logits to $-\infty$. Renormalize over survivors.

- **KEPT** indices: `[0, 1, 5]` $\rightarrow$ tokens `['the', 'cat', 'on']`
- **MASKED** indices: `[2, 3, 4, 6, 7]`

| idx | token | logit   | prob (renorm) |
|-----|-------|---------|---------------|
| 0   | the   | +2.3000 | 0.3376        |
| 1   | cat   | +2.0000 | 0.2501        |
| 5   | on    | +2.5000 | **0.4123**    |
| others | — | -inf  | 0.0000        |

**The flaw of top-$k$**: $k$ is *fixed*. On a peaked distribution (one token at 95%), $k=50$ lets 49 junk tokens back in. On a flat distribution, $k=10$ cuts good options. Top-$k$ is blind to distribution shape — that's what top-$p$ fixes.

---

### Top-$p = 0.6$ / Nucleus Sampling (Section E)

Keep the **smallest set** whose cumulative probability $\ge p$. Adaptive size.

**Algorithm:**
1. Sort tokens DESC by probability
2. $\text{cumsum}(\text{probs})$ — **on probs, NOT logprobs** (see pitfall below)
3. Keep where $\text{cumsum} < p$; **always keep top-1** (nucleus never empty)
4. Mask the rest to $-\infty$

| rank | idx | token | prob   | cumsum    | cumsum<0.6? | kept?  |
|------|-----|-------|--------|-----------|-------------|--------|
| 0    | 5   | on    | 0.2903 | 0.2903    | yes         | **KEEP** |
| 1    | 0   | the   | 0.2377 | **0.5281** | yes        | **KEEP** |
| 2    | 1   | cat   | 0.1761 | 0.7042    | no          | mask   |
| 3    | 3   | sat   | 0.1068 | 0.8110    | no          | mask   |
| 4    | 7   | mat   | 0.0791 | 0.8901    | no          | mask   |
| 5    | 6   | a     | 0.0480 | 0.9381    | no          | mask   |
| 6    | 2   | xyz   | 0.0356 | 0.9737    | no          | mask   |
| 7    | 4   | qqq   | 0.0263 | 1.0000    | no          | mask   |

**NUCLEUS (top-$p=0.6$) = indices `[0, 5]`** (`['the', 'on']`), prob mass `0.5281`.

**Top-$k$ vs top-$p$ on this distribution:**

| | top-$k=3$ | top-$p=0.6$ |
|---|---|---|
| Kept indices | `[0, 1, 5]` | `[0, 5]` |
| Size | 3 (fixed) | 2 (adaptive) |
| Why | always 3 | top-2 already cover 52.8% $> p$; 3rd token excluded |

---

### The #1 Bug: cumsum on logprobs instead of probs (Section F)

Logprobs are always $\le 0$. Their cumsum stays negative forever — always less than any positive $p$. Result: **nothing gets masked**; the nucleus silently becomes the entire vocabulary.

| | Correct: cumsum on **probs** | Wrong: cumsum on **logprobs** |
|---|---|---|
| Nucleus | **2 tokens** `[0, 5]` | **8 tokens** (entire vocab!) |
| Filtered? | ✓ YES | ✗ NO — silent bug |

Concrete numbers ($p=0.6$):
- $\text{cumsum}(\text{probs})$ at cat = **0.7042** $\rightarrow$ $> 0.6$ $\rightarrow$ masked ✓
- $\text{cumsum}(\log \text{probs})$ at cat = **−4.4100** $\rightarrow$ $< 0.6$ $\rightarrow$ NOT masked (bug!)

**Fix**: `cumsum(exp(logprobs))` — the `exp` is mandatory.

---

### Combined Pipeline (Section G)

Config: $T=0.7$, top-$k=3$, top-$p=0.6$

After top-$k=3$ then top-$p=0.6$, only `idx 5 ("on")` survives both filters.
After $/T=0.7$ and renormalize: `idx 5 ("on")` has $\text{prob} = 1.0000$.

`torch.manual_seed(0); multinomial → idx 5 ("on")`

> **Key insight**: composing filters is NOT set-intersection. Top-$p$ runs on the **renormalized post-top-$k$ distribution**, so the nucleus boundary shifts. The order and renormalization both matter.

---

## Complexity & Trade-offs

| Metric | Value | Notes |
|--------|-------|-------|
| Greedy complexity | $\mathcal{O}(V)$ | argmax scan |
| Temperature overhead | $\mathcal{O}(V)$ | scalar division + softmax |
| Top-$k$ overhead | $\mathcal{O}(V \log k)$ | partial sort |
| Top-$p$ overhead | $\mathcal{O}(V \log V)$ | full sort + cumsum |
| Top-$k$: fixed or adaptive? | Fixed | Always keeps exactly $k$ tokens |
| Top-$p$: fixed or adaptive? | **Adaptive** | Set size varies per distribution |
| RNG steps per token | 1 | Only the final multinomial draw |
| Seed usage | Once per generation | Makes entire decode reproducible |
| Production default | $T=0.7$, top-$p=0.95$ | Nucleus with mild temperature |

---

## Common Interview Questions & How to Answer

### Q1: What is the difference between top-$k$ and top-$p$ sampling?
- **Answer**: Top-$k$ keeps a **fixed number** of tokens (always $k$). Top-$p$ (nucleus) keeps the **smallest set** of tokens whose cumulative probability reaches $p$ — so the set size *adapts* to the distribution shape. On a confident distribution, top-$p$ may keep just 1 token; on a flat distribution it may keep 20+. Concrete example: top-$k=3$ keeps `[0,1,5]` (always 3), top-$p=0.6$ keeps `[0,5]` (just 2, because the top-2 already cover 52.8%). Top-$p$ is adaptive; top-$k$ is blind to distribution shape.

### Q2: Why must you cumsum on probabilities and NOT log-probabilities in top-$p$?
- **Answer**: Logprobs are always $\le 0$, so their cumsum stays negative forever, making `cumsum(logprobs) < p` always true for any positive $p$. This means *nothing* ever gets masked — the nucleus silently becomes the whole vocabulary with no error. The fix is `cumsum(exp(logprobs))`. This is the single most common top-$p$ implementation bug.

### Q3: What does temperature do mathematically, and what is its effect on entropy?
- **Answer**: Temperature $T$ divides the logits *before* softmax: `probs_T = softmax(z / T)`. Dividing by $T < 1$ widens the logit gaps (sharpens toward argmax); $T > 1$ narrows gaps (flattens toward uniform). Real numbers: $\text{entropy}(T=0.5) = 1.3981 \text{ nats}$, $\text{entropy}(T=1.0) = 1.8062 \text{ nats}$, $\text{entropy}(T=2.0) = 1.9984 \text{ nats}$. $T=0$ collapses to a one-hot $\rightarrow$ greedy.

### Q4: What is the correct sampling pipeline order and why does it matter?
- **Answer**: The order is: $/T \rightarrow \text{top-}k \rightarrow \text{top-}p \rightarrow \text{multinomial}$. Temperature must come first because it reshapes the distribution that top-$p$ then cuts. Applying temperature *after* top-$p$ means top-$p$ computed on the wrong distribution. Top-$k$ is order-insensitive to temperature (positive scaling preserves rank), but top-$p$ is sensitive (temperature reshapes cumulative probabilities). Filter steps are deterministic; only the final `multinomial` uses the RNG.

### Q5: When would you use greedy vs nucleus sampling?
- **Answer**: Use **greedy** ($T=0$) for factual QA, benchmarks, or any task needing reproducibility and the single-best answer. Use **nucleus** ($\text{top-}p \in [0.9, 0.95]$, $T=0.7$) for creative generation, dialogue, and summarization — where diversity and avoiding repetition loops matter. Greedy is prone to degenerate looping on creative tasks.

### Q6: What is "neural text degeneration" and which sampling strategy addresses it?
- **Answer**: Neural text degeneration (Holtzman et al., ICLR 2020) is the failure mode where greedy or beam search produces repetitive, loopy text — because the most likely next token after a repeated phrase is the phrase again. Top-$p$ (nucleus) sampling addresses it by cutting the low-probability tail while adapting the shortlist to the distribution shape, preventing the model from getting stuck in high-probability repetition loops.

---

## Pro-Tip: How to Impress the Interviewer

- **Cite real numbers**: "On 8-token vocab with logits `[2.3,2.0,0.4,1.5,0.1,2.5,0.7,1.2]`, top-$k=3$ keeps `[0,1,5]` but top-$p=0.6$ keeps `[0,5]` because the top-2 already hold $52.8\%$ — and adding a third would push past 0.6."
- **Know the silent failure mode**: logprob cumsum produces no error, no crash — just a nucleus equaling the entire vocabulary. "I always `assert nucleus_size < vocab_size` in integration tests."
- **Know all three components**: $T$ (reshapes), top-$k$ (hard cutoff), top-$p$ (adaptive cutoff). Production systems use all three in sequence.
- **Mention beam search as a contrast**: keeps top-$B$ *sequences* (not tokens) across steps. Deterministic but expensive $\mathcal{O}(B \times V)$ per step and prone to generic outputs. Nucleus remains the production default.
- **Temperature entropy intuition**: at $T=0.5$, entropy drops to $1.3981\text{ nats}$ ($-23\%$ from $T=1$); at $T=2.0$, it rises to $1.9984\text{ nats}$ ($+11\%$). The "creativity dial" has concrete, measurable effects.
