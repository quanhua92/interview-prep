# Trie — Flashcards

4 cards. Drill: read the trigger, recall the pattern + move, then click to verify.

<details><summary><b>Design a prefix tree supporting insert, search, and startsWith operations</b></summary>

Pattern: Trie &nbsp;|&nbsp; O(L) per op
Move: Each node holds 26 child pointers plus an is_end flag; insert walks/creates nodes char-by-char, and search/startsWith walk down the same path.
File: [coding_implement_trie.md](../../tiers/advanced/coding_implement_trie.md)
</details>

<details><summary><b>Trie that supports a '.' wildcard matching any single character in search</b></summary>

Pattern: Trie &nbsp;|&nbsp; O(26^L) worst
Move: Same as a standard Trie, but on '.' recurse into every existing child and accept the first full match; prune empty branches early.
File: [coding_design_add_search.md](../../tiers/advanced/coding_design_add_search.md)
</details>

<details><summary><b>m x n grid of chars and a list of words — return every word findable by walking adjacent cells</b></summary>

Pattern: Trie &nbsp;|&nbsp; O(m * n * 4^L)
Move: Insert all words into a Trie; DFS the grid cell-by-cell descending only when a Trie child exists; prune Trie leaves on each word hit to avoid re-reporting.
File: [coding_word_search_ii.md](../../tiers/advanced/coding_word_search_ii.md)
</details>

<details><summary><b>List of words — return each word that is a concatenation of two or more other words in the list</b></summary>

Pattern: Trie &nbsp;|&nbsp; O(N * L^2)
Move: For each word run word-break DP where the dictionary is the other words; a Trie lets every prefix lookup share the same search tree.
File: [coding_concatenated_words.md](../../tiers/advanced/coding_concatenated_words.md)
</details>

---

[Back to Flashcard Index](../README.md) | [Advanced Tier README](../../tiers/advanced/README.md)
