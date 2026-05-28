# AGENTS.md — Project Knowledge for AI Assistants

## Project Overview

Interview prep toolkit: 144 LeetCode coding problems across 29 patterns x 5 languages (Python, C, C++, Rust, JS) = 720 problem files + 720 solution files. Runs in Docker with WASM sandbox (wasmtime). FastAPI web dashboard + CLI.

## Tech Stack

- **Runtime:** Python 3.14, uv package manager
- **Web:** FastAPI + Uvicorn (port 8888)
- **Sandbox:** wasmtime (WASM) — no native subprocess for code execution
- **Languages:** Python (CPython WASM), C (wasi-sdk clang), C++ (wasi-sdk clang++), Rust (rustc wasm32-wasip1), JS (QuickJS-NG WASI)
- **Test:** pytest
- **Lint:** ruff (Python)

## Key Commands

```bash
# Docker (primary dev environment)
docker exec interview-prep python run.py --all --problems      # 144 SKIP expected
docker exec interview-prep python run.py --all --solution       # 144 PASS expected
docker exec interview-prep python run.py dfs --problems         # single pattern
docker exec interview-prep python run.py dfs --solution --lang c  # specific lang

# Local (no WASM, limited)
uv run python run.py --all --problems
uv run python run.py --all --solution

# Tests
uv run pytest

# Lint
uv run ruff check --fix
```

## Architecture

```
run.py                          # CLI entry — discovers patterns, loads judges, runs WASM
tracker.py                     # Data layer (CRUD on progress/tracker.json)
web.py                         # FastAPI server + HTML dashboard
src/
  runners/wasm_runner.py       # Compile to .wasm + execute via wasmtime
  utils/judge_base.py          # JudgeBase class with IO helpers
  wasm_libs/                   # Per-language IO libraries (linked into WASM)
    py/io.py                   # read_ints, read_line, write_int, write_bool, etc.
    c/io.h, io.c
    cpp/io.h, io.cpp
    rs/lib.rs
    js/io.mjs

tier{1-4}_*/
  <pattern>/
    problems/                  # User workspace — stubs only (solve() + raise NotImplementedError)
    solutions/                 # Answer keys — full implementation
    test_runners/              # JudgeBase subclass per problem (single source of truth for test cases)
```

### How the Judge Works

1. `run.py` loads `test_runners/pXXX.py` → gets `test_cases`, `to_stdin()`, `check_stdout()`
2. Scans problem/solution file for stub marker → SKIP if found
3. Compiles to `.wasm` (or runs python.wasm / quickjs.wasm)
4. For each test case: pipe `to_stdin()` → wasmtime → capture stdout → `check_stdout()`
5. PASS/FAIL per test case

### Stub Detection (before compiling)

| Language | Stub Pattern |
|----------|-------------|
| Python | `raise NotImplementedError` |
| C / C++ | `abort()` |
| Rust | `todo!()` |
| JS | `throw new Error("NotImplementedError")` |

### Pre-commit Hook

`.githooks/pre-commit` blocks commits where `problems/*.py` files have a working `solve()` method (no `raise NotImplementedError`). Forces stubs to stay clean.

## Problem File Structure

### Canonical Pattern (Python)

```python
"""PXXX: Title (Difficulty)
https://leetcode.com/problems/...
Topics: ...
<full problem description, examples, constraints, template, hint>
"""

from src.wasm_libs.py.io import *


def solve(param: type) -> type:
    raise NotImplementedError


if __name__ == "__main__":
    <read stdin using read_ints/read_line/etc>
    result = solve(...)
    <write stdout using write_int/write_bool/etc>
```

### Rules

- **problems/** = user workspace. Contains ONLY stubs (`raise NotImplementedError`). No algorithm implementation.
- **solutions/** = answer keys. Full implementation.
- **test_runners/** = judge definitions. Single source of truth for test cases and I/O contract.
- `random.seed(42)` is NOT a leak — required for deterministic WASM judge output. Keep it in both problem and solution files.
- `solve()` signature and `__main__` I/O must match between problem and solution.
- I/O uses `wasm_libs` helpers (`read_ints`, `write_int`, etc.), never raw `input()`/`print()` (except where the solution intentionally uses `print` — match the solution's pattern).

## 144 Problems by Tier

| Tier | Dir | Patterns | Problems |
|------|-----|----------|:--------:|
| 1 Foundation | `tier1_foundation/` | bfs, fast_slow_pointers, hashmap, merge_intervals, sliding_window, string, two_pointers | 39 |
| 2 Intermediate | `tier2_intermediate/` | binary_search, bit_manipulation, design, dfs, divide_and_conquer, dynamic_programming, math, prefix_sum, randomized, stack, top_k_elements, two_heaps | 44 |
| 3 Advanced | `tier3_advanced/` | backtracking, cyclic_sort, modified_binary_search, subsets, trie | 19 |
| 4 Expert | `tier4_expert/` | graph, greedy, matrix_traversal, monotonic_stack, union_find | 42 |

## Non-Coding Sections

Each has `discussion.md` + `checklist.md` (or `README.md` + `TIPS.md` for ai_assisted):
- `system_design/` (25 topics)
- `behavioral/` (12 themes)
- `salary_negotiation/` (8 topics)
- `cs_fundamentals/` (22 topics)
- `resume_career/` (6 topics)
- `role_specific/` (6 topics)
- `ai_assisted/` (6 scenarios)
- `data_analytics/` (9 topics)
- `low_level_design/` (12 topics)
- `production_engineering/` (10 topics)

---

## AUDIT WORKFLOW — MANDATORY FOR ALL FILE EDITS

These rules apply to ALL edits of problem/solution files across ALL languages. Violating them can corrupt problem descriptions, leak solutions, or break the WASM judge.

### RULE 1: NO AUTOMATED BATCH PROCESSING

> **NEVER** write scripts that loop over files and edit them programmatically. No `sed`, no `awk`, no custom Python scripts that mutate files in bulk. Even if 100 files need the same fix, edit them one at a time.

### RULE 2: EDIT ONE FILE AT A TIME

> Use the Edit tool on each file individually. Read the file, understand the context, make the precise edit. Each file deserves human attention.

### RULE 3: SPAWN SUBAGENTS FOR PARALLELISM

> If there are many files to fix, spawn multiple subagents — each one reads, understands, and edits a small batch of files (5-10 max). Each subagent uses the Edit tool file-by-file. Parallelism through agents, not through scripts.

### RULE 4: READ BEFORE EDIT

> Always read the file first. Never assume content. The Edit tool requires an exact match — this forces precision.

### RULE 5: VERIFY AFTER EDIT

> After editing, re-read the file to confirm the change is correct. No blind edits.

### RULE 6: RESPECT THE CANONICAL PATTERN

> Every edit must produce output that matches the canonical structure. No shortcuts, no "close enough."

### RULE 7: RUN THE JUDGE AFTER EDITS

> After editing problem files, verify with `docker exec`:
> - `docker exec interview-prep python run.py <pattern> --problems` → all SKIP
> - `docker exec interview-prep python run.py <pattern> --solution` → all PASS
> - `docker exec interview-prep python run.py --all --problems` → 144 SKIP
> - `docker exec interview-prep python run.py --all --solution` → 144 PASS

### RULE 8: NEVER CHANGE SOLUTION FILES UNLESS EXPLICITLY ASKED

> Solutions are verified correct. Only edit when explicitly instructed. If editing solutions, re-verify they still PASS.

### Why These Rules Exist

These files are hand-crafted LeetCode problems. A single wrong automated edit can:
- Corrupt problem descriptions
- Leak the algorithm solution into the problem stub
- Break the WASM judge's stdin/stdout contract
- Break the pre-commit hook

**Taking time is acceptable. Breaking things is not.**

### Audit Checklist (per file)

```
1. DOCSTRING: title, URL, topics, examples, constraints present? Topics match folder?
2. STUB: solve() with raise NotImplementedError / abort() / todo!() / throw?
3. NO LEAK: no algorithm implementation in problem file? No data structure init in __init__?
4. I/O: imports wasm_libs? __main__ reads stdin + writes stdout? Matches solution format?
5. SEED: random.seed(42) present in both problem and solution (randomized problems)?
6. SOLUTION EXISTS: corresponding solutions/pXXX.* file present with implementation?
7. CROSS-LANGUAGE: same stdin/stdout contract as other language versions?
```
