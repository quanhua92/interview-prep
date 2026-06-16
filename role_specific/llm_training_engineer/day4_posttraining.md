# Day 4 — Post-Training: DPO, GRPO & the Reasoning Revolution

> SFT makes a model fluent in your domain; post-training makes it *prefer the right answers*. Understand the post-training stack, why **DPO displaced RLHF**, how **GRPO + RLVR** power reasoning models, and run a light DPO.

## Objectives
- Understand the **post-training stack** and why each stage exists.
- Explain why **DPO displaced PPO-RLHF**, and pick among the **DPO family** (IPO/KTO/SimPO/ORPO).
- Explain **GRPO** (no critic) and **RLVR** (verifiable rewards), and why they unlocked reasoning models (DeepSeek-R1, Qwen3-thinking).
- Sketch the **R1 / Qwen3 reasoning pipelines** and know when to **distill** instead.
- Build **preference data** (human vs synthetic/RLAIF) and reason about judge bias.
- Run a **DPO via TRL `DPOTrainer`** on top of your Day-3 model.

---

## Concepts

### 1. The post-training stack

After SFT you have a model that *can* produce domain text. Post-training shapes *what it prefers*. The modern stack:

```
   ┌─────────────┐     ┌──────────────────────────┐     ┌──────────────────┐
   │  Base model │ ──► │        SFT               │ ──► │ Preference align │
   │ (pretrained)│     │ (instruction format,     │     │ (RLHF | DPO-     │
   └─────────────┘     │  domain style, facts)    │     │  family | RLAIF) │
                       └──────────────────────────┘     └────────┬─────────┘
                                                                │
                                          ┌─────────────────────┴─────────────────────┐
                                          ▼                                           ▼
                              ┌──────────────────────┐                  ┌──────────────────────────┐
                              │ IF task is verifiable│                  │  Optional general RL     │
                              │ (code/math/SQL/proof)│                  │  (helpfulness/safety)    │
                              │  → GRPO + RLVR loop  │                  │                          │
                              └──────────────────────┘                  └──────────────────────────┘
```

**Why each stage exists:**
- **SFT** — teaches format + domain knowledge from demonstrations.
- **Preference alignment** — encodes *which* of several valid answers is better, from human or synthetic preferences. DPO-family is the open default.
- **RLVR** — when the task has a **deterministic checker**, RL on verifiable rewards sharpens reasoning far beyond what SFT + DPO reach.

### 2. Classic RLHF (reward model + PPO)

The original pipeline: train a **reward model** on preference data, then run **PPO** to optimize the policy against it.
- **4 models in memory:** policy, reference, reward, critic → huge VRAM.
- **On-policy sampling** (generate from current policy each step) + KL penalty to the reference.
- **Brittle:** reward hacking, instability, hyperparameter-heavy.

**Still used at frontier labs** for subjective signals (helpfulness/safety) where no verifier exists — but **displaced in open work** by DPO and GRPO.

### 3. DPO — why it displaced RLHF

**DPO (Direct Preference Optimization)** reframes RLHF: the optimal policy is recoverable **in closed form** from preference pairs. So you optimize a **single binary cross-entropy** on `(chosen, rejected)` pairs — **no reward model, no RL, no critic**, and stable.

```
L_DPO = -log σ( β · [ log π(chosen)/π_ref(chosen)  -  log π(rejected)/π_ref(rejected) ] )
```

- `β` controls how far you move from the reference (SFT) policy.
- You keep a **reference model** (frozen SFT copy) for the KL anchor, but no separately trained reward model.
- **Result:** simpler, cheaper, more stable → became the open default after SFT.

### 4. The DPO family (2026)

| Variant | One-line idea | When to use |
|---|---|---|
| **DPO** | Ref-anchored pair loss (baseline) | Safe default |
| **IPO** | KL-regularized; robust on noisy/small data | Small/low-quality pref sets |
| **KTO** | **Unpaired** thumbs-up/down (unary) | Only pointwise feedback available |
| **SimPO** | **Reference-free** + length-normalized; often beats DPO | Want no reference model + better quality |
| **ORPO** | **Fuses SFT + preference in one stage** — no separate SFT→DPO | Fewer steps, simplest pipeline |

**2026 picks:** **SimPO/ORPO** for simplicity + no reference model; **KTO** when you only have unary feedback; **plain DPO** as the safe default.

### 5. GRPO — the open reasoning optimizer

**GRPO (Group Relative Policy Optimization)**, from **DeepSeekMath**, is the RL engine behind **DeepSeek-R1**. The key difference from PPO:

> **No critic / value model.** Sample a **group of G completions** per prompt, then use the group's mean/std as the baseline advantage:
>
> `A_i = (r_i − mean(r)) / std(r)`

```
   prompt ──► sample G completions ──► score each r_i ──► normalize within group ──► update policy
                                      (verifier or RM)    A_i = (r_i - μ) / σ
```

Removing the value function → **cheaper + more stable** → made **large-scale reasoning RL tractable**. GRPO is now the **de-facto open reasoning optimizer**.

**Related algorithms worth knowing (2026):**
- **REINFORCE++** — a simpler, often more stable baseline within the GRPO family; built into OpenRLHF.
- **RLOO (REINFORCE Leave-One-Out)** — uses leave-one-out within the group for lower-variance advantage estimates; also in OpenRLHF.
- **AsyncGRPO** (TRL 2026) — rollout worker runs in a separate child process with its own GIL, preventing autograd engine stalls that plagued vanilla GRPO at scale.

**GRPO stability tips (don't parrot the vanilla recipe uncritically):** conditional truncation masking for long outputs, diversity-determined temperature, removing KL loss with high clip ratios to encourage exploration.

### 6. RLVR — the 2025–26 trend

**RLVR (Reinforcement Learning with Verifiable Rewards):** use **deterministic, checkable rewards** — math answer match, code passing tests, a valid proof, a well-formed SQL/JSON — instead of a noisy reward model.

```
   prompt ──► sample k ──► deterministic verifier ──► binary reward ──► GRPO update ──► (harden verifier)
```

**Why it's central to reasoning models:**
- Sparse, **high-precision** rewards drive genuine exploration.
- **DeepSeek-R1** showed **emergent self-reflection / backtracking WITHOUT human reasoning traces** — the model learned to `think` and re-check purely from the reward signal.
- Underpins **DeepSeek-R1, Qwen3-thinking, QwQ, o1-style** models.

**Healthy skepticism (cite this in interviews):**
- **NeurIPS 2025** — *"Does RL Really Incentivize Reasoning Capacity in LLMs Beyond the Base Model?"* — argues RLVR may **narrow** exploration toward existing capability rather than invent fundamentally new reasoning (the gain is often in *sampling efficiency*, not new skill).
- **ICML 2026 — "Spurious Rewards"** — reports gains **even with random rewards**, casting doubt on what RLVR actually learns.
- **ICML 2026 — "Provable Benefits of RLVR over SFT"** — *counters* it, showing RLVR formally beats pure SFT under reasonable assumptions.
- Net: RLVR is powerful and real, but the field is actively debating *why* it works. Don't parrot "RL creates new reasoning" uncritically.

### 7. Reasoning model training (R1 / Qwen3 pipeline)

**DeepSeek-R1 route:**
1. **R1-Zero** — pure RL (GRPO + RLVR) *directly on the base model*, no SFT. Demonstrated emergent reasoning but messy output.
2. **R1** — **cold-start SFT** → **RLVR** → **rejection sampling** to build higher-quality SFT data → another RL pass → **distillation** into smaller dense models.

**Qwen3 four-stage pipeline:**
1. **Long-CoT cold-start SFT** (seed the thinking format).
2. **Reasoning RL** (GRPO + RLVR on verifiable tasks).
3. **Thinking-mode fusion SFT** — teaches the **`</think>` toggle** so the model can switch between thinking and non-thinking modes.
4. **General RL** (broad capability + safety).

**Distillation from a big reasoner into small models is now standard** — and often **cheaper than running your own RL.** If you need a small reasoner, distill from R1/Qwen3-thinking rather than training reasoning RL from scratch.

### 8. Preference data

| Source | Pros | Cons |
|---|---|---|
| **Human annotation** | Gold signal, captures nuance | Slow, expensive, inconsistent |
| **Synthetic / RLAIF** | Cheap, scalable | Judge bias, self-confirming loops |

**Common synthetic patterns:** sample **k completions** per prompt, rank with a **strong model (LLM-as-judge)**; **self-rewarding**; **best-of-n** filtering. Watch for **judge bias** (length, self-preference, position) and run judge calibration.

### 9. Safety, Constitutional AI, RLAIF

For **harmlessness/safety** there's no verifier, so **Constitutional AI / RLAIF** (model critiques its own outputs against a constitution) remains dominant. In practice RLVR and RLAIF **coexist**: **RLVR for skills, RLAIF + DPO for safety/style.**

### 10. Tooling (2026)

| Tool | Role | Notes |
|---|---|---|
| **TRL** | `DPOTrainer` / `GRPOTrainer` / `PPOTrainer` | Mainstream default; integrates with PEFT; research-focused trainers in `trl.experimental` |
| **verl** (volcengine) | Production-grade RL | **Leading for serious GRPO/RLVR at scale**; hybrid engine co-locates actor+vLLM on same GPUs |
| **OpenRLHF** | Ray-based, scalable RL | Good for distributed PPO/DPO/GRPO; REINFORCE++ and RLOO variants built in |
| **open-r1** | HF's open R1 reproduction | Reference implementation for reasoning RL |
| **Unsloth** | DPO / SFT / ORPO | Single-GPU; great for fast DPO iteration |

> `trlX` has been **largely superseded by TRL** — reach for TRL, not trlX.

### 11. What a startup actually does in 2026

```
1. Start from an OPEN base / reasoner  (Qwen3 / DeepSeek-R1-Distill / Llama 4)
2. Domain SFT                          (Unsloth + QLoRA — Day 3)
3. DPO / SimPO / ORPO on prefs         (generate via best-of-n + LLM-as-judge,
                                        or real user feedback)
4. IF the task is verifiable           (code / math / SQL / structured extraction)
   → add a LIGHT GRPO + RLVR loop      (deterministic checker as reward)
5. Distill a big reasoner into your    (often cheaper than running own RL)
   small deploy model
6. Skip reward-model + PPO             (unless you have frontier-lab infra)
```

---

## Hands-on exercise

**Run a DPO via TRL `DPOTrainer`** on top of your Day-3 SFT'd model.

1. Take your **Day-3 fine-tuned model** (`qwen25-7b-fin-qlora`).
2. Build **~200–500 `(prompt, chosen, rejected)` pairs**: for each prompt, generate **2 completions**, then have a **strong model (or yourself)** pick the better (chosen) and worse (rejected).
3. Format to TRL's **preference dataset schema** (`prompt` / `chosen` / `rejected`, each a string or chat-formatted list).
4. Run `DPOTrainer` with `lr=5e-6`, `beta=0.1`, 1 epoch.
5. **Qualitatively compare** SFT vs SFT+DPO on 5 prompts — look for tighter, more on-format, less hedged answers.

```python
# Day 4 hands-on — DPO with TRL on top of your Day-3 SFT model
import torch
from datasets import load_dataset
from unsloth import FastLanguageModel
from trl import DPOTrainer, DPOConfig

# 1. Load your Day-3 SFT model as both policy and frozen reference
model, tokenizer = FastLanguageModel.from_pretrained(
    model_name     = "qwen25-7b-fin-qlora",   # your Day-3 adapter dir
    max_seq_length = 2048,
    dtype          = None,
    load_in_4bit   = True,
)

# 2. Attach LoRA for the DPO update (keep base frozen, as in SFT)
model = FastLanguageModel.get_peft_model(
    model,
    r              = 16,
    target_modules = ["q_proj", "k_proj", "v_proj", "o_proj",
                      "gate_proj", "up_proj", "down_proj"],
    lora_alpha     = 16,
    lora_dropout   = 0,
    bias           = "none",
    use_gradient_checkpointing = "unsloth",
    random_state   = 3407,
)

# 3. Load preference data (JSONL: {"prompt","chosen","rejected"})
dataset = load_dataset("json",
                       data_files="day4_pref_pairs.jsonl",
                       split="train")

# 4. Build DPO trainer
trainer = DPOTrainer(
    model         = model,
    ref_model     = None,          # None -> PEFT auto-disables adapter for the ref
    tokenizer     = tokenizer,
    train_dataset = dataset,
    args = DPOConfig(
        per_device_train_batch_size = 2,
        gradient_accumulation_steps = 4,
        learning_rate     = 5e-6,   # MUCH lower than SFT's 2e-4
        max_length        = 2048,
        max_prompt_length = 1024,
        beta              = 0.1,    # KL strength to reference policy
        num_train_epochs  = 1,
        bf16              = torch.cuda.is_bf16_supported(),
        logging_steps     = 10,
        optim             = "adamw_8bit",
        lr_scheduler_type = "cosine",
        output_dir        = "outputs_dpo",
        report_to         = "none",
    ),
)

# 5. Train + save
trainer.train()
model.save_pretrained("qwen25-7b-fin-dpo")
tokenizer.save_pretrained("qwen25-7b-fin-dpo")

# 6. Qualitative compare: SFT vs SFT+DPO on 5 held-out prompts
FastLanguageModel.for_inference(model)
for prompt in HELD_OUT_PROMPTS:
    inputs = tokenizer.apply_chat_template(
        [{"role": "user", "content": prompt}],
        tokenize=True, add_generation_prompt=True, return_tensors="pt").to("cuda")
    print(tokenizer.decode(
        model.generate(input_ids=inputs, max_new_tokens=256,
                       do_sample=False)[0], skip_special_tokens=True))
```

**Preference data schema** (`day4_pref_pairs.jsonl`, one record per line):

```json
{"prompt": "Analyze FPT's weekly trend.", "chosen": "<tight, well-grounded analysis>", "rejected": "<vague, hedged, off-format answer>"}
```

**What "better" looks like for this domain:** correct numbers, clear direction (bullish/bearish/neutral), follows your analysis template, **no invented facts**. The DPO loss pushes the model toward the chosen distribution and away from the rejected one.

---

## Checklist
- [ ] Can draw the post-training stack (SFT → preference align → optional RLVR).
- [ ] Can explain **why DPO displaced PPO-RLHF** (closed-form, no RM, no critic, stable).
- [ ] Know the DPO family tradeoffs and a 2026 pick per situation.
- [ ] Can explain **GRPO's trick** (group-relative advantage, no value model).
- [ ] Can explain **RLVR** and **why it powers reasoning** — plus the healthy skepticism.
- [ ] Can sketch the **R1** and **Qwen3** pipelines and know when to **distill**.
- [ ] Built **~200–500 preference pairs** (best-of-n + LLM-as-judge or hand-labeled).
- [ ] Ran `DPOTrainer` at `lr=5e-6`, `beta=0.1`, 1 epoch on the Day-3 model.
- [ ] Compared **SFT vs SFT+DPO** on 5 prompts and noted concrete differences.

## What to explain in interview

**Q: Why did DPO displace RLHF/PPO?**
DPO shows the optimal policy is recoverable in closed form from preference pairs, so you train a single binary cross-entropy on (chosen, rejected) — no reward model, no critic, no RL loop — making it simpler, cheaper, and far more stable.

**Q: When would you use KTO or SimPO instead of DPO?**
KTO when I only have unary thumbs-up/down (no pairs); SimPO when I want to drop the reference model and add length-normalization, which often beats plain DPO; ORPO if I want to skip the separate SFT step entirely.

**Q: What is GRPO and why does it matter for reasoning?**
GRPO samples a group of G completions per prompt and uses the group's mean/std as the advantage baseline, so it needs **no value/critic model** — cheaper and more stable than PPO, which is what made large-scale reasoning RL (DeepSeek-R1) tractable.

**Q: What is RLVR and why is it the 2025–26 trend?**
RLVR uses deterministic, checkable rewards (math answer match, code passing tests) instead of a noisy reward model; sparse high-precision rewards drive exploration and produced emergent self-reflection in DeepSeek-R1. That said, recent work debates whether RLVR invents new reasoning or just sharpens sampling efficiency.

**Q: How would you build a small reasoner without frontier-lab infra?**
Start from an open base/reasoner, do domain SFT, then DPO/ORPO on preference pairs; if the task is verifiable, add a light GRPO+RLVR loop with a deterministic checker; otherwise **distill a big reasoner** (R1/Qwen3-thinking) into my small deploy model — usually cheaper than running my own RL.

**Q: How do you mitigate reward-model / judge bias in preference data?**
Use multiple judge models or judge ensembles, control for length/position bias, calibrate the judge against a small human-labeled set, and prefer **verifiable rewards** over model-judged rewards whenever the task allows.
