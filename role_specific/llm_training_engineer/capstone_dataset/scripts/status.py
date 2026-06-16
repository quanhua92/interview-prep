#!/usr/bin/env python3
"""Coverage: how many questions each teacher has filled (status: done)."""
from __future__ import annotations
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from _mdutil import parse_md, teacher_dirs  # noqa: E402

data = Path("data")
template = data / "COPY_AND_RENAME"
n_q = len(list(template.rglob("q_*.md"))) if template.exists() else 0
print(f"COPY_AND_RENAME template: {n_q} questions\n")

teachers = teacher_dirs("data")
if not teachers:
    print("no teacher folders yet. Copy data/COPY_AND_RENAME to data/<model>/ and fill it.")
    sys.exit(0)

for t in teachers:
    mds = sorted(t.rglob("q_*.md"))
    done = sum(1 for md in mds if parse_md(md)["done"])
    print(f"{t.name:<28} {done}/{len(mds)} done")
