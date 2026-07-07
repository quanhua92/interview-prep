# Island Perimeter

- **Category**: Coding
- **Difficulty**: Easy
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 463, Glassdoor
- **Flashcards**: [BFS deck](../../flash_cards/coding/bfs.md)

---

## Question Description

You are given `row x col` `grid` representing a map where `grid[i][j] = 1` represents land and `grid[i][j] = 0` represents water.

Grid cells are connected horizontally/vertically (not diagonally). The grid is completely surrounded by water, and there is exactly one island (i.e., one or more connected land cells).

The island doesn't have "lakes", meaning the water inside isn't connected to the water around the island. One cell is a square with side length 1. The grid is rectangular, width and height don't exceed 100. Determine the perimeter of the island.

### Examples
*   **Input**: `grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]`
    *   **Output**: `16`
*   **Input**: `grid = [[1]]`
    *   **Output**: `4`
*   **Input**: `grid = [[1,0]]`
    *   **Output**: `4`

---

## Detailed Solution (C++)

There are two primary ways to solve this problem:
1.  **Graph Traversal (BFS/DFS)**: Locate the single island, perform a traversal, and sum the outer edges (boundaries with water or grid edges).
2.  **Mathematical Deduction ($\mathcal{O}(1)$ Space)**: Iterate through the grid. Every land cell initially contributes `4` to the perimeter. If it has a neighbor directly to its right or bottom that is also land, they share an edge, so we subtract `2` from the total perimeter (1 contribution for each cell).

### Standard C++ Production Code

```cpp
#include <vector>
#include <queue>
#include <utility>

class Solution {
public:
    // BFS Solution: O(R * C) Time and O(R * C) Space
    int islandPerimeterBFS(std::vector<std::vector<int>>& grid) {
        int rows = static_cast<int>(grid.size());
        int cols = static_cast<int>(grid[0].size());
        std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
        int perimeter = 0;

        const int dr[] = {0, 0, 1, -1};
        const int dc[] = {1, -1, 0, 0};

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 1) {
                    std::queue<std::pair<int, int>> q;
                    q.push({r, c});
                    visited[r][c] = true;

                    while (!q.empty()) {
                        auto [cr, cc] = q.front();
                        q.pop();

                        for (int d = 0; d < 4; ++d) {
                            int nr = cr + dr[d];
                            int nc = cc + dc[d];

                            // If neighbor is out of bounds or water, it's a boundary edge
                            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || grid[nr][nc] == 0) {
                                perimeter++;
                            } else if (!visited[nr][nc]) {
                                visited[nr][nc] = true;
                                q.push({nr, nc});
                            }
                        }
                    }
                    return perimeter; // Since there is exactly one island, we are done
                }
            }
        }
        return 0;
    }

    // Mathematical Deduction: O(R * C) Time and O(1) Space
    int islandPerimeter(const std::vector<std::vector<int>>& grid) {
        int rows = static_cast<int>(grid.size());
        int cols = static_cast<int>(grid[0].size());
        int perimeter = 0;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 1) {
                    perimeter += 4;
                    // If right neighbor is land, subtract 2 (shared boundary)
                    if (c + 1 < cols && grid[r][c + 1] == 1) {
                        perimeter -= 2;
                    }
                    // If bottom neighbor is land, subtract 2 (shared boundary)
                    if (r + 1 < rows && grid[r + 1][c] == 1) {
                        perimeter -= 2;
                    }
                }
            }
        }
        return perimeter;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below are the two approaches implemented in Python.

```python
from typing import List
from collections import deque

class Solution:
    def islandPerimeterBFS(self, grid: List[List[int]]) -> int:
        """
        Calculates the perimeter of the island using BFS.
        
        Time Complexity: O(R * C)
        Space Complexity: O(R * C)
        """
        rows, cols = len(grid), len(grid[0])
        visited = set()
        perimeter = 0
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]

        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 1:
                    queue = deque([(r, c)])
                    visited.add((r, c))

                    while queue:
                        cr, cc = queue.popleft()
                        for dr, dc in directions:
                            nr, nc = cr + dr, cc + dc
                            if nr < 0 or nr >= rows or nc < 0 or nc >= cols or grid[nr][nc] == 0:
                                perimeter += 1
                            elif (nr, nc) not in visited:
                                visited.add((nr, nc))
                                queue.append((nr, nc))
                    return perimeter
        return 0

    def islandPerimeter(self, grid: List[List[int]]) -> int:
        """
        Calculates the perimeter using O(1) space deduction.
        
        Time Complexity: O(R * C)
        Space Complexity: O(1)
        """
        perimeter = 0
        rows, cols = len(grid), len(grid[0])

        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 1:
                    perimeter += 4
                    # If right neighbor is land, subtract 2 (for the shared edge)
                    if c + 1 < cols and grid[r][c + 1] == 1:
                        perimeter -= 2
                    # If bottom neighbor is land, subtract 2 (for the shared edge)
                    if r + 1 < rows and grid[r + 1][c] == 1:
                        perimeter -= 2
        return perimeter
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Set Lookup vs. In-place Mutation
*   In the BFS approach, we tracked visited cells using a set (`visited`). While set operations (`in`, `add`) are average-case $\mathcal{O}(1)$, hash collisions can degrade this, and storing tuples `(r, c)` in a set incurs high object allocation overhead in Python.
*   To achieve the absolute fastest execution speed, perform in-place mutation (e.g., mark visited cells as `2`) and restore them back to `1` afterward if the grid needs to remain uncorrupted.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(rows \times cols)$ | We scan all cells in the grid. For the mathematical approach, we do a single sweep. |
| **Space Complexity** | $\mathcal{O}(1)$ | For the mathematical deduction approach, only primitive loop counter variables are used. For BFS, it requires $\mathcal{O}(rows \times cols)$ space for the queue and visited tracking. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if there are multiple disconnected islands, and we want the perimeter of all of them?
*   **The Answer**: The mathematical deduction approach is completely local; it does not assume connectivity. It naturally works for any number of disconnected islands, return the exact sum of all island perimeters in $\mathcal{O}(1)$ auxiliary space.

### Q2: What if the land cells are represented as a list of coordinates (sparse grid) rather than a 2D matrix?
*   **The Solution**: Storing a giant matrix is memory-inefficient for sparse islands. If we have a list of coordinate pairs:
    1.  Insert all coordinates into a hash set for $\mathcal{O}(1)$ lookup.
    2.  For each coordinate $(r, c)$, check its 4 orthogonal neighbors.
    3.  If a neighbor is NOT in the hash set, increment the perimeter count by 1.
*   **Python Snippet**:
    ```python
    land_set = set(coordinates)
    perimeter = 0
    for r, c in land_set:
        for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            if (r + dr, c + dc) not in land_set:
                perimeter += 1
    ```
*   **Complexity**: $\mathcal{O}(L)$ time and $\mathcal{O}(L)$ space, where $L$ is the number of land cells. This is highly optimal for sparse grids where $L \ll rows \times cols$.

---

## Pro-Tip: How to Impress the Interviewer

*   **Highlight the Cache-Friendliness of Row-Major Scans**: In the mathematical deduction approach, the grid is processed in row-major order (`grid[r][c]`). In C++, this aligns perfectly with how 2D arrays are stored contiguously in memory. Scanning row-by-row ensures maximum L1 cache hit rate because adjacent values are pre-fetched by the CPU cache controller. Scanning column-major instead would result in L1 cache misses.
*   **Prevent Double Counting**: Clearly explain the logic behind subtracting `2` for each shared edge: a shared edge between cell $A$ and cell $B$ reduces the perimeter of cell $A$ by 1, and the perimeter of cell $B$ by 1. Checking only right and bottom neighbors guarantees that every shared edge is visited exactly once, avoiding duplicate substractions.
