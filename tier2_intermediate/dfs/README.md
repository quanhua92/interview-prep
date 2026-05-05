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

## Common Pitfalls

- Forgetting to mark cells/nodes as **visited** before recursing (causes infinite loops).
- Not restoring state when backtracking in permutation/path problems.
- Exceeding Python's default recursion limit on very deep inputs (use `sys.setrecursionlimit` or an iterative stack).
