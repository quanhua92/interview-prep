# Cyclic Sort — Flashcards

3 cards. Drill: read the trigger, recall the pattern + move, then click to verify.

<details><summary><b>Array of n distinct ints in [0, n], one missing — find it in O(n) time, O(1) space</b></summary>

Pattern: Cyclic Sort &nbsp;|&nbsp; O(n)
Move: Cyclic-sort by swapping each value into its target slot (nums[i] → index nums[i]); the index still holding a wrong value is the missing one. XOR-summing 0..n against the array is an O(1)-space alternative.
File: [coding_missing_number.md](../../tiers/advanced/coding_missing_number.md)
</details>

<details><summary><b>Array of n ints, each value in [1, n], some appear twice — list all duplicates without extra space</b></summary>

Pattern: Cyclic Sort &nbsp;|&nbsp; O(n)
Move: For each value x, flip nums[abs(x) - 1] negative as a marker; if it is already negative when you visit it, x is a duplicate.
File: [coding_find_duplicates.md](../../tiers/advanced/coding_find_duplicates.md)
</details>

<details><summary><b>Array of n ints in [1, n], some appear twice, others vanish — return all missing numbers in O(n)</b></summary>

Pattern: Cyclic Sort &nbsp;|&nbsp; O(n)
Move: For every value x, negate nums[x - 1] as a seen-flag; after the pass, indices still holding a positive value are the missing numbers.
File: [coding_find_disappeared.md](../../tiers/advanced/coding_find_disappeared.md)
</details>

---

[Back to Flashcard Index](../README.md) | [Advanced Tier README](../../tiers/advanced/README.md)
