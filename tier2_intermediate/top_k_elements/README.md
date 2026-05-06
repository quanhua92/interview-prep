# Top-K Elements

## Core Idea

Use a **heap** (priority queue) to efficiently find the top-k or bottom-k
elements of a dataset without fully sorting it.  A min-heap of size *k* gives
the k-th largest; a max-heap of size *k* gives the k-th smallest.

## When to Recognize

Look for keywords and problem structures such as:

- "top k frequent" / "k most frequent"
- "kth largest" / "kth smallest"
- "closest points" / "k closest"
- Problems where you need an ordered subset but **not** a full sort

## Complexity

| Metric | Value |
|--------|-------|
| Time   | O(n log k) — better than O(n log n) full sort when k << n |
| Space  | O(k) for the heap (or O(n) if counting frequencies) |

## Key Variants

1. **Kth largest with min-heap** — keep a min-heap of size k
2. **Top K frequent elements** — combine frequency counting with a heap
3. **K closest points** — max-heap keyed by distance, capped at size k

## Practice Problems

| # | Problem | Difficulty |
|---|---------|------------|
| 215 | [Kth Largest Element in an Array](./p215_kth_largest.py) | Medium |
| 347 | [Top K Frequent Elements](./p347_top_k_frequent.py) | Medium |
| 973 | [K Closest Points to Origin](./p973_k_closest_points.py) | Medium |
| 407 | [Trapping Rain Water II](./solutions/p407_trapping_rain_water_ii.py) | Hard |

## Common Pitfalls

- Choosing the **wrong heap direction** (min vs max).  For k-th largest you
  want a **min-heap** so the smallest of the top-k is at the root.
- Using ``heapq.nlargest`` on the entire array when a manual size-k heap would
  save memory for very large inputs.
- Forgetting to handle edge cases where ``k`` equals the array length.
