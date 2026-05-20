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
    "salary": "salary_negotiation",
    "cs": "cs_fundamentals",
    "resume": "resume_career",
    "role": "role_specific",
    "ai_assisted": "ai_assisted",
    "data_analytics": "data_analytics",
    "lld": "low_level_design",
    "prod_eng": "production_engineering",
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
        tracker = {
            "patterns": [],
            "system_design": [],
            "behavioral": [],
            "salary_negotiation": [],
            "cs_fundamentals": [],
            "resume_career": [],
            "role_specific": [],
            "ai_assisted": [],
            "data_analytics": [],
            "low_level_design": [],
            "production_engineering": [],
        }
    else:
        tracker = json.loads(TRACKER_PATH.read_text())

    # Auto-discover and sync all sections
    _sync_section(tracker, "patterns", _discover_patterns(), has_tier=True)
    _sync_section(tracker, "system_design", _discover_topics("system_design"))
    _sync_section(tracker, "behavioral", _discover_topics("behavioral"))
    _sync_section(tracker, "salary_negotiation", _discover_topics("salary_negotiation"))
    _sync_section(tracker, "cs_fundamentals", _discover_topics("cs_fundamentals"))
    _sync_section(tracker, "resume_career", _discover_topics("resume_career"))
    _sync_section(tracker, "role_specific", _discover_topics("role_specific"))
    _sync_section(tracker, "ai_assisted", _discover_topics("ai_assisted"))
    _sync_section(tracker, "data_analytics", _discover_topics("data_analytics"))
    _sync_section(tracker, "low_level_design", _discover_topics("low_level_design"))
    _sync_section(tracker, "production_engineering", _discover_topics("production_engineering"))

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
    sal_items = tracker.get("salary_negotiation", [])
    cs_items = tracker.get("cs_fundamentals", [])
    res_items = tracker.get("resume_career", [])
    role_items = tracker.get("role_specific", [])
    ai_items = tracker.get("ai_assisted", [])
    da_items = tracker.get("data_analytics", [])
    lld_items = tracker.get("low_level_design", [])
    pe_items = tracker.get("production_engineering", [])

    print()
    print(f"{'='*60}")
    print("  Interview Prep Progress Dashboard")
    print(f"{'='*60}")

    # Coding Patterns
    print("\n  SECTION: Coding Patterns")
    print(f"  {'-'*56}")
    for tier in range(1, 5):
        tier_label = TIER_NAMES[tier]
        tier_patterns = [p for p in patterns if p["tier"] == tier]
        print(f"\n    Tier {tier}: {tier_label}")
        for p in tier_patterns:
            _print_item(p)

    # System Design
    print("\n  SECTION: System Design")
    print(f"  {'-'*56}")
    for item in sd_items:
        _print_item(item)

    # Behavioral
    print("\n  SECTION: Behavioral")
    print(f"  {'-'*56}")
    for item in beh_items:
        _print_item(item)

    # Salary Negotiation
    print("\n  SECTION: Salary Negotiation")
    print(f"  {'-'*56}")
    for item in sal_items:
        _print_item(item)

    # CS Fundamentals
    print("\n  SECTION: CS Fundamentals")
    print(f"  {'-'*56}")
    for item in cs_items:
        _print_item(item)

    # Resume & Career
    print("\n  SECTION: Resume & Career")
    print(f"  {'-'*56}")
    for item in res_items:
        _print_item(item)

    # Role-Specific
    print("\n  SECTION: Role-Specific")
    print(f"  {'-'*56}")
    for item in role_items:
        _print_item(item)

    # AI-Assisted
    print("\n  SECTION: AI-Assisted")
    print(f"  {'-'*56}")
    for item in ai_items:
        _print_item(item)

    # Data Analytics
    print("\n  SECTION: Data Analytics")
    print(f"  {'-'*56}")
    for item in da_items:
        _print_item(item)

    # Low-Level Design
    print("\n  SECTION: Low-Level Design")
    print(f"  {'-'*56}")
    for item in lld_items:
        _print_item(item)

    # Production Engineering
    print("\n  SECTION: Production Engineering")
    print(f"  {'-'*56}")
    for item in pe_items:
        _print_item(item)

    # Summary
    c_total, c_done, c_prog = _section_stats(patterns)
    s_total, s_done, s_prog = _section_stats(sd_items)
    b_total, b_done, b_prog = _section_stats(beh_items)
    sal_total, sal_done, sal_prog = _section_stats(sal_items)
    cs_total, cs_done, cs_prog = _section_stats(cs_items)
    res_total, res_done, res_prog = _section_stats(res_items)
    role_total, role_done, role_prog = _section_stats(role_items)
    ai_total, ai_done, ai_prog = _section_stats(ai_items)
    da_total, da_done, da_prog = _section_stats(da_items)
    lld_total, lld_done, lld_prog = _section_stats(lld_items)
    pe_total, pe_done, pe_prog = _section_stats(pe_items)
    g_total = c_total + s_total + b_total + sal_total + cs_total + res_total + role_total + ai_total + da_total + lld_total + pe_total
    g_done = c_done + s_done + b_done + sal_done + cs_done + res_done + role_done + ai_done + da_done + lld_done + pe_done
    g_prog = c_prog + s_prog + b_prog + sal_prog + cs_prog + res_prog + role_prog + ai_prog + da_prog + lld_prog + pe_prog

    print(f"\n  {'-'*56}")
    print(f"  Coding:         {c_total:>3} total | {c_done:>3} completed | {c_prog:>3} in progress")
    print(f"  System Design:  {s_total:>3} total | {s_done:>3} completed | {s_prog:>3} in progress")
    print(f"  Behavioral:     {b_total:>3} total | {b_done:>3} completed | {b_prog:>3} in progress")
    print(f"  Salary Neg:     {sal_total:>3} total | {sal_done:>3} completed | {sal_prog:>3} in progress")
    print(f"  CS Fundamentals:{cs_total:>3} total | {cs_done:>3} completed | {cs_prog:>3} in progress")
    print(f"  Resume/Career:  {res_total:>3} total | {res_done:>3} completed | {res_prog:>3} in progress")
    print(f"  Role-Specific:  {role_total:>3} total | {role_done:>3} completed | {role_prog:>3} in progress")
    print(f"  AI-Assisted:    {ai_total:>3} total | {ai_done:>3} completed | {ai_prog:>3} in progress")
    print(f"  Data Analytics: {da_total:>3} total | {da_done:>3} completed | {da_prog:>3} in progress")
    print(f"  Low-Level Design:{lld_total:>3} total | {lld_done:>3} completed | {lld_prog:>3} in progress")
    print(f"  Prod Eng:       {pe_total:>3} total | {pe_done:>3} completed | {pe_prog:>3} in progress")
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


def cmd_attempt(item_name):
    tracker = load_tracker()
    section_key, item = _find_item(tracker, item_name)

    if not item:
        print(f"Error: Unknown item '{item_name}'")
        sys.exit(1)

    item["attempts"] = item.get("attempts", 0) + 1
    item["last_attempt"] = date.today().isoformat()
    save_tracker(tracker)
    print(f"Recorded attempt for {item_name} ({section_key}): {item['attempts']} total attempts")


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
    elif command == "attempt":
        if len(sys.argv) < 3:
            print("Usage: python main.py attempt <topic>")
            sys.exit(1)
        cmd_attempt(sys.argv[2])
    elif command == "test":
        pattern_name = sys.argv[2] if len(sys.argv) > 2 else None
        cmd_test(pattern_name)
    else:
        print(f"Unknown command: {command}")
        print("Usage: python main.py [status|update|attempt|test]")
        sys.exit(1)


if __name__ == "__main__":
    main()
