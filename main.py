#!/usr/bin/env python3
"""CLI for interview-prep.

Usage:
    python main.py status                        Show all topics with progress
    python main.py update <topic> <status>       Mark topic as completed/in_progress/not_started
    python main.py attempt <topic>               Record a practice attempt
    python main.py report                        Generate static HTML progress report
    python main.py start                         Launch interactive web dashboard on :8888
    python main.py run [pattern|--all]           Run WIP problem files
    python main.py test [pattern]                Run coding tests (all or specific pattern)
"""
import subprocess
import sys
from pathlib import Path

from tracker import (
    TIER_NAMES,
    _find_item,
    _section_stats,
    load_tracker,
    record_attempt,
    update_item_status,
)

STATUS_ICONS = {"not_started": " ", "in_progress": "~", "completed": "*"}
REPORT_PATH = Path(__file__).parent / "progress" / "report.html"


def _print_item(item, width=25):
    icon = STATUS_ICONS.get(item["status"], "?")
    attempts = item.get("attempts", 0)
    status = item["status"].replace("_", " ").title()
    name = item["name"]
    print(f"    [{icon}] {name:<{width}s} {status:<15s} (attempts: {attempts})")


def cmd_status():
    t = load_tracker()
    sections = {
        "patterns": ("Coding Patterns", True),
        "system_design": ("System Design", False),
        "behavioral": ("Behavioral", False),
        "salary_negotiation": ("Salary Negotiation", False),
        "cs_fundamentals": ("CS Fundamentals", False),
        "resume_career": ("Resume & Career", False),
        "role_specific": ("Role-Specific", False),
        "ai_assisted": ("AI-Assisted", False),
        "data_analytics": ("Data Analytics", False),
        "low_level_design": ("Low-Level Design", False),
        "production_engineering": ("Production Engineering", False),
    }

    print()
    print(f"{'='*60}")
    print("  Interview Prep Progress Dashboard")
    print(f"{'='*60}")

    for key, (label, is_patterns) in sections.items():
        items = t.get(key, [])
        print(f"\n  SECTION: {label}")
        print(f"  {'-'*56}")
        if is_patterns:
            for tier in range(1, 5):
                tier_items = [i for i in items if i.get("tier") == tier]
                if not tier_items:
                    continue
                print(f"\n    Tier {tier}: {TIER_NAMES[tier]}")
                for p in tier_items:
                    _print_item(p)
        else:
            for item in items:
                _print_item(item)

    # Summary
    g_total = g_done = g_prog = 0
    summary_lines = []
    for key, (label, _) in sections.items():
        items = t.get(key, [])
        total, done, prog = _section_stats(items)
        g_total += total
        g_done += done
        g_prog += prog
        short = label[:15]
        summary_lines.append(f"  {short:<16s}{total:>3} total | {done:>3} completed | {prog:>3} in progress")

    print(f"\n  {'-'*56}")
    for line in summary_lines:
        print(line)
    print(f"  {'-'*56}")
    print(f"  OVERALL:        {g_total:>3} total | {g_done:>3} completed | {g_prog:>3} in progress | {g_total - g_done} remaining")
    print(f"{'='*60}\n")


def cmd_update(item_name):
    if len(sys.argv) < 4:
        t = load_tracker()
        section_key, item = _find_item(t, item_name)
        if not item:
            print(f"Error: Unknown item '{item_name}'")
            sys.exit(1)
        print(f"Section: {section_key}")
        print(f"Current status: {item['status']}")
        print(f"Usage: python main.py update {item_name} <completed|in_progress|not_started>")
        sys.exit(0)

    new_status = sys.argv[3]
    try:
        result = update_item_status(item_name, new_status)
        print(f"Updated {item_name} ({result['section_key']}): {result['old_status']} -> {new_status}")
    except ValueError as e:
        print(f"Error: {e}")
        sys.exit(1)


def cmd_attempt(item_name):
    try:
        result = record_attempt(item_name)
        print(f"Recorded attempt for {item_name} ({result['section_key']}): {result['item']['attempts']} total attempts")
    except ValueError as e:
        print(f"Error: {e}")
        sys.exit(1)


def cmd_report():
    from web import _build_dashboard_html

    html = _build_dashboard_html()
    REPORT_PATH.parent.mkdir(parents=True, exist_ok=True)
    REPORT_PATH.write_text(html)
    print(f"Report generated: {REPORT_PATH}")


def cmd_test(pattern_name=None):
    if pattern_name:
        t = load_tracker()
        _, item = _find_item(t, pattern_name)
        if not item:
            patterns = t.get("patterns", [])
            found = any(p["name"] == pattern_name for p in patterns)
            if not found:
                print(f"Error: Unknown pattern '{pattern_name}'")
                sys.exit(1)
        result = subprocess.run(
            [sys.executable, "-m", "pytest", f"tests/test_{pattern_name}.py", "-v"],
            capture_output=False,
        )
        sys.exit(result.returncode)
    else:
        result = subprocess.run(
            [sys.executable, "-m", "pytest", "-v"],
            capture_output=False,
        )
        sys.exit(result.returncode)


def _print_help():
    print(__doc__.strip())


def main():
    if len(sys.argv) < 2:
        _print_help()
        return

    command = sys.argv[1]
    if command == "status":
        cmd_status()
    elif command == "update":
        if len(sys.argv) < 3:
            print("Usage: python main.py update <topic> <completed|in_progress|not_started>")
            sys.exit(1)
        cmd_update(sys.argv[2])
    elif command == "attempt":
        if len(sys.argv) < 3:
            print("Usage: python main.py attempt <topic>")
            sys.exit(1)
        cmd_attempt(sys.argv[2])
    elif command == "report":
        cmd_report()
    elif command == "start":
        from web import serve_dashboard
        serve_dashboard()
    elif command == "run":
        from run import main as run_main
        sys.argv = sys.argv[1:]
        run_main()
    elif command == "test":
        pattern_name = sys.argv[2] if len(sys.argv) > 2 else None
        cmd_test(pattern_name)
    else:
        print(f"Unknown command: {command}")
        _print_help()
        sys.exit(1)


if __name__ == "__main__":
    main()
