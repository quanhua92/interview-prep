#!/usr/bin/env python3
"""Score each teacher's verdicts against realized outcomes (outcomes.jsonl).

Two reward layers:
  CORE (direction): bias vs realized_dir, confidence-weighted, signal-rich gated.
  PATH (target/invalidation vs MFE/MAE): direction-aware, using entry + max_high/min_low —
       target reachable within the peak  -> small bonus (+0.2 x conviction)
       invalidation breached by the trough -> small penalty (-0.3 x conviction)
Aggregates over signal-rich examples (single outcomes are noisy).
Writes data/<teacher>/_scores.jsonl and scores_summary.json.
"""
from __future__ import annotations
import argparse
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from _mdutil import parse_md, teacher_dirs  # noqa: E402

MIN_SIGNAL = 1.0
TARGET_BONUS = 0.2          # x conviction
INVALIDATION_PENALTY = 0.3  # x conviction


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


def _f(x):
    try:
        return float(x)
    except (TypeError, ValueError):
        return None


def path_checks(bias_dir, verdict, outcome):
    """Direction-aware: was the target reachable / was the invalidation hit?

    Bullish: target above entry (checked vs max_high), stop below entry (vs min_low).
    Bearish: target below entry (vs min_low), stop above entry (vs max_high).
    Targets/stops on the wrong side (nonsense) are ignored. Returns (None, None) if
    the needed prices are missing or bias is neutral.
    """
    entry = _f(outcome.get("entry"))
    mxh = _f(outcome.get("max_high"))
    mnl = _f(outcome.get("min_low"))
    target = _f(verdict.get("target"))
    inval = _f(verdict.get("invalidation"))
    if None in (entry, mxh, mnl) or bias_dir in (None, "flat"):
        return None, None
    target_reached = invalidation_hit = None
    if bias_dir == "up":
        if target is not None and target > entry:
            target_reached = mxh >= target
        if inval is not None and inval < entry:
            invalidation_hit = mnl <= inval
    else:  # bearish / "down"
        if target is not None and target < entry:
            target_reached = mnl <= target
        if inval is not None and inval > entry:
            invalidation_hit = mxh >= inval
    return target_reached, invalidation_hit


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--data-dir", default="data")
    ap.add_argument("--outcomes", default="outcomes.jsonl")
    ap.add_argument("--min-signal", type=float, default=MIN_SIGNAL)
    args = ap.parse_args()

    op = Path(args.outcomes)
    if not op.exists():
        sys.exit(f"outcomes not found: {op}. run make_real_questions.py first.")
    outcomes = {}
    for line in op.read_text().splitlines():
        if line.strip():
            o = json.loads(line)
            outcomes[o["id"]] = o["outcome"]

    summary = {}
    for t in teacher_dirs(args.data_dir):
        rows = []
        for md in sorted(t.rglob("q_*.md")):
            r = parse_md(md)
            oid = r["id"]
            if oid not in outcomes or not r["verdict"]:
                continue
            out = outcomes[oid]
            v = r["verdict"]
            bias_dir = dir_of(v.get("bias"))
            realized = out.get("realized_dir")
            ret = float(out.get("ret_20d", 0.0))
            vol = float(out.get("vol_20d", 0.0)) or 1e-9
            strength = abs(ret) / vol
            signal_rich = strength >= args.min_signal
            hit = (bias_dir == realized) if (bias_dir and realized) else None
            conv = float(v.get("conviction", 0.5))
            signed = (conv if hit else -conv) * min(strength, 3.0) if hit is not None else 0.0
            target_reached, invalidation_hit = path_checks(bias_dir, v, out)
            path = 0.0
            if target_reached:
                path += TARGET_BONUS * conv
            if invalidation_hit:
                path -= INVALIDATION_PENALTY * conv
            rows.append({
                "id": oid, "teacher": t.name, "bias": v.get("bias"),
                "bias_dir": bias_dir, "realized_dir": realized, "hit": hit,
                "signal_rich": signal_rich, "ret_20d": ret, "vol_20d": vol,
                "signed_score": round(signed, 4),
                "target_reached": target_reached, "invalidation_hit": invalidation_hit,
                "path_score": round(path, 4), "reward": round(signed + path, 4),
            })
        (t / "_scores.jsonl").write_text(
            "\n".join(json.dumps(x, ensure_ascii=False) for x in rows)
            + ("\n" if rows else ""))
        rich = [r for r in rows if r["signal_rich"] and r["hit"] is not None]
        n = len(rich) or 1
        acc = sum(r["hit"] for r in rich) / n
        mean_signed = sum(r["signed_score"] for r in rich) / n
        mean_reward = sum(r["reward"] for r in rich) / n
        summary[t.name] = {"n_signal_rich": len(rich), "accuracy": round(acc, 3),
                           "mean_signed": round(mean_signed, 3),
                           "mean_reward": round(mean_reward, 3)}
        print(f"{t.name:<28} answered={len(rows):>4} signal_rich={len(rich):>4} "
              f"acc={acc:.3f} signed={mean_signed:+.3f} reward={mean_reward:+.3f}")

    Path("scores_summary.json").write_text(json.dumps(summary, indent=2))
    print("wrote scores_summary.json")


if __name__ == "__main__":
    main()
