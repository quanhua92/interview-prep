# Graph — Flashcards

3 cards. Drill: read the trigger, recall the pattern + move, then click to verify.

<details><summary><b>numCourses and prerequisite pairs [a, b] meaning "b before a" — can you finish every course?</b></summary>

Pattern: Graph &nbsp;|&nbsp; O(V + E)
Move: Build the adjacency list, then run Kahn's BFS (queue in-degree-zero nodes) or DFS color states (0/1/2) to detect a back-edge — a cycle means impossible.
File: [coding_course_schedule.md](../../tiers/expert/coding_course_schedule.md)
</details>

<details><summary><b>numCourses and prerequisites — return any valid topological order, or [] if none exists</b></summary>

Pattern: Graph &nbsp;|&nbsp; O(V + E)
Move: Kahn's BFS — repeatedly dequeue an in-degree-zero node, append it to the order, decrement its neighbors; if the output count is below n, return [].
File: [coding_course_schedule_ii.md](../../tiers/expert/coding_course_schedule_ii.md)
</details>

<details><summary><b>n people and a trust list [a, b] meaning "a trusts b" — find the one who trusts nobody yet is trusted by everyone (else -1)</b></summary>

Pattern: Graph &nbsp;|&nbsp; O(n + t)
Move: Trust-score each person: trustee +1, truster -1; the judge is the single index whose net score equals n - 1.
File: [coding_town_judge.md](../../tiers/expert/coding_town_judge.md)
</details>

---

[Back to Flashcard Index](../README.md) | [Expert Tier README](../../tiers/expert/README.md)
