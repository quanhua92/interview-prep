# Problem 04: Maze Solver / Pathfinder

**Role:** Software Engineer
**Duration:** 45-60 minutes
**Difficulty:** Medium
**Format:** Feature Build-Out

---

## Background

We're building a robot navigation system. The robot operates on a 2D grid where some cells are blocked (walls) and others are traversable. Your job is to implement the pathfinding engine that finds the shortest path from a start position to a goal.

The grid may contain **weighted terrain** — some cells cost more to traverse than others (e.g., rough terrain costs 3, smooth terrain costs 1).

## Functional Requirements

1. Parse a 2D grid from a string representation:
   - `#` = wall (impassable)
   - `.` = open terrain (cost 1)
   - `~` = rough terrain (cost 3)
   - `S` = start
   - `G` = goal
2. Find the **shortest path** from `S` to `G` considering terrain weights.
3. Return the path as a list of `(row, col)` coordinates from start to goal.
4. If no path exists, return an empty list.

## Non-Functional Requirements

- The solution should work for grids up to 1,000 x 1,000 efficiently.
- Memory usage should be proportional to the grid size, not exponential.
- The path should be optimal (lowest total cost).

## Constraints

- Grid is rectangular (same number of columns per row).
- Movement is allowed in 4 directions: up, down, left, right (no diagonals).
- The start and goal positions are always on open or weighted terrain (never a wall).

## Starter Interface

```python
class MazeSolver:
    def solve(self, grid: list[str]) -> list[tuple[int, int]]:
        """
        Find the shortest path from S to G in the grid.

        Args:
            grid: List of strings, e.g. ["S..#G", ".#~..", "..#.."]

        Returns:
            List of (row, col) coordinates from start to goal, empty if no path.
        """
        ...
```

Example grid:
```
S..#.
.#~..
..#G.
```

Optimal path (accounting for walls and terrain weights):
```
S → . → . → ~ → . → G     cost = 1+1+3+1+1 = 7
(0,0) (0,1) (0,2) (1,2) (1,3) (2,3)
```
Note: going through `~` (cost 3) is unavoidable here — the `#` walls block the cheaper routes.

---

## Follow-Up Questions

### Follow-Up 1: Algorithm Selection
> "You used BFS, which works for unweighted grids. Now with weighted terrain (`~` costs 3), BFS won't find the optimal path. What algorithm should you use instead?"

- Implement **Dijkstra's algorithm** (or A* with a suitable heuristic).
- What heuristic is admissible for this grid? (Manhattan distance)
- Compare time and space complexity: BFS O(V+E) vs. Dijkstra O((V+E) log V).

### Follow-Up 2: Scaling to Massive Grids
> "Now the grid is 1,000,000 x 1,000,000 but most of it is empty. How do you avoid allocating a full 2D array?"

- Represent the grid as a **sparse structure** (set/dict of walls and weighted cells only).
- How does this change your neighbor-generation logic?
- What's the new memory footprint?

### Follow-Up 3: Multiple Agents
> "We now have 3 robots in the same maze. They can't occupy the same cell simultaneously. How do you find collision-free paths?"

- Discuss **Conflict-Based Search (CBS)** or simple priority-based planning.
- Is finding optimal collision-free paths NP-hard? (Yes, in general.)
- Can you settle for a "good enough" solution?

### Follow-Up 4: Dynamic Obstacles
> "The maze changes over time — walls appear and disappear. How do you handle replanning?"

- **D\* Lite** or **LPA\*** algorithms for incremental replanning.
- How often should you replan? On every change, or only when the current path is blocked?
- Trade-off between plan quality and computation frequency.
