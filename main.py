#!/usr/bin/env python3
"""CLI dashboard for interview-prep coding patterns.

Usage:
    python main.py status              Show all 20 patterns with progress
    python main.py update <pattern>    Mark pattern as completed/in_progress/not_started
    python main.py test [pattern]      Run tests (all or specific pattern)
"""
import json
import subprocess
import sys
from datetime import datetime, date
from pathlib import Path

TRACKER_PATH = Path(__file__).parent / "progress" / "tracker.json"

TIER_NAMES = {1: "Foundation", 2: "Intermediate", 3: "Advanced", 4: "Expert"}
TIER_DIRS = {
    1: "tier1_foundation",
    2: "tier2_intermediate",
    3: "tier3_advanced",
    4: "tier4_expert",
}

STATUS_ICONS = {
    "not_started": " ",
    "in_progress": "~",
    "completed": "*",
}


def load_tracker():
    if not TRACKER_PATH.exists():
        TRACKER_PATH.parent.mkdir(parents=True, exist_ok=True)
        TRACKER_PATH.write_text(json.dumps({"patterns": []}))
    return json.loads(TRACKER_PATH.read_text())


def save_tracker(tracker):
    TRACKER_PATH.parent.mkdir(parents=True, exist_ok=True)
    TRACKER_PATH.write_text(json.dumps(tracker, indent=2))


def cmd_status():
    tracker = load_tracker()
    patterns = tracker.get("patterns", [])
    print()
    print(f"{'='*60}")
    print(f"  Interview Prep Progress Dashboard")
    print(f"{'='*60}")

    for tier in range(1, 5):
        tier_label = TIER_NAMES[tier]
        tier_patterns = [p for p in patterns if p["tier"] == tier]
        print(f"\n  Tier {tier}: {tier_label}")
        print(f"  {'-'*56}")

        for p in tier_patterns:
            icon = STATUS_ICONS.get(p["status"], "?")
            attempts = p.get("attempts", 0)
            status = p["status"].replace("_", " ").title()
            name = p["name"]
            print(f"    [{icon}] {name:<25s} {status:<15s} (attempts: {attempts})")

    total = len(patterns)
    completed = sum(1 for p in patterns if p["status"] == "completed")
    in_progress = sum(1 for p in patterns if p["status"] == "in_progress")
    print(f"\n  {'-'*56}")
    print(f"  Total: {total}  |  Completed: {completed}  |  In Progress: {in_progress}  |  Remaining: {total - completed}")
    print(f"{'='*60}\n")


def cmd_update(pattern_name):
    tracker = load_tracker()
    patterns = tracker.get("patterns", [])
    pattern = None
    for p in patterns:
        if p["name"] == pattern_name:
            pattern = p
            break

    if not pattern:
        print(f"Error: Unknown pattern '{pattern_name}'")
        print(f"Available patterns: {', '.join(p['name'] for p in patterns)}")
        sys.exit(1)

    if len(sys.argv) < 4:
        print(f"Current status: {pattern['status']}")
        print(f"Usage: python main.py update {pattern_name} <completed|in_progress|not_started>")
        sys.exit(0)

    new_status = sys.argv[3]
    if new_status not in ("completed", "in_progress", "not_started"):
        print(f"Error: Invalid status '{new_status}'. Use completed, in_progress, or not_started.")
        sys.exit(1)

    old_status = pattern["status"]
    pattern["status"] = new_status
    if new_status == "completed":
        pattern["attempts"] = pattern.get("attempts", 0) + 1
        pattern["last_attempt"] = date.today().isoformat()
    elif new_status == "in_progress":
        pattern["attempts"] = pattern.get("attempts", 0) + 1
        pattern["last_attempt"] = date.today().isoformat()

    save_tracker(tracker)
    print(f"Updated {pattern_name}: {old_status} -> {new_status}")


def cmd_test(pattern_name=None):
    if pattern_name:
        tracker = load_tracker()
        patterns = tracker.get("patterns", [])
        pattern = None
        for p in patterns:
            if p["name"] == pattern_name:
                pattern = p
                break

        if not pattern:
            print(f"Error: Unknown pattern '{pattern_name}'")
            sys.exit(1)

        test_file = f"tests/test_{pattern_name}.py"
        result = subprocess.run(
            [sys.executable, "-m", "pytest", test_file, "-v"],
            capture_output=False,
        )
        sys.exit(result.returncode)
    else:
        result = subprocess.run(
            [sys.executable, "-m", "pytest", "-v"],
            capture_output=False,
        )
        sys.exit(result.returncode)


def main():
    if len(sys.argv) < 2:
        cmd_status()
        return

    command = sys.argv[1]
    if command == "status":
        cmd_status()
    elif command == "update":
        if len(sys.argv) < 3:
            print("Usage: python main.py update <pattern> [completed|in_progress|not_started]")
            sys.exit(1)
        cmd_update(sys.argv[2])
    elif command == "test":
        pattern_name = sys.argv[2] if len(sys.argv) > 2 else None
        cmd_test(pattern_name)
    else:
        print(f"Unknown command: {command}")
        print("Usage: python main.py [status|update|test]")
        sys.exit(1)


if __name__ == "__main__":
    main()
