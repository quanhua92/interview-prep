# Math — Flashcards

5 cards. Drill: read the trigger, recall the pattern + move, then click to verify.

<details><summary><b>fewest pigs needed to find the one poisonous bucket given T test rounds</b></summary>

Pattern: Math &nbsp;|&nbsp; Hard
Move: Each pig has (rounds+1) states; find smallest p with (T+1)^p >= buckets.
File: [coding_poor_pigs.md](../../tiers/intermediate/coding_poor_pigs.md)
</details>

<details><summary><b>generate a uniformly random point inside a unit circle</b></summary>

Pattern: Math &nbsp;|&nbsp; Medium
Move: Inverse-CDF sample: r = R * sqrt(rand()), theta = 2*pi*rand(); reject corners.
File: [coding_generate_random_point_in_a_circle.md](../../tiers/intermediate/coding_generate_random_point_in_a_circle.md)
</details>

<details><summary><b>largest palindrome that is the product of two n-digit numbers</b></summary>

Pattern: Math &nbsp;|&nbsp; Hard
Move: Construct the palindrome from the upper half, search for factors, mod 1337.
File: [coding_largest_palindrome_product.md](../../tiers/intermediate/coding_largest_palindrome_product.md)
</details>

<details><summary><b>smallest integer greater than n using the same digits</b></summary>

Pattern: Math &nbsp;|&nbsp; Medium
Move: Next-permutation algorithm, then verify no 32-bit signed overflow.
File: [coding_next_greater_element_iii.md](../../tiers/intermediate/coding_next_greater_element_iii.md)
</details>

<details><summary><b>closest integer (not equal to n) that is a palindrome</b></summary>

Pattern: Math &nbsp;|&nbsp; Hard
Move: Mirror the first half; also test half +/- 1 and the 9...9 / 10...01 edge cases.
File: [coding_find_the_closest_palindrome.md](../../tiers/intermediate/coding_find_the_closest_palindrome.md)
</details>

---

[Back to Flashcard Index](../README.md) | [Intermediate Tier README](../../tiers/intermediate/README.md)
