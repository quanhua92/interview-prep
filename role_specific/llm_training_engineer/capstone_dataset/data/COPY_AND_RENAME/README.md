# Teacher run folder — rename me to the model

This folder is a copy of `data/COPY_AND_RENAME/`. **Rename it to your teacher
model**, e.g. `data/claude-opus-4.8/`. Each `q_*.md` has a question on top and an
empty `# Answer` section waiting to be filled.

## How to fill it (opencode / Claude Code / Gemini CLI / Cursor)

Spawn subagents — one per file, or batched — each of which reads
`SUBAGENT_PROMPT.md` and fills one `q_*.md`. Paste this into your CLI:

> For every `q_*.md` in `data/<TEACHER>/` whose frontmatter `status` is `todo`,
> spawn a subagent that reads `SUBAGENT_PROMPT.md` and appends its analysis to the
> end of that file's `# Answer` section, then sets `status: done`. Run in parallel
> batches of ~10. **Subagents must use NO tools.** Skip any file with
> `status: done`.

Replace `<TEACHER>` with this folder's name.

## Batching

If the orchestrator struggles with many files, split them into subfolders of
~50–100 files each (e.g. `data/<TEACHER>/batch_01/`). The scoring/build scripts
recurse into subfolders, so batching is safe.

## After filling

From `capstone_dataset/`:

```bash
python scripts/status.py                       # coverage (done / todo per teacher)
python scripts/score.py                        # grade verdicts vs realized outcomes
python scripts/build_dataset.py --mode sft     # -> build/sft_train.jsonl
python scripts/build_dataset.py --mode dpo     # -> build/dpo_train.jsonl
```

## Rules recap

- The `# Question` section is data-window only (no future). Teachers must stay
  blind — that's why subagents are forbidden from using tools.
- Each answer must end with the fenced `verdict` block; that's what `score.py`
  compares against the realized outcome (stored separately in `outcomes.jsonl`,
  never inside these files).
