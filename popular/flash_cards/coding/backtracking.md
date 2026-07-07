# Backtracking — Flashcards

6 cards. Drill: read the trigger, recall the pattern + move, then click to verify.

<details><summary><b>Phone keypad digits (2-9) — list every letter string the digits could spell</b></summary>

Pattern: Backtracking &nbsp;|&nbsp; O(4^n)
Move: Map each digit to its letters and recurse by appending one letter per digit, walking the digit string left to right (equivalently, a BFS queue of growing prefixes).
File: [coding_letter_combinations.md](../../tiers/advanced/coding_letter_combinations.md)
</details>

<details><summary><b>Distinct candidates and a target — list every unique combination summing to target (unlimited reuse)</b></summary>

Pattern: Backtracking &nbsp;|&nbsp; O(2^n)
Move: Sort the candidates, then backtrack passing the same start index on the recursive call (allowing reuse) while skipping earlier picks to prevent duplicate combinations.
File: [coding_combination_sum.md](../../tiers/advanced/coding_combination_sum.md)
</details>

<details><summary><b>Distinct-int array — return all possible subsets (the power set)</b></summary>

Pattern: Backtracking &nbsp;|&nbsp; O(2^n)
Move: Recursively decide include/exclude for each element to cascade-build subsets, or enumerate bitmask integers 0..2^n-1 and map set bits to indices.
File: [coding_subsets.md](../../tiers/advanced/coding_subsets.md)
</details>

<details><summary><b>Array of matchstick lengths — can every stick be used exactly once to form a square?</b></summary>

Pattern: Backtracking &nbsp;|&nbsp; O(4^n)
Move: Sort descending so large sticks fail early, recurse into 4 sides of target sum/4, and break symmetry by skipping sibling sides with equal partial sums.
File: [coding_matchsticks_to_square.md](../../tiers/advanced/coding_matchsticks_to_square.md)
</details>

<details><summary><b>Board string of colored balls plus a hand of balls — minimum insertions to clear the board</b></summary>

Pattern: Backtracking &nbsp;|&nbsp; exponential
Move: DFS over (board, hand) states; collapse runs of ≥ 3 on each insertion, memoize visited states, and prune branches whose hand grows past the best-so-far insertion count.
File: [coding_zuma_game.md](../../tiers/advanced/coding_zuma_game.md)
</details>

<details><summary><b>Array of ints — return all distinct non-decreasing subsequences of length ≥ 2</b></summary>

Pattern: Backtracking &nbsp;|&nbsp; O(2^n)
Move: Backtrack preserving input order; at each recursion level skip a value equal to a previously-skipped sibling so the same subsequence can never be regenerated.
File: [coding_non_decreasing_subsequences.md](../../tiers/advanced/coding_non_decreasing_subsequences.md)
</details>

---

[Back to Flashcard Index](../README.md) | [Advanced Tier README](../../tiers/advanced/README.md)
