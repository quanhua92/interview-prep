# Sliding Window

## Core Idea

Maintain a window (contiguous subarray/substring) that slides through the data structure. As the right boundary advances, the left boundary contracts when the window violates the constraint. This avoids recomputing from scratch on every step.

## When to Recognize

Look for these keywords in the problem statement:

- "Longest/shortest subarray/substring with condition"
- "Maximum/minimum of all subarrays of size k"
- "Find a contiguous subarray that satisfies ..."
- Constraints mention at most/at least/k consecutive elements

## Complexity

| Variant | Time | Space |
|---------|------|-------|
| Fixed-size window | O(n) | O(k) |
| Variable-size (shrink) | O(n) | O(k) |
| Variable-size (exact count) | O(n) | O(k) |

## Key Insight

The window invariant is what makes it work. Every element is added to the window exactly once (right pointer moves forward) and removed at most once (left pointer moves forward). This gives amortized O(n) time.

## Problems in This Pattern

| Problem | Difficulty | Variant |
|---------|-----------|---------|
| P003 Longest Substring Without Repeating Characters | Medium | Variable-size with shrinking |
| P438 Find All Anagrams in a String | Medium | Fixed-size window |
| P424 Longest Repeating Character Replacement | Medium | Variable-size with constraint budget |
| P395 Longest Substring with At Least K Repeating Characters | Medium | Sliding window (unique target) |
| P567 Permutation in String | Medium | Fixed-size sliding window + counter |

## Template Variants

1. **Fixed-size window** -- max of subarrays of size k
2. **Variable-size window with shrinking** -- longest substring meeting condition
3. **Variable-size window with exact condition** -- count of subarrays

See `template.py` for annotated skeleton code for each variant.
