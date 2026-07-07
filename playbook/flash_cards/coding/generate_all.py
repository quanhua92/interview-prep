#!/usr/bin/env python3
"""Generate ALL.md: all coding flashcards shuffled with a fixed seed.

Reads every <details> card from the *.md files in this directory,
shuffles them, and writes ALL.md so you can drill top-to-bottom
without knowing which pattern a card belongs to.

Usage:
    python3 generate_all.py
"""

import random
import re
from pathlib import Path

SEED = 42

DIR = Path(__file__).parent
OUTPUT = DIR / "ALL.md"

CARD_RE = re.compile(r"<details>.*?</details>", re.DOTALL)


def extract_cards(filepath: Path) -> list[str]:
    text = filepath.read_text(encoding="utf-8")
    return [c.strip() for c in CARD_RE.findall(text)]


def main() -> None:
    md_files = sorted(f for f in DIR.glob("*.md") if f.name != "ALL.md")

    cards: list[str] = []
    for f in md_files:
        cards.extend(extract_cards(f))

    random.seed(SEED)
    random.shuffle(cards)

    total = len(cards)

    lines = [
        "# All Coding Flashcards — Shuffled",
        "",
        f"{total} cards from {len(md_files)} pattern decks, "
        f"shuffled with seed={SEED}.",
        "Read top-to-bottom. The pattern is hidden until you expand — "
        "you must recall it yourself.",
        "",
        "---",
        "",
    ]

    for i, card in enumerate(cards, 1):
        lines.append(f"**{i} / {total}**")
        lines.append("")
        lines.append(card)
        lines.append("")

    lines.append("---")
    lines.append("")
    lines.append("[Back to Flashcard Index](../README.md)")

    OUTPUT.write_text("\n".join(lines), encoding="utf-8")
    print(f"Wrote {total} shuffled cards from {len(md_files)} decks to {OUTPUT.name}")


if __name__ == "__main__":
    main()
