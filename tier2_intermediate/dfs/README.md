# DFS (Depth-First Search)

## Core Idea

Explore as deep as possible along each branch before backtracking. DFS uses
recursion (or an explicit stack) to visit nodes, diving to the deepest level
of the current path before returning to explore alternatives.

## When to Recognize

Look for keywords and problem structures such as:

- "all paths" / "find every path" / "return all possible ..."
- "connected components" / "number of islands"
- "permutations" / "combinations"
- Tree traversal (pre-order, in-order, post-order)
- Any problem that requires visiting every node of a graph/tree exactly once

## Complexity

| Metric | Value |
|--------|-------|
| Time   | O(V + E) where V = vertices, E = edges |
| Space  | O(V) for the recursion stack (worst case for a linear graph) |

## Key Variants

1. **Tree DFS** — pre-order, in-order, post-order traversal
2. **Island / connected components DFS** — flood-fill on a grid
3. **Path-finding DFS** — enumerate all paths from source to target

## Practice Problems

| # | Problem | Difficulty |
|---|---------|------------|
| 200 | [Number of Islands](./p200_number_of_islands.py) | Medium |
| 695 | [Max Area of Island](./p695_max_area_island.py) | Medium |
| 1306 | [Jump Game III](./p1306_jump_game_three.py) | Medium |
| 385 | [Mini Parser](./solutions/p385_mini_parser.py) | Medium |
| 388 | [Longest Absolute File Path](./solutions/p388_longest_absolute_file_path.py) | Medium |
| 508 | [Most Frequent Subtree Sum](./solutions/p508_most_frequent_subtree_sum.py) | Medium |
| 538 | [Convert BST to Greater Tree](./solutions/p538_convert_bst_to_greater_tree.py) | Medium |
| 565 | [Array Nesting](./solutions/p565_array_nesting.py) | Medium |
| 572 | [Subtree of Another Tree](./solutions/p572_subtree_of_another_tree.py) | Easy |
| 450 | [Delete Node in a BST](./solutions/p450_delete_node_in_a_bst.py) | Medium |

## Common Pitfalls

- Forgetting to mark cells/nodes as **visited** before recursing (causes infinite loops).
- Not restoring state when backtracking in permutation/path problems.
- Exceeding Python's default recursion limit on very deep inputs (use `sys.setrecursionlimit` or an iterative stack).
