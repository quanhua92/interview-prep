# Merge Intervals — Flashcards

4 cards. Drill: read the trigger, recall the pattern + move, then click to verify.

<details><summary><b>A list of closed intervals — merge all overlapping ones and return the disjoint set</b></summary>

Pattern: Merge Intervals &nbsp;|&nbsp; O(n log n)
Move: Sort by start; iterate and either extend the running interval when starts overlap its end, or push it and start a new one.
File: [coding_merge_intervals.md](../../tiers/foundation/coding_merge_intervals.md)
</details>

<details><summary><b>A sorted list of non-overlapping intervals and one new interval — insert and merge</b></summary>

Pattern: Merge Intervals &nbsp;|&nbsp; O(n)
Move: Single linear pass in 3 stages — copy intervals ending before the new one, then merge all that overlap the new one, then copy the rest.
File: [coding_insert_interval.md](../../tiers/foundation/coding_insert_interval.md)
</details>

<details><summary><b>An array of meeting start/end times — minimum number of conference rooms required</b></summary>

Pattern: Merge Intervals &nbsp;|&nbsp; O(n log n)
Move: Sweep-line — sort starts and ends separately, walk a counter that +1 on a start and -1 on an end, tracking the running peak.
File: [coding_meeting_rooms.md](../../tiers/foundation/coding_meeting_rooms.md)
</details>

<details><summary><b>A series of (time, duration) attacks — total time the target is poisoned (no stacking, later attack refreshes)</b></summary>

Pattern: Merge Intervals &nbsp;|&nbsp; O(n)
Move: Walk consecutive attacks; for each, add min(duration, gap-to-next-attack) so overlapping poison windows don't double-count.
File: [coding_teemo_attacking.md](../../tiers/foundation/coding_teemo_attacking.md)
</details>

---

[Back to Flashcard Index](../README.md) | [Foundation Tier README](../../tiers/foundation/README.md)
