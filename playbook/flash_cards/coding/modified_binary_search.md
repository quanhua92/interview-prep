# Modified Binary Search — Flashcards

3 cards. Drill: read the trigger, recall the pattern + move, then click to verify.

<details><summary><b>Rotated sorted array of distinct ints — find the target index in O(log n)</b></summary>

Pattern: Modified Binary Search &nbsp;|&nbsp; O(log n)
Move: At each midpoint, identify which half is properly sorted; check whether the target lies inside that sorted half to decide which side to keep, then narrow bounds.
File: [coding_search_rotated.md](../../tiers/advanced/coding_search_rotated.md)
</details>

<details><summary><b>Split array into m contiguous subarrays — minimize the largest subarray sum</b></summary>

Pattern: Modified Binary Search &nbsp;|&nbsp; O(n log(sum))
Move: Binary-search the answer in [max(nums), sum(nums)]; the feasibility test greedily counts how many subarrays are needed at a given cap and returns true if ≤ m.
File: [coding_split_array_sum.md](../../tiers/advanced/coding_split_array_sum.md)
</details>

<details><summary><b>k piles of bananas, h hours to eat them all (k per hour per pile) — find the minimum eating speed</b></summary>

Pattern: Modified Binary Search &nbsp;|&nbsp; O(n log maxPile)
Move: Binary-search the speed in [1, max(piles)]; feasibility test sums ceil(pile / speed) over piles and compares against h.
File: [coding_koko_bananas.md](../../tiers/advanced/coding_koko_bananas.md)
</details>

---

[Back to Flashcard Index](../README.md) | [Advanced Tier README](../../tiers/advanced/README.md)
