# Greedy — Flashcards

8 cards. Drill: read the trigger, recall the pattern + move, then click to verify.

<details><summary><b>Array of max jump lengths — starting at index 0, can you reach the last index?</b></summary>

Pattern: Greedy &nbsp;|&nbsp; O(n)
Move: Track the maximum reachable index as you scan left to right; if i ever passes it, the goal is unreachable.
File: [coding_jump_game.md](../../tiers/expert/coding_jump_game.md)
</details>

<details><summary><b>Two arrays (gas, cost) around a circular route — return the start index that completes the loop, or -1</b></summary>

Pattern: Greedy &nbsp;|&nbsp; O(n)
Move: If total gas ≥ total cost a solution exists; the valid start is the index immediately after the prefix with the largest cumulative deficit.
File: [coding_gas_station.md](../../tiers/expert/coding_gas_station.md)
</details>

<details><summary><b>Children ratings in a line — each needs ≥ 1 candy and strictly more than any lower-rated neighbor; minimize total candies</b></summary>

Pattern: Greedy &nbsp;|&nbsp; O(n)
Move: Two passes — left-to-right raises the candy count when the rating rises, then right-to-left raises it to satisfy right neighbors; take the per-child max and sum.
File: [coding_candy.md](../../tiers/expert/coding_candy.md)
</details>

<details><summary><b>Balloons as [start, end] horizontal intervals — minimum arrows to burst them all (one arrow bursts its x-coordinate)</b></summary>

Pattern: Greedy &nbsp;|&nbsp; O(n log n)
Move: Sort intervals by end; greedily fire an arrow at the earliest end and skip every interval that also covers that point.
File: [coding_minimum_number_of_arrows_to_burst_balloons.md](../../tiers/expert/coding_minimum_number_of_arrows_to_burst_balloons.md)
</details>

<details><summary><b>Children greed factors g[] and cookie sizes s[] — maximize content children (a cookie satisfies a child iff size ≥ greed)</b></summary>

Pattern: Greedy &nbsp;|&nbsp; O(n log n + m log m)
Move: Sort both arrays; two-pointer match — feed the smallest remaining cookie that satisfies the smallest unmet greed.
File: [coding_assign_cookies.md](../../tiers/expert/coding_assign_cookies.md)
</details>

<details><summary><b>Projects each with a capital need and a profit, plus starting capital w and at most k picks — maximize final capital</b></summary>

Pattern: Greedy &nbsp;|&nbsp; O((N + k) log N)
Move: Sort projects by capital need; sweep capital pushing affordable projects' profits into a max-heap and pick the top one, k times.
File: [coding_ipo.md](../../tiers/expert/coding_ipo.md)
</details>

<details><summary><b>Array of task labels and a cooldown n between two same tasks — minimum intervals to run them all (idle allowed)</b></summary>

Pattern: Greedy &nbsp;|&nbsp; O(n)
Move: Compute the max-frequency task; idle slots = (maxFreq - 1) * (n + 1) plus the count of tasks tied at that max, floored at the total task count.
File: [coding_task_scheduler.md](../../tiers/expert/coding_task_scheduler.md)
</details>

<details><summary><b>Tasks with durations to run across a fixed number of machines — minimize the makespan to finish all</b></summary>

Pattern: Greedy &nbsp;|&nbsp; O(n log n + n log m)
Move: Sort tasks descending by duration; keep machines in a min-heap keyed by earliest free time and assign each task to the soonest-free machine.
File: [coding_task_scheduler_multi_machine.md](../../tiers/expert/coding_task_scheduler_multi_machine.md)
</details>

---

[Back to Flashcard Index](../README.md) | [Expert Tier README](../../tiers/expert/README.md)
