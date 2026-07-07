# Binary Search — Flashcards

7 cards. Drill: read the trigger, recall the pattern + move, then click to verify.

<details><summary><b>find minimum element in a rotated sorted array with no duplicates</b></summary>

Pattern: Binary Search &nbsp;|&nbsp; Medium
Move: Identify the unsorted half; the inflection (minimum) always lies there.
File: [coding_find_min_rotated.md](../../tiers/intermediate/coding_find_min_rotated.md)
</details>

<details><summary><b>find first bad version in a linear sequence via an isBadVersion API</b></summary>

Pattern: Binary Search &nbsp;|&nbsp; Easy
Move: Left-biased convergence to minimize bad API calls.
File: [coding_first_bad_version.md](../../tiers/intermediate/coding_first_bad_version.md)
</details>

<details><summary><b>maintain a set of disjoint intervals as numbers stream in</b></summary>

Pattern: Binary Search &nbsp;|&nbsp; Hard
Move: Look up ordered boundaries, merge overlapping intervals on each add.
File: [coding_data_stream_as_disjoint_intervals.md](../../tiers/intermediate/coding_data_stream_as_disjoint_intervals.md)
</details>

<details><summary><b>maximum number of russian-doll-envelopes you can nest</b></summary>

Pattern: Binary Search &nbsp;|&nbsp; Hard
Move: Sort by (width asc, height desc), then LIS via patience search on heights.
File: [coding_russian_doll_envelopes.md](../../tiers/intermediate/coding_russian_doll_envelopes.md)
</details>

<details><summary><b>smallest base b whose representation of n is all 1s</b></summary>

Pattern: Binary Search &nbsp;|&nbsp; Hard
Move: For each geometric-series length, binary-search the base representation.
File: [coding_smallest_good_base.md](../../tiers/intermediate/coding_smallest_good_base.md)
</details>

<details><summary><b>pick a uniformly random point across a set of non-overlapping rectangles</b></summary>

Pattern: Binary Search &nbsp;|&nbsp; Medium
Move: Prefix the weighted areas, binary-search the random pick by area, decode coords.
File: [coding_random_point_in_non_overlapping_rectangles.md](../../tiers/intermediate/coding_random_point_in_non_overlapping_rectangles.md)
</details>

<details><summary><b>find target index in a sorted array</b></summary>

Pattern: Binary Search &nbsp;|&nbsp; Easy
Move: Classical mid-point search with overflow-safe midpoint (lo + (hi-lo)/2).
File: [coding_binary_search.md](../../tiers/intermediate/coding_binary_search.md)
</details>

---

[Back to Flashcard Index](../README.md) | [Intermediate Tier README](../../tiers/intermediate/README.md)
