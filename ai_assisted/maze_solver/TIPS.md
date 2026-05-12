# Tips: Maze Solver / Pathfinder

## Key Concepts to Know

- **BFS** — Finds shortest path in unweighted graphs. Explores level by level. O(V+E) time, O(V) space.
- **Dijkstra's Algorithm** — Shortest path with non-negative weights. Uses a min-heap priority queue. O((V+E) log V).
- **A\* Search** — Dijkstra + heuristic. Uses `f(n) = g(n) + h(n)` where `g` is actual cost and `h` is estimated cost to goal. Faster than Dijkstra with a good heuristic.
- **Manhattan Distance** — `|x1 - x2| + |y1 - y2|`. Admissible heuristic for 4-directional grids.
- **Sparse representation** — Only store non-empty cells when the grid is mostly empty.

## Common Mistakes

| Mistake | Why It's Wrong |
|---------|---------------|
| Using BFS on weighted terrain | BFS assumes uniform edge cost — won't find optimal weighted path |
| Using DFS for shortest path | DFS finds *a* path, not the *shortest* path |
| Not tracking visited cells | Infinite loops or exponential revisits |
| Revisiting cells with worse cost | In Dijkstra, a cell can be reached via multiple paths — keep the best |
| Allocating a full NxM array for sparse grids | Wastes memory when most cells are identical |

## How to Prompt the AI Effectively

1. **Start with BFS:** "Implement BFS pathfinding on a 2D grid with walls. Return the shortest path as coordinates."
2. **Upgrade to weighted:** "Now some cells cost 3 instead of 1. Convert to Dijkstra's algorithm using a min-heap."
3. **Add A\*:** "Optimize Dijkstra with A* using Manhattan distance as the heuristic."
4. **Test edge cases:** "What happens when start == goal? When the goal is completely surrounded by walls? When the grid is 1x1?"

## Algorithm Decision Tree

```
Is the grid unweighted?
├── Yes → BFS (simplest, optimal)
└── No
    ├── Do you know where the goal is?
    │   ├── Yes → A* with Manhattan heuristic
    │   └── No  → Dijkstra
    └── Does the grid change dynamically?
        ├── Yes → D* Lite / LPA*
        └── No  → A* or Dijkstra
```

## Complexity Comparison

| Algorithm | Time | Space | Optimal? |
|-----------|------|-------|----------|
| BFS | O(V+E) | O(V) | Yes (unweighted) |
| Dijkstra | O((V+E) log V) | O(V) | Yes (non-negative weights) |
| A* | O(E) best case | O(V) | Yes (with admissible heuristic) |
| DFS | O(V+E) | O(V) | No |

## What Interviewers Look For

- Correct algorithm selection based on the problem characteristics (weighted vs. unweighted).
- Clean implementation of BFS/Dijkstra with proper visited tracking.
- Understanding of heuristic design (why Manhattan distance is admissible for 4-directional grids).
- Ability to reason about scaling (sparse representations for large grids).
- Awareness of multi-agent and dynamic replanning as advanced extensions.
