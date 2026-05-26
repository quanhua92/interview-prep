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
| 403 | [Frog Jump](./solutions/p403_frog_jump.py) | Hard |
| 466 | [Count The Repetitions](./solutions/p466_count_the_repetitions.py) | Hard |
| 467 | [Unique Substrings in Wraparound String](./solutions/p467_unique_substrings_in_wraparound_string.py) | Medium |
| 514 | [Freedom Trail](./solutions/p514_freedom_trail.py) | Hard |
| 516 | [Longest Palindromic Subsequence](./solutions/p516_longest_palindromic_subsequence.py) | Medium |
| 518 | [Coin Change II](./solutions/p518_coin_change_ii.py) | Medium |
| 552 | [Student Attendance Record II](./solutions/p552_student_attendance_record_ii.py) | Hard |
| 553 | [Optimal Division](./solutions/p553_optimal_division.py) | Medium |
| 576 | [Out of Boundary Paths](./solutions/p576_out_of_boundary_paths.py) | Medium |

## Common Pitfalls

- Not handling **base cases** correctly (e.g. dp[0] = 0 for coin change).
- Using the wrong recurrence direction (top-down vs bottom-up) — bottom-up
  avoids recursion overhead and stack limits.
- Integer overflow (not an issue in Python) or incorrect sentinel values for
  "impossible" states.
- Modifying the input when it should be treated as immutable (e.g. coin change
  on an in-place grid).
