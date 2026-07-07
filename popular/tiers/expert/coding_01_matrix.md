# 01 Matrix

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 542, Glassdoor

---

## Question Description

Given an $m \times n$ binary matrix `mat`, return the distance of the nearest `0` for each cell.

The distance between two cells sharing a common edge is `1`.

### Examples
*   **Input**: `mat = [[0,0,0],[0,1,0],[0,0,0]]`
    *   **Output**: `[[0,0,0],[0,1,0],[0,0,0]]`
*   **Input**: `mat = [[0,0,0],[0,1,0],[1,1,1]]`
    *   **Output**: `[[0,0,0],[0,1,0],[1,2,1]]`

---

## Detailed Solution (C++)

There are two optimal ways to solve this problem:

### Method 1: Multi-Source Breadth-First Search (BFS)
Instead of running a standard BFS from each `1` (which would take $\mathcal{O}((m \cdot n)^2)$ time), we run a single BFS starting from **all** `0`s simultaneously.
1.  Initialize a `dist` matrix of the same size with $-1$ (unvisited).
2.  Enqueue all coordinates of cells containing `0` and set their distance to `0`.
3.  Pop coordinates from the queue. For each popped cell, check its 4-directional neighbors.
4.  If a neighbor is unvisited (distance is $-1$), update its distance to `current_distance + 1` and push it to the queue.
5.  This traverses the matrix in concentric levels starting from the `0`s, guaranteeing the shortest path is found in linear time.

### Method 2: Two-Pass Dynamic Programming (Optimal $\mathcal{O}(1)$ Space)
A cell's shortest distance to a `0` is determined by its neighbors:
$$\text{dist}[r][c] = 1 + \min(\text{dist}[r-1][c], \text{dist}[r+1][c], \text{dist}[r][c-1], \text{dist}[r][c+1])$$
Since we cannot evaluate all four neighbors in a single traversal, we split the process into two passes:
1.  **First Pass (Top-Left to Bottom-Right)**: Compute the distance using only top and left neighbors.
    $$\text{dist}[r][c] = \min(\text{dist}[r][c], \min(\text{dist}[r-1][c], \text{dist}[r][c-1]) + 1)$$
2.  **Second Pass (Bottom-Right to Top-Left)**: Compute the distance using only bottom and right neighbors.
    $$\text{dist}[r][c] = \min(\text{dist}[r][c], \min(\text{dist}[r+1][c], \text{dist}[r][c+1]) + 1)$$

This method eliminates the queue allocation and runs in-place, achieving $\mathcal{O}(1)$ auxiliary space.

### Standard C++ Production Code

```cpp
#include <vector>
#include <queue>
#include <algorithm>

class Solution {
public:
    // Method 1: Multi-source BFS
    std::vector<std::vector<int>> updateMatrixBFS(const std::vector<std::vector<int>>& mat) {
        if (mat.empty() || mat[0].empty()) return {};
        
        int m = static_cast<int>(mat.size());
        int n = static_cast<int>(mat[0].size());
        std::vector<std::vector<int>> dist(m, std::vector<int>(n, -1));
        std::queue<std::pair<int, int>> q;

        // Enqueue all 0 sources
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (mat[r][c] == 0) {
                    dist[r][c] = 0;
                    q.push({r, c});
                }
            }
        }

        const int dr[] = {-1, 1, 0, 0};
        const int dc[] = {0, 0, -1, 1};

        // Standard BFS
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int d = 0; d < 4; ++d) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                // If neighbor is within bounds and unvisited
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }

        return dist;
    }

    // Method 2: Two-pass DP (Optimal Space)
    std::vector<std::vector<int>> updateMatrix(std::vector<std::vector<int>>& mat) {
        if (mat.empty() || mat[0].empty()) return {};

        int m = static_cast<int>(mat.size());
        int n = static_cast<int>(mat[0].size());
        int maxDist = m + n; // Maximum possible distance

        // Pass 1: Top-Left to Bottom-Right
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (mat[r][c] == 0) {
                    continue;
                }
                int top = (r > 0) ? mat[r - 1][c] : maxDist;
                int left = (c > 0) ? mat[r][c - 1] : maxDist;
                mat[r][c] = std::min(top, left) + 1;
            }
        }

        // Pass 2: Bottom-Right to Top-Left
        for (int r = m - 1; r >= 0; --r) {
            for (int c = n - 1; c >= 0; --c) {
                if (mat[r][c] == 0) {
                    continue;
                }
                int bottom = (r < m - 1) ? mat[r + 1][c] : maxDist;
                int right = (c < n - 1) ? mat[r][c + 1] : maxDist;
                mat[r][c] = std::min(mat[r][c], std::min(bottom, right) + 1);
            }
        }

        return mat;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

```python
from typing import List
from collections import deque

class Solution:
    def updateMatrix(self, mat: List[List[int]]) -> List[List[int]]:
        """
        Calculates the nearest distance to a 0 for each cell using Two-Pass DP.
        
        Time Complexity: O(M * N)
        Space Complexity: O(1) auxiliary space (modifying mat in-place).
        """
        if not mat or not mat[0]:
            return []
            
        m, n = len(mat), len(mat[0])
        max_dist = m + n
        
        # Pass 1: Top-Left to Bottom-Right
        for r in range(m):
            for c in range(n):
                if mat[r][c] == 0:
                    continue
                top = mat[r - 1][c] if r > 0 else max_dist
                left = mat[r][c - 1] if c > 0 else max_dist
                mat[r][c] = min(top, left) + 1
                
        # Pass 2: Bottom-Right to Top-Left
        for r in range(m - 1, -1, -1):
            for c in range(n - 1, -1, -1):
                if mat[r][c] == 0:
                    continue
                bottom = mat[r + 1][c] if r < m - 1 else max_dist
                right = mat[r][c + 1] if c < n - 1 else max_dist
                mat[r][c] = min(mat[r][c], min(bottom, right) + 1)
                
        return mat
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Integer Limits and Initialization values
*   In languages like C++, initializing values to `INT_MAX` can cause integer overflow when adding `+ 1` during the comparison.
*   In Python, arbitrary precision integers won't overflow, but using `float('inf')` is common. However, `float('inf')` converts integers to floats, causing slow operations. 
*   Initializing with a safe upper bound (such as `m + n`, which is greater than any possible path distance in a grid) is preferred because it keeps all variables as primitive integers, maximizing execution speed.

### 2. Double-Ended Queue performance in BFS
*   If you choose the BFS approach, avoid using a standard Python `list` as a queue. Inserting or removing from the front of a list takes $\mathcal{O}(V)$ time. Use `collections.deque` for true $\mathcal{O}(1)$ queue operations.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(m \times n)$ | Every cell is processed exactly twice in the DP approach (or visited at most once in BFS). |
| **Space Complexity** | $\mathcal{O}(1)$ | The DP approach modifies the input matrix in-place. The BFS approach requires $\mathcal{O}(m \times n)$ space for the queue. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What is the relationship between Multi-Source BFS and Dijkstra's Algorithm?
*   **Answer**: Multi-Source BFS is a special case of Dijkstra's Algorithm:
    *   Dijkstra's algorithm operates on weighted graphs and uses a **Priority Queue** (Min-Heap) to extract the minimum distance node, taking $\mathcal{O}(E \log V)$ time.
    *   Since the edge weights in this grid are all uniformly `1`, a standard FIFO queue naturally maintains its elements in monotonically increasing order of distance. Thus, we can replace the Min-Heap with a simple queue, reducing the time complexity to $\mathcal{O}(V + E) = \mathcal{O}(m \cdot n)$.

### Q2: What if we can only move diagonally?
*   **Answer**: If only diagonal steps are allowed:
    *   The Manhattan distance changes to Chebyshev distance.
    *   The grid splits into two independent, disjoint bipartite subgrids (like black and white squares on a chessboard).
    *   We change the neighbor direction offsets to `(-1, -1)`, `(-1, 1)`, `(1, -1)`, and `(1, 1)`.
    *   The DP passes would still work, but top/left would check `(r-1, c-1)` and `(r-1, c+1)` / `(r+1, c-1)`.

---

## Pro-Tip: How to Impress the Interviewer

*   **Proactively Propose the DP Method for Space Constraints**: Most candidates immediately jump to BFS. Explaining the DP approach shows you understand state dependency and trade-offs. Point out that the DP approach has much better **spatial locality of reference** because it processes rows sequentially, making it extremely friendly to CPU cache prefetchers.
*   **Mention the Cache Performance of Grid Iterations**: Explain that in both passes of the DP approach, the outer loop iterates over `r` and the inner loop over `c`. This represents row-major ordering, which accesses adjacent cells sequentially in memory, avoiding cache misses. Never iterate columns in the outer loop (`c` then `r`) as it degrades performance due to stride-based cache misses.
