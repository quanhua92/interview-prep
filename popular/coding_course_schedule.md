# Course Schedule

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI System Engineer / Architect
- **Source**: LeetCode 207, Glassdoor

---

## Question Description

There are a total of `numCourses` courses you have to take, labeled from `0` to `numCourses - 1`. You are given an array `prerequisites` where `prerequisites[i] = [a_i, b_i]` indicates that you **must** take course `b_i` first if you want to take course `a_i`.

*   For example, the pair `[0, 1]`, indicates that to take course `0` you have to first take course `1`.

Return `true` if you can finish all courses. Otherwise, return `false`.

### Examples
*   **Input**: `numCourses = 2`, `prerequisites = [[1,0]]`
    *   **Output**: `true`
    *   **Explanation**: There are a total of 2 courses to take. To take course 1 you should have finished course 0. So it is possible.
*   **Input**: `numCourses = 2`, `prerequisites = [[1,0],[0,1]]`
    *   **Output**: `false`
    *   **Explanation**: There are 2 courses. To take 1 you must finish 0, and to take 0 you must finish 1. This creates a cyclic dependency.

---

## Detailed Solution (C++)

This problem is isomorphic to detecting a cycle in a directed graph. If a cycle exists, topological sorting is impossible. We can resolve this using **Kahn's Algorithm** (Breadth-First Search topological sort) or DFS cycle detection. Kahn's algorithm is preferred in production systems because it is recursive-free, preventing stack overflow, and models queue-based resource schedulers.

### C++ Kahn's Algorithm Implementation with Strict Bounds Checks

```cpp
#include <vector>
#include <queue>
#include <stdexcept>

class Solution {
public:
    bool canFinish(int numCourses, const std::vector<std::vector<int>>& prerequisites) noexcept {
        if (numCourses <= 0) {
            return true;
        }

        // Step 1: Build the Adjacency List and compute In-degrees
        std::vector<std::vector<int>> adj(numCourses);
        std::vector<int> inDegree(numCourses, 0);

        for (const auto& pre : prerequisites) {
            if (pre.size() < 2) {
                continue; // Ignore malformed inputs safely
            }
            int dest = pre[0];
            int src = pre[1];

            // Critical Bounds Check: Avoid out-of-bounds vector access
            if (dest < 0 || dest >= numCourses || src < 0 || src >= numCourses) {
                return false; 
            }
            
            adj[src].push_back(dest);
            inDegree[dest]++;
        }

        // Step 2: Queue all nodes with in-degree 0 (courses with no prerequisites)
        std::queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        int processedCount = 0;

        // Step 3: Process the queue
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            processedCount++;

            // For all outgoing edges from the current course
            for (int neighbor : adj[curr]) {
                inDegree[neighbor]--;
                // If all prerequisites are cleared, add to queue
                if (inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        // Step 4: If processedCount equals numCourses, no cycle exists
        return processedCount == numCourses;
    }
};
```

---

## Detailed Solutions (Python)

We provide both Kahn's Algorithm (BFS-based, recommended) and a 3-state coloring DFS cycle detection in Python.

### Method 1: Kahn's Algorithm (BFS - Recommended)

This version uses `collections.deque` and pre-allocated list structures to maximize performance under CPython.

```python
from typing import List
from collections import deque

class SolutionKahn:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        """
        Kahn's Algorithm (BFS Topological Sort) to check cycle existence.
        
        Time Complexity: O(V + E)
        Space Complexity: O(V + E)
        """
        if numCourses <= 0:
            return True

        # Pre-allocated list of lists is much faster than defaultdict(list)
        adj: List[List[int]] = [[] for _ in range(numCourses)]
        in_degree: List[int] = [0] * numCourses

        # Step 1: Build adjacency list and compute in-degrees
        for pre in prerequisites:
            if len(pre) < 2:
                continue  # Safe protection against malformed input
            dest, src = pre[0], pre[1]

            # Critical boundary check
            if dest < 0 or dest >= numCourses or src < 0 or src >= numCourses:
                return False

            adj[src].append(dest)
            in_degree[dest] += 1

        # Step 2: Queue all nodes with in-degree 0 using list comprehension
        queue = deque([i for i in range(numCourses) if in_degree[i] == 0])
        processed_count = 0

        # Step 3: Process the queue
        while queue:
            curr = queue.popleft()
            processed_count += 1

            for neighbor in adj[curr]:
                in_degree[neighbor] -= 1
                if in_degree[neighbor] == 0:
                    queue.append(neighbor)

        # Step 4: If we processed all vertices, the graph is a DAG
        return processed_count == numCourses
```

### Method 2: Depth-First Search (DFS - 3-State Coloring)

```python
from typing import List

class SolutionDFS:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        """
        DFS cycle detection using 3-state vertex coloring.
        
        States:
          0 = Unvisited
          1 = Visiting (in current recursion path)
          2 = Visited (fully explored, no cycles)
          
        Time Complexity: O(V + E)
        Space Complexity: O(V + E)
        """
        if numCourses <= 0:
            return True

        adj: List[List[int]] = [[] for _ in range(numCourses)]
        for pre in prerequisites:
            if len(pre) < 2:
                continue
            dest, src = pre[0], pre[1]
            if dest < 0 or dest >= numCourses or src < 0 or src >= numCourses:
                return False
            adj[src].append(dest)

        states = [0] * numCourses

        def has_cycle(curr: int) -> bool:
            states[curr] = 1  # State: Visiting
            
            for neighbor in adj[curr]:
                if states[neighbor] == 1:
                    return True  # Found back-edge (cycle detected)
                if states[neighbor] == 0:
                    if has_cycle(neighbor):
                        return True

            states[curr] = 2  # State: Visited
            return False

        for i in range(numCourses):
            if states[i] == 0:
                if has_cycle(i):
                    return False

        return True
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Adjacency List: `list` vs `dict` vs `defaultdict`
*   In Python, standard graphs are often stored as `defaultdict(list)` or `dict` mapping node keys to lists. However, when node IDs are sequential integers ($0$ to $V-1$), using a pre-allocated array of lists `[[] for _ in range(numCourses)]` is significantly faster.
*   Pre-allocated list lookups compile to C-level offset dereferencing, avoiding the dynamic hash computation and dictionary key collision overheads.

### 2. List Comprehension Optimization
*   Initializing the queue using `deque([i for i in range(numCourses) if in_degree[i] == 0])` is optimized at the interpreter level. In CPython, list comprehensions run at C-speed, making them faster than manual loops that call `list.append()` repeatedly.

### 3. DFS Recursion Stack Overflow Risk
*   Using recursive DFS runs the risk of a `RecursionError` in Python if the dependency chain is linear and deep ($> 1000$ courses).
*   For this reason, Kahn's BFS approach is safer and highly recommended for large graph scheduling in production Python scripts.

### 4. Memory Allocations
*   Every list inside `adj` starts as a dynamic array. Python lists allocate memory with a growth pattern ($4, 8, 16, 25, 35, 46...$). For sparse graphs, this over-allocation can waste substantial memory. If memory is tight, representing the graph in a 1D flat array (comparable to C++ CSR layout) can mitigate this.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(V + E)$ | Where $V = \text{numCourses}$ and $E = \text{prerequisites.size()}$. We visit each vertex and traverse each edge exactly once. |
| **Space Complexity** | $\mathcal{O}(V + E)$ | Required for the adjacency list `adj` ($\mathcal{O}(V + E)$) and the `inDegree` array of size $V$. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How do you return the actual course scheduling sequence instead of just a boolean? (LeetCode 210)
*   **Answer**: Maintain an array `result` (pre-allocated to size `numCourses` for performance). Every time you pop a node from the queue, append it to `result`. 
    If `processedCount == numCourses`, return `result`. Otherwise, return an empty array `{}` indicating that scheduling is impossible due to a cycle.

### Q2: What are the differences between DFS and BFS (Kahn's) for cycle detection?
*   **Answer**:
    *   **DFS Cycle Detection**: Uses a state array (`0 = unvisited`, `1 = visiting`, `2 = visited`). If DFS visits a neighbor currently in the `visiting` state, a back-edge (cycle) is detected. DFS is recursively based, making it prone to stack overflows on large linear graphs.
    *   **Kahn's (BFS) Algorithm**: Uses in-degree tracking. It is iterative and naturally fits thread-pool scheduling models where tasks are dispatched as dependencies drop to zero. It is highly robust against stack overflow.

### Q3: How does dependency resolution scale to distributed build systems (e.g., Bazel, monorepos)?
*   **Answer**: In distributed build systems, the dependency graph is too massive to reside on a single scheduler.
    1.  **Graph Partitioning**: Partition the DAG across different servers.
    2.  **Distributed Notification**: When a node on Server A finishes compilation, it sends a network message to decrement the in-degree of its successor nodes on Server B.
    3.  **Dynamic Deadlock Detection**: Distributed cycles are resolved via timeouts or distributed cycle detection protocols (e.g., Chandy-Misra-Haas).

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention Out-of-Bounds Memory Safety**: Note that raw competitive programming solutions often skip bounds checking on `prerequisites` elements. Explaining that an invalid prerequisite value (e.g., `[-1, 100]` or `[numCourses + 5, 0]`) leads to immediate segfaults/memory corruption, and showing how you write code to handle it, highlights your attention to production-grade safety.
*   **Discuss cuGRAPH and CSR (Compressed Sparse Row)**: Emphasize that while `std::vector<std::vector<int>>` is standard for interviews, it causes cache thrashing in high-performance graph frameworks (like NVIDIA cuGraph). Suggest representing graphs using **Compressed Sparse Row (CSR)** layouts: three flat arrays (`offsets`, `edges`, and `weights`). This eliminates double-indirection and maximizes GPU global memory coalesced access.
*   **Connect to NVIDIA Hardware Schedulers**: Connect topological sort to hardware: modern GPU warps and Tensor Core schedulers track instruction register dependencies using scoreboard registers (essentially tracking in-degrees of operands) to execute instruction streams out-of-order safely.
