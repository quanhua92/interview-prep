# String — Flashcards

4 cards. Drill: read the trigger, recall the pattern + move, then click to verify.

<details><summary><b>A sentence string — count how many segments (space-separated words) it contains</b></summary>

Pattern: String &nbsp;|&nbsp; O(n)
Move: Walk the string tracking space/non-space transitions with a state flag; a segment starts when a non-space follows a space (or begins the string).
File: [coding_number_of_segments_in_a_string.md](../../tiers/foundation/coding_number_of_segments_in_a_string.md)
</details>

<details><summary><b>A license key string and group size k — reformat into groups of k separated by dashes, all uppercase</b></summary>

Pattern: String &nbsp;|&nbsp; O(n)
Move: Strip dashes, uppercase, then process backward grouping into blocks of k; the first (leading) group absorbs the remainder.
File: [coding_license_key_formatting.md](../../tiers/foundation/coding_license_key_formatting.md)
</details>

<details><summary><b>A single word — check if its capitalization is valid (all caps, all lower, or only first letter caps)</b></summary>

Pattern: String &nbsp;|&nbsp; O(n)
Move: Count uppercase letters; valid iff the count equals the length, equals zero, or equals one and the first char is uppercase.
File: [coding_detect_capital.md](../../tiers/foundation/coding_detect_capital.md)
</details>

<details><summary><b>Two strings — length of the longest uncommon subsequence (a subsequence of one but not the other)</b></summary>

Pattern: String &nbsp;|&nbsp; O(min(n, m))
Move: Logical deduction — if the strings are equal, no uncommon subsequence exists (-1); otherwise the longer string itself is the answer.
File: [coding_longest_uncommon_subsequence_i.md](../../tiers/foundation/coding_longest_uncommon_subsequence_i.md)
</details>

---

[Back to Flashcard Index](../README.md) | [Foundation Tier README](../../tiers/foundation/README.md)
