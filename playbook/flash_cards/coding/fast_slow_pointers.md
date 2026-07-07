# Fast & Slow Pointers — Flashcards

3 cards. Drill: read the trigger, recall the pattern + move, then click to verify.

<details><summary><b>Singly linked list head — does it contain a cycle?</b></summary>

Pattern: Fast & Slow Pointers &nbsp;|&nbsp; O(n)
Move: Floyd's cycle detection — advance a slow pointer one step and a fast pointer two; if they meet, a cycle exists, if fast hits null, none.
File: [coding_linked_list_cycle.md](../../tiers/foundation/coding_linked_list_cycle.md)
</details>

<details><summary><b>A positive integer — repeatedly replace it with the sum of the squares of its digits; does it converge to 1?</b></summary>

Pattern: Fast & Slow Pointers &nbsp;|&nbsp; O(log n)
Move: Treat the digit-sum sequence like a linked list; run slow/fast on the function iterates — a cycle that isn't 1 means unhappy.
File: [coding_happy_number.md](../../tiers/foundation/coding_happy_number.md)
</details>

<details><summary><b>Singly linked list head — return the middle node (second of two middles for even length)</b></summary>

Pattern: Fast & Slow Pointers &nbsp;|&nbsp; O(n)
Move: Slow moves one step, fast moves two; when fast reaches the end, slow lands on the middle node by parity.
File: [coding_middle_of_linked_list.md](../../tiers/foundation/coding_middle_of_linked_list.md)
</details>

---

[Back to Flashcard Index](../README.md) | [Foundation Tier README](../../tiers/foundation/README.md)
