# Trapping Rain Water II

- **Category**: Coding
- **Difficulty**: Hard
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 407, Glassdoor
- **Flashcards**: [Top K Elements deck](../../flash_cards/coding/top_k_elements.md)

---

## Question Description

Given an $m \times n$ integer matrix `heightMap` representing the height of each unit cell in a 2D elevation map, return the volume of water it can trap after raining.

### Examples
*   **Input**: `heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]`
    *   **Output**: `4`
    *   **Explanation**: After the rain, water is trapped between the blocks. We have two small ponds of 1 and 3 units trapped. The total volume of water trapped is 4.
*   **Input**: `heightMap = [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]`
    *   **Output**: `10`

---

## Detailed Solution (C++)

To solve this in 2D, we must find the "weakest link" or the lowest point on the boundary surrounding any interior cell. The water level at any interior cell cannot exceed the maximum height of its lowest surrounding barrier.

We can model this using a **Min-Heap (Priority Queue)** and a **Breadth-First Search (BFS)** traversal starting from the boundary inwards:
1. **Initialize Boundary**: Push all border cells of the matrix into the min-heap and mark them as `visited`. These border cells represent the initial water containment boundary.
2. **Expand Inwards**: Pop the cell with the lowest height `h` from the heap. Because this is the lowest boundary point, water cannot spill out at any level lower than `h`.
3. **Inspect Neighbors**: For each of the 4 adjacent neighbors:
   - If it has not been visited, mark it as `visited`.
   - If its height is less than `h`, it traps water: `water += h - heightMap[nr][nc]`.
   - Push the neighbor into the heap with its effective height: `max(h, heightMap[nr][nc])`. This is because if the neighbor was lower than `h`, it is now filled with water up to height `h`, which acts as the boundary for cells further inland.
4. **Repeat** until the heap is empty.

### Standard C++ Production Code

```cpp
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

class Solution {
public:
    int trapRainWater(std::vector<std::vector<int>>& heightMap) {
        int m = static_cast<int>(heightMap.size());
        if (m < 3) return 0;
        int n = static_cast<int>(heightMap[0].size());
        if (n < 3) return 0;

        // Min-Heap containing tuples of {height, row, col}
        using Cell = std::tuple<int, int, int>;
        std::priority_queue<Cell, std::vector<Cell>, std::greater<Cell>> pq;
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));

        // Add left and right borders
        for (int r = 0; r < m; ++r) {
            pq.push({heightMap[r][0], r, 0});
            visited[r][0] = true;
            pq.push({heightMap[r][n - 1], r, n - 1});
            visited[r][n - 1] = true;
        }

        // Add top and bottom borders (excluding corners which are already added)
        for (int c = 1; c < n - 1; ++c) {
            pq.push({heightMap[0][c], 0, c});
            visited[0][c] = true;
            pq.push({heightMap[m - 1][c], m - 1, c});
            visited[m - 1][c] = true;
        }

        int totalWater = 0;
        const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        while (!pq.empty()) {
            auto [h, r, c] = pq.top();
            pq.pop();

            for (int i = 0; i < 4; ++i) {
                int nr = r + dirs[i][0];
                int nc = c + dirs[i][1];

                if (nr >= 0 && nr < m && nc >= 0 && nc < n && !visited[nr][nc]) {
                    visited[nr][nc] = true;
                    // If the neighbor is lower than the current boundary height, it traps water
                    if (heightMap[nr][nc] < h) {
                        totalWater += (h - heightMap[nr][nc]);
                    }
                    // Push the neighbor with the updated effective boundary height
                    pq.push({std::max(h, heightMap[nr][nc]), nr, nc});
                }
            }
        }

        return totalWater;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

```python
import heapq
from typing import List

class Solution:
    def trapRainWater(self, heightMap: List[List[int]]) -> int:
        """
        Calculates the volume of trapped water using a priority queue.
        
        Time Complexity: O(m * n * log(m * n))
        Space Complexity: O(m * n)
        """
        if not heightMap or not heightMap[0]:
            return 0
            
        m, n = len(heightMap), len(heightMap[0])
        if m < 3 or n < 3:
            return 0
            
        visited = [[False] * n for _ in range(m)]
        heap = []
        
        # Insert all boundary cells
        for r in range(m):
            for c in (0, n - 1):
                heapq.heappush(heap, (heightMap[r][c], r, c))
                visited[r][c] = True
                
        for c in range(1, n - 1):
            for r in (0, m - 1):
                heapq.heappush(heap, (heightMap[r][c], r, c))
                visited[r][c] = True
                
        water = 0
        dirs = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        
        while heap:
            h, r, c = heapq.heappop(heap)
            
            for dr, dc in dirs:
                nr, nc = r + dr, c + dc
                
                if 0 <= nr < m and 0 <= nc < n and not visited[nr][nc]:
                    visited[nr][nc] = True
                    # If neighbor is lower, trap water
                    if heightMap[nr][nc] < h:
                        water += (h - heightMap[nr][nc])
                    # Push effective height
                    heapq.heappush(heap, (max(h, heightMap[nr][nc]), nr, nc))
                    
        return water
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Dynamic Tuple Comparisons in Heap
*   Python compares tuples element-by-element: `(height, r, c)`. Since height is the first element, `heapq` naturally sorts cells by height. If heights are identical, it compares `r`, then `c`. This is correct and doesn't affect water trapping logic, but it means cell indices are compared to break ties.

### 2. Large Matrix Allocations
*   Creating a 2D boolean array `visited = [[False] * n for _ in range(m)]` is fast. However, for extremely large grids, flat 1D arrays of size $m \times n$ (with index lookup `r * n + c`) offer better cache line locality and lower memory allocation overhead in Python.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(m \cdot n \log(m \cdot n))$ | Every cell is inserted and popped from the min-heap at most once. Heap operations take logarithmic time in the number of boundary elements, bounded by $\mathcal{O}(\log(m \cdot n))$. |
| **Space Complexity** | $\mathcal{O}(m \cdot n)$ | For the `visited` matrix and priority queue. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Why must we use a Min-Heap instead of standard Breadth-First Search (BFS)?
*   **Answer**: Water naturally spills from the lowest point of any surrounding boundary. Standard BFS explores nodes level-by-level without regard to height, which can lead to overestimating the water level by exploring path heights out of order. A min-heap acts like Dijkstra's algorithm, resolving spillways in strictly increasing order of boundary height.

### Q2: How does this relate to Trapping Rain Water I (1D version)?
*   **Answer**: In the 1D version, the "boundary" is just two points: the left and right extremities. We always move the pointer with the lower height inwards. In the 2D version, the boundary is a closed loop of cells. We always pop the cell with the lowest height from this boundary and expand inwards. Thus, the 2D heap approach is the direct multidimensional generalization of the 1D two-pointer approach.

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain Dijkstra Metaphor**: Frame the solution as finding the **minimax path** in a graph. For any cell, its water level is $\min(\text{max height of path from cell to boundary})$. The min-heap operates similarly to Dijkstra's algorithm to resolve these paths.
*   **Optimize Cache Performance**: Suggest that for very large grids, instead of a heap of tuples (which creates node objects in Python or tuple overhead in C++), you can encode coordinates into a single integer `r * n + c` to improve cache locality and memory density.
