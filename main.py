#!/usr/bin/env python3
"""CLI dashboard for interview-prep.

Usage:
    python main.py status              Show all topics with progress
    python main.py update <topic>      Mark topic as completed/in_progress/not_started
    python main.py attempt <topic>     Record a practice attempt
    python main.py report              Generate HTML progress report
    python main.py report --serve      Serve report on http://0.0.0.0:8888
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


REPORT_PATH = ROOT / "progress" / "report.html"

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


def _status_badge(status):
    colors = {"completed": "bg-emerald-500", "in_progress": "bg-amber-500", "not_started": "bg-zinc-600"}
    return colors.get(status, "bg-zinc-600")


def _status_text_color(status):
    colors = {"completed": "text-emerald-400", "in_progress": "text-amber-400", "not_started": "text-zinc-500"}
    return colors.get(status, "text-zinc-500")


def _progress_ring(pct, size=80, stroke=6):
    r = (size - stroke) / 2
    c = 2 * 3.14159265 * r
    offset = c * (1 - pct / 100)
    return f'''<svg width="{size}" height="{size}" class="-rotate-90">
      <circle cx="{size/2}" cy="{size/2}" r="{r}" fill="none" stroke="#27272a" stroke-width="{stroke}"/>
      <circle cx="{size/2}" cy="{size/2}" r="{r}" fill="none" stroke="url(#grad)" stroke-width="{stroke}"
        stroke-dasharray="{c}" stroke-dashoffset="{offset}" stroke-linecap="round"/>
      <defs><linearGradient id="grad" x1="0%" y1="0%" x2="100%" y2="0%">
        <stop offset="0%" style="stop-color:#10b981"/><stop offset="100%" style="stop-color:#3b82f6"/>
      </linearGradient></defs>
    </svg>'''


def _build_section_html(key, items, meta):
    total, done, prog = _section_stats(items)
    remaining = total - done
    pct = round(done / total * 100) if total else 0

    rows = ""
    if meta["has_tiers"]:
        for tier in range(1, 5):
            tier_items = [i for i in items if i.get("tier") == tier]
            if not tier_items:
                continue
            rows += f'''<div class="col-span-3 text-xs font-semibold text-zinc-500 uppercase tracking-wider mt-4 mb-1">
              Tier {tier}: {TIER_NAMES[tier]}
            </div>'''
            for item in tier_items:
                rows += _build_item_row(item)
    else:
        for item in items:
            rows += _build_item_row(item)

    return f'''
    <div class="bg-zinc-900 rounded-2xl border border-zinc-800 overflow-hidden">
      <div class="px-6 py-5 border-b border-zinc-800 flex items-center justify-between">
        <div class="flex items-center gap-3">
          <span class="text-2xl">{meta['icon']}</span>
          <div>
            <h2 class="text-lg font-bold text-white">{meta['label']}</h2>
            <p class="text-sm text-zinc-400">{done}/{total} completed &middot; {remaining} remaining</p>
          </div>
        </div>
        <div class="flex items-center gap-2">
          <div class="w-32 h-2 bg-zinc-800 rounded-full overflow-hidden">
            <div class="h-full rounded-full bg-gradient-to-r from-emerald-500 to-blue-500" style="width:{pct}%"></div>
          </div>
          <span class="text-sm font-mono text-zinc-300">{pct}%</span>
        </div>
      </div>
      <div class="px-6 py-4 grid grid-cols-3 gap-x-6 gap-y-2 text-sm">
        <div class="col-span-1 text-xs font-semibold text-zinc-500 uppercase tracking-wider">Topic</div>
        <div class="col-span-1 text-xs font-semibold text-zinc-500 uppercase tracking-wider">Status</div>
        <div class="col-span-1 text-xs font-semibold text-zinc-500 uppercase tracking-wider">Attempts</div>
        {rows}
      </div>
    </div>'''


def _build_item_row(item):
    status = item["status"]
    badge = _status_badge(status)
    label = status.replace("_", " ").title()
    text_color = _status_text_color(status)
    attempts = item.get("attempts", 0)
    last = item.get("last_attempt", "")
    last_str = f'<span class="text-zinc-600 ml-1">&middot; {last}</span>' if last else ""
    name = item["name"].replace("_", " ").title()

    return f'''
        <div class="col-span-1 text-zinc-200 py-1">{name}</div>
        <div class="col-span-1 py-1"><span class="inline-block w-2 h-2 rounded-full {badge} mr-2"></span><span class="{text_color}">{label}</span></div>
        <div class="col-span-1 text-zinc-400 py-1">{attempts}{last_str}</div>'''


def cmd_report():
    tracker = load_tracker()

    all_sections = []
    totals = {"total": 0, "done": 0, "prog": 0}
    section_summaries = []

    for key, meta in SECTION_META.items():
        items = tracker.get(key, [])
        total, done, prog = _section_stats(items)
        totals["total"] += total
        totals["done"] += done
        totals["prog"] += prog
        all_sections.append(_build_section_html(key, items, meta))
        pct = round(done / total * 100) if total else 0
        section_summaries.append({
            "label": meta["label"], "icon": meta["icon"],
            "total": total, "done": done, "prog": prog, "pct": pct,
        })

    g_pct = round(totals["done"] / totals["total"] * 100) if totals["total"] else 0
    sections_html = "\n".join(all_sections)

    summary_cards = ""
    for s in section_summaries:
        bar_color = "from-emerald-500 to-emerald-600" if s["pct"] >= 100 else "from-blue-500 to-blue-600" if s["pct"] >= 50 else "from-amber-500 to-amber-600" if s["prog"] > 0 else "from-zinc-600 to-zinc-700"
        summary_cards += f'''
          <div class="bg-zinc-900 rounded-xl border border-zinc-800 p-4">
            <div class="flex items-center justify-between mb-2">
              <span class="text-lg">{s['icon']}</span>
              <span class="text-xs font-mono text-zinc-500">{s['pct']}%</span>
            </div>
            <div class="text-sm font-semibold text-white mb-1">{s['label']}</div>
            <div class="text-xs text-zinc-400 mb-3">{s['done']}/{s['total']} completed</div>
            <div class="w-full h-1.5 bg-zinc-800 rounded-full overflow-hidden">
              <div class="h-full rounded-full bg-gradient-to-r {bar_color}" style="width:{s['pct']}%"></div>
            </div>
          </div>'''

    today = date.today().strftime("%B %d, %Y")
    remaining = totals["total"] - totals["done"]

    html = f'''<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8"/>
  <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
  <title>Interview Prep Report</title>
  <script src="https://cdn.jsdelivr.net/npm/@tailwindcss/browser@4"></script>
  <style type="text/tailwindcss">
    @theme {{
      --color-bg: #09090b;
    }}
  </style>
</head>
<body class="bg-bg min-h-screen text-white antialiased">
  <div class="max-w-6xl mx-auto px-6 py-12">

    <!-- Header -->
    <div class="flex items-start justify-between mb-12">
      <div>
        <h1 class="text-4xl font-extrabold tracking-tight mb-2">Interview Prep</h1>
        <p class="text-zinc-400">Progress Report &middot; {today}</p>
      </div>
      <div class="relative flex items-center justify-center">
        {_progress_ring(g_pct, 100, 8)}
        <div class="absolute text-center">
          <div class="text-2xl font-bold">{g_pct}%</div>
          <div class="text-[10px] text-zinc-500 uppercase tracking-wider">Overall</div>
        </div>
      </div>
    </div>

    <!-- Stats Row -->
    <div class="grid grid-cols-4 gap-4 mb-10">
      <div class="bg-zinc-900 rounded-xl border border-zinc-800 p-5 text-center">
        <div class="text-3xl font-extrabold text-white">{totals['total']}</div>
        <div class="text-xs text-zinc-500 uppercase tracking-wider mt-1">Total Topics</div>
      </div>
      <div class="bg-zinc-900 rounded-xl border border-zinc-800 p-5 text-center">
        <div class="text-3xl font-extrabold text-emerald-400">{totals['done']}</div>
        <div class="text-xs text-zinc-500 uppercase tracking-wider mt-1">Completed</div>
      </div>
      <div class="bg-zinc-900 rounded-xl border border-zinc-800 p-5 text-center">
        <div class="text-3xl font-extrabold text-amber-400">{totals['prog']}</div>
        <div class="text-xs text-zinc-500 uppercase tracking-wider mt-1">In Progress</div>
      </div>
      <div class="bg-zinc-900 rounded-xl border border-zinc-800 p-5 text-center">
        <div class="text-3xl font-extrabold text-zinc-400">{remaining}</div>
        <div class="text-xs text-zinc-500 uppercase tracking-wider mt-1">Remaining</div>
      </div>
    </div>

    <!-- Section Summary Cards -->
    <div class="grid grid-cols-4 gap-4 mb-12">
      {summary_cards}
    </div>

    <!-- Sections Detail -->
    <div class="space-y-8">
      {sections_html}
    </div>

    <!-- Footer -->
    <div class="mt-16 text-center text-xs text-zinc-600">
      Generated by <span class="text-zinc-400">interview-prep</span> CLI &middot; {today}
    </div>

  </div>
</body>
</html>'''

    REPORT_PATH.parent.mkdir(parents=True, exist_ok=True)
    REPORT_PATH.write_text(html)

    if "--serve" in sys.argv:
        import http.server

        html_content = html

        class _Handler(http.server.BaseHTTPRequestHandler):
            def do_GET(self):
                self.send_response(200)
                self.send_header("Content-Type", "text/html")
                self.end_headers()
                self.wfile.write(html_content.encode())

            def log_message(self, format, *args):
                pass

        port = 8888

        class _QuietServer(http.server.HTTPServer):
            def server_bind(self):
                import socketserver
                socketserver.TCPServer.server_bind(self)

        httpd = _QuietServer(("0.0.0.0", port), _Handler)
        print(f"Serving report at http://0.0.0.0:{port}")
        try:
            httpd.serve_forever()
        except KeyboardInterrupt:
            print("\nStopped.")
            httpd.server_close()
    else:
        print(f"Report generated: {REPORT_PATH}")
        print("Serve with: python main.py report --serve")


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
    elif command == "report":
        cmd_report()
    elif command == "test":
        pattern_name = sys.argv[2] if len(sys.argv) > 2 else None
        cmd_test(pattern_name)
    else:
        print(f"Unknown command: {command}")
        print("Usage: python main.py [status|update|attempt|report|test]")
        sys.exit(1)


if __name__ == "__main__":
    main()
