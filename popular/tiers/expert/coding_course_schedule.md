# Course Schedule

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 207, Glassdoor
- **Flashcards**: [Graph deck](../../flash_cards/coding/graph.md)

---

## Question Description

There are a total of `numCourses` courses you have to take, labeled from `0` to `numCourses - 1`. You are given an array `prerequisites` where `prerequisites[i] = [ai, bi]` indicates that you must take course `bi` first if you want to take course `ai`.

*   For example, the pair `[1, 0]` indicates that to take course `1` you must first take course `0`.

Return `true` if you can finish all courses. Otherwise, return `false`.

### Examples
*   **Input**: `numCourses = 2`, `prerequisites = [[1,0]]`
    *   **Output**: `true`
    *   **Explanation**: There are a total of 2 courses to take. To take course 1 you should have finished course 0. So it is possible.
*   **Input**: `numCourses = 2`, `prerequisites = [[1,0],[0,1]]`
    *   **Output**: `false`
    *   **Explanation**: There are a total of 2 courses to take. To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.

---

## Detailed Solution (C++)

The problem of finding if a course schedule is possible is equivalent to detecting a cycle in a directed graph. If the graph contains a cycle (e.g., $A \to B \to A$), then no topological ordering exists, and it is impossible to finish all courses.

We use **Kahn's Algorithm** (BFS-based Topological Sort):
1.  **Build the Graph**: Represent the graph using an adjacency list and keep track of the in-degrees of all nodes.
2.  **Initialize Queue**: Push all nodes with an in-degree of `0` (courses with no prerequisites) into a queue.
3.  **Process Graph**: Pop a node from the queue, increment our visited count, and decrement the in-degree of all its neighbors. If a neighbor's in-degree drops to `0`, push it to the queue.
4.  **Cycle Check**: If the visited count equals `numCourses`, then a valid topological order exists (return `true`). Otherwise, a cycle exists (return `false`).

### Standard C++ Production Code

```cpp
#include <vector>
#include <queue>

class Solution {
public:
    bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites) {
        // Build graph and calculate in-degrees
        std::vector<std::vector<int>> adj(numCourses);
        std::vector<int> inDegree(numCourses, 0);
        
        for (const auto& edge : prerequisites) {
            int course = edge[0];
            int prereq = edge[1];
            adj[prereq].push_back(course);
            inDegree[course]++;
        }

        // Initialize queue with courses having no prerequisites
        std::queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        int processedCount = 0;

        // Process courses topological-order BFS
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            processedCount++;

            for (int neighbor : adj[current]) {
                if (--inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        // If processedCount matches numCourses, we succeeded in processing all nodes without cycles
        return processedCount == numCourses;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

```python
from collections import deque
from typing import List

class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        """
        Determines if all courses can be finished using Kahn's algorithm (BFS topological sort).
        
        Time Complexity: O(V + E) where V is numCourses and E is prerequisites length.
        Space Complexity: O(V + E) for adjacency list and queue.
        """
        # Build graph and in-degree table
        graph = {i: [] for i in range(numCourses)}
        in_degree = [0] * numCourses
        
        for course, prereq in prerequisites:
            graph[prereq].append(course)
            in_degree[course] += 1
            
        # Push courses with 0 in-degrees to the queue
        queue = deque(i for i in range(numCourses) if in_degree[i] == 0)
        
        processed_count = 0
        
        while queue:
            node = queue.popleft()
            processed_count += 1
            
            for neighbor in graph[node]:
                in_degree[neighbor] -= 1
                if in_degree[neighbor] == 0:
                    queue.append(neighbor)
                    
        return processed_count == numCourses
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Choice of Queue Structure (`collections.deque` vs `list`)
*   Using a standard Python list as a queue (`list.pop(0)`) is an $\mathcal{O}(n)$ operation because it requires shifting all subsequent elements in memory.
*   Always use `collections.deque` (double-ended queue), which provides $\mathcal{O}(1)$ time complexity for both `append()` and `popleft()`.

### 2. Initializing Adjacency Lists: `dict` vs `list` of `list`s
*   Since course IDs are continuous integers from `0` to `numCourses - 1`, we can use either a list of lists `[[] for _ in range(numCourses)]` or a dictionary. 
*   A list of lists typically has less memory overhead and faster lookups because array access by index in Python does not involve hash computations.

### 3. Avoiding Recursion Limits with DFS
*   If cycle detection is implemented using Depth-First Search (DFS), recursion can reach a depth equal to the number of vertices $V$.
*   Python's default recursion limit is $1000$. For $numCourses = 2000$, a deep recursive path could raise a `RecursionError`. BFS (Kahn's algorithm) avoids recursion entirely and is safer for production.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(V + E)$ | Every vertex $V$ and edge $E$ (prerequisite) is processed exactly once. |
| **Space Complexity** | $\mathcal{O}(V + E)$ | Adjacency list stores $E$ edges, and the in-degree array / queue store at most $V$ elements. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How would you detect a cycle using DFS instead of BFS?
*   **Answer**: DFS-based cycle detection uses three states for each node:
    1.  **White (0)**: Unvisited.
    2.  **Gray (1)**: Visiting (currently in the recursion stack).
    3.  **Black (2)**: Visited (all descendants processed).
*   During DFS, if we transition to a neighbor that is in the **Gray** state, we have found a back-edge, indicating a cycle.
*   **C++ DFS Implementation Snippet**:
    ```cpp
    bool hasCycle(int node, const std::vector<std::vector<int>>& adj, std::vector<int>& state) {
        state[node] = 1; // Mark Gray
        for (int neighbor : adj[node]) {
            if (state[neighbor] == 1) return true; // Found cycle
            if (state[neighbor] == 0 && hasCycle(neighbor, adj, state)) return true;
        }
        state[node] = 2; // Mark Black
        return false;
    }
    ```

### Q2: What if we need to find the lexicographically smallest course schedule?
*   **Answer**: Instead of a standard queue (which gives an arbitrary valid order depending on insertion), we can use a **Min-Priority Queue** (Min-Heap) to store courses with $0$ in-degree.
*   In C++, use `std::priority_queue<int, std::vector<int>, std::greater<int>>`. In Python, use the `heapq` module.
*   Each time we pop from the heap, we process the smallest index course available, which guarantees a lexicographically sorted order.

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention Vector-Based Queue Optimization**: Explain that in C++, instead of using `std::queue<int>`, we can use a `std::vector<int> q` and an index `front` acting as our read pointer. Because Kahn's algorithm visits each node exactly once, the vector will grow to a maximum size of `numCourses`, saving allocation overhead and providing contiguous cache lines for the queue storage.
*   **Memory Footprint & Locality**: Discuss how adjacency lists can be stored as a single contiguous array (`std::vector<int> edges` and `std::vector<int> offsets`) instead of `std::vector<std::vector<int>>` to reduce heap allocation fragmentation and improve CPU cache locality (L1/L2 cache prefetching).
