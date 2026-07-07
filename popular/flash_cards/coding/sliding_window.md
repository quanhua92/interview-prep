# Sliding Window — Flashcards

5 cards. Drill: read the trigger, recall the pattern + move, then click to verify.

<details><summary><b>A string — length of the longest substring with no repeating characters</b></summary>

Pattern: Sliding Window &nbsp;|&nbsp; O(n)
Move: Expand right, keep a map of last-seen indices; when a repeat falls inside the window, jump the left pointer past it (dynamic left update).
File: [coding_longest_substring.md](../../tiers/foundation/coding_longest_substring.md)
</details>

<details><summary><b>A string and int k — length of the longest substring where every char appears at least k times</b></summary>

Pattern: Sliding Window &nbsp;|&nbsp; O(n * 26)
Move: For each candidate count h of unique chars (1..26), run a window whose char set stays at size h; valid when every in-window char count >= k.
File: [coding_longest_substring_with_at_least_k_repeating_characters.md](../../tiers/foundation/coding_longest_substring_with_at_least_k_repeating_characters.md)
</details>

<details><summary><b>A string of uppercase letters and int k — longest substring achievable by replacing at most k chars</b></summary>

Pattern: Sliding Window &nbsp;|&nbsp; O(n)
Move: Track window char frequencies; the window is valid while (length - max_freq) <= k, so never shrink — just shift right when it exceeds.
File: [coding_longest_repeating_char.md](../../tiers/foundation/coding_longest_repeating_char.md)
</details>

<details><summary><b>Strings s and p — find all start indices in s of substrings that are anagrams of p</b></summary>

Pattern: Sliding Window &nbsp;|&nbsp; O(|s|)
Move: Fixed-width window of size |p| sliding one step; compare the window's char frequency map against p's map (diffing counters).
File: [coding_find_anagrams.md](../../tiers/foundation/coding_find_anagrams.md)
</details>

<details><summary><b>Strings s1 and s2 — does s2 contain a permutation of s1 as a contiguous substring?</b></summary>

Pattern: Sliding Window &nbsp;|&nbsp; O(|s2|)
Move: Slide a fixed |s1|-width window over s2; sliding-frequency-compare against s1's frequency map and report when they match.
File: [coding_permutation_in_string.md](../../tiers/foundation/coding_permutation_in_string.md)
</details>

---

[Back to Flashcard Index](../README.md) | [Foundation Tier README](../../tiers/foundation/README.md)
