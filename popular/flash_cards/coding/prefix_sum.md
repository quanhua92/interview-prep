# Prefix Sum — Flashcards

6 cards. Drill: read the trigger, recall the pattern + move, then click to verify.

<details><summary><b>compute product of every element except self, no division allowed</b></summary>

Pattern: Prefix Sum &nbsp;|&nbsp; Medium &nbsp;|&nbsp; O(1) space
Move: Build prefix/suffix products consolidated into a single output pass.
File: [coding_product_except_self.md](../../tiers/intermediate/coding_product_except_self.md)
</details>

<details><summary><b>count contiguous subarrays whose sum equals k</b></summary>

Pattern: Prefix Sum &nbsp;|&nbsp; Medium
Move: Hash cumulative sums and look up prior prefix frequencies.
File: [coding_subarray_sum_equals_k.md](../../tiers/intermediate/coding_subarray_sum_equals_k.md)
</details>

<details><summary><b>count contiguous subarrays whose product is less than k</b></summary>

Pattern: Prefix Sum &nbsp;|&nbsp; Medium
Move: Sliding window with combinatorial count of new subarrays per right bound.
File: [coding_subarray_product_less_than_k.md](../../tiers/intermediate/coding_subarray_product_less_than_k.md)
</details>

<details><summary><b>does any contiguous subarray of size >= 2 sum to a multiple of k?</b></summary>

Pattern: Prefix Sum &nbsp;|&nbsp; Medium
Move: Hash prefix-sum remainders mod k to match earlier offsets (distance >= 2).
File: [coding_continuous_subarray_sum.md](../../tiers/intermediate/coding_continuous_subarray_sum.md)
</details>

<details><summary><b>max length of a contiguous subarray with equal 0s and 1s</b></summary>

Pattern: Prefix Sum &nbsp;|&nbsp; Medium
Move: Treat 0 as -1, track first index per running offset; max distance wins.
File: [coding_contiguous_array.md](../../tiers/intermediate/coding_contiguous_array.md)
</details>

<details><summary><b>pick an index at random, weighted by w[i]</b></summary>

Pattern: Prefix Sum &nbsp;|&nbsp; Medium
Move: Build cumulative weight prefix sums, binary-search the random roll.
File: [coding_random_pick_with_weight.md](../../tiers/intermediate/coding_random_pick_with_weight.md)
</details>

---

[Back to Flashcard Index](../README.md) | [Intermediate Tier README](../../tiers/intermediate/README.md)
