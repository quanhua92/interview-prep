#!/usr/bin/env python3
"""Benchmark patterns across languages with timing.

Usage:
    python scripts/bench.py                              Run all patterns in all langs
    python scripts/bench.py sliding_window                Run one pattern in all langs
    python scripts/bench.py sliding_window --lang py      Run one pattern in Python only
    python scripts/bench.py --all --lang c                Run all patterns in C only
    python scripts/bench.py --lang py --lang js           Run all patterns in Python + JS
"""

import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

LANGS = ["py", "c", "cpp", "rs", "js"]
PATTERNS = [
    "sliding_window", "two_pointers", "bfs", "fast_slow_pointers",
    "merge_intervals", "binary_search", "bit_manipulation", "dfs",
    "divide_and_conquer", "dynamic_programming", "prefix_sum", "stack",
    "top_k_elements", "two_heaps", "backtracking", "cyclic_sort",
    "modified_binary_search", "subsets", "trie", "graph", "greedy",
    "matrix_traversal", "monotonic_stack", "union_find", "hashmap",
    "string", "design", "math", "randomized",
]


def parse_args():
    args = sys.argv[1:]
    langs = []
    patterns = []
    rest = iter(args)
    for arg in rest:
        if arg == "--lang":
            try:
                langs.append(next(rest))
            except StopIteration:
                print("Error: --lang requires a value")
                sys.exit(1)
        elif arg == "--all":
            patterns = PATTERNS[:]
        elif arg.startswith("--"):
            print(f"Error: unknown flag {arg}")
            sys.exit(1)
        else:
            patterns.append(arg)
    if not patterns:
        patterns = PATTERNS[:]
    if not langs:
        langs = LANGS[:]
    return patterns, langs


def run_one(pattern, lang):
    t0 = time.time()
    r = subprocess.run(
        ["uv", "run", "python", "run.py", pattern, "--lang", lang, "--solution"],
        capture_output=True, text=True, timeout=300,
        cwd=str(ROOT),
    )
    elapsed = time.time() - t0
    out = r.stdout
    total_line = ""
    fails = 0
    for line in out.split("\n"):
        if "TOTAL:" in line:
            total_line = line.strip()
        if "[FAIL]" in line:
            fails += 1
    return elapsed, total_line, fails, r.returncode


def main():
    patterns, langs = parse_args()

    all_results = []
    max_name_len = max(len(p) + len(ln) + 3 for p in patterns for ln in langs)

    for pattern in patterns:
        for lang in langs:
            label = f"{pattern} ({lang})"
            elapsed, total, fails, rc = run_one(pattern, lang)
            status = "OK" if rc == 0 else "FAIL"
            print(f"  {label:{max_name_len}}  {elapsed:6.2f}s  {total}  {status}")
            all_results.append((pattern, lang, elapsed, fails, rc))

    total_ok = sum(1 for *_, r in all_results if r == 0)
    total_fail = sum(1 for *_, r in all_results if r != 0)
    grand_total = sum(e for *_, e, _, _ in all_results)
    total_fails = sum(f for *_, _, f, _ in all_results)

    print()
    print(f"  Patterns: {len(patterns)}, Languages: {len(langs)}")
    print(f"  Total time: {grand_total:.2f}s")
    print(f"  Passed: {total_ok}, Failed (exit code): {total_fail}")
    print(f"  Test failures: {total_fails}")

    sys.exit(1 if total_fail > 0 or total_fails > 0 else 0)


if __name__ == "__main__":
    main()
