# Bit Manipulation — Flashcards

4 cards. Drill: read the trigger, recall the pattern + move, then click to verify.

<details><summary><b>count the number of set bits (popcount) in an unsigned integer</b></summary>

Pattern: Bit Manipulation &nbsp;|&nbsp; Easy
Move: Brian Kernighan's n & (n-1) clears the lowest set bit each iteration.
File: [coding_number_of_1_bits.md](../../tiers/intermediate/coding_number_of_1_bits.md)
</details>

<details><summary><b>find the lone element that appears once while all others appear twice</b></summary>

Pattern: Bit Manipulation &nbsp;|&nbsp; Easy
Move: XOR all elements; identical pairs cancel (x ^ x = 0) and leave the singleton.
File: [coding_single_number.md](../../tiers/intermediate/coding_single_number.md)
</details>

<details><summary><b>return popcount for every integer from 0 to n</b></summary>

Pattern: Bit Manipulation &nbsp;|&nbsp; Easy
Move: DP on bits: dp[i] = dp[i >> 1] + (i & 1).
File: [coding_counting_bits.md](../../tiers/intermediate/coding_counting_bits.md)
</details>

<details><summary><b>flip all bits of a non-negative integer (no leading zeros kept)</b></summary>

Pattern: Bit Manipulation &nbsp;|&nbsp; Easy
Move: Build an all-ones mask the bit-length of n, then XOR n with that mask.
File: [coding_number_complement.md](../../tiers/intermediate/coding_number_complement.md)
</details>

---

[Back to Flashcard Index](../README.md) | [Intermediate Tier README](../../tiers/intermediate/README.md)
