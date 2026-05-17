# Dynamic Programming — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Problem Identification (1-2 min)
- [ ] Read the problem and check for DP signals:
  - [ ] Does the problem ask for "count the number of ways", "find min/max cost", "longest/shortest", or "is it possible to reach X"?
  - [ ] Does a naive recursive solution solve the same subproblem multiple times (overlapping subproblems)?
  - [ ] Does the optimal solution depend on optimal solutions to smaller subproblems (optimal substructure)?
- [ ] Confirm DP is the right pattern (not greedy, not just recursion):
  - [ ] Would a greedy choice always be optimal? If yes, DP is overkill.
  - [ ] Are there overlapping subproblems? If no, consider divide-and-conquer instead.

## Phase 2: State Definition (2-3 min)
- [ ] Define the state precisely:
  - [ ] 1D: What does dp[i] represent? (e.g., "min coins to make amount i")
  - [ ] 2D: What does dp[i][j] represent? (e.g., "min edits to convert word1[:i] to word2[:j]")
  - [ ] Identify the DP type from taxonomy: 1D Linear, 2D Grid, Knapsack, Interval, Sequence, Tree
- [ ] Identify base cases:
  - [ ] What is the simplest subproblem? (e.g., dp[0] = 0, dp[0][j] = j)
  - [ ] Are there sentinel/initialization values for "impossible" states? (e.g., float('inf'), -1)

## Phase 3: Recurrence and Computation (3-5 min)
- [ ] Write the recurrence relation:
  - [ ] How does dp[i] (or dp[i][j]) relate to smaller subproblems?
  - [ ] Is it min or max of transitions? Or a sum for counting problems?
  - [ ] List all possible transitions (e.g., for each coin, for each previous index j < i)
- [ ] Choose computation approach:
  - [ ] Top-down (memoization): good for sparse state spaces, natural recursion
  - [ ] Bottom-up (tabulation): no recursion overhead, easier to space-optimize
- [ ] Determine iteration order:
  - [ ] Ensure each subproblem is solved before it is needed
  - [ ] For Knapsack 1D: iterate capacity backwards (0-1) or forwards (unbounded)
- [ ] Identify the answer extraction point:
  - [ ] Is it dp[n], max(dp), dp[n][m], or something else?

## Phase 4: Implementation and Optimization (5-8 min)
- [ ] Write clean bottom-up solution:
  - [ ] Initialize dp array/table with correct size and sentinel values
  - [ ] Set base cases
  - [ ] Iterate in correct order with recurrence
  - [ ] Extract and return the answer
- [ ] Consider space optimization:
  - [ ] Does dp[i] only depend on dp[i-1] and dp[i-2]? Reduce to O(1) with two variables.
  - [ ] Does dp[i][j] only depend on previous row? Reduce to O(m) with rolling array.
  - [ ] For Knapsack: reduce from O(n*W) to O(W) with single array (iterate backwards).
- [ ] Verify complexity:
  - [ ] State the time complexity (states * transitions per state)
  - [ ] State the space complexity (after optimization)
  - [ ] Check if it fits within constraints for n up to 10^5 or 10^6

## Phase 5: Edge Cases and Verification (2-3 min)
- [ ] Test with trivial inputs: empty array, single element, amount = 0
- [ ] Test with the simplest non-trivial case and trace through the dp table
- [ ] Check for common pitfalls:
  - [ ] Off-by-one errors in indexing (dp size n+1 vs n)
  - [ ] Wrong sentinel value (float('inf') vs -1 vs 0)
  - [ ] Incorrect iteration direction (backwards for 0-1 Knapsack)
  - [ ] Forgetting to return max(dp) instead of dp[n] (e.g., LIS)
- [ ] Walk through the solution verbally and confirm it makes sense

## Phase 6: Extensions (if interviewer asks)
- [ ] Reconstruct the actual solution (path tracing with parent pointers)
- [ ] Handle variants: unbounded Knapsack, multi-dimensional state, bitmask DP
- [ ] Discuss alternative algorithms (e.g., LIS in O(n log n) with patience sorting)

## Practice Notes
- Date: _______  Problem: ____________  Score: ___/10  Notes:
- Date: _______  Problem: ____________  Score: ___/10  Notes:
- Date: _______  Problem: ____________  Score: ___/10  Notes:

Source: [Dynamic Programming: From Recursion to Optimization (CalibreOS)](https://www.calibreos.com/learn/dsa-dynamic-programming)
