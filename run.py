#!/usr/bin/env python3
"""Run problem files for coding patterns.

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
import re
import subprocess
import sys

from tracker import ROOT, TIER_DIRS, load_tracker

LANG_FLAGS = ("--lang", "-l")
SOLUTION_FLAGS = ("--solution", "-s")


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
                print(f"WIP patterns: {chr(39).join(available)}")
            sys.exit(1)
        return matched

    wip = [p for p in patterns if p["status"] == "in_progress"]
    if not wip:
        print("No WIP patterns found. Use --all to run everything.")
        sys.exit(0)
    return wip


def _run_pattern(pattern, lang=None, solution=False):
    name = pattern["name"]
    tier = pattern.get("tier", 1)
    tier_dir = TIER_DIRS.get(tier)
    if not tier_dir:
        print(f"  Skipping {name}: unknown tier {tier}")
        return 0, 0

    subdir = "solutions" if solution else "problems"
    work_dir = ROOT / tier_dir / name / subdir
    if not work_dir.exists():
        print(f"  Skipping {name}: no {subdir}/ directory")
        return 0, 0

    ref_dir = ROOT / tier_dir / name / "solutions"
    if not ref_dir.exists():
        print(f"  Skipping {name}: no solutions/ directory")
        return 0, 0

    files = sorted(f for f in ref_dir.iterdir() if f.suffix == ".py" and not f.name.startswith("_"))
    if not files:
        print(f"  Skipping {name}: no solution files")
        return 0, 0

    if lang:
        suffix_map = {"c": ".c", "cpp": ".cpp", "rs": ".rs", "js": ".mjs"}
        if lang not in suffix_map:
            print(f"  Skipping {name}: unknown language '{lang}'")
            return 0, 0
        target_suffix = suffix_map[lang]
        files = [f for f in files if (work_dir / f"{f.stem}{target_suffix}").exists()]
        if not files:
            print(f"  Skipping {name}: no {lang} counterparts found in {subdir}/")
            return 0, 0

    display_name = name.replace("_", " ").title()
    mode_label = "solution" if solution else "problem"
    lang_label = f" ({lang})" if lang else ""
    print(f"\n  {display_name}{lang_label} ({len(files)} {mode_label}s)")
    print("  " + "-" * 50)

    passed = 0
    failed = 0
    skipped = 0

    for f in files:
        if lang:
            from src.runners.wasm_runner import wasm_sandbox_active, compile_to_wasm, run_wasm

            target_file = work_dir / f"{f.stem}{target_suffix}"

            if wasm_sandbox_active() and lang in ("c", "cpp", "rs", "js"):
                _STUB_PATTERNS = {
                    "c": [r"(?<!\S)abort\(\)"],
                    "cpp": [r"(?<!\S)abort\(\)"],
                    "rs": [r"(?<!\S)todo!\(\)"],
                    "js": [r"(?<!\S)throw\s+new\s+Error\(\"NotImplementedError\"\)"],
                }
                source_text = target_file.read_text(errors="replace")
                is_stub = any(re.search(p, source_text, re.MULTILINE) for p in _STUB_PATTERNS.get(lang, []))

                if is_stub:
                    skipped += 1
                    print(f"    [SKIP] {f.stem}{target_suffix}")
                    continue

                try:
                    wasm_path = compile_to_wasm(target_file, lang)
                    result = run_wasm(wasm_path, target_file.parent)
                    if result.get("timed_out"):
                        status = "FAIL"
                        failed += 1
                        print(f"    [{status}] {f.stem}{target_suffix}")
                        print(f"             {result.get('error', 'Timed out')}")
                        continue
                    if result["exit_code"] == 0:
                        status = "PASS"
                        passed += 1
                    else:
                        status = "FAIL"
                        failed += 1
                        skipped += sum(1 for line in result["output"].split("\n") if "SKIP" in line)
                        if result["exit_code"] != 2:
                            skipped = 0
                    print(f"    [{status}] {f.stem}{target_suffix}")
                    if status == "FAIL" and result.get("output"):
                        for line in result["output"].strip().split("\n")[-5:]:
                            print(f"             {line}")
                    continue
                except Exception as e:
                    print(f"    [FAIL] {f.stem}{target_suffix}")
                    print(f"             {e}")
                    failed += 1
                    continue

            from src.runners import CRunner, CppRunner, JSRunner, RustRunner

            runners = {"c": CRunner, "cpp": CppRunner, "rs": RustRunner, "js": JSRunner}
            runner = runners[lang]()
            results = runner.run_all(target_file)
            file_passed = sum(1 for r in results if r["status"] == "PASS")
            file_failed = sum(1 for r in results if r["status"] not in ("PASS", "SKIP"))
            file_skipped = sum(1 for r in results if r["status"] == "SKIP")
            passed += file_passed
            failed += file_failed
            skipped += file_skipped
            status = "SKIP" if file_failed == 0 and file_skipped > 0 else ("PASS" if file_failed == 0 else "FAIL")
            print(f"    [{status}] {f.stem}{target_suffix}")
            for r in results:
                if r["status"] != "PASS":
                    err = r.get("error", "")
                    out = r.get("output", "")
                    if err:
                        for line in err.strip().split("\n"):
                            print(f"             {line}")
                    elif out:
                        for line in out.strip().split("\n")[-5:]:
                            print(f"             {line}")
        else:
            from src.runners.wasm_runner import wasm_sandbox_active, run_python_wasm

            target_file = work_dir / f.name
            if wasm_sandbox_active():
                result = run_python_wasm(target_file, ROOT)
                if result.get("timed_out"):
                    status = "FAIL"
                    failed += 1
                    print(f"    [{status}] {f.name}")
                    print(f"             {result.get('error', 'Timed out')}")
                    continue
                if result["exit_code"] == 0:
                    status = "PASS"
                    passed += 1
                elif result["exit_code"] == 2:
                    status = "SKIP"
                    skipped += 1
                else:
                    status = "FAIL"
                    failed += 1
                print(f"    [{status}] {f.name}")
                output = result.get("output", "")
                if status == "FAIL" and output.strip():
                    for line in output.strip().split("\n"):
                        print(f"    │ {line}")
                continue
            target_file = work_dir / f.name
            try:
                result = subprocess.run(
                    [sys.executable, str(target_file)],
                    capture_output=True,
                    text=True,
                    timeout=10,
                )
            except subprocess.TimeoutExpired:
                status = "FAIL"
                failed += 1
                print(f"    [{status}] {f.name}")
                print("    │ Timed out after 10s — possible infinite loop")
                continue
            if result.returncode == 0:
                status = "PASS"
                passed += 1
            elif result.returncode == 2:
                status = "SKIP"
                skipped += 1
            else:
                status = "FAIL"
                failed += 1

            print(f"    [{status}] {f.name}")
            output = (result.stdout or "") + (result.stderr or "")
            if status == "FAIL" and output.strip():
                for line in output.strip().split("\n"):
                    print(f"    │ {line}")

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
