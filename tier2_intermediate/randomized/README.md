# Randomized / Reservoir Sampling

## Core Idea

Use random number generation and probability to solve problems that require uniform sampling, rejection sampling, or random selection from a data structure. Key technique: reservoir sampling allows uniform random selection from a stream of unknown length using O(1) space.

## When to Recognize

- "Random pick", "random node", "random flip"
- "Rand10 using Rand7" — convert between random ranges
- "Weighted random", "uniform probability"
- Problems where you must select elements with equal probability

## Complexity

| Variant | Time | Space |
|---------|------|-------|
| Reservoir sampling (stream) | O(n) | O(1) |
| Rejection sampling | Expected O(1) | O(1) |
| Fisher-Yates shuffle | O(n) | O(1) |

## Problems in This Pattern

| Problem | Difficulty | Variant |
|---------|-----------|---------|
| P519 Random Flip Matrix | Medium | Fisher-Yates style swap with HashMap |
| P470 Implement Rand10() Using Rand7 | Medium | Rejection sampling |
