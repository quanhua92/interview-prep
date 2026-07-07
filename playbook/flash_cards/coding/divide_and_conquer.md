# Divide & Conquer — Flashcards

5 cards. Drill: read the trigger, recall the pattern + move, then click to verify.

<details><summary><b>merge k sorted linked lists into one sorted list</b></summary>

Pattern: Divide & Conquer &nbsp;|&nbsp; Hard
Move: Min-heap of current list-heads, or recursively partition-merge pairs of lists.
File: [coding_merge_k_sorted_lists.md](../../tiers/intermediate/coding_merge_k_sorted_lists.md)
</details>

<details><summary><b>find the element appearing more than floor(n/2) times</b></summary>

Pattern: Divide & Conquer &nbsp;|&nbsp; Easy
Move: Boyer-Moore voting: count up for the candidate, down on mismatch.
File: [coding_majority_element.md](../../tiers/intermediate/coding_majority_element.md)
</details>

<details><summary><b>build a quad tree from an n x n grid of 0s/1s</b></summary>

Pattern: Divide & Conquer &nbsp;|&nbsp; Medium
Move: Quad-partition the grid; collapse uniform quadrants into leaves.
File: [coding_construct_quad_tree.md](../../tiers/intermediate/coding_construct_quad_tree.md)
</details>

<details><summary><b>count pairs i < j with nums[i] > 2 * nums[j]</b></summary>

Pattern: Divide & Conquer &nbsp;|&nbsp; Hard
Move: Merge sort while counting cross inversions of nums[i] > 2*nums[j].
File: [coding_reverse_pairs.md](../../tiers/intermediate/coding_reverse_pairs.md)
</details>

<details><summary><b>sort an array without using the built-in sort</b></summary>

Pattern: Divide & Conquer &nbsp;|&nbsp; Medium
Move: Implement quicksort, mergesort, or heapsort safely with correct partitioning.
File: [coding_sort_an_array.md](../../tiers/intermediate/coding_sort_an_array.md)
</details>

---

[Back to Flashcard Index](../README.md) | [Intermediate Tier README](../../tiers/intermediate/README.md)
