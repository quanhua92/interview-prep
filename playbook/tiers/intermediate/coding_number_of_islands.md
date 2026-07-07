# Number of Islands

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 200, Glassdoor
- **Flashcards**: [DFS deck](../../flash_cards/coding/dfs.md)

---

## Question Description

Given an $m \times n$ 2D binary grid `grid` which represents a map of `'1'`s (land) and `'0'`s (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

### Examples
*   **Input**: 
    ```text
    grid = [
      ["1","1","1","1","0"],
      ["1","1","0","1","0"],
      ["1","1","0","0","0"],
      ["0","0","0","0","0"]
    ]
    ```
    *   **Output**: `1`
*   **Input**:
    ```text
    grid = [
      ["1","1","0","0","0"],
      ["1","1","0","0","0"],
      ["0","0","1","0","0"],
      ["0","0","0","1","1"]
    ]
    ```
    *   **Output**: `3`

---

## Detailed Solution (C++)

The standard solution for finding connected components in a 2D matrix uses **Depth-First Search (DFS)**. 
We traverse the grid. When we encounter a `'1'`, we increment our island count and trigger a DFS traversal from that cell to find and "sink" (change `'1'` to `'0'`) all connected land cells. This avoids allocating extra $O(m \times n)$ auxiliary memory for a `visited` array.

### Standard C++ Production Code

```cpp
#include <vector>

class Solution {
private:
    void dfs(std::vector<std::vector<char>>& grid, int r, int c, int rows, int cols) noexcept {
        // Base Case: check bounds and if cell is water
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] != '1') {
            return;
        }

        // Sink the island in-place to save auxiliary space
        grid[r][c] = '0';

        // Explore all 4 orthogonal neighbors
        dfs(grid, r + 1, c, rows, cols);
        dfs(grid, r - 1, c, rows, cols);
        dfs(grid, r, c + 1, rows, cols);
        dfs(grid, r, c - 1, rows, cols);
    }

public:
    int numIslands(std::vector<std::vector<char>>& grid) noexcept {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }

        int rows = static_cast<int>(grid.size());
        int cols = static_cast<int>(grid[0].size());
        int island_count = 0;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == '1') {
                    ++island_count;
                    dfs(grid, r, c, rows, cols);
                }
            }
        }

        return island_count;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python DFS implementation. It mutates the grid in-place to optimize memory footprint.

```python
from typing import List

class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        """
        Calculates the number of islands in a 2D binary grid using DFS.
        
        Time Complexity: O(M * N)
        Space Complexity: O(M * N) in the worst case due to the recursion stack.
        """
        if not grid or not grid[0]:
            return 0

        rows = len(grid)
        cols = len(grid[0])
        island_count = 0

        def dfs(r: int, c: int) -> None:
            # Base Case: bounds check and water check
            if r < 0 or r >= rows or c < 0 or c >= cols or grid[r][c] != "1":
                return
            
            # Sink the land cell
            grid[r][c] = "0"
            
            # DFS search in all four directions
            dfs(r + 1, c)
            dfs(r - 1, c)
            dfs(r, c + 1)
            dfs(r, c - 1)

        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == "1":
                    island_count += 1
                    dfs(r, c)

        return island_count
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. In-place Mutation vs Functional Integrity
*   In LeetCode and competitive programming, mutating the input matrix in-place (e.g., changing `grid[r][c] = "0"`) is standard. 
*   However, in production environment APIs, mutating input arguments is considered a **bad practice** (side-effects make code harder to debug and test, and it violates functional programming standards).
*   If mutation is disallowed, we must use a `visited` structure:
    ```python
    visited = [[False] * cols for _ in range(rows)]
    ```
    This adds $\mathcal{O}(m \times n)$ auxiliary space.

### 2. Deep Recursion Limitations
*   With a maximum grid size of $300 \times 300 = 9 \times 10^4$ cells, a snake-like land grid can cause a recursion depth of up to $90,000$.
*   Since Python's standard recursion limit is $1000$, this will result in a `RecursionError`.
*   **Production Alternative**: Use an iterative DFS (with a Python `list` as a stack) or BFS (with `collections.deque`).

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(m \times n)$ | Every cell is visited at most a constant number of times (once in the outer loops, and at most once during DFS traversal). |
| **Space Complexity** | $\mathcal{O}(m \times n)$ | In the worst case (all land), the call stack depth is $\mathcal{O}(m \times n)$. If grid mutation is not allowed, a `visited` structure also takes $\mathcal{O}(m \times n)$ space. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if the grid is too large to fit into memory? (e.g. billions of rows/columns)
*   **The Problem**: A standard DFS/BFS requires loading the entire grid into RAM.
*   **The Solution**: Use a **Union-Find (Disjoint Set)** algorithm processing the grid **row-by-row**. 
    *   Maintain only the current row and the previous row in memory.
    *   For each cell in the current row, check its connection to its left neighbor and the neighbor directly above it (in the previous row).
    *   Union the sets and discard the row before the previous one. This reduces active memory requirements from $\mathcal{O}(m \times n)$ to $\mathcal{O}(n)$ (width of the grid).

### Q2: Compare DFS, BFS, and Union-Find (DSU) for this problem.
*   **DFS**: Easiest to write. Minimum code size. Recursive DFS has $\mathcal{O}(m \times n)$ call stack space overhead.
*   **BFS**: Avoids stack overflow (heap-allocated queue). Can find shortest paths if we needed to measure distance.
*   **Union-Find**: Excellent for streaming/incremental grids (where we add land cells dynamically and need to maintain the island count in real-time). DSU adds small union/find overhead (using path compression and rank optimization, complexity is almost linear: $\mathcal{O}(m \times n \cdot \alpha(m \times n))$ where $\alpha$ is the Inverse Ackermann function).

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention Cache Locality**: In C++, traversing row-by-row (row-major order) is much faster than column-by-column because of **spatial cache locality** (elements of the same row are adjacent in memory, so loading one brings the others into CPU L1/L2 caches). The DFS should visit orthogonal neighbors, but keeping nested loops row-major is crucial.
*   **Explicit Stack-Safe Iterative DFS**: Show how to implement DFS iteratively in a few lines to prove you write code resistant to stack overflow under heavy workloads.
    ```cpp
    // Conceptual Iterative DFS
    std::vector<std::pair<int, int>> stack;
    stack.push_back({r, c});
    grid[r][c] = '0';
    while(!stack.empty()) {
        auto [cr, cc] = stack.back();
        stack.pop_back();
        // check and push neighbors
    }
    ```
