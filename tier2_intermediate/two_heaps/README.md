# Two Heaps

## Core Idea

Maintain **two heaps** to efficiently access the median (or boundary) of a
dataset:

- A **max-heap** for the smaller half of elements.
- A **min-heap** for the larger half of elements.

By keeping the heaps balanced (differing in size by at most 1), you can
retrieve the median in O(1) time after each insertion.

## When to Recognize

Look for keywords and problem structures such as:

- "running median" / "median from data stream"
- "top k" and "bottom k" simultaneously
- "sliding window median"
- Problems where you need efficient access to both the largest-of-small and
  smallest-of-large values

## Complexity

| Metric | Value |
|--------|-------|
| Time   | O(n log n) — each insertion is O(log n) |
| Space  | O(n) — storing all elements across both heaps |

## Key Variants

1. **Running median** — add numbers one at a time, query median
2. **Sliding window max (heap approach)** — maintain a heap over a sliding window
3. **K closest elements** — use a max-heap of size k to track closest elements

## Practice Problems

| # | Problem | Difficulty |
|---|---------|------------|
| 295 | [Find Median from Data Stream](./p295_median_finder.py) | Hard |
| 480 | [Sliding Window Median](./p480_sliding_window_median.py) | Hard |

## Common Pitfalls

- Python only has ``heapq`` (min-heap).  To get a max-heap, **negate** the values.
- Forgetting to **rebalance** after every insertion, which breaks the size
  invariant.
- Floating-point precision issues when computing the average of two integers
  for the even-count median.
