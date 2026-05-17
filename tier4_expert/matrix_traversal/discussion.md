# Matrix Traversal — Discussion & Deep Dive

## One-Liner
Master matrix traversal patterns by recognizing two families: traversal-order problems (spiral, rotate, diagonal) and connectivity/spread problems (islands, flood fill, multi-source BFS).

## The Two Core Pattern Families

Matrix problems reduce to two fundamental approaches once you recognize the underlying structure:

### Family 1: Traversal Order Problems
- **Examples:** Spiral matrix, rotate 90 degrees, diagonal traversal
- **Technique:** Simulate movement using a direction array `[(0,1),(1,0),(0,-1),(-1,0)]` (right, down, left, up) and boundary conditions
- **Key insight:** Maintain current direction and rotate when boundary is hit

### Family 2: Connectivity / Spread Problems
- **Examples:** Number of islands, rotting oranges, flood fill, 0/1 matrix
- **Technique:** Model as a graph where cells are nodes and adjacent cells (4-directional or 8-directional) are edges
- **Key insight:** BFS for "spread" problems (shortest distance, simultaneous spread); DFS for "count connected components" problems

**Signal words:** "island," "connected," "flood," "rotting," "spread," "spiral," "diagonal," "distance to nearest 0."

## What Interviewers Evaluate

| Score | What They Expect |
|-------|-----------------|
| 6/10 | Can do BFS/DFS on a matrix with lots of boilerplate. Forgets bounds checking. Uses separate visited array when in-place marking would work. |
| 8/10 | Uses direction array idiom cleanly. Marks cells in-place during DFS (avoids extra O(m*n) space). Recognizes multi-source BFS for "rotting oranges" type problems. |
| 10/10 | Recognizes when BFS gives optimal distance (shortest path on unweighted grid) while DFS only gives any path. Applies multi-source BFS (enqueue all sources at once) for simultaneous spread. Solves spiral traversal cleanly with boundary shrinkage. Identifies 8-directional vs 4-directional connectivity. Knows space tradeoff: modifying input in-place vs separate visited array. |

## Matrix Problem Toolkit

### 1. Direction Array: The Universal Traversal Primitive
- `DIRS = [(0,1),(0,-1),(1,0),(-1,0)]` for 4-directional
- Add `(1,1),(1,-1),(-1,1),(-1,-1)` for 8-directional
- Pattern: `for dr, dc in DIRS: nr, nc = r+dr, c+dc; if valid(nr,nc): process`
- In-bounds check: `0 <= nr < rows and 0 <= nc < cols`
- Replaces 4 separate if-statements and scales to any grid dimension

### 2. DFS for Connected Components (Number of Islands)
- For each unvisited land cell: start DFS, mark all connected land cells as visited, increment island count
- In-place marking: modify grid with `'#'` or use visited set
- Time: O(m*n), each cell visited at most once
- In-place marking avoids O(m*n) extra space but modifies input
- Signal: "count components," "size of largest island," "connected regions"

### 3. Multi-Source BFS for Simultaneous Spread (Rotting Oranges)
- When multiple sources spread simultaneously, enqueue ALL sources at time=0
- BFS naturally propagates in waves: all cells at distance d processed before d+1
- Final answer: max BFS level reached
- If any fresh orange unreached: return -1 (impossible case)
- Time: O(m*n)
- Signal: "minimum time," "nearest distance," "simultaneous spread from multiple points"

### 4. Spiral Traversal: Boundary Shrinkage
- Maintain top, bottom, left, right boundaries
- Traverse: left->right (top row), top->bottom (right col), right->left (bottom row), bottom->top (left col)
- After each traversal, shrink the boundary (top++, right--, bottom--, left++)
- Stop when top > bottom or left > right
- Time: O(m*n), Space: O(m*n) for output

### 5. BFS for Shortest Distance (0/1 Matrix)
- Distance of each cell to nearest 0: initialize BFS queue with all 0-cells at distance 0
- BFS propagates distance: unvisited neighbors get distance+1
- Same as multi-source BFS but for distance propagation
- Alternative: DP (left-to-right pass, then right-to-left pass) also works for Manhattan distance without obstacles
- BFS handles obstacles naturally

## Problem → Approach Mapping

| Problem | Approach | Why | Complexity |
|---------|----------|-----|------------|
| Number of Islands | DFS from each unvisited land cell | Explore connected components; in-place marking avoids visited set | O(m*n) time, O(m*n) stack space |
| Rotting Oranges | Multi-source BFS from all rotten cells | Simultaneous spread; BFS gives minimum time naturally | O(m*n) time and space |
| 0/1 Matrix (distance to nearest 0) | Multi-source BFS from all 0 cells | Shortest distance; BFS gives optimal distance | O(m*n) time and space |
| Spiral Order | Boundary shrinkage simulation | Order problem, not connectivity; simulate direction changes | O(m*n) time, O(m*n) for output |
| Flood Fill (paint region) | DFS or BFS from source cell | Connectivity: change all connected cells of one color | O(m*n) time and space |
| Word Search (find word in grid) | DFS with visited marking (backtracking) | Explore all paths; backtrack on mismatch | O(m*n * 4^len(word)) worst case |
| Unique Paths (count paths) | DP (not DFS, exponential paths) | Overlapping subproblems; DFS revisits states | O(m*n) time and space |

## Common Mistakes

1. **DFS instead of BFS for minimum distance:** DFS finds A path, not the SHORTEST path. For "minimum time to rot all oranges" or "distance to nearest 0," you need BFS. DFS will give wrong answers for minimum distance problems.

2. **Single-source BFS when multi-source is needed:** Starting BFS from one rotten orange and then the next sequentially doesn't model simultaneous spreading. All sources must be enqueued at the start with time=0.

3. **Missing the freshCount check:** After BFS, if any fresh orange remains (isolated region with no path to any rotten orange), return -1. Without this check, you'd return a seemingly valid time for an impossible case.

4. **Off-by-one in spiral matrix:** The inner loops for bottom row and left column need guards (`if top <= bottom` and `if left <= right`) to avoid duplicating rows/columns when the matrix has odd dimensions or is a single row/column. Trace through a 1x5 matrix to verify.

5. **Recursion depth on large grids:** DFS on a 1000x1000 all-land grid has recursion depth 10^6, Python hits its default recursion limit (1000) immediately. Either use iterative DFS (explicit stack) or increase `sys.setrecursionlimit()`. Mention this in interviews.

## Interview Communication

Always state which approach before coding:

> "This is a connected components problem, I'll use DFS, marking visited cells in-place to avoid extra space."

> "This is a simultaneous spread problem, I need multi-source BFS, enqueuing all starting points at time=0."

The direction array idiom is a signal of fluency: instead of writing 4 if-statements, say "I'll use a direction array and iterate through the 4 neighbors." Write it at the top of your solution before the main logic.

For bounds checking, say it explicitly: "I check 0 <= nr < rows and 0 <= nc < cols before accessing the cell, this handles all boundary cases without separate conditions."

## Core Templates

### Number of Islands (DFS, in-place marking)

```python
def numIslands(grid: list[list[str]]) -> int:
    rows, cols = len(grid), len(grid[0])
    DIRS = [(0,1),(0,-1),(1,0),(-1,0)]
    count = 0

    def dfs(r, c):
        if r < 0 or r >= rows or c < 0 or c >= cols or grid[r][c] != '1':
            return
        grid[r][c] = '#'   # mark visited in-place
        for dr, dc in DIRS:
            dfs(r+dr, c+dc)

    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == '1':
                count += 1
                dfs(r, c)
    return count
# O(m*n) time, O(m*n) space for recursion stack (worst case: all land)
```

### Rotting Oranges (multi-source BFS)

```python
from collections import deque

def orangesRotting(grid: list[list[int]]) -> int:
    rows, cols = len(grid), len(grid[0])
    DIRS = [(0,1),(0,-1),(1,0),(-1,0)]
    q = deque()
    fresh = 0
    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == 2: q.append((r, c, 0))
            elif grid[r][c] == 1: fresh += 1

    time = 0
    while q:
        r, c, t = q.popleft()
        for dr, dc in DIRS:
            nr, nc = r+dr, c+dc
            if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] == 1:
                grid[nr][nc] = 2
                fresh -= 1
                time = max(time, t+1)
                q.append((nr, nc, t+1))
    return time if fresh == 0 else -1
```

### Spiral Matrix

```python
def spiralOrder(matrix: list[list[int]]) -> list[int]:
    result = []
    top, bottom, left, right = 0, len(matrix)-1, 0, len(matrix[0])-1
    while top <= bottom and left <= right:
        for c in range(left, right+1):   result.append(matrix[top][c])
        top += 1
        for r in range(top, bottom+1):   result.append(matrix[r][right])
        right -= 1
        if top <= bottom:
            for c in range(right, left-1, -1): result.append(matrix[bottom][c])
            bottom -= 1
        if left <= right:
            for r in range(bottom, top-1, -1): result.append(matrix[r][left])
            left += 1
    return result
# O(m*n) time, O(m*n) space for output
```

Source: [Matrix Patterns: Spiral Traversal, Island Problems & Multi-Source BFS (CalibreOS)](https://www.calibreos.com/learn/dsa-matrix-patterns)
