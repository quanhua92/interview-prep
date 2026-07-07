# Two Pointers — Flashcards

8 cards. Drill: read the trigger, recall the pattern + move, then click to verify.

<details><summary><b>Array of heights, two lines chosen form a container — maximize water area</b></summary>

Pattern: Two Pointers &nbsp;|&nbsp; O(n)
Move: Greedy choice between left/right boundaries; move the shorter wall inward to seek a taller line and shrink width.
File: [coding_container_water.md](../../tiers/foundation/coding_container_water.md)
</details>

<details><summary><b>Array of ints, find all unique triplets summing to zero</b></summary>

Pattern: Two Pointers &nbsp;|&nbsp; O(n^2)
Move: Sort, then fix one element and run two-pointer pair search; skip duplicates at each anchor to avoid repeated triplets.
File: [coding_three_sum.md](../../tiers/foundation/coding_three_sum.md)
</details>

<details><summary><b>Sorted array, find two elements summing to target, return 1-based indices</b></summary>

Pattern: Two Pointers &nbsp;|&nbsp; O(n)
Move: Walk one pointer from each end; sum too small → advance left, too large → retreat right, using sorted order for O(1) space lookup.
File: [coding_two_sum.md](../../tiers/foundation/coding_two_sum.md)
</details>

<details><summary><b>Two strings s and t — is s a subsequence of t (order preserved, chars deletable)?</b></summary>

Pattern: Two Pointers &nbsp;|&nbsp; O(|t|)
Move: Greedy match pointer in t advances only on matches; if the s pointer reaches the end, it is a subsequence.
File: [coding_is_subsequence.md](../../tiers/foundation/coding_is_subsequence.md)
</details>

<details><summary><b>Array of houses and heaters on a line — find the minimum radius so every house is warmed</b></summary>

Pattern: Two Pointers &nbsp;|&nbsp; O(n log n + m log m)
Move: Sort both, then for each house advance the heater pointer to the nearest one; take max of per-house nearest distances.
File: [coding_heaters.md](../../tiers/foundation/coding_heaters.md)
</details>

<details><summary><b>List of strings — return length of the longest one that is not a subsequence of any other string in the list</b></summary>

Pattern: Two Pointers &nbsp;|&nbsp; O(n^2 * L)
Move: For each candidate, check it against all others via subsequence test; longer string can never be a subsequence of a shorter one.
File: [coding_longest_uncommon_subsequence_ii.md](../../tiers/foundation/coding_longest_uncommon_subsequence_ii.md)
</details>

<details><summary><b>A string s and a dictionary of words — find the longest word in dict that can be formed by deleting chars from s</b></summary>

Pattern: Two Pointers &nbsp;|&nbsp; O(d * |s|)
Move: Sort dict by length desc then lexicographic; greedily walk each candidate against s with a match pointer; first match wins.
File: [coding_longest_word_in_dictionary_through_deleting.md](../../tiers/foundation/coding_longest_word_in_dictionary_through_deleting.md)
</details>

<details><summary><b>Array of ints and a target diff k — count unique pairs (a, b) with |a - b| == k</b></summary>

Pattern: Two Pointers &nbsp;|&nbsp; O(n log n)
Move: Sort, then walk two pointers; special-case k == 0 (count values appearing 2+ times) and skip duplicates to prevent double counting.
File: [coding_k_diff_pairs_in_an_array.md](../../tiers/foundation/coding_k_diff_pairs_in_an_array.md)
</details>

---

[Back to Flashcard Index](../README.md) | [Foundation Tier README](../../tiers/foundation/README.md)
