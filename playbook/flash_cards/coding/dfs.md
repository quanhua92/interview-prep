# DFS — Flashcards

10 cards. Drill: read the trigger, recall the pattern + move, then click to verify.

<details><summary><b>can you reach any index holding value 0, jumping by +/- arr[i]?</b></summary>

Pattern: DFS &nbsp;|&nbsp; Medium
Move: Mark visited by negating arr[i]; DFS the two jump targets within bounds.
File: [coding_jump_game_three.md](../../tiers/intermediate/coding_jump_game_three.md)
</details>

<details><summary><b>count islands of connected 1s in a 2D grid</b></summary>

Pattern: DFS &nbsp;|&nbsp; Medium
Move: Flood-fill (sink) each land cell discovered during a grid scan.
File: [coding_number_of_islands.md](../../tiers/intermediate/coding_number_of_islands.md)
</details>

<details><summary><b>parse "[123,[456,[789]]]" into a nested integer tree</b></summary>

Pattern: DFS &nbsp;|&nbsp; Medium
Move: Recursive-descent parser building NestedInteger nodes from the token stream.
File: [coding_mini_parser.md](../../tiers/intermediate/coding_mini_parser.md)
</details>

<details><summary><b>find the longest absolute file path in a "\t"-indented filesystem string</b></summary>

Pattern: DFS &nbsp;|&nbsp; Medium
Move: Track depth via tab count; stack maintains cumulative path length per level.
File: [coding_longest_absolute_file_path.md](../../tiers/intermediate/coding_longest_absolute_file_path.md)
</details>

<details><summary><b>delete a node with a given key from a BST</b></summary>

Pattern: DFS &nbsp;|&nbsp; Medium
Move: Replace with in-order successor (or predecessor), then rewire the subtree.
File: [coding_delete_node_in_a_bst.md](../../tiers/intermediate/coding_delete_node_in_a_bst.md)
</details>

<details><summary><b>find the most frequent subtree sum in a binary tree</b></summary>

Pattern: DFS &nbsp;|&nbsp; Medium
Move: Post-order sum each subtree, tally frequencies in a hashmap.
File: [coding_most_frequent_subtree_sum.md](../../tiers/intermediate/coding_most_frequent_subtree_sum.md)
</details>

<details><summary><b>add to each BST node the sum of all nodes with greater value</b></summary>

Pattern: DFS &nbsp;|&nbsp; Medium
Move: Reverse in-order traversal accumulating a running sum.
File: [coding_convert_bst_to_greater_tree.md](../../tiers/intermediate/coding_convert_bst_to_greater_tree.md)
</details>

<details><summary><b>longest set you can form by chaining index -> nums[index] starting anywhere</b></summary>

Pattern: DFS &nbsp;|&nbsp; Medium
Move: Walk the permutation, negating visited indices to mark cycle membership.
File: [coding_array_nesting.md](../../tiers/intermediate/coding_array_nesting.md)
</details>

<details><summary><b>is tree s an exact subtree (structure + values) of tree t?</b></summary>

Pattern: DFS &nbsp;|&nbsp; Easy
Move: Recurse: sameTree check at every node, else recurse into t's children.
File: [coding_subtree_of_another_tree.md](../../tiers/intermediate/coding_subtree_of_another_tree.md)
</details>

<details><summary><b>largest island area (4-connected 1s) in a grid</b></summary>

Pattern: DFS &nbsp;|&nbsp; Medium
Move: DFS each land cell, sink visited cells, accumulate and track max area.
File: [coding_max_area_island.md](../../tiers/intermediate/coding_max_area_island.md)
</details>

---

[Back to Flashcard Index](../README.md) | [Intermediate Tier README](../../tiers/intermediate/README.md)
