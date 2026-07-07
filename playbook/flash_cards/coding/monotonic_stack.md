# Monotonic Stack — Flashcards

6 cards. Drill: read the trigger, recall the pattern + move, then click to verify.

<details><summary><b>Array of bar heights — find the area of the largest rectangle in the histogram</b></summary>

Pattern: Monotonic Stack &nbsp;|&nbsp; O(n)
Move: Push indices while heights stay non-decreasing; on a smaller bar, pop and compute area = height * (i - stack.top() - 1); track the running max.
File: [coding_largest_rectangle.md](../../tiers/expert/coding_largest_rectangle.md)
</details>

<details><summary><b>Array of ints — does any subsequence i < j < k satisfy nums[i] < nums[k] < nums[j]?</b></summary>

Pattern: Monotonic Stack &nbsp;|&nbsp; O(n)
Move: Scan right to left tracking the largest valid nums[k] candidate so far; a decreasing stack exposes a nums[j] above it to test against.
File: [coding_132_pattern.md](../../tiers/expert/coding_132_pattern.md)
</details>

<details><summary><b>Circular array of ints — for each element find the next greater one, wrapping around the end</b></summary>

Pattern: Monotonic Stack &nbsp;|&nbsp; O(n)
Move: Iterate indices 0..2n-1 (mod n); push them onto a decreasing stack, and on a larger value pop and record it for the original index.
File: [coding_next_greater_element_ii.md](../../tiers/expert/coding_next_greater_element_ii.md)
</details>

<details><summary><b>Daily temperatures — for each day return the count of days until a warmer one (or 0)</b></summary>

Pattern: Monotonic Stack &nbsp;|&nbsp; O(n)
Move: Maintain a decreasing stack of indices; when a warmer day arrives, pop each cooler index and record the day-gap to it.
File: [coding_daily_temperatures.md](../../tiers/expert/coding_daily_temperatures.md)
</details>

<details><summary><b>Cars at given positions and speeds heading to a target on a single-lane road — count fleets arriving together</b></summary>

Pattern: Monotonic Stack &nbsp;|&nbsp; O(n log n)
Move: Sort cars by position and compute each one's arrival time; a car fleets with the one ahead if its time ≤ that fleet's time, so count strictly increasing times.
File: [coding_car_fleet.md](../../tiers/expert/coding_car_fleet.md)
</details>

<details><summary><b>Array of ints — sum the minimum element across every contiguous subarray (mod 1e9+7)</b></summary>

Pattern: Monotonic Stack &nbsp;|&nbsp; O(n)
Move: For each value find the previous- and next-lesser-element bounds via stacks; its contribution is value * leftCount * rightCount.
File: [coding_sum_of_subarray_minimums.md](../../tiers/expert/coding_sum_of_subarray_minimums.md)
</details>

---

[Back to Flashcard Index](../README.md) | [Expert Tier README](../../tiers/expert/README.md)
