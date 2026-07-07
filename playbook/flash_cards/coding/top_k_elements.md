# Top K Elements — Flashcards

4 cards. Drill: read the trigger, recall the pattern + move, then click to verify.

<details><summary><b>find the kth largest element in an unsorted array</b></summary>

Pattern: Top K Elements &nbsp;|&nbsp; Medium
Move: Quickselect partition, or maintain a size-k min-heap of the largest seen.
File: [coding_kth_largest.md](../../tiers/intermediate/coding_kth_largest.md)
</details>

<details><summary><b>return the k most frequent elements</b></summary>

Pattern: Top K Elements &nbsp;|&nbsp; Medium
Move: Frequency map then bucket sort by count, or size-k min-heap on frequencies.
File: [coding_top_k_frequent.md](../../tiers/intermediate/coding_top_k_frequent.md)
</details>

<details><summary><b>volume of trapped rainwater on a 2D elevation map</b></summary>

Pattern: Top K Elements &nbsp;|&nbsp; Hard
Move: Priority-queue BFS expanding the border; each cell traps by its min-border.
File: [coding_trapping_rain_water_ii.md](../../tiers/intermediate/coding_trapping_rain_water_ii.md)
</details>

<details><summary><b>find the k points closest to the origin</b></summary>

Pattern: Top K Elements &nbsp;|&nbsp; Medium
Move: Max-heap of size k keyed by squared Euclidean distance; pop when over k.
File: [coding_k_closest_points.md](../../tiers/intermediate/coding_k_closest_points.md)
</details>

---

[Back to Flashcard Index](../README.md) | [Intermediate Tier README](../../tiers/intermediate/README.md)
