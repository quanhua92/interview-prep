"""Shared markdown parsing for question/teacher .md files.

A teacher .md has YAML frontmatter, a `# Question` section (data-window only),
and an `# Answer` section the subagent fills, ending with a fenced verdict block.
"""
from __future__ import annotations
import json
import re
from pathlib import Path

_VERDICT = re.compile(r"```verdict\s*(\{.*?\})\s*```", re.S)


def parse_frontmatter(text: str) -> tuple[dict, str]:
    lines = text.splitlines()
    if not lines or lines[0].strip() != "---":
        return {}, text
    end = None
    for i in range(1, len(lines)):
        if lines[i].strip() == "---":
            end = i
            break
    if end is None:
        return {}, text
    fm: dict[str, str] = {}
    for line in lines[1:end]:
        if ":" in line:
            k, v = line.split(":", 1)
            fm[k.strip()] = v.strip()
    return fm, "\n".join(lines[end + 1:])


def extract_verdict(text: str) -> dict | None:
    m = _VERDICT.search(text)
    if not m:
        return None
    try:
        return json.loads(m.group(1))
    except Exception:
        return None


def split_sections(body: str) -> tuple[str, str]:
    """Return (question, answer) from the body (frontmatter already stripped)."""
    qi = body.find("# Question")
    ai = body.find("# Answer")
    if qi == -1 or ai == -1:
        return body.strip(), ""
    question = body[qi + len("# Question"):ai].strip()
    answer = body[ai + len("# Answer"):].strip()
    if answer.startswith("<!--"):
        answer = answer.split("-->", 1)[1].strip() if "-->" in answer else answer
    return question, answer


def parse_md(path: str | Path) -> dict:
    text = Path(path).read_text()
    fm, body = parse_frontmatter(text)
    question, answer = split_sections(body)
    return {
        "fm": fm,
        "id": fm.get("id", Path(path).stem),
        "ticker": fm.get("ticker", ""),
        "as_of": fm.get("as_of", ""),
        "tags": fm.get("tags", ""),
        "status": fm.get("status", ""),
        "question": question,
        "answer": answer,
        "verdict": extract_verdict(answer),
        "done": fm.get("status", "").lower() == "done" or bool(answer.strip()),
    }


def teacher_dirs(data_dir: str | Path = "data") -> list[Path]:
    """Teacher folders = subdirs of data/ except the COPY_AND_RENAME template."""
    d = Path(data_dir)
    if not d.exists():
        return []
    return sorted(p for p in d.iterdir() if p.is_dir() and p.name != "COPY_AND_RENAME")
