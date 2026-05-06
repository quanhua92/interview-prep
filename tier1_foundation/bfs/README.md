# BFS (Breadth-First Search)

## Core Idea

Explore a graph or tree level by level using a queue (FIFO). Start from a
source node, visit all its neighbors, then all neighbors of neighbors, and
so on. BFS guarantees that the first time we reach a node, we have found
the shortest path to it (in an unweighted graph).

## When to Recognize

Look for these keywords in the problem statement:

- "Shortest path" (in an unweighted graph or grid)
- "Level-order traversal"
- "Minimum steps", "minimum moves"
- "Neighbors", "adjacent cells", "connected components"
- Grid problems: "rotting oranges", "island count", "walls and gates"
- Word ladder, gene mutation, and other transformation problems

## Complexity

| Variant | Time | Space |
|---------|------|-------|
| Tree level-order traversal | O(V) | O(W) |
| Graph shortest path (unweighted) | O(V + E) | O(V + E) |
| Grid BFS (multi-source) | O(R * C) | O(R * C) |

Where V = vertices, E = edges, W = max width of the tree.

## Key Insight

BFS uses a queue to ensure FIFO ordering: nodes closer to the source are
dequeued before nodes farther away. This guarantees the shortest path in
unweighted graphs. For grid problems, multi-source BFS (initializing the
queue with all starting positions) is a common optimization.

## Problems in This Pattern

| Problem | Difficulty | Variant |
|---------|-----------|---------|
| P102 Binary Tree Level Order Traversal | Medium | Tree level-order traversal |
| P994 Rotting Oranges | Medium | Grid BFS (multi-source) |
| P1091 Shortest Path in Binary Matrix | Medium | Grid BFS, 8-directional, single-source shortest path |
| P463 Island Perimeter | Easy | Count cell edges on grid |
| P513 Find Bottom Left Tree Value | Medium | BFS level order, first of last row |
| P515 Find Largest Value in Each Tree Row | Medium | BFS level order, max per level |

## Template Variants

1. **Tree level-order traversal** -- process nodes level by level
2. **Graph shortest path** -- BFS with visited set and parent tracking
3. **Grid BFS** -- multi-source BFS on a 2D grid (rotting oranges pattern)

See `template.py` for annotated skeleton code for each variant.
