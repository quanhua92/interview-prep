#!/usr/bin/env python3
"""RLVR (TRL GRPOTrainer) -- reward the student's OWN call vs realized outcomes.

reward = CORE (direction: bias vs realized_dir, confidence-weighted, signal-rich gated)
       + PATH (target/invalidation vs MFE/MAE, direction-aware). Mirrors score.py.

The outcome is passed to the reward function as a DATASET COLUMN (never injected
into the prompt text -> leakage-safe). Prompts are the evidence from the question
files; outcomes come from outcomes.jsonl. This is the stage where the teacher is
irrelevant -- only the student's call vs reality is rewarded.

Requires: a GPU, TRL (>=0.16 with GRPOTrainer), and vLLM for fast generation.
TRL's GRPO API evolves; the config knobs below may need tweaking per version.

pip install "trl>=0.16" peft transformers accelerate vllm
"""
from __future__ import annotations
import json
import re
import sys
from pathlib import Path

from datasets import Dataset
from peft import LoraConfig
from transformers import AutoModelForCausalLM
from trl import GRPOTrainer, GRPOConfig

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "scripts"))
from _mdutil import parse_md  # noqa: E402

SFT_MODEL = "qwen-finance-sft"          # the cold-start student (from sft.py)
QUESTIONS = Path(__file__).resolve().parent.parent / "data" / "COPY_AND_RENAME"
OUTCOMES = Path(__file__).resolve().parent.parent / "outcomes.jsonl"

_VERDICT = re.compile(r"```verdict\s*(\{.*?\})\s*```", re.S)
TARGET_BONUS, INVAL_PENALTY = 0.2, 0.3


def _f(x):
    try:
        return float(x)
    except (TypeError, ValueError):
        return None


def extract_verdict(text):
    m = _VERDICT.search(text or "")
    if not m:
        return {}
    try:
        return json.loads(m.group(1))
    except Exception:
        return {}


def dir_of(bias):
    if not bias:
        return None
    b = bias.lower()
    return ("up" if b.startswith("bull") else "down" if b.startswith("bear")
            else "flat" if b.startswith("neutral") else None)


def reward(prompts, completions, **kwargs):
    """GRPO reward: list-aligned (completions, kwargs['outcome'])."""
    outs = kwargs["outcome"]
    out = []
    for comp, o in zip(completions, outs):
        v = extract_verdict(comp)
        bd = dir_of(v.get("bias"))
        realized = o.get("realized_dir")
        ret = float(o.get("ret_20d", 0.0))
        vol = float(o.get("vol_20d", 0.0)) or 1e-9
        strength = abs(ret) / vol
        hit = (bd == realized) if (bd and realized) else None
        conv = float(v.get("conviction", 0.5))
        signed = (conv if hit else -conv) * min(strength, 3.0) if hit is not None else 0.0
        e, mx, mn = _f(o.get("entry")), _f(o.get("max_high")), _f(o.get("min_low"))
        tg, iv = _f(v.get("target")), _f(v.get("invalidation"))
        path = 0.0
        if None not in (e, mx, mn) and bd in ("up", "down"):
            if bd == "up":
                if tg is not None and tg > e and mx >= tg:
                    path += TARGET_BONUS * conv
                if iv is not None and iv < e and mn <= iv:
                    path -= INVAL_PENALTY * conv
            else:
                if tg is not None and tg < e and mn <= tg:
                    path += TARGET_BONUS * conv
                if iv is not None and iv > e and mx >= iv:
                    path -= INVAL_PENALTY * conv
        out.append((signed + path) if strength >= 1.0 else 0.0)  # signal-rich gate
    return out


def build_dataset():
    outcomes = {}
    for line in OUTCOMES.read_text().splitlines():
        if line.strip():
            o = json.loads(line)
            outcomes[o["id"]] = o["outcome"]
    rows = []
    for md in sorted(QUESTIONS.glob("q_*.md")):
        r = parse_md(md)
        if r["id"] in outcomes:
            rows.append({"prompt": [{"role": "user", "content": r["question"]}],
                         "outcome": outcomes[r["id"]]})
    return Dataset.from_list(rows)


def main():
    model = AutoModelForCausalLM.from_pretrained(SFT_MODEL)
    ds = build_dataset()
    cfg = GRPOConfig(
        output_dir="outputs_rlvr",
        learning_rate=1e-6,
        per_device_train_batch_size=4,
        gradient_accumulation_steps=4,
        num_generations=8,                 # group size G for GRPO
        max_completion_length=640,
        temperature=0.7,
        beta=0.04,                         # KL to reference
        bf16=True,
        logging_steps=10,
        report_to="none",
        use_vllm=True,                     # fast on-policy generation
        vllm_mode="colocate",
    )
    trainer = GRPOTrainer(
        model=model, reward_funcs=reward, args=cfg, train_dataset=ds,
        peft_config=LoraConfig(r=16, lora_alpha=16,
                               target_modules=["q_proj", "k_proj", "v_proj", "o_proj"],
                               lora_dropout=0, bias="none", task_type="CAUSAL_LM"))
    trainer.train()
    trainer.save_model("qwen-finance-rlvr")


if __name__ == "__main__":
    main()
