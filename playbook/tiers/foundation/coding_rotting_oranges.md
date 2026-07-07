# Rotting Oranges

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 994, Glassdoor
- **Flashcards**: [BFS deck](../../flash_cards/coding/bfs.md)

---

## Question Description

You are given an `m x n` `grid` where each cell can have one of three values:
*   `0` representing an empty cell,
*   `1` representing a fresh orange, or
*   `2` representing a rotten orange.

Every minute, any fresh orange that is **4-directionally adjacent** to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return `-1`.

### Examples
*   **Input**: `grid = [[2,1,1],[1,1,0],[0,1,1]]`
    *   **Output**: `4`
*   **Input**: `grid = [[2,1,1],[0,1,1],[1,0,1]]`
    *   **Output**: `-1`
    *   **Explanation**: The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.
*   **Input**: `grid = [[0,2]]`
    *   **Output**: `0`
    *   **Explanation**: Since there are already no fresh oranges at minute 0, the answer is just 0.

---

## Detailed Solution (C++)

This problem represents a classic propagation process on a grid. Because multiple rotten oranges can rot adjacent fresh oranges simultaneously, we must perform a **Multi-Source BFS**.

1.  **Initialization**: Sweep the grid to:
    *   Push all coordinates of initial rotten oranges (`2`) into the queue.
    *   Count the total number of fresh oranges (`fresh`).
2.  **Edge Case**: If there are no fresh oranges, return `0` immediately.
3.  **Propagation**: Perform BFS. In each iteration, pop all nodes currently in the queue (representing one minute of rotting spread). If any fresh orange is turned rotten, push it to the queue, decrement `fresh`, and set a flag `rotted_any = true`.
4.  **Time Accumulation**: Increment `minutes` only if `rotted_any` was true during the level traversal.
5.  **Result**: If `fresh == 0`, return `minutes`; otherwise, return `-1`.

### Standard C++ Production Code

```cpp
#include <vector>
#include <queue>
#include <utility>

class Solution {
public:
    int orangesRotting(std::vector<std::vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }

        int rows = static_cast<int>(grid.size());
        int cols = static_cast<int>(grid[0].size());
        
        std::queue<std::pair<int, int>> q;
        int fresh = 0;

        // Initialize queue with all source nodes (initial rotten oranges)
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 2) {
                    q.push({r, c});
                } else if (grid[r][c] == 1) {
                    fresh++;
                }
            }
        }

        // If there are no fresh oranges to rot, 0 minutes are needed
        if (fresh == 0) {
            return 0;
        }

        int minutes = 0;
        const int dr[] = {0, 0, 1, -1};
        const int dc[] = {1, -1, 0, 0};

        while (!q.empty()) {
            int sz = static_cast<int>(q.size());
            bool rotted_any = false;

            for (int i = 0; i < sz; ++i) {
                auto [r, c] = q.front();
                q.pop();

                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    // Check bounds and if neighbor is a fresh orange
                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == 1) {
                        grid[nr][nc] = 2; // Rot the fresh orange in-place
                        fresh--;
                        q.push({nr, nc});
                        rotted_any = true;
                    }
                }
            }

            if (rotted_any) {
                minutes++;
            }
        }

        // If fresh is 0, all oranges have rotted; otherwise, some were unreachable
        return fresh == 0 ? minutes : -1;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the multi-source BFS implementation using `collections.deque`.

```python
from typing import List
from collections import deque

class Solution:
    def orangesRotting(self, grid: List[List[int]]) -> int:
        """
        Finds the minimum time for all oranges to rot.
        Uses a multi-source BFS.
        
        Time Complexity: O(R * C)
        Space Complexity: O(R * C)
        """
        if not grid or not grid[0]:
            return 0

        rows, cols = len(grid), len(grid[0])
        queue = deque()
        fresh = 0

        # Step 1: Scan grid for rotten oranges (sources) and count fresh oranges
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 2:
                    queue.append((r, c))
                elif grid[r][c] == 1:
                    fresh += 1

        # If there are no fresh oranges, return 0 minutes immediately
        if fresh == 0:
            return 0

        minutes = 0
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]

        # Step 2: Multi-source BFS propagation
        while queue:
            rotted_any = False
            
            # Process all currently rotten oranges for this minute level
            for _ in range(len(queue)):
                r, c = queue.popleft()
                
                for dr, dc in directions:
                    nr, nc = r + dr, c + dc
                    
                    if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] == 1:
                        grid[nr][nc] = 2  # Rot the orange in-place
                        fresh -= 1
                        queue.append((nr, nc))
                        rotted_any = True
            
            if rotted_any:
                minutes += 1

        # Return minutes if all fresh oranges rotted, else -1 (isolated components)
        return minutes if fresh == 0 else -1
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. BFS Level-by-Level Incrementing Gotcha
*   A common mistake is incrementing `minutes` unconditionally inside the `while queue:` loop. If the final level does not rot any new oranges, it should not contribute to the minute count.
*   By tracking whether at least one orange rotted using a boolean flag (`rotted_any`), we avoid off-by-one errors (e.g. returning `5` instead of `4` because we incremented for the final queue clear).

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(rows \times cols)$ | We scan the grid initially, and each grid cell is queued/visited at most once. |
| **Space Complexity** | $\mathcal{O}(rows \times cols)$ | In the worst-case, the queue holds $\mathcal{O}(rows \times cols)$ coordinates (e.g., if the entire grid starts as rotten). |

---

## Common Follow-Up Questions & How to Answer

### Q1: What is the difference between running Multi-Source BFS vs. multiple Single-Source BFS traversals?
*   **Multi-Source BFS**: We insert all source nodes into the queue at level 0. The wave spreads outwards simultaneously. The time complexity is $\mathcal{O}(R \times C)$.
*   **Multiple Single-Source BFS**: Running BFS from each rotten orange one-by-one to calculate the shortest path to every fresh orange, and then calculating the maximum of the minimums. This would take $\mathcal{O}(K \times R \times C)$ time (where $K$ is the number of initial rotten oranges), which is highly inefficient for dense grids.

### Q2: What if we are not allowed to modify the input grid?
*   **The Solution**: If input modification is forbidden (e.g., for concurrency safety), maintain a separate `visited` set containing coordinates of newly rotten oranges, or copy the grid. However, copying the grid or keeping a `visited` set changes auxiliary space from $\mathcal{O}(1)$ to $\mathcal{O}(R \times C)$.

### Q3: How do we solve this if the grid size is massive (e.g. $10^9 \times 10^9$) but the number of oranges is very small (sparse grid)?
*   **The Solution**: Storing a $10^9 \times 10^9$ array is impossible. Instead, represent the grid as a hash map of coordinates to state: `hash_map: Coordinate -> State`. 
*   We only store the coordinates of actual oranges. The BFS will query neighbors using hash map lookups.
*   This drops the space and time complexity to $\mathcal{O}(O)$ (where $O$ is the total number of oranges), making it independent of grid size.

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain Multi-Source Initialization**: Emphasize that the key to multi-source BFS is that **all** source nodes must be in the queue at the start (minute 0). Adding them sequentially or processing them in separate BFS executions changes the correctness of the traversal.
*   **Mention Connectivity & Disjoint Sets**: Note that if the final fresh orange count is greater than 0, it indicates the graph has multiple disconnected components (islands), and at least one component containing fresh oranges had no initial source (rotten orange).
