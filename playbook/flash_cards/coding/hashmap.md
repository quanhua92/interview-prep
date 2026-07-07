# Hashmap — Flashcards

8 cards. Drill: read the trigger, recall the pattern + move, then click to verify.

<details><summary><b>Design a set with insert, remove, and getRandom all in average O(1)</b></summary>

Pattern: Hashmap &nbsp;|&nbsp; O(1) avg per op
Move: Combine a dynamic vector (values) with a hash table (value → index); swap-remove the last element into the deleted slot to keep indices valid.
File: [coding_insert_delete_getrandom_o1.md](../../tiers/foundation/coding_insert_delete_getrandom_o1.md)
</details>

<details><summary><b>Given a singly linked list, return a random node's value with uniform probability</b></summary>

Pattern: Hashmap &nbsp;|&nbsp; O(n) one pass
Move: Reservoir sampling (size 1) — at the i-th node, pick it with probability 1/i; no second pass or length storage needed.
File: [coding_linked_list_random_node.md](../../tiers/foundation/coding_linked_list_random_node.md)
</details>

<details><summary><b>Axis-aligned rectangles — do they exactly tile a single larger rectangle with no gaps or overlaps?</b></summary>

Pattern: Hashmap &nbsp;|&nbsp; O(n)
Move: Sum areas and verify against the bounding rectangle's area; all corners must appear an even number of times except the four bounding corners.
File: [coding_perfect_rectangle.md](../../tiers/foundation/coding_perfect_rectangle.md)
</details>

<details><summary><b>An array possibly with duplicates — pick a random index of a given target value, uniform over its occurrences</b></summary>

Pattern: Hashmap &nbsp;|&nbsp; O(n) one pass
Move: Reservoir sampling — when a value equals target, hold its index with probability 1/count_so_far; alternatively precompute a target → indices map.
File: [coding_random_pick_index.md](../../tiers/foundation/coding_random_pick_index.md)
</details>

<details><summary><b>n points in 2D plane — count ordered triples (i, j, k) where dist(i, j) == dist(i, k)</b></summary>

Pattern: Hashmap &nbsp;|&nbsp; O(n^2)
Move: For each pivot, hash distances to all others; each bucket of size m contributes m*(m-1) ordered boomerangs (permutations counting).
File: [coding_number_of_boomerangs.md](../../tiers/foundation/coding_number_of_boomerangs.md)
</details>

<details><summary><b>A list of words — return those that can be typed using letters of only one row of a US keyboard</b></summary>

Pattern: Hashmap &nbsp;|&nbsp; O(total letters)
Move: Build a set per keyboard row (or a char → row map); a word qualifies iff all its chars map to the same row set.
File: [coding_keyboard_row.md](../../tiers/foundation/coding_keyboard_row.md)
</details>

<details><summary><b>Design a TinyURL-like service: encode a long URL to a short key and decode it back</b></summary>

Pattern: Hashmap &nbsp;|&nbsp; O(1) per op
Move: Two-way map (long ↔ short) backed by a random base62 ID generator; encode generates a new key, decode looks it up.
File: [coding_encode_and_decode_tinyurl.md](../../tiers/foundation/coding_encode_and_decode_tinyurl.md)
</details>

<details><summary><b>An even-length candy array — max number of different types a person can take if they get exactly n/2 candies</b></summary>

Pattern: Hashmap &nbsp;|&nbsp; O(n)
Move: Count distinct types via a set; the answer is the min of distinct types and n/2 (you cannot take more types than candies you're allowed).
File: [coding_distribute_candies.md](../../tiers/foundation/coding_distribute_candies.md)
</details>

---

[Back to Flashcard Index](../README.md) | [Foundation Tier README](../../tiers/foundation/README.md)
