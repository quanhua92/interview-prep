# Subsets — Flashcards

3 cards. Drill: read the trigger, recall the pattern + move, then click to verify.

<details><summary><b>Array of distinct ints — return all possible permutations</b></summary>

Pattern: Subsets &nbsp;|&nbsp; O(n!)
Move: At each index i, swap it with every j ≥ i, recurse, then swap back (backtrack). Alternatively, sort and walk std::next_permutation to enumerate.
File: [coding_permutations.md](../../tiers/advanced/coding_permutations.md)
</details>

<details><summary><b>Two ints n and k — list every k-combination from [1..n]</b></summary>

Pattern: Subsets &nbsp;|&nbsp; O(C(n,k) * k)
Move: Backtrack with a running size limit; record once it hits k and prune branches that can no longer reach k. Gosper's hack enumerates the k-bit integer masks directly.
File: [coding_combinations.md](../../tiers/advanced/coding_combinations.md)
</details>

<details><summary><b>Int array that may contain duplicates — return all distinct subsets</b></summary>

Pattern: Subsets &nbsp;|&nbsp; O(2^n)
Move: Sort the array first; at each recursion level skip a value equal to the sibling you just declined at this depth to prevent regenerating the same subset.
File: [coding_subsets_ii.md](../../tiers/advanced/coding_subsets_ii.md)
</details>

---

[Back to Flashcard Index](../README.md) | [Advanced Tier README](../../tiers/advanced/README.md)
