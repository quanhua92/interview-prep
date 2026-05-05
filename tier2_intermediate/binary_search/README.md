# Binary Search

## Core Idea

Halve the search space at each step.  Binary search works on **sorted** (or
partially sorted) data by comparing the target to the middle element and
discarding the half where the target cannot reside.

## When to Recognize

Look for keywords and problem structures such as:

- Sorted array and "find target"
- "first/last position" of a value
- "search in rotated sorted array"
- "find minimum" in a rotated sorted array
- Any problem where the answer space is **monotonic** (yes/no decision)

## Complexity

| Metric | Value |
|--------|-------|
| Time   | O(log n) |
| Space  | O(1) (iterative) / O(log n) (recursive stack) |

## Key Variants

1. **Standard binary search** — find exact target in a sorted array
2. **Leftmost binary search (lower bound)** — find first occurrence / insertion point
3. **Rotated sorted array** — search or find minimum when the array has been rotated

## Practice Problems

| # | Problem | Difficulty |
|---|---------|------------|
| 704 | [Binary Search](./p704_binary_search.py) | Easy |
| 153 | [Find Minimum in Rotated Sorted Array](./p153_find_min_rotated.py) | Medium |

## Common Pitfalls

- Using ``mid = (left + right) // 2`` instead of ``mid = left + (right - left) // 2``
  (the former can overflow in languages with fixed-width integers; Python is safe
  but the idiom is good practice).
- Off-by-one errors in loop conditions: ``while left <= right`` vs
  ``while left < right`` — understand which invariant each maintains.
- Forgetting that binary search requires a **sorted** (or monotonic) search space.
