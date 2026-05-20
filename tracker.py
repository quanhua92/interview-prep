"""Shared data layer for interview-prep progress tracker."""

import json
from datetime import date
from pathlib import Path

ROOT = Path(__file__).parent
TRACKER_PATH = ROOT / "progress" / "tracker.json"

TIER_NAMES = {1: "Foundation", 2: "Intermediate", 3: "Advanced", 4: "Expert"}
TIER_DIRS = {
    1: "tier1_foundation",
    2: "tier2_intermediate",
    3: "tier3_advanced",
    4: "tier4_expert",
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

SECTION_META = {
    "patterns": {"label": "Coding Patterns", "icon": "💻", "has_tiers": True},
    "system_design": {"label": "System Design", "icon": "🏗️", "has_tiers": False},
    "behavioral": {"label": "Behavioral", "icon": "🧠", "has_tiers": False},
    "salary_negotiation": {"label": "Salary Negotiation", "icon": "💰", "has_tiers": False},
    "cs_fundamentals": {"label": "CS Fundamentals", "icon": "📚", "has_tiers": False},
    "resume_career": {"label": "Resume & Career", "icon": "📄", "has_tiers": False},
    "role_specific": {"label": "Role-Specific", "icon": "🎯", "has_tiers": False},
    "ai_assisted": {"label": "AI-Assisted", "icon": "🤖", "has_tiers": False},
    "data_analytics": {"label": "Data Analytics", "icon": "📊", "has_tiers": False},
    "low_level_design": {"label": "Low-Level Design", "icon": "🔧", "has_tiers": False},
    "production_engineering": {"label": "Production Engineering", "icon": "🚀", "has_tiers": False},
}


def _discover_patterns():
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
    topics = []
    path = ROOT / section_dir
    if not path.exists():
        return topics
    for d in sorted(path.iterdir()):
        if d.is_dir() and not d.name.startswith("_") and d.name != "README.md":
            topics.append({"name": d.name})
    return topics


def _sync_section(tracker, array_key, discovered, has_tier=False):
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


def _section_stats(items):
    total = len(items)
    completed = sum(1 for i in items if i["status"] == "completed")
    in_progress = sum(1 for i in items if i["status"] == "in_progress")
    return total, completed, in_progress


def _find_item(tracker, item_name):
    for section_key, array_key in SECTION_KEYS.items():
        for item in tracker.get(array_key, []):
            if item["name"] == item_name:
                return section_key, item
    return None, None


def update_item_status(item_name, new_status):
    if new_status not in ("completed", "in_progress", "not_started"):
        raise ValueError(f"Invalid status: {new_status}")
    tracker = load_tracker()
    section_key, item = _find_item(tracker, item_name)
    if not item:
        raise ValueError(f"Unknown item: {item_name}")
    old_status = item["status"]
    item["status"] = new_status
    if new_status in ("completed", "in_progress"):
        item["attempts"] = item.get("attempts", 0) + 1
        item["last_attempt"] = date.today().isoformat()
    save_tracker(tracker)
    return {"section_key": section_key, "item": item, "old_status": old_status}


def record_attempt(item_name):
    tracker = load_tracker()
    section_key, item = _find_item(tracker, item_name)
    if not item:
        raise ValueError(f"Unknown item: {item_name}")
    item["attempts"] = item.get("attempts", 0) + 1
    item["last_attempt"] = date.today().isoformat()
    save_tracker(tracker)
    return {"section_key": section_key, "item": item}


def get_tracker_summary():
    tracker = load_tracker()
    sections = []
    global_total = global_done = global_prog = 0
    for key, meta in SECTION_META.items():
        items = tracker.get(key, [])
        total, done, prog = _section_stats(items)
        pct = round(done / total * 100) if total else 0
        sections.append({
            "key": key, "label": meta["label"], "icon": meta["icon"],
            "has_tiers": meta["has_tiers"], "total": total,
            "done": done, "prog": prog, "pct": pct, "items": items,
        })
        global_total += total
        global_done += done
        global_prog += prog
    global_pct = round(global_done / global_total * 100) if global_total else 0
    return {
        "sections": sections,
        "global": {"total": global_total, "done": global_done, "prog": global_prog, "pct": global_pct},
    }
