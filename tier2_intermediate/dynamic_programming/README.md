# Dynamic Programming

## Core Idea

Break the problem into **overlapping subproblems**, solve each subproblem
once, and **cache** (memoize) the result.  By building up solutions from
smaller subproblems you avoid the exponential blow-up of naive recursion.

## When to Recognize

Look for keywords and problem structures such as:

- "optimal" / "maximum" / "minimum" number of ways
- "can you reach" / "is it possible"
- Fibonacci-like recurrence relations
- Problems where the answer to a large instance depends on answers to
  smaller instances of the **same** problem

## Complexity

| Metric | Value |
|--------|-------|
| Time   | Varies: O(n) for 1D, O(n^2) for 2D with single pass, O(n*m) for table DP |
| Space  | O(n) for 1D, O(n*m) for full 2D table (often optimisable to O(n)) |

## Key Variants

1. **1D DP (Fibonacci / Climbing Stairs)** — each state depends on 1-2 previous states
2. **1D DP with full scan (House Robber / Max Subarray)** — each state depends on a global scan
3. **2D DP (Knapsack / Coin Change)** — states indexed by (item, capacity) or (position, sum)

## Practice Problems

| # | Problem | Difficulty |
|---|---------|------------|
| 70  | [Climbing Stairs](./p070_climbing_stairs.py) | Easy |
| 322 | [Coin Change](./p322_coin_change.py) | Medium |
| 198 | [House Robber](./p198_house_robber.py) | Medium |

## Common Pitfalls

- Not handling **base cases** correctly (e.g. dp[0] = 0 for coin change).
- Using the wrong recurrence direction (top-down vs bottom-up) — bottom-up
  avoids recursion overhead and stack limits.
- Integer overflow (not an issue in Python) or incorrect sentinel values for
  "impossible" states.
- Modifying the input when it should be treated as immutable (e.g. coin change
  on an in-place grid).
