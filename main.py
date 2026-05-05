#!/usr/bin/env python3
"""CLI dashboard for interview-prep.

Usage:
    python main.py status              Show all topics with progress
    python main.py update <topic>      Mark topic as completed/in_progress/not_started
    python main.py test [pattern]      Run coding tests (all or specific pattern)
"""
import json
import subprocess
import sys
from datetime import date
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

SECTION_KEYS = {
    "coding": "patterns",
    "system_design": "system_design",
    "behavioral": "behavioral",
}

ROOT = Path(__file__).parent


def _discover_patterns():
    """Scan tier directories for coding patterns."""
    patterns = []
    for tier, dirname in TIER_DIRS.items():
        tier_path = ROOT / dirname
        if not tier_path.exists():
            continue
        for d in sorted(tier_path.iterdir()):
            if d.is_dir() and not d.name.startswith("_"):
                patterns.append({"name": d.name, "tier": tier})
    return patterns


def _discover_topics(section_dir):
    """Scan a section directory for topic folders."""
    topics = []
    path = ROOT / section_dir
    if not path.exists():
        return topics
    for d in sorted(path.iterdir()):
        if d.is_dir() and not d.name.startswith("_") and d.name != "README.md":
            topics.append({"name": d.name})
    return topics


def _sync_section(tracker, array_key, discovered, has_tier=False):
    """Add new items from discovered list, preserve existing progress."""
    existing = tracker.get(array_key, [])
    existing_names = {item["name"] for item in existing}
    for item in discovered:
        if item["name"] not in existing_names:
            entry = {"name": item["name"], "status": "not_started", "attempts": 0, "last_attempt": None}
            if has_tier:
                entry["tier"] = item["tier"]
            existing.append(entry)
    tracker[array_key] = existing


def load_tracker():
    if not TRACKER_PATH.exists():
        TRACKER_PATH.parent.mkdir(parents=True, exist_ok=True)
        tracker = {"patterns": [], "system_design": [], "behavioral": []}
    else:
        tracker = json.loads(TRACKER_PATH.read_text())

    # Auto-discover and sync all sections
    _sync_section(tracker, "patterns", _discover_patterns(), has_tier=True)
    _sync_section(tracker, "system_design", _discover_topics("system_design"))
    _sync_section(tracker, "behavioral", _discover_topics("behavioral"))

    save_tracker(tracker)
    return tracker


def save_tracker(tracker):
    TRACKER_PATH.parent.mkdir(parents=True, exist_ok=True)
    TRACKER_PATH.write_text(json.dumps(tracker, indent=2))


def _print_item(item, width=25):
    icon = STATUS_ICONS.get(item["status"], "?")
    attempts = item.get("attempts", 0)
    status = item["status"].replace("_", " ").title()
    name = item["name"]
    print(f"    [{icon}] {name:<{width}s} {status:<15s} (attempts: {attempts})")


def _section_stats(items):
    total = len(items)
    completed = sum(1 for i in items if i["status"] == "completed")
    in_progress = sum(1 for i in items if i["status"] == "in_progress")
    return total, completed, in_progress


def cmd_status():
    tracker = load_tracker()
    patterns = tracker.get("patterns", [])
    sd_items = tracker.get("system_design", [])
    beh_items = tracker.get("behavioral", [])

    print()
    print(f"{'='*60}")
    print(f"  Interview Prep Progress Dashboard")
    print(f"{'='*60}")

    # Coding Patterns
    print(f"\n  SECTION: Coding Patterns")
    print(f"  {'-'*56}")
    for tier in range(1, 5):
        tier_label = TIER_NAMES[tier]
        tier_patterns = [p for p in patterns if p["tier"] == tier]
        print(f"\n    Tier {tier}: {tier_label}")
        for p in tier_patterns:
            _print_item(p)

    # System Design
    print(f"\n  SECTION: System Design")
    print(f"  {'-'*56}")
    for item in sd_items:
        _print_item(item)

    # Behavioral
    print(f"\n  SECTION: Behavioral")
    print(f"  {'-'*56}")
    for item in beh_items:
        _print_item(item)

    # Summary
    c_total, c_done, c_prog = _section_stats(patterns)
    s_total, s_done, s_prog = _section_stats(sd_items)
    b_total, b_done, b_prog = _section_stats(beh_items)
    g_total = c_total + s_total + b_total
    g_done = c_done + s_done + b_done
    g_prog = c_prog + s_prog + b_prog

    print(f"\n  {'-'*56}")
    print(f"  Coding:         {c_total:>3} total | {c_done:>3} completed | {c_prog:>3} in progress")
    print(f"  System Design:  {s_total:>3} total | {s_done:>3} completed | {s_prog:>3} in progress")
    print(f"  Behavioral:     {b_total:>3} total | {b_done:>3} completed | {b_prog:>3} in progress")
    print(f"  {'-'*56}")
    print(f"  OVERALL:        {g_total:>3} total | {g_done:>3} completed | {g_prog:>3} in progress | {g_total - g_done} remaining")
    print(f"{'='*60}\n")


def _find_item(tracker, item_name):
    """Search all sections for an item by name. Returns (section_key, item) or (None, None)."""
    for section_key, array_key in SECTION_KEYS.items():
        for item in tracker.get(array_key, []):
            if item["name"] == item_name:
                return section_key, item
    return None, None


def cmd_update(item_name):
    tracker = load_tracker()
    section_key, item = _find_item(tracker, item_name)

    if not item:
        all_names = []
        for sk, ak in SECTION_KEYS.items():
            all_names.extend(
                f"{i['name']} ({sk})" for i in tracker.get(ak, [])
            )
        print(f"Error: Unknown item '{item_name}'")
        print(f"Available: {', '.join(all_names)}")
        sys.exit(1)

    if len(sys.argv) < 4:
        print(f"Section: {section_key}")
        print(f"Current status: {item['status']}")
        print(f"Usage: python main.py update {item_name} <completed|in_progress|not_started>")
        sys.exit(0)

    new_status = sys.argv[3]
    if new_status not in ("completed", "in_progress", "not_started"):
        print(f"Error: Invalid status '{new_status}'. Use completed, in_progress, or not_started.")
        sys.exit(1)

    old_status = item["status"]
    item["status"] = new_status
    if new_status in ("completed", "in_progress"):
        item["attempts"] = item.get("attempts", 0) + 1
        item["last_attempt"] = date.today().isoformat()

    save_tracker(tracker)
    print(f"Updated {item_name} ({section_key}): {old_status} -> {new_status}")


def cmd_test(pattern_name=None):
    if pattern_name:
        tracker = load_tracker()
        _, item = _find_item(tracker, pattern_name)
        if not item:
            # Maybe it's a valid pattern name not yet in tracker
            patterns = tracker.get("patterns", [])
            found = any(p["name"] == pattern_name for p in patterns)
            if not found:
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
            print("Usage: python main.py update <topic> [completed|in_progress|not_started]")
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
