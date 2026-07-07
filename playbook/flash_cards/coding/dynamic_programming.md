# Dynamic Programming — Flashcards

13 cards. Drill: read the trigger, recall the pattern + move, then click to verify.

<details><summary><b>count distinct ways to climb n stairs taking 1 or 2 steps</b></summary>

Pattern: Dynamic Programming &nbsp;|&nbsp; Easy
Move: dp[i] = dp[i-1] + dp[i-2] (Fibonacci); reduce to two rolling variables.
File: [coding_climbing_stairs.md](../../tiers/intermediate/coding_climbing_stairs.md)
</details>

<details><summary><b>maximum money you can rob without touching two adjacent houses</b></summary>

Pattern: Dynamic Programming &nbsp;|&nbsp; Medium
Move: dp[i] = max(dp[i-1], dp[i-2] + nums[i]); two-variable reduction.
File: [coding_house_robber.md](../../tiers/intermediate/coding_house_robber.md)
</details>

<details><summary><b>fewest coins needed to make amount, given unlimited coins of each denomination</b></summary>

Pattern: Dynamic Programming &nbsp;|&nbsp; Medium
Move: 1D unbounded knapsack; dp[a] = min(dp[a], 1 + dp[a - coin]).
File: [coding_coin_change.md](../../tiers/intermediate/coding_coin_change.md)
</details>

<details><summary><b>can a frog cross stones, with next jump being k-1, k, or k+1 of the last?</b></summary>

Pattern: Dynamic Programming &nbsp;|&nbsp; Hard
Move: DFS with memo on (position, last jump); jumps are last-1, last, last+1.
File: [coding_frog_jump.md](../../tiers/intermediate/coding_frog_jump.md)
</details>

<details><summary><b>max count of s2 obtainable by repeating s1 enough times to contain s2</b></summary>

Pattern: Dynamic Programming &nbsp;|&nbsp; Hard
Move: Detect the cycle of matched char counts per s1 repetition to extrapolate.
File: [coding_count_the_repetitions.md](../../tiers/intermediate/coding_count_the_repetitions.md)
</details>

<details><summary><b>count distinct substrings of the infinite cyclic "abcd...xyzabcd..." string</b></summary>

Pattern: Dynamic Programming &nbsp;|&nbsp; Medium
Move: For each letter, track the max cyclic-consecutive run length ending in it.
File: [coding_unique_substrings_in_wraparound_string.md](../../tiers/intermediate/coding_unique_substrings_in_wraparound_string.md)
</details>

<details><summary><b>min steps to spell a key by rotating a ring and pressing its center button</b></summary>

Pattern: Dynamic Programming &nbsp;|&nbsp; Hard
Move: dp[i][j] = min steps to spell key[i:] starting with ring at position j.
File: [coding_freedom_trail.md](../../tiers/intermediate/coding_freedom_trail.md)
</details>

<details><summary><b>length of the longest palindromic subsequence of a string</b></summary>

Pattern: Dynamic Programming &nbsp;|&nbsp; Medium
Move: 2D range DP; dp[i][j] = dp[i+1][j-1] + 2 on match else max of inner.
File: [coding_longest_palindromic_subsequence.md](../../tiers/intermediate/coding_longest_palindromic_subsequence.md)
</details>

<details><summary><b>number of distinct coin combinations that sum to amount</b></summary>

Pattern: Dynamic Programming &nbsp;|&nbsp; Medium
Move: Unbounded knapsack combos; outer loop = coins, inner loop = amounts (no double-count).
File: [coding_coin_change_ii.md](../../tiers/intermediate/coding_coin_change_ii.md)
</details>

<details><summary><b>count valid attendance records of length n (no triple L, at most one A)</b></summary>

Pattern: Dynamic Programming &nbsp;|&nbsp; Hard
Move: 6-state DP (A-count 0/1 x trailing-L-run 0/1/2), summed mod 1e9+7.
File: [coding_student_attendance_record_ii.md](../../tiers/intermediate/coding_student_attendance_record_ii.md)
</details>

<details><summary><b>parenthesize a/b/c/d/... to maximize the resulting value</b></summary>

Pattern: Dynamic Programming &nbsp;|&nbsp; Medium
Move: For n >= 3 the max is nums[0] / (nums[1] / nums[2] / ... / nums[n-1]).
File: [coding_optimal_division.md](../../tiers/intermediate/coding_optimal_division.md)
</details>

<details><summary><b>count paths of length N that move a ball out of an m x n grid</b></summary>

Pattern: Dynamic Programming &nbsp;|&nbsp; Medium
Move: dp[step][r][c] = sum of four neighbors' counts, aggregated mod 1e9+7.
File: [coding_out_of_boundary_paths.md](../../tiers/intermediate/coding_out_of_boundary_paths.md)
</details>

<details><summary><b>fewest drops to find the highest safe floor with K eggs and N floors</b></summary>

Pattern: Dynamic Programming &nbsp;|&nbsp; Hard
Move: Inverse DP: dp[moves][eggs] = max floors testable; binary-search the moves.
File: [coding_super_egg_drop.md](../../tiers/intermediate/coding_super_egg_drop.md)
</details>

---

[Back to Flashcard Index](../README.md) | [Intermediate Tier README](../../tiers/intermediate/README.md)
