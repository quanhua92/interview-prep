# Shortest Path in Binary Matrix

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 1091, Glassdoor

---

## Question Description

Given an $n \times n$ binary matrix `grid`, return the length of the shortest clear path in the matrix. If there is no clear path, return `-1`.

A **clear path** in a binary matrix is a path from the top-left cell (i.e., `(0, 0)`) to the bottom-right cell (i.e., `(n - 1, n - 1)`) such that:
*   All the visited cells of the path are `0` (walkable).
*   All the adjacent cells of the path are **8-directionally** connected (i.e., they share an edge or a corner).
*   The length of a clear path is the number of visited cells of this path.

### Examples
*   **Input**: `grid = [[0,1],[1,0]]`
    *   **Output**: `2`
*   **Input**: `grid = [[0,0,0],[1,1,0],[1,1,0]]`
    *   **Output**: `4`
*   **Input**: `grid = [[1,0,0],[1,1,0],[1,1,0]]`
    *   **Output**: `-1`

---

## Detailed Solution (C++)

The problem asks for the shortest path in an unweighted grid with 8-directional movement. The optimal algorithm for finding the shortest path in an unweighted graph is **Breadth-First Search (BFS)**. 

To avoid the memory and time overhead of maintaining a separate `visited` matrix, we can mark cells as visited **in-place** by overwriting `grid[r][c] = 1`.

### Standard C++ Production Code

```cpp
#include <vector>
#include <queue>
#include <tuple>
#include <cstddef>

class Solution {
public:
    int shortestPathBinaryMatrix(std::vector<std::vector<int>>& grid) {
        // Edge Case: Handle empty grid
        if (grid.empty() || grid[0].empty()) {
            return -1;
        }

        int n = static_cast<int>(grid.size());
        
        // Edge Case: If start or end cell is blocked
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) {
            return -1;
        }
        
        // Edge Case: 1x1 matrix
        if (n == 1) {
            return 1;
        }

        // Queue storing: {row, col, distance}
        std::queue<std::tuple<int, int, int>> q;
        q.push({0, 0, 1});
        grid[0][0] = 1; // Mark start as visited in-place

        // 8-directional arrays
        const int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        const int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

        while (!q.empty()) {
            auto [r, c, dist] = q.front();
            q.pop();

            for (int d = 0; d < 8; ++d) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                // Boundary and validity check
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 0) {
                    // Check if we reached the bottom-right corner
                    if (nr == n - 1 && nc == n - 1) {
                        return dist + 1;
                    }
                    
                    // Mark visited immediately when pushing to prevent redundant queue entries
                    grid[nr][nc] = 1;
                    q.push({nr, nc, dist + 1});
                }
            }
        }

        return -1;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation using `collections.deque` for the BFS queue.

```python
from typing import List
from collections import deque

class Solution:
    def shortestPathBinaryMatrix(self, grid: List[List[int]]) -> int:
        """
        Finds the shortest clear path in an N x N binary matrix.
        Uses BFS for shortest path in an unweighted grid with 8-directional movements.
        
        Time Complexity: O(N^2)
        Space Complexity: O(N^2) (or O(1) auxiliary if in-place modification is permitted)
        """
        if not grid or not grid[0]:
            return -1

        n = len(grid)
        
        # Edge Case: Start or destination cell is blocked
        if grid[0][0] == 1 or grid[n - 1][n - 1] == 1:
            return -1
            
        # Edge Case: 1x1 grid
        if n == 1:
            return 1

        # 8-directional offsets
        directions = [
            (-1, -1), (-1, 0), (-1, 1),
            (0, -1),           (0, 1),
            (1, -1),  (1, 0),  (1, 1)
        ]

        # Queue stores: (row, col, distance)
        queue = deque([(0, 0, 1)])
        grid[0][0] = 1  # Mark as visited in-place

        while queue:
            r, c, dist = queue.popleft()

            for dr, dc in directions:
                nr, nc = r + dr, c + dc

                if 0 <= nr < n and 0 <= nc < n and grid[nr][nc] == 0:
                    if nr == n - 1 and nc == n - 1:
                        return dist + 1
                    
                    # Mark visited immediately before pushing to queue
                    grid[nr][nc] = 1
                    queue.append((nr, nc, dist + 1))

        return -1
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. BFS Queue Performance Gotcha
*   Do not use Python's built-in `queue.Queue` from the standard library for coding interviews. `queue.Queue` is designed for multi-threaded systems and uses locking primitives (`threading.Lock`), which adds significant CPU thread overhead. 
*   Always use `collections.deque` for single-threaded queue needs.

### 2. Mutating Inputs vs. Functional Purity
*   Overwriting `grid[r][c] = 1` avoids the $\mathcal{O}(n^2)$ space cost of a separate `visited` set or matrix.
*   However, in production environments, mutating input arguments is often considered a side-effect that can lead to concurrency bugs (e.g., if other threads are reading the grid). If input mutation is not allowed, instantiate a `visited` matrix/set at the cost of $\mathcal{O}(n^2)$ space:
    ```python
    visited = [[False] * n for _ in range(n)]
    ```

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n^2)$ | In the worst-case, we check all $n \times n$ cells of the grid. |
| **Space Complexity** | $\mathcal{O}(n^2)$ | The queue size can grow up to $\mathcal{O}(n^2)$ elements in worst-case scenarios. Auxiliary space is $\mathcal{O}(1)$ since we modify the grid in-place. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if the grid is extremely large (e.g., $10^5 \times 10^5$) and cannot fit in memory?
*   **The Problem**: A standard BFS will run out of memory because the size of the BFS queue (frontier) grows linearly with the perimeter of the search wavefront.
*   **The Solution**: Use **A\* search** with a heuristic function like **Chebyshev distance** (since 8-directional movement is permitted). 
    $$\text{Chebyshev}(A, B) = \max(|x_1 - x_2|, |y_1 - y_2|)$$
    A\* will prune the search space by steering the search towards the target. If memory is still a constraint, **IDA\* (Iterative Deepening A\*)** or **Bidirectional BFS** can be used.

### Q2: Why must we mark cells as visited *when pushing* rather than *when popping*?
*   **The Core Bug**: If we only mark cells as visited when they are popped, multiple nodes in the current BFS layer can look at the same neighbor and push it into the queue. This leads to duplicate processing, exponential queue growth, and results in Time/Memory Limit Exceeded errors.
*   **Correction**: Always mark the cell visited *immediately* before or during queue pushing.

### Q3: How does Bidirectional BFS optimize search time?
*   **The Concept**: Run two simultaneous BFS traversals—one starting at the source node, and the other starting at the target node. We alternate expanding layers between both queues.
*   **Benefit**: If the shortest path is of length $d$, a single BFS search tree expands to $O(b^d)$ nodes (where $b$ is the average branching factor). Bidirectional BFS will meet in the middle, expanding only $O(b^{d/2} + b^{d/2}) = O(b^{d/2})$ nodes. This yields an exponential reduction in state space exploration.

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention CPU Branch Predictor and 8-Direction Iteration**: In C++, iterate through directions using static arrays (`dr` and `dc`) rather than conditional `if` statements. This reduces branching and lets the compiler optimize the loop using vectorization (SIMD) or loop unrolling.
*   **Chebyshev vs. Manhattan Distance**: Point out that since diagonal moves are allowed, the appropriate heuristic is Chebyshev distance. If diagonal moves were forbidden, Manhattan distance ($|x_1 - x_2| + |y_1 - y_2|$) would be correct. Showing this theoretical understanding proves your pathfinding expertise.
