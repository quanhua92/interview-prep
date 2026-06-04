# Evaluation Playbook

Senior roles index heavily on *how* you prove the system works. "Vibes-based" evaluation is an automatic red flag.

## 1. The Golden Dataset (Ground Truth)

A curated collection of query-context-answer triples.
- **Sourcing:** Use real-world production logs, not just synthetic data. Synthetic data is good for edge cases; real logs reflect actual user behavior.
- **Diversity:** Include direct lookups, multi-hop reasoning, ambiguous queries, and negative cases (queries where the answer is *not* in the context).
- **Metadata:** Tag datasets by difficulty and category to identify specific pipeline regressions.

## 2. LLM-as-a-Judge Best Practices

Using an LLM to evaluate another LLM's output.
- **Human Calibration:** Take 20-50 examples from the Golden Dataset, have human experts grade them, and compare against the LLM Judge. Tweak the judge's prompt until it aligns with human experts.
- **Crispy Rubrics:** Avoid vague 1-5 scales. Use binary (Pass/Fail) or strictly constrained rubrics.
- **Specialized Judges:** Use different prompts/models for different dimensions (e.g., *Faithfulness* vs. *Answer Relevance*).
- **Disagreement Analysis:** Investigate edge cases where the LLM Judge and humans disagree—this improves the rubric.

## 3. RAGAS Metrics Integration

- **Offline Evaluation:** Run RAGAS metrics (Faithfulness, Context Precision/Recall, Answer Correctness) locally and in CI/CD pipelines.
- **CI/CD Gates:** If `Context Precision` drops by >5% on a Pull Request (e.g., due to a chunking strategy change), block the merge.
- **Offline-to-Online Gap:** Remember that offline scores don't perfectly predict production user satisfaction. Bridge this with shadow traffic evaluation and A/B testing.
- **Online Metrics (Implicit Feedback):** Track user behavior in production such as copy/paste events, thumbs up/down, regeneration requests, and time-to-accept to complement offline LLM-as-a-judge scores.
