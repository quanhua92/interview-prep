# Subagent task — fill ONE file's Answer section

Your orchestrator assigns you one or more `q_*.md` files in this folder. For each:

1. Open the file.
2. Read **only** the `# Question` section (everything above `# Answer`). It is a
   market-analysis task with data-window evidence.
3. Write a rigorous **Wyckoff-method + price-action** analysis below the
   `<!-- subagent writes below this line -->` marker (inside `# Answer`).
   Cover: (1) phase / market position, (2) supply vs demand,
   (3) effort-vs-result on recent bars, (4) key levels, (5) scenario bias with
   conviction, (6) risks / invalidation.
4. End your answer with a fenced verdict block:

   ```verdict
   {"bias": "bullish|bearish|neutral", "conviction": 0.0-1.0, "target": <num>, "invalidation": <num>}
   ```

5. Set the frontmatter `status: done`.

## Hard rules (do not break these)

- **USE NO TOOLS.** No web, no bash, no `aipa`, no reading other files. You are a
  blind analyst at the `as_of` date — you know ONLY what is written in the
  Question section. Never reference or infer anything after `as_of`. (Looking up
  what the ticker actually did would leak the future and corrupt the whole dataset.)
- **Do NOT edit anything above `# Answer`.**
- Write **real analysis prose** (~300–600 words). The verdict is just the final
  1-line tag used for scoring; the prose is what the student learns from.
