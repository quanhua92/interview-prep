# BFS — Flashcards

7 cards. Drill: read the trigger, recall the pattern + move, then click to verify.

<details><summary><b>Binary tree root — return its nodes level by level, left to right (list of lists)</b></summary>

Pattern: BFS &nbsp;|&nbsp; O(n)
Move: Queue with per-level sizing — record the queue length, dequeue exactly that many to build one sub-array, enqueue their children, repeat.
File: [coding_level_order.md](../../tiers/foundation/coding_level_order.md)
</details>

<details><summary><b>n x n binary grid — length of the shortest clear path from (0,0) to (n-1,n-1) moving in 8 directions</b></summary>

Pattern: BFS &nbsp;|&nbsp; O(n^2)
Move: 8-directional BFS from the start; mark cells in-place on visit and expand level by level; the level when the target is dequeued is the answer.
File: [coding_shortest_path_binary.md](../../tiers/foundation/coding_shortest_path_binary.md)
</details>

<details><summary><b>Binary search tree — serialize to a string and reconstruct the BST from it</b></summary>

Pattern: BFS &nbsp;|&nbsp; O(n)
Move: Stream a level-order (or pre-order) binary sequence; on deserialize, rebuild respecting BST bounds (or split by min/max ranges at each node).
File: [coding_serialize_and_deserialize_bst.md](../../tiers/foundation/coding_serialize_and_deserialize_bst.md)
</details>

<details><summary><b>A 2D grid with a single connected landmass of 1s surrounded by water — compute its perimeter</b></summary>

Pattern: BFS &nbsp;|&nbsp; O(rows * cols)
Move: For each land cell, add 4 and subtract 1 for each shared land neighbor (or sum 1 per water/out-of-bounds edge); dedupe shared boundaries.
File: [coding_island_perimeter.md](../../tiers/foundation/coding_island_perimeter.md)
</details>

<details><summary><b>Binary tree — find the leftmost value in its last (bottom) row</b></summary>

Pattern: BFS &nbsp;|&nbsp; O(n)
Move: Level-order traversal enqueuing children right-to-left; the last node dequeued is the bottom-left value (queue state preservation).
File: [coding_find_bottom_left_tree_value.md](../../tiers/foundation/coding_find_bottom_left_tree_value.md)
</details>

<details><summary><b>Binary tree — return the largest value in each row (level)</b></summary>

Pattern: BFS &nbsp;|&nbsp; O(n)
Move: Level-order BFS; at each level boundary track the row's running maximum and append it to the result list.
File: [coding_find_largest_value_in_each_tree_row.md](../../tiers/foundation/coding_find_largest_value_in_each_tree_row.md)
</details>

<details><summary><b>A grid of fresh and rotten oranges — every minute, rotten oranges rot 4-directional neighbors; min time until all rotten (or -1)</b></summary>

Pattern: BFS &nbsp;|&nbsp; O(rows * cols)
Move: Multi-source BFS — seed the queue with all initially rotten oranges, count fresh ones; expand level by level, decrementing the fresh count each infection; -1 if any fresh remains.
File: [coding_rotting_oranges.md](../../tiers/foundation/coding_rotting_oranges.md)
</details>

---

[Back to Flashcard Index](../README.md) | [Foundation Tier README](../../tiers/foundation/README.md)
