"""Interactive web dashboard for interview-prep progress tracker."""

from datetime import date, datetime
from pathlib import Path
import subprocess
import sys

import uvicorn
from fastapi import FastAPI, HTTPException
from fastapi.responses import HTMLResponse
from pydantic import BaseModel

import tracker

app = FastAPI()

# --- HTML helpers ---


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
    return f'''<svg viewBox="0 0 {size} {size}" class="w-36 h-36 sm:w-[100px] sm:h-[100px] -rotate-90">
      <circle cx="{size/2}" cy="{size/2}" r="{r}" fill="none" stroke="#27272a" stroke-width="{stroke}"/>
      <circle cx="{size/2}" cy="{size/2}" r="{r}" fill="none" stroke="url(#grad)" stroke-width="{stroke}"
        stroke-dasharray="{c}" stroke-dashoffset="{offset}" stroke-linecap="round"/>
      <defs><linearGradient id="grad" x1="0%" y1="0%" x2="100%" y2="0%">
        <stop offset="0%" style="stop-color:#10b981"/><stop offset="100%" style="stop-color:#3b82f6"/>
      </linearGradient></defs>
    </svg>'''


def _build_item_row(item):
    status = item["status"]
    badge = _status_badge(status)
    label = status.replace("_", " ").title()
    text_color = _status_text_color(status)
    attempts = item.get("attempts", 0)
    last = item.get("last_attempt", "")
    last_str = f'<span class="text-zinc-600 ml-1">&middot; {last}</span>' if last else ""
    name = item["name"]
    display_name = name.replace("_", " ").title()

    return f'''
      <div data-status="{status}" data-name="{display_name.lower()}" class="contents">
        <div class="col-span-1 sm:col-span-1 text-zinc-200 py-1.5 flex items-center gap-2">
          <a href="javascript:void(0)" onclick="openEditor('{name}')" class="hover:text-blue-400 transition-colors cursor-pointer">{display_name}</a>
          <span class="inline-block w-2 h-2 rounded-full {badge}"></span>
          <span class="{text_color} text-xs">{label}</span>
        </div>
        <div class="col-span-1 sm:col-span-1 text-zinc-400 py-1.5 flex items-center gap-1.5">
          <span>{attempts}x{last_str}</span>
          <button onclick="recordAttempt('{name}')"
            class="px-1.5 py-1 rounded text-xs bg-blue-900/50 hover:bg-blue-700 text-blue-300 cursor-pointer">+1</button>
        </div>
        <div class="col-span-1 sm:col-span-3 col-start-1 py-1 pb-3 mb-1 flex gap-2 border-b border-zinc-700">
          <button onclick="updateStatus('{name}','not_started')"
            class="flex-1 py-2 rounded text-sm bg-zinc-800/50 hover:bg-zinc-600 text-zinc-400 cursor-pointer font-medium">Reset</button>
          <button onclick="updateStatus('{name}','in_progress')"
            class="flex-1 py-2 rounded text-sm {"bg-amber-600 hover:bg-amber-500 text-amber-100" if status == "in_progress" else "bg-amber-900/50 hover:bg-amber-700 text-amber-300"} cursor-pointer font-medium">{"In Progress" if status == "in_progress" else "Start"}</button>
          <button onclick="updateStatus('{name}','completed')"
            class="flex-1 py-2 rounded text-sm {"bg-emerald-600 hover:bg-emerald-500 text-emerald-100" if status == "completed" else "bg-emerald-900/50 hover:bg-emerald-700 text-emerald-300"} cursor-pointer font-medium">Done</button>
        </div>
      </div>'''


def _build_section_html(section):
    key = section["key"]
    items = section["items"]
    meta = tracker.SECTION_META[key]
    total, done = section["total"], section["done"]
    remaining = total - done
    pct = section["pct"]

    rows = ""
    if meta["has_tiers"]:
        for tier in range(1, 5):
            tier_items = [i for i in items if i.get("tier") == tier]
            if not tier_items:
                continue
            rows += f'''<div class="col-span-1 sm:col-span-3 text-xs font-semibold text-zinc-500 uppercase tracking-wider mt-4 mb-1">
              Tier {tier}: {tracker.TIER_NAMES[tier]}
            </div>'''
            for item in tier_items:
                rows += _build_item_row(item)
    else:
        for item in items:
            rows += _build_item_row(item)

    return f'''
    <div data-section class="bg-zinc-900 rounded-2xl border border-zinc-800 overflow-hidden">
      <div class="px-4 sm:px-6 py-5 border-b border-zinc-800 flex flex-wrap items-center justify-between gap-2">
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
      <div class="px-4 sm:px-6 py-4 grid grid-cols-1 sm:grid-cols-3 gap-x-6 gap-y-2 text-sm">
        <div class="hidden sm:block col-span-1 text-xs font-semibold text-zinc-500 uppercase tracking-wider">Topic</div>
        <div class="hidden sm:block col-span-1 text-xs font-semibold text-zinc-500 uppercase tracking-wider">Status</div>
        <div class="hidden sm:block col-span-1 text-xs font-semibold text-zinc-500 uppercase tracking-wider">Attempts</div>
        {rows}
      </div>
    </div>'''


def _build_dashboard_html():
    summary = tracker.get_tracker_summary()
    global_ = summary["global"]
    sections = summary["sections"]
    today = date.today().strftime("%B %d, %Y")
    remaining = global_["total"] - global_["done"]

    sections_html = "\n".join(_build_section_html(s) for s in sections)

    summary_cards = ""
    for s in sections:
        bar_color = (
            "from-emerald-500 to-emerald-600" if s["pct"] >= 100
            else "from-blue-500 to-blue-600" if s["pct"] >= 50
            else "from-amber-500 to-amber-600" if s["prog"] > 0
            else "from-zinc-600 to-zinc-700"
        )
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

    template = (tracker.ROOT / "index.html").read_text()
    return template.format(
        subtitle=f"Interactive Dashboard &middot; {today}",
        progress_ring=_progress_ring(global_["pct"], 100, 8),
        pct=global_["pct"],
        total=global_["total"],
        done=global_["done"],
        prog=global_["prog"],
        remaining=remaining,
        summary_cards=summary_cards,
        sections_html=sections_html,
        footer=f"Use the buttons below each topic to update status or record an attempt &middot; {today}",
    )


# --- Request models ---


class UpdateRequest(BaseModel):
    name: str
    status: str


class AttemptRequest(BaseModel):
    name: str


class SaveFileRequest(BaseModel):
    content: str


# --- Routes ---


@app.get("/", response_class=HTMLResponse)
def dashboard():
    return _build_dashboard_html()


@app.get("/api/tracker")
def get_tracker():
    return tracker.load_tracker()


@app.post("/api/update")
def update_status(req: UpdateRequest):
    try:
        result = tracker.update_item_status(req.name, req.status)
        return {"ok": True, **result}
    except ValueError as e:
        raise HTTPException(status_code=400, detail=str(e))


@app.post("/api/attempt")
def record_attempt(req: AttemptRequest):
    try:
        result = tracker.record_attempt(req.name)
        return {"ok": True, **result}
    except ValueError as e:
        raise HTTPException(status_code=400, detail=str(e))


@app.post("/api/run")
def run_problems():
    try:
        result = subprocess.run(
            [sys.executable, str(tracker.ROOT / "run.py")],
            capture_output=True,
            text=True,
            timeout=120,
            cwd=str(tracker.ROOT),
        )
        output = result.stdout
        if result.stderr:
            output += "\n" + result.stderr
        return {"output": output, "exit_code": result.returncode}
    except subprocess.TimeoutExpired:
        raise HTTPException(status_code=408, detail="Run timed out after 120 seconds")


# --- File editor helpers ---

_file_snapshots: dict[str, list[dict]] = {}


def _validate_fs_name(name: str):
    if ".." in name or "/" in name or "\\" in name or "\0" in name:
        raise HTTPException(status_code=400, detail="Invalid name")


def _resolve_safe_path(item_name: str, filename: str) -> Path | None:
    try:
        _, base_dir = tracker.resolve_item_dir(item_name)
    except ValueError:
        return None
    if not base_dir:
        return None
    resolved = (base_dir / filename).resolve()
    if not resolved.is_relative_to(base_dir.resolve()):
        return None
    return resolved


@app.get("/api/files/ls")
def list_files(name: str):
    _validate_fs_name(name)
    try:
        section_key, base_dir = tracker.resolve_item_dir(name)
    except ValueError as e:
        raise HTTPException(status_code=404, detail=str(e))

    if not base_dir:
        return {"has_files": False, "files": []}

    files = []
    for f in sorted(base_dir.iterdir()):
        if f.is_file() and not f.name.startswith("_") and not f.name.startswith("."):
            if f.suffix.lower() in (".py", ".md"):
                files.append({"name": f.name, "size": f.stat().st_size})
    return {"has_files": len(files) > 0, "files": files}


@app.get("/api/files/read")
def read_file(name: str, file: str):
    _validate_fs_name(name)
    _validate_fs_name(file)
    file_path = _resolve_safe_path(name, file)
    if not file_path or not file_path.exists():
        raise HTTPException(status_code=404, detail="File not found")

    ext_map = {".py": "python", ".md": "markdown"}
    language = ext_map.get(file_path.suffix.lower(), "text")
    content = file_path.read_text()
    key = f"{name}/{file}"
    if key not in _file_snapshots:
        _file_snapshots[key] = [{"label": "Original", "content": content}]
    return {"content": content, "language": language}


@app.post("/api/files/write")
def write_file(name: str, file: str, req: SaveFileRequest):
    _validate_fs_name(name)
    _validate_fs_name(file)
    file_path = _resolve_safe_path(name, file)
    if not file_path:
        raise HTTPException(status_code=404, detail="Item directory not found")

    file_path.write_text(req.content)
    key = f"{name}/{file}"
    ts = datetime.now().strftime("%H:%M:%S")
    if key not in _file_snapshots:
        _file_snapshots[key] = [{"label": "Original", "content": req.content}]
    _file_snapshots[key].append({"label": f"Save @ {ts}", "content": req.content})
    return {"ok": True, "size": len(req.content)}


@app.get("/api/files/in-progress")
def list_in_progress_files():
    tracker_data = tracker.load_tracker()
    files = []
    for section_key, array_key in tracker.SECTION_KEYS.items():
        for item in tracker_data.get(array_key, []):
            if item["status"] != "in_progress":
                continue
            try:
                _, base_dir = tracker.resolve_item_dir(item["name"])
            except ValueError:
                continue
            if not base_dir:
                continue
            for f in sorted(base_dir.iterdir()):
                if f.is_file() and not f.name.startswith("_") and not f.name.startswith("."):
                    if f.suffix.lower() in (".py", ".md"):
                        files.append({
                            "item": item["name"],
                            "name": f.name,
                            "size": f.stat().st_size,
                        })
    return {"files": files}


@app.get("/api/files/history")
def file_history(name: str, file: str):
    _validate_fs_name(name)
    _validate_fs_name(file)
    key = f"{name}/{file}"
    versions = _file_snapshots.get(key, [])
    return {"versions": [{"label": v["label"]} for v in versions]}


@app.post("/api/files/revert")
def revert_file(name: str, file: str, version: int = -1):
    _validate_fs_name(name)
    _validate_fs_name(file)
    file_path = _resolve_safe_path(name, file)
    if not file_path or not file_path.exists():
        raise HTTPException(status_code=404, detail="File not found")

    key = f"{name}/{file}"
    versions = _file_snapshots.get(key, [])
    if not versions:
        raise HTTPException(status_code=400, detail="No versions available — open the file first")

    idx = version if version >= 0 else len(versions) - 1
    if idx >= len(versions):
        raise HTTPException(status_code=400, detail="Invalid version")

    content = versions[idx]["content"]
    current = file_path.read_text()
    if content == current:
        return {"ok": True, "skipped": True}
    file_path.write_text(content)
    return {"ok": True}


# --- Static files (mounted after routes to avoid conflicts) ---

from fastapi.staticfiles import StaticFiles  # noqa: E402

app.mount("/static", StaticFiles(directory=tracker.ROOT / "static"), name="static")


# --- Entry point ---


def serve_dashboard(host="0.0.0.0", port=8888):
    uvicorn.run(app, host=host, port=port, log_level="warning")
