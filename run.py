#!/usr/bin/env python3
"""Run problem files for coding patterns via judge system.

Usage:
    python run.py                        Run all WIP pattern problem files (Python)
    python run.py sliding_window         Run a specific pattern's problems
    python run.py --all                  Run all patterns regardless of status
    python run.py --lang c               Run C counterparts instead of Python
    python run.py --lang cpp             Run C++ counterparts instead of Python
    python run.py --lang rs              Run Rust counterparts instead of Python
    python run.py --lang js              Run JavaScript counterparts instead of Python
    python run.py --all --lang c         Run all C problem stubs
    python run.py --solution             Run solutions instead of problem stubs
    python run.py --solution --lang c    Run all C solutions
"""

import importlib
import os
import re
import subprocess
import sys

from tracker import ROOT, TIER_DIRS, load_tracker

LANG_FLAGS = ("--lang", "-l")
SOLUTION_FLAGS = ("--solution", "-s")

_SUFFIX_MAP = {"c": ".c", "cpp": ".cpp", "rs": ".rs", "js": ".mjs", "py": ".py"}

_STUB_PATTERNS = {
    ".c": [r"(?<!\S)abort\(\)"],
    ".cpp": [r"(?<!\S)abort\(\)"],
    ".rs": [r"(?<!\S)todo!\(\)"],
    ".mjs": [r'throw\s+new\s+Error\("NotImplementedError"\)'],
    ".py": [r"raise NotImplementedError"],
}


def _parse_args(args):
    lang = None
    solution = False
    rest = []
    i = 0
    while i < len(args):
        if args[i] in LANG_FLAGS:
            i += 1
            if i < len(args):
                lang = args[i].lower()
            else:
                print("Error: --lang requires a value (c, cpp, rs, or js)")
                sys.exit(1)
        elif args[i] in SOLUTION_FLAGS:
            solution = True
        else:
            rest.append(args[i])
        i += 1
    return lang, solution, rest


def _get_patterns(args):
    t = load_tracker()
    patterns = t.get("patterns", [])

    if "--all" in args:
        return patterns

    if args and not args[0].startswith("-"):
        name = args[0]
        matched = [p for p in patterns if p["name"] == name]
        if not matched:
            print(f"Error: Unknown pattern '{name}'")
            available = [p["name"] for p in patterns if p["status"] == "in_progress"]
            if available:
                print(f"WIP patterns: {', '.join(available)}")
            sys.exit(1)
        return matched

    wip = [p for p in patterns if p["status"] == "in_progress"]
    if not wip:
        print("No WIP patterns found. Use --all to run everything.")
        sys.exit(0)
    return wip


def _is_stub(path):
    patterns = _STUB_PATTERNS.get(path.suffix, [])
    if not patterns:
        return False
    source = path.read_text(errors="replace")
    return any(re.search(p, source, re.MULTILINE) for p in patterns)


def _run_python_wasm(target, stdin_text):
    from src.runners.wasm_runner import run_python_wasm
    return run_python_wasm(target, ROOT, stdin_text=stdin_text)


def _run_js_wasm(target, stdin_text):
    from src.runners.wasm_runner import run_quickjs_wasm
    return run_quickjs_wasm(target, stdin_text=stdin_text)


def _run_wasm_lang(target, lang, stdin_text, work_dir):
    from src.runners.wasm_runner import wasm_sandbox_active, judge_compile_to_wasm, run_wasm

    if not wasm_sandbox_active():
        return {"exit_code": -1, "output": "wasmtime not available", "timed_out": False}

    try:
        wasm_path = judge_compile_to_wasm(target, lang)
        return run_wasm(wasm_path, work_dir, stdin_text=stdin_text)
    except Exception as e:
        return {"exit_code": -1, "output": str(e)[:500], "timed_out": False}


def _run_pattern(pattern, lang=None, solution=False):
    from src.utils.judge_base import JudgeBase

    name = pattern["name"]
    tier = pattern.get("tier", 1)
    tier_dir = TIER_DIRS.get(tier)
    if not tier_dir:
        print(f"  Skipping {name}: unknown tier {tier}")
        return 0, 0, 0

    pattern_dir = ROOT / tier_dir / name
    test_runners_dir = pattern_dir / "test_runners"
    if not test_runners_dir.is_dir():
        print(f"  Error: {name} has no test_runners/ directory")
        print("         Patterns must have test_runners/ with judge definitions.")
        return 0, 0, 0

    subdir = "solutions" if solution else "problems"
    work_dir = pattern_dir / subdir
    if not work_dir.exists():
        print(f"  Skipping {name}: no {subdir}/ directory")
        return 0, 0, 0

    stem_to_judge = {}
    for tr_file in sorted(test_runners_dir.glob("*.py")):
        if tr_file.name.startswith("_"):
            continue
        module_name = f"{tier_dir}.{name}.test_runners.{tr_file.stem}"
        try:
            mod = importlib.import_module(module_name)
        except ImportError:
            continue
        for attr_name in dir(mod):
            cls = getattr(mod, attr_name)
            if isinstance(cls, type) and issubclass(cls, JudgeBase) and cls is not JudgeBase:
                stem_to_judge[tr_file.stem] = cls
                break

    if not stem_to_judge:
        print(f"  Error: {name} has no judges in test_runners/")
        return 0, 0, 0

    effective_lang = lang or "py"
    suffix = _SUFFIX_MAP.get(effective_lang, ".py")
    lang_label = f" ({effective_lang})" if lang else ""
    mode_label = "solution" if solution else "problem"
    display_name = name.replace("_", " ").title()

    files = []
    for stem, judge_cls in sorted(stem_to_judge.items()):
        target = work_dir / f"{stem}{suffix}"
        if target.exists():
            files.append((target, stem, judge_cls))

    if not files:
        print(f"\n  {display_name}{lang_label}: no {effective_lang} files in {subdir}/")
        return 0, 0, 0

    print(f"\n  {display_name}{lang_label} ({len(files)} {mode_label}s)")
    print("  " + "-" * 50)

    passed = 0
    failed = 0
    skipped = 0

    for target, stem, judge_cls in files:
        if _is_stub(target):
            skipped += 1
            print(f"    [SKIP] {target.name}")
            continue

        judge = judge_cls()
        case_passed = 0
        case_failed = 0
        case_details = []

        for tc in judge.test_cases:
            stdin = judge.to_stdin(tc.input)
            expected = tc.expected

            if effective_lang == "py":
                result = _run_python_wasm(target, stdin)
            elif effective_lang == "js":
                result = _run_js_wasm(target, stdin)
            else:
                result = _run_wasm_lang(target, effective_lang, stdin, work_dir)

            if result.get("timed_out"):
                case_failed += 1
                case_details.append(f"    {tc.label}: TIMEOUT")
                continue

            if result["exit_code"] != 0:
                if "NotImplementedError" in result["output"]:
                    case_passed = 0
                    case_failed = 0
                    break
                case_failed += 1
                case_details.append(f"    {tc.label}: exit={result['exit_code']}")
                if result["output"]:
                    for line in result["output"].strip().split("\n")[-3:]:
                        case_details.append(f"      {line}")
                continue

            if judge.check_stdout(result["output"], expected):
                case_passed += 1
            else:
                case_failed += 1
                case_details.append(f"    {tc.label}: expected={expected!r}, got={result['output'].strip()!r}")

        total = len(judge.test_cases)
        if case_passed == 0 and case_failed == 0:
            skipped += 1
            print(f"    [SKIP] {target.name}")
        elif case_failed == 0:
            passed += 1
            print(f"    [PASS] {target.name} ({case_passed}/{total} tests)")
        else:
            failed += 1
            print(f"    [FAIL] {target.name} ({case_passed}/{total} tests)")
            for detail in case_details[:8]:
                print(detail)

    return passed, failed, skipped


def main():
    args = sys.argv[1:]
    lang, solution, rest = _parse_args(args)
    patterns = _get_patterns(rest)

    lang_label = f" ({lang})" if lang else ""
    mode_label = "solution" if solution else "problem"
    print()
    print("=" * 60)
    print(f"  Running {len(patterns)} pattern(s){lang_label} ({mode_label}s)")
    print("=" * 60)

    total_passed = 0
    total_failed = 0
    total_skipped = 0

    for p in patterns:
        p_ok, p_fail, p_skipped = _run_pattern(p, lang=lang, solution=solution)
        total_passed += p_ok
        total_failed += p_fail
        total_skipped += p_skipped

    print()
    print("  " + "-" * 50)
    print(f"  TOTAL: {total_passed} passed, {total_failed} failed, {total_skipped} skipped")
    print("=" * 60)

    sys.exit(1 if total_failed > 0 else 0)


if __name__ == "__main__":
    main()
