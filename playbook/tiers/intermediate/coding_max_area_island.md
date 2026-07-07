# Max Area of Island

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 695, Glassdoor
- **Flashcards**: [DFS deck](../../flash_cards/coding/dfs.md)

---

## Question Description

You are given an $m \times n$ binary matrix `grid`. An island is a group of `1`s (representing land) connected **4-directionally** (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.

The **area** of an island is the number of cells with a value `1` in the island.

Return the **maximum area** of an island in `grid`. If there is no island, return `0`.

### Examples
*   **Input**: 
    ```text
    grid = [
      [0,0,1,0,0,0,0,1,0,0,0,0,0],
      [0,0,0,0,0,0,0,1,1,1,0,0,0],
      [0,1,1,0,1,0,0,0,0,0,0,0,0],
      [0,1,0,0,1,1,0,0,1,0,1,0,0],
      [0,1,0,0,1,1,0,0,1,1,1,0,0],
      [0,0,0,0,0,0,0,0,0,0,1,0,0],
      [0,0,0,0,0,0,0,1,1,1,0,0,0],
      [0,0,0,0,0,0,0,1,1,0,0,0,0]
    ]
    ```
    *   **Output**: `6`
    *   **Explanation**: The answer is the area of the highlighted island of size 6 in the bottom-middle.
*   **Input**: `grid = [[0,0,0,0,0,0,0,0]]`
    *   **Output**: `0`

---

## Detailed Solution (C++)

Using **Depth-First Search (DFS)**, we traverse the matrix. When we encounter a `'1'`, we compute the area of its island by recursively exploring all connected land cells. We "sink" each visited cell by resetting it to `0` to prevent infinite loops and ensure each island cell is counted exactly once.

### Standard C++ Production Code

```cpp
#include <vector>
#include <algorithm>

class Solution {
private:
    int dfs(std::vector<std::vector<int>>& grid, int r, int c, int rows, int cols) noexcept {
        // Base Case: check boundaries and if cell is water
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] != 1) {
            return 0;
        }

        // Sink the island cell
        grid[r][c] = 0;

        // Sum the current cell + areas of all 4 neighbors
        return 1 + dfs(grid, r + 1, c, rows, cols)
                 + dfs(grid, r - 1, c, rows, cols)
                 + dfs(grid, r, c + 1, rows, cols)
                 + dfs(grid, r, c - 1, rows, cols);
    }

public:
    int maxAreaOfIsland(std::vector<std::vector<int>>& grid) noexcept {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }

        int rows = static_cast<int>(grid.size());
        int cols = static_cast<int>(grid[0].size());
        int max_area = 0;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 1) {
                    max_area = std::max(max_area, dfs(grid, r, c, rows, cols));
                }
            }
        }

        return max_area;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the recursive Python implementation. We use a nested function to access `rows` and `cols` without passing them explicitly.

```python
from typing import List

class Solution:
    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        """
        Computes the maximum island area in a 2D binary grid.
        
        Time Complexity: O(M * N)
        Space Complexity: O(M * N) stack space in the worst case.
        """
        if not grid or not grid[0]:
            return 0

        rows = len(grid)
        cols = len(grid[0])
        max_area = 0

        def dfs(r: int, c: int) -> int:
            # Base Case: check boundaries and if cell is water
            if r < 0 or r >= rows or c < 0 or c >= cols or grid[r][c] != 1:
                return 0
            
            # Sink the land cell
            grid[r][c] = 0
            
            # Recursively sum current cell and 4 directions
            return (
                1
                + dfs(r + 1, c)
                + dfs(r - 1, c)
                + dfs(r, c + 1)
                + dfs(r, c - 1)
            )

        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 1:
                    max_area = max(max_area, dfs(r, c))

        return max_area
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Recursion Stack Limits
*   For a $50 \times 50$ grid, the maximum possible area is $2500$ cells.
*   In the worst case (a snake-like island filling the entire grid), recursive DFS will make $2500$ nested calls.
*   Python's default call stack limit is $1000$. A deep DFS will trigger a `RecursionError`.
*   **Workaround**: Increase the system limit using `sys.setrecursionlimit(3000)`, or rewrite the traversal iteratively using a queue (BFS) or stack (DFS).

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(m \times n)$ | We visit every cell in the grid a constant number of times. |
| **Space Complexity** | $\mathcal{O}(m \times n)$ | In the worst case (entire grid is land), the call stack depth is $\mathcal{O}(m \times n)$. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if we are not allowed to mutate the input grid?
*   **Answer**: If grid mutation is prohibited, we must maintain a separate `visited` grid of size $m \times n$.
    *   In C++, `std::vector<std::vector<char>> visited(rows, std::vector<char>(cols, 0))` or a flattened `std::vector<char> visited(rows * cols, 0)` is highly efficient.

### Q2: How does BFS compare to DFS in terms of memory overhead?
*   **DFS (Recursive)**: Memory is allocated on the thread's call stack. In the worst case, the stack depth is $\mathcal{O}(m \times n)$.
*   **BFS (Queue-based)**: Memory is allocated on the heap (for the queue). The maximum queue size is bounded by the perimeter/width of the largest island, which is generally much smaller than $\mathcal{O}(m \times n)$ for compact islands but can still reach $\mathcal{O}(m \times n)$ for comb-like patterns. BFS is stack-safe.

---

## Pro-Tip: How to Impress the Interviewer

*   **Flattening a 2D Matrix**: When storing visited states or writing BFS, mention that representing coordinates as a single index `r * cols + c` (flattening) instead of pairs `(r, c)` saves space and reduces heap allocations. In C++, popping and pushing standard structures like `std::pair` or custom classes creates minor overhead compared to single integers.
*   **Spatial Locality in 2D Scans**: Always search the grid in a row-major nested loop (outer loop `r`, inner loop `c`). This ensures that the CPU cache lines prefetch sequential grid elements, which significantly accelerates execution compared to column-major scans.
