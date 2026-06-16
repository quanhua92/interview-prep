#!/usr/bin/env python3
"""Scale up questions: sample N random (ticker, as_of) windows from an aipa dump,
build a question .md + outcome for each, append to COPY_AND_RENAME/ and outcomes.jsonl.

Reuses make_real_questions.build(). Fetch the dump PER TICKER first:
  for T in VCB FPT HPG ...; do
    uvx aipa-cli get-ohlcv-data $T --start-date 2024-01-01 --end-date 2026-06-16 \
      --no-system-prompt >> ohlcv.txt
  done
  python scripts/sampler.py ohlcv.txt --tickers VCB FPT HPG MWG GAS \
      --from-date 2024-06-01 --to-date 2026-03-01 --n 1000
"""
from __future__ import annotations
import argparse
import json
import random
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from make_real_questions import parse, build, TEMPLATE_DIR, OUTCOMES_FILE  # noqa: E402

MIN_HISTORY = 60   # bars before as_of (for MA200-ish + structure)
MIN_FUTURE = 21    # bars after as_of (20 + 1)


def max_id() -> int:
    best = 0
    for p in TEMPLATE_DIR.glob("q_*.md"):
        try:
            best = max(best, int(p.stem[2:]))
        except ValueError:
            pass
    return best


def tags_for(ticker: str) -> list[str]:
    return ["crypto"] if ticker.upper().endswith("USDT") else ["vn_stock"]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("data_file", help="aipa OHLCV+MA dump (per-ticker fetched)")
    ap.add_argument("--tickers", nargs="+", required=True)
    ap.add_argument("--from-date", required=True, help="earliest as_of YYYY-MM-DD")
    ap.add_argument("--to-date", required=True, help="latest as_of YYYY-MM-DD")
    ap.add_argument("--n", type=int, default=200)
    ap.add_argument("--seed", type=int, default=42)
    args = ap.parse_args()

    random.seed(args.seed)
    rows = parse(args.data_file)
    by_ticker: dict[str, list[str]] = {}
    for r in rows:
        by_ticker.setdefault(r["sym"], []).append(r["d"])

    cands = []
    for t in args.tickers:
        dates = sorted(by_ticker.get(t, []))
        for i, d in enumerate(dates):
            if args.from_date <= d <= args.to_date and i >= MIN_HISTORY and i <= len(dates) - MIN_FUTURE:
                cands.append((t, d))
    if not cands:
        sys.exit("no eligible (ticker, as_of) windows in range")
    random.shuffle(cands)

    qid = max_id()
    written = 0
    with open(OUTCOMES_FILE, "a") as f:
        for t, d in cands:
            if written >= args.n:
                break
            res, err = build(t, d, tags_for(t), rows)
            if err:
                continue
            md, outcome, dfrom, fto = res
            qid += 1
            q = f"q_{qid:06d}"
            (TEMPLATE_DIR / f"{q}.md").write_text(md.replace("{id}", q))
            f.write(json.dumps(
                {"id": q, "ticker": t, "as_of": d,
                 "data_range": {"from": dfrom, "to": d},
                 "future_range": {"to": fto, "horizon_days": 20},
                 "outcome": outcome}, ensure_ascii=False) + "\n")
            written += 1
    print(f"wrote {written} new questions (up to q_{qid:06d}) -> {TEMPLATE_DIR}")
    print(f"appended outcomes -> {OUTCOMES_FILE}")


if __name__ == "__main__":
    main()
