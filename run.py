#!/usr/bin/env python3
"""Run problem files for coding patterns.

Usage:
    python run.py                  Run all WIP pattern problem files
    python run.py sliding_window   Run a specific pattern's problems
    python run.py --all            Run all patterns regardless of status
"""
import subprocess
import sys

from tracker import ROOT, TIER_DIRS, load_tracker


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


def _run_pattern(pattern):
    name = pattern["name"]
    tier = pattern.get("tier", 1)
    tier_dir = TIER_DIRS.get(tier)
    if not tier_dir:
        print(f"  Skipping {name}: unknown tier {tier}")
        return 0, 0

    problems_dir = ROOT / tier_dir / name / "problems"
    if not problems_dir.exists():
        print(f"  Skipping {name}: no problems/ directory")
        return 0, 0

    files = sorted(f for f in problems_dir.iterdir() if f.suffix == ".py" and not f.name.startswith("_"))
    if not files:
        print(f"  Skipping {name}: no problem files")
        return 0, 0

    display_name = name.replace("_", " ").title()
    print(f"\n  {display_name} ({len(files)} problems)")
    print(f"  {'-' * 50}")

    passed = 0
    failed = 0
    for f in files:
        result = subprocess.run(
            [sys.executable, str(f)],
            capture_output=True,
            text=True,
            timeout=30,
        )
        status = "PASS" if result.returncode == 0 else "FAIL"
        if result.returncode == 0:
            passed += 1
        else:
            failed += 1
            if result.stderr:
                for line in result.stderr.strip().split("\n")[:3]:
                    print(f"    ! {line}")

        print(f"    [{status}] {f.name}")

    return passed, failed


def main():
    args = sys.argv[1:]
    patterns = _get_patterns(args)

    print()
    print(f"{'=' * 60}")
    print(f"  Running {len(patterns)} pattern(s)")
    print(f"{'=' * 60}")

    total_passed = 0
    total_failed = 0

    for p in patterns:
        p_ok, p_fail = _run_pattern(p)
        total_passed += p_ok
        total_failed += p_fail

    print(f"\n  {'-' * 50}")
    print(f"  TOTAL: {total_passed} passed, {total_failed} failed")
    print(f"{'=' * 60}\n")

    sys.exit(1 if total_failed > 0 else 0)


if __name__ == "__main__":
    main()
