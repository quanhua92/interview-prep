#!/usr/bin/env python3
"""Generate REAL markdown question files from aipa OHLCV+MA+score data, plus a
separate outcomes.jsonl scoring index.

Fetch PER TICKER (multi-ticker + date-range is unreliable), e.g.:
  for T in VCB FPT BTCUSDT; do
    uvx aipa-cli get-ohlcv-data $T --start-date 2025-06-01 --end-date 2026-06-16 \
      --no-system-prompt >> ohlcv.txt
  done
  python scripts/make_real_questions.py ohlcv.txt

For each (ticker, as_of) writes:
  data/COPY_AND_RENAME/q_NNNNNN.md   <- question on top, EMPTY Answer, NO outcome
  outcomes.jsonl                     <- one line per id with the realized outcome
The outcome NEVER goes in the .md (the teacher must stay blind to the future).
"""
from __future__ import annotations
import json
import math
import sys
from pathlib import Path

DATA_FILE_DEFAULT = "/var/folders/hd/20zqmjkj7cd0wm4rv2230bm00000gn/T/opencode/ohlcv3.txt"
TEMPLATE_DIR = Path(__file__).resolve().parent.parent / "data" / "COPY_AND_RENAME"
OUTCOMES_FILE = Path(__file__).resolve().parent.parent / "outcomes.jsonl"
FUTURE_BARS = 20

TARGETS = [
    ("FPT", "2026-04-15", ["vn_stock", "tech"]),
    ("VCB", "2026-04-22", ["vn_stock", "banking"]),
    ("BTCUSDT", "2026-05-01", ["crypto", "trend"]),
]

QUESTION_BODY = (
    "Analyze {ticker} ({timeframe}) AS OF {as_of} using the Wyckoff method and "
    "price action. Use ONLY the evidence below; do NOT assume any knowledge of "
    "prices after the as-of date.\n\n"
    "Evidence (data range {dfrom} to {as_of}):\n{evidence}\n\n"
    "Cover: (1) phase / market position, (2) supply vs demand, (3) effort-vs-result "
    "on recent bars, (4) key levels, (5) scenario bias with conviction, "
    "(6) risks / invalidation. End with the fenced verdict block described in "
    "SUBAGENT_PROMPT.md."
)

MD_TMPL = """\
---
id: {id}
ticker: {ticker}
as_of: {as_of}
timeframe: {timeframe}
tags: [{tags}]
status: todo
---

# Question

{body}

# Answer

<!-- subagent writes below this line; never edit above this heading -->
"""


def parse(path):
    rows = []
    for line in Path(path).read_text().splitlines():
        p = line.split()
        if len(p) < 20 or p[0] == "time":
            continue
        try:
            rows.append({
                "d": p[0], "o": float(p[1]), "h": float(p[2]), "l": float(p[3]),
                "c": float(p[4]), "v": float(p[5]), "sym": p[6],
                "ma10": float(p[7]), "ma20": float(p[8]), "ma50": float(p[9]),
                "ma100": float(p[10]), "ma200": float(p[11]),
                "s10": float(p[12]), "s20": float(p[13]), "s50": float(p[14]),
                "s100": float(p[15]), "s200": float(p[16]),
                "cc": float(p[17]), "vc": float(p[18]), "tm": float(p[19]),
            })
        except ValueError:
            continue
    return rows


def swings(highs, lows, span=60):
    h = highs[-span:]
    lw = lows[-span:]
    sh = sl = ph = pl = None
    for i in range(len(h) - 2, 0, -1):
        if sh is None and h[i] >= h[i - 1] and h[i] >= h[i + 1]:
            sh = h[i]
        if ph is None and sh is not None and i < len(h) - 3 and \
           h[i] >= h[i - 1] and h[i] >= h[i + 1] and h[i] != sh:
            ph = h[i]
        if sl is None and lw[i] <= lw[i - 1] and lw[i] <= lw[i + 1]:
            sl = lw[i]
        if pl is None and sl is not None and i < len(lw) - 3 and \
           lw[i] <= lw[i - 1] and lw[i] <= lw[i + 1] and lw[i] != sl:
            pl = lw[i]
        if sh and sl:
            break
    hi = sh if sh else max(h)
    lo = sl if sl else min(lw)
    return hi, lo, sh, sl, ph, pl


def build(ticker, as_of, tags, all_rows):
    rows = [r for r in all_rows if r["sym"] == ticker and r["d"] <= as_of]
    fut = [r for r in all_rows if r["sym"] == ticker and r["d"] > as_of][:FUTURE_BARS]
    if len(rows) < 60 or len(fut) < FUTURE_BARS:
        return None, f"skip {ticker}: rows={len(rows)} fut={len(fut)}"
    r0 = rows[-1]
    closes = [r["c"] for r in rows]
    highs = [r["h"] for r in rows]
    lows = [r["l"] for r in rows]
    vols = [r["v"] for r in rows]
    entry = r0["c"]
    dfrom = rows[0]["d"]

    ret5 = entry / closes[-6] - 1 if len(closes) >= 6 else 0.0
    avg20v = sum(vols[-21:-1]) / 20
    vrat = r0["v"] / avg20v if avg20v else 0.0
    hi, lo, sh, sl, ph, pl = swings(highs, lows)
    pos = (entry - lo) / (hi - lo) if hi > lo else 0.5
    hh = sh is not None and ph is not None and sh > ph
    hl = sl is not None and pl is not None and sl > pl
    if hh and hl:
        struct = "HH/HL (uptrend)"
    elif sh is not None and ph is not None and sl is not None and pl is not None \
            and sh < ph and sl < pl:
        struct = "LH/LL (downtrend)"
    else:
        struct = "mixed/range"
    if r0["ma20"] > r0["ma50"] > r0["ma200"]:
        stack = "bullish (MA20>MA50>MA200)"
    elif r0["ma20"] < r0["ma50"] < r0["ma200"]:
        stack = "bearish (MA20<MA50<MA200)"
    else:
        stack = "mixed"

    evidence = (
        f"Price: close {entry:,.1f} | 1d {r0['cc']:+.2f}% | 5d {ret5*100:+.1f}%.\n"
        f"MA values: MA10 {r0['ma10']:,.0f} | MA20 {r0['ma20']:,.0f} | "
        f"MA50 {r0['ma50']:,.0f} | MA100 {r0['ma100']:,.0f} | MA200 {r0['ma200']:,.1f}.\n"
        f"MA scores (% above/below each MA): MA10 {r0['s10']:+.2f}% | "
        f"MA20 {r0['s20']:+.2f}% | MA50 {r0['s50']:+.2f}% | MA100 {r0['s100']:+.2f}% | "
        f"MA200 {r0['s200']:+.2f}%.\n"
        f"MA stack: {stack}.\n"
        f"Volume: {r0['v']/1e6:.2f}M vs 20d-avg {avg20v/1e6:.2f}M ({vrat:.2f}x) | "
        f"vol_changed {r0['vc']:+.1f}% | money_flow {r0['tm']/1e9:+.2f}B.\n"
        f"Structure: recent swing high {hi:,.1f} | recent swing low {lo:,.1f} | "
        f"60d range [{lo:,.1f}, {hi:,.1f}] | position {pos:.2f} | {struct}."
    )

    body = QUESTION_BODY.format(ticker=ticker, timeframe="daily", as_of=as_of,
                                dfrom=dfrom, evidence=evidence)
    md = MD_TMPL.format(id="{id}", ticker=ticker, as_of=as_of, timeframe="daily",
                        tags=", ".join(tags), body=body)

    f_c = [r["c"] for r in fut]
    f_h = [r["h"] for r in fut]
    f_l = [r["l"] for r in fut]
    ret_5d = f_c[4] / entry - 1
    ret_10d = f_c[9] / entry - 1
    ret_20d = f_c[-1] / entry - 1
    mfe = max(f_h) / entry - 1
    mae = min(f_l) / entry - 1
    rets = [closes[i] / closes[i - 1] - 1 for i in range(-20, 0)]
    mean = sum(rets) / len(rets)
    vol20 = math.sqrt(sum((x - mean) ** 2 for x in rets) / (len(rets) - 1))
    thr = 0.5 * vol20 * math.sqrt(20)
    rdir = "up" if ret_20d > thr else ("down" if ret_20d < -thr else "flat")
    outcome = {
        "ret_5d": round(ret_5d, 4), "ret_10d": round(ret_10d, 4),
        "ret_20d": round(ret_20d, 4),
        "max_favorable": round(mfe, 4), "max_adverse": round(mae, 4),
        "realized_dir": rdir, "vol_20d": round(vol20, 4),
        "entry": round(entry, 2), "max_high": round(max(f_h), 2),
        "min_low": round(min(f_l), 2),
    }
    return (md, outcome, dfrom, fut[-1]["d"]), None


def main():
    data_file = sys.argv[1] if len(sys.argv) > 1 else DATA_FILE_DEFAULT
    if not Path(data_file).exists():
        sys.exit(f"data file not found: {data_file}\nfetch it first, e.g.:\n"
                 f"  for T in VCB FPT BTCUSDT; do\n"
                 f"    uvx aipa-cli get-ohlcv-data $T --start-date 2025-06-01 "
                 f"--end-date 2026-06-16 --no-system-prompt >> ohlcv.txt\n  done")
    all_rows = parse(data_file)
    TEMPLATE_DIR.mkdir(parents=True, exist_ok=True)
    i = 1
    out_lines = []
    for ticker, as_of, tags in TARGETS:
        res, err = build(ticker, as_of, tags, all_rows)
        if err:
            print(err)
            continue
        md, outcome, dfrom, fto = res
        qid = f"q_{i:06d}"
        i += 1
        (TEMPLATE_DIR / f"{qid}.md").write_text(md.replace("{id}", qid))
        out_lines.append(json.dumps(
            {"id": qid, "ticker": ticker, "as_of": as_of,
             "data_range": {"from": dfrom, "to": as_of},
             "future_range": {"to": fto, "horizon_days": FUTURE_BARS},
             "outcome": outcome}, ensure_ascii=False))
        print(f"wrote {qid}.md  {ticker} {as_of}  dir={outcome['realized_dir']}  "
              f"ret20d={outcome['ret_20d']:+.1%}")
    OUTCOMES_FILE.write_text("\n".join(out_lines) + ("\n" if out_lines else ""))
    print(f"wrote {len(out_lines)} questions -> {TEMPLATE_DIR}/")
    print(f"wrote outcomes -> {OUTCOMES_FILE}  (kept OUT of the .md files)")


if __name__ == "__main__":
    main()
