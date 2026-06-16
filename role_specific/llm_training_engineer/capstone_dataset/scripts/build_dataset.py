#!/usr/bin/env python3
"""Assemble ChatML train/eval JSONL from filled teacher markdown.

Reads data/<teacher>/**/*.md (recurses into batch subfolders) and joins each
answer's verdict with the realized outcome in outcomes.jsonl. The outcome is used
as a LABEL/REWARD only and is NEVER written into the messages (leakage guard).

Modes:
  sft : one assistant target per question; prefer a teacher whose verdict matched
        the realized direction (rejection-sampling), else the first available.
  dpo : for questions with >=2 teachers, emit {prompt, chosen, rejected} where
        chosen matched the future, rejected missed it. Signal-rich only.
"""
from __future__ import annotations
import argparse
import json
import random
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from _mdutil import parse_md, teacher_dirs  # noqa: E402


def dir_of(bias):
    if not bias:
        return None
    b = bias.lower()
    if b.startswith("bull"):
        return "up"
    if b.startswith("bear"):
        return "down"
    if b.startswith("neutral") or b.startswith("flat"):
        return "flat"
    return None


def signal_hit(verdict, outcome, min_signal):
    out = outcome or {}
    bias_dir = dir_of((verdict or {}).get("bias"))
    realized = out.get("realized_dir")
    ret = float(out.get("ret_20d", 0.0))
    vol = float(out.get("vol_20d", 0.0)) or 1e-9
    signal_rich = abs(ret) / vol >= min_signal
    hit = (bias_dir == realized) if (bias_dir and realized) else None
    return signal_rich, hit


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--mode", choices=["sft", "dpo"], default="sft")
    ap.add_argument("--manifest", default="manifest.json")
    ap.add_argument("--data-dir", default="data")
    ap.add_argument("--outcomes", default="outcomes.jsonl")
    ap.add_argument("--out-dir", default="build")
    ap.add_argument("--min-signal", type=float, default=1.0)
    ap.add_argument("--seed", type=int, default=42)
    args = ap.parse_args()

    m = json.loads(Path(args.manifest).read_text())
    random.seed(args.seed)
    system = m.get("system_prompt")
    holdout_tickers = set(m.get("holdout_tickers", []))
    holdout_frac = float(m.get("holdout_frac", 0.1))

    outcomes = {}
    for line in Path(args.outcomes).read_text().splitlines():
        if line.strip():
            o = json.loads(line)
            outcomes[o["id"]] = (o["outcome"], o.get("ticker", ""))

    # gather answers: id -> list of teacher records
    by_id: dict[str, list] = {}
    for t in teacher_dirs(args.data_dir):
        for md in sorted(t.rglob("q_*.md")):
            r = parse_md(md)
            if not r["answer"].strip() or r["id"] not in outcomes:
                continue
            outcome, _ = outcomes[r["id"]]
            by_id.setdefault(r["id"], []).append({
                "teacher": t.name, "ticker": r["ticker"], "as_of": r["as_of"],
                "question": r["question"], "answer": r["answer"],
                "verdict": r["verdict"], "outcome": outcome,
            })

    def is_holdout(ticker):
        return ticker in holdout_tickers or random.random() < holdout_frac

    train, held = [], []
    for oid, recs in by_id.items():
        if args.mode == "sft":
            # prefer a teacher whose verdict matched the realized direction
            cands = []
            for a in recs:
                rich, hit = signal_hit(a["verdict"], a["outcome"], args.min_signal)
                if rich and hit:
                    cands.append(a)
            chosen = cands[0] if cands else recs[0]
            msgs = []
            if system:
                msgs.append({"role": "system", "content": system})
            msgs.append({"role": "user", "content": chosen["question"]})
            msgs.append({"role": "assistant", "content": chosen["answer"]})
            row = {"id": oid, "teacher": chosen["teacher"], "messages": msgs,
                   "meta": {"ticker": chosen["ticker"], "as_of": chosen["as_of"]}}
            (held if is_holdout(chosen["ticker"]) else train).append(row)
        else:  # dpo
            rich = []
            for a in recs:
                sr, hit = signal_hit(a["verdict"], a["outcome"], args.min_signal)
                if sr and hit is not None:
                    rich.append((hit, a))
            hits = [a for hit, a in rich if hit]
            miss = [a for hit, a in rich if not hit]
            if not hits or not miss:
                continue
            ch, rj = random.choice(hits), random.choice(miss)
            row = {"id": oid, "prompt": ch["question"],
                   "chosen": ch["answer"], "rejected": rj["answer"],
                   "meta": {"ticker": ch["ticker"], "as_of": ch["as_of"]}}
            if system:
                row["system"] = system
            (held if is_holdout(ch["ticker"]) else train).append(row)

    out = Path(args.out_dir)
    out.mkdir(parents=True, exist_ok=True)
    (out / f"{args.mode}_train.jsonl").write_text(
        "\n".join(json.dumps(r, ensure_ascii=False) for r in train) + ("\n" if train else ""))
    (out / f"{args.mode}_eval.jsonl").write_text(
        "\n".join(json.dumps(r, ensure_ascii=False) for r in held) + ("\n" if held else ""))

    leaked = sum(
        any(k in json.dumps(r, ensure_ascii=False)
            for k in ('"realized_dir"', '"ret_20d"', '"future_range"'))
        for r in train + held)
    print(f"mode={args.mode}  train={len(train)}  eval={len(held)}  -> {out}/")
    print(f"LEAKAGE CHECK: {leaked} rows contain outcome fields (must be 0)")


if __name__ == "__main__":
    main()
