# Number of Islands

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Engineer / Systems Developer
- **Source**: LeetCode 200, Taro, Glassdoor, Voz
- **Flashcards**: [Coding Playbook deck](flash_cards/behavioral_qa/coding_playbook.md)

---

## Question Description

Given an `m x n` 2D binary grid `grid` which represents a map of `'1'`s (land) and `'0'`s (water), return *the number of islands*.

An **island** is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

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

## Detailed Solutions (C++)

We provide two approaches:
1.  **Depth-First Search (DFS)**: Recursive exploration (optimal when grid dimensions are small/medium).
2.  **Disjoint Set Union (DSU) / Union-Find**: Highly effective for streaming grid inputs, dynamic modifications, and parallel execution.

### Method 1: Depth-First Search (DFS)

```cpp
#include <vector>
#include <cstddef>

class SolutionDFS {
private:
    void dfs(std::vector<std::vector<char>>& grid, int r, int c, int rows, int cols) noexcept {
        // Base case: check boundary and water conditions
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] != '1') {
            return;
        }

        // Sinks the land to water ('0') to mark it as visited (avoids auxiliary space)
        grid[r][c] = '0';

        // Recurse on 4 adjacent directions (DFS)
        dfs(grid, r - 1, c, rows, cols); // Up
        dfs(grid, r + 1, c, rows, cols); // Down
        dfs(grid, r, c - 1, rows, cols); // Left
        dfs(grid, r, c + 1, rows, cols); // Right
    }

public:
    int numIslands(std::vector<std::vector<char>>& grid) noexcept {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        
        int rows = static_cast<int>(grid.size());
        int cols = static_cast<int>(grid[0].size());
        int islandCount = 0;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == '1') {
                    islandCount++;
                    dfs(grid, r, c, rows, cols);
                }
            }
        }

        return islandCount;
    }
};
```

### Method 2: Union-Find (DSU)

```cpp
#include <vector>
#include <numeric>

class UnionFind {
private:
    std::vector<int> parent;
    std::vector<int> rank;
    int count; // Number of active disjoint sets (islands)

public:
    explicit UnionFind(int n) : count(0) {
        parent.resize(n, -1);
        rank.resize(n, 0);
    }

    void setParent(int i) noexcept {
        if (parent[i] == -1) {
            parent[i] = i;
            count++;
        }
    }

    int getCount() const noexcept { return count; }

    int find(int i) noexcept {
        if (parent[i] == i) {
            return i;
        }
        return parent[i] = find(parent[i]); // Path compression
    }

    void unionSets(int i, int j) noexcept {
        int rootI = find(i);
        int rootJ = find(j);
        
        if (rootI != rootJ) {
            // Union by rank to keep tree shallow
            if (rank[rootI] < rank[rootJ]) {
                parent[rootI] = rootJ;
            } else if (rank[rootI] > rank[rootJ]) {
                parent[rootJ] = rootI;
            } else {
                parent[rootJ] = rootI;
                rank[rootI]++;
            }
            count--;
        }
    }
};

class SolutionDSU {
public:
    int numIslands(std::vector<std::vector<char>>& grid) noexcept {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }

        int rows = static_cast<int>(grid.size());
        int cols = static_cast<int>(grid[0].size());
        UnionFind uf(rows * cols);

        // First pass: initialize disjoint set elements for all '1' blocks
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == '1') {
                    uf.setParent(r * cols + c);
                }
            }
        }

        // Second pass: union adjacent land cells
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == '1') {
                    int currentIdx = r * cols + c;
                    
                    // Look down
                    if (r + 1 < rows && grid[r + 1][c] == '1') {
                        uf.unionSets(currentIdx, (r + 1) * cols + c);
                    }
                    // Look right
                    if (c + 1 < cols && grid[r][c + 1] == '1') {
                        uf.unionSets(currentIdx, r * cols + (c + 1));
                    }
                }
            }
        }

        return uf.getCount();
    }
};
```

---

## Detailed Solutions (Python)

We provide three approaches in Python:
1. **Depth-First Search (DFS)**: Recursive exploration (simple, but susceptible to recursion limits).
2. **Breadth-First Search (BFS)**: Iterative queue-based exploration (safer for deep grids, avoiding recursion limits).
3. **Disjoint Set Union (DSU) / Union-Find**: Best for streaming inputs or real-time graph components.

### Method 1: Depth-First Search (DFS - Recursive)

```python
from typing import List

class SolutionDFS:
    def numIslands(self, grid: List[List[str]]) -> int:
        """
        Recursive DFS. Mutates the input grid in-place to track visited cells.
        
        Time Complexity: O(M * N)
        Space Complexity: O(M * N) - recursion stack
        """
        if not grid or not grid[0]:
            return 0

        rows, cols = len(grid), len(grid[0])
        island_count = 0

        def dfs(r: int, c: int) -> None:
            # Base case: Out of bounds or water cell ('0')
            if r < 0 or r >= rows or c < 0 or c >= cols or grid[r][c] != '1':
                return

            # Sink the land cell to mark it as visited
            grid[r][c] = '0'

            # Recurse on all 4 directions
            dfs(r - 1, c)  # Up
            dfs(r + 1, c)  # Down
            dfs(r, c - 1)  # Left
            dfs(r, c + 1)  # Right

        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == '1':
                    island_count += 1
                    dfs(r, c)

        return island_count
```

### Method 2: Breadth-First Search (BFS - Iterative)

Using `collections.deque` to prevent recursion limit limits and maintain true $\mathcal{O}(1)$ queue updates.

```python
from typing import List
from collections import deque

class SolutionBFS:
    def numIslands(self, grid: List[List[str]]) -> int:
        """
        Iterative BFS. Avoids Python's recursion limit limits.
        
        Time Complexity: O(M * N)
        Space Complexity: O(min(M, N)) - queue size
        """
        if not grid or not grid[0]:
            return 0

        rows, cols = len(grid), len(grid[0])
        island_count = 0

        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == '1':
                    island_count += 1
                    
                    # Begin BFS
                    # Mark cell as visited immediately upon queueing to prevent duplicate additions
                    grid[r][c] = '0'
                    queue = deque([(r, c)])
                    
                    while queue:
                        curr_r, curr_c = queue.popleft()
                        for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                            nr, nc = curr_r + dr, curr_c + dc
                            if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] == '1':
                                grid[nr][nc] = '0'  # Sink neighbor
                                queue.append((nr, nc))

        return island_count
```

### Method 3: Union-Find (DSU)

```python
from typing import List

class UnionFind:
    def __init__(self, n: int):
        self.parent = [-1] * n
        self.rank = [0] * n
        self.count = 0

    def set_parent(self, i: int) -> None:
        if self.parent[i] == -1:
            self.parent[i] = i
            self.count += 1

    def find(self, i: int) -> int:
        if self.parent[i] == i:
            return i
        # Path compression
        self.parent[i] = self.find(self.parent[i])
        return self.parent[i]

    def union(self, i: int, j: int) -> None:
        root_i = self.find(i)
        root_j = self.find(j)
        
        if root_i != root_j:
            # Union by rank to keep tree shallow
            if self.rank[root_i] < self.rank[root_j]:
                self.parent[root_i] = root_j
            elif self.rank[root_i] > self.rank[root_j]:
                self.parent[root_j] = root_i
            else:
                self.parent[root_j] = root_i
                self.rank[root_i] += 1
            self.count -= 1


class SolutionDSU:
    def numIslands(self, grid: List[List[str]]) -> int:
        """
        DSU Solution.
        
        Time Complexity: O(M * N * alpha(M * N))
        Space Complexity: O(M * N)
        """
        if not grid or not grid[0]:
            return 0

        rows, cols = len(grid), len(grid[0])
        uf = UnionFind(rows * cols)

        # First pass: Initialize parents for all lands
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == '1':
                    uf.set_parent(r * cols + c)

        # Second pass: Union neighbors
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == '1':
                    curr_idx = r * cols + c
                    
                    # Look down
                    if r + 1 < rows and grid[r + 1][c] == '1':
                        uf.union(curr_idx, (r + 1) * cols + c)
                    # Look right
                    if c + 1 < cols and grid[r][c + 1] == '1':
                        uf.union(curr_idx, r * cols + (c + 1))

        return uf.count
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Recursion Limits and Stack Safety
*   **The Problem**: Python has a default recursion limit of $1000$. For a large grid (e.g., a snake-like island on a $100 \times 100$ grid with $5000$ cells), recursive DFS will trigger a `RecursionError: maximum recursion depth exceeded`.
*   **The Solution**: While you can raise the limit using `sys.setrecursionlimit()`, doing so can cause a segmentation fault in CPython if the thread's physical stack overflows. For production systems or large inputs, always use **Iterative BFS** (using a queue) or **Iterative DFS** (using a custom list as a stack) to guarantee safety.

### 2. Queue Performance: `list` vs `collections.deque`
*   In Python, using a standard list `[]` as a queue (e.g., `queue.pop(0)`) is an $\mathcal{O}(k)$ time operation because it shifts all remaining elements in memory by one index.
*   Always use `collections.deque`, which is implemented in C as a doubly linked list of fixed-size blocks. It offers true $\mathcal{O}(1)$ time complexity for both `append()` and `popleft()`.

### 3. Allocation Overhead of Dynamic Tuples
*   Every coordinate pair `(r, c)` queued or stacked is a dynamically allocated tuple object in Python. Instantiating millions of these tuples in a large grid search creates substantial GC pressure.
*   **Optimization**: Use 1D indexing (`r * cols + c`) to represent coordinates as integers, which Python caches (for numbers $-5$ to $256$) or handles with much lower memory footprint than tuple allocations.

### 4. Generator-Based Traversals
*   An advanced technique in Python is using generators (`yield`) to model the graph traversal. This decouples the search algorithm from the business logic (e.g. visiting a cell), allowing clean separation. However, generators incur a call/yield stack frame overhead that is higher than standard iterative loops.

---

## Complexity Analysis

### DFS
*   **Time Complexity**: $\mathcal{O}(M \times N)$, where $M$ is the row count and $N$ is the column count. Every cell is visited at most once.
*   **Space Complexity**: $\mathcal{O}(M \times N)$ in the worst case (e.g., an entirely land-filled grid). The OS execution stack will grow to the size of the grid.

### Union-Find (DSU)
*   **Time Complexity**: $\mathcal{O}(M \times N \cdot \alpha(M \times N))$, where $\alpha$ is the Inverse Ackermann function, which grows so slowly that it is effectively $\mathcal{O}(1)$ in practice.
*   **Space Complexity**: $\mathcal{O}(M \times N)$ to store the disjoint set parent and rank arrays.

---

## Common Follow-Up Questions & How to Answer

### Q1: What if the grid is too large to fit in memory (e.g., satellite imagery data spanning terabytes)?
*   **Answer**: Apply an **out-of-core / chunked processing** algorithm.
    1. Divide the massive grid into horizontal slices or tiles that comfortably fit in system memory.
    2. Process each slice independently to count local islands. Keep track of the active components along the boundary borders.
    3. Use a Union-Find system to reconcile and merge components that cross slice borders as adjacent slices are compared. This allows streaming computation, keeping memory overhead limited to $\mathcal{O}(\text{slice\_width})$ rather than the full size of the grid.

### Q2: What if the grid is dynamically updated (cells turn from water to land in real-time)?
*   **Answer**: Recursive DFS is highly inefficient for dynamic grids, as updating it would require running a full $\mathcal{O}(M \times N)$ traversal for every change.
    Use **Union-Find (DSU)** to support real-time dynamic additions ($\mathcal{O}(\alpha(M \times N))$ per update):
    1. Keep a running count of islands.
    2. When a water cell at `(r, c)` transitions to land:
       - Set its DSU parent to itself and increment the island count by 1.
       - Inspect the four neighboring cells. If a neighbor is already land, run `unionSets((r, c), neighbor)`.
       - If the union succeeds (meaning the neighbor belonged to a different island), decrement the island count by 1.

### Q3: How would you parallelize the island computation on a multi-core CPU?
*   **Answer**: Divide the grid into $K$ disjoint rectangular tiles.
    1. Assign each tile to a separate CPU thread to compute components locally.
    2. In a thread-safe global Union-Find structure, merge nodes along the tile boundaries. This dramatically reduces sequential processing bottleneck.

---

## Pro-Tip: How to Impress the Interviewer

*   **Highlight OS Stack Overflow Vulnerabilities**: Mention that recursive DFS on very large grids (e.g., $10000 \times 10000$ or in kernel-mode environments with limited stack sizes like $8\text{KB}$ in Linux) will crash with a Stack Overflow. Show that you know how to write an **iterative DFS** using a heap-allocated `std::vector<std::pair<int, int>>` acting as a stack to guarantee memory safety.
*   **State Traversal Direction and Cache Friendliness**: C++ arrays are stored in Row-Major format. Traversing row-by-row utilizes CPU spatial prefetching. Mention that you access cells in horizontal sequences (`c` changes faster than `r`) to minimize D-cache misses.
*   **Discuss Input Mutability Guidelines**: Point out that although sinking the island directly in `grid` avoids $\mathcal{O}(M \times N)$ auxiliary visited-set memory, mutating input parameters is often forbidden in concurrent, read-only pipelines. Suggest allocating a bitset or thread-safe visited tracker when needed.
