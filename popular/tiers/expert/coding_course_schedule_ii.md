# Course Schedule II

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 210, Glassdoor
- **Flashcards**: [Graph deck](../../flash_cards/coding/graph.md)

---

## Question Description

There are a total of `numCourses` courses you have to take, labeled from `0` to `numCourses - 1`. You are given an array `prerequisites` where `prerequisites[i] = [ai, bi]` indicates that you must take course `bi` first if you want to take course `ai`.

*   For example, the pair `[1, 0]` indicates that to take course `1` you must first take course `0`.

Return the ordering of courses you should take to finish all courses. If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.

### Examples
*   **Input**: `numCourses = 2`, `prerequisites = [[1,0]]`
    *   **Output**: `[0,1]`
    *   **Explanation**: There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is `[0,1]`.
*   **Input**: `numCourses = 4`, `prerequisites = [[1,0],[2,0],[3,1],[3,2]]`
    *   **Output**: `[0,2,1,3]` (or `[0,1,2,3]`)
    *   **Explanation**: There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0. So one correct course order is `[0,1,2,3]`. Another correct ordering is `[0,2,1,3]`.
*   **Input**: `numCourses = 1`, `prerequisites = []`
    *   **Output**: `[0]`

---

## Detailed Solution (C++)

This problem asks us to find a valid **topological sort** of the courses, represented as a Directed Acyclic Graph (DAG). If a cycle exists, topological sort is impossible, and we return an empty array.

We use **Kahn's Algorithm** (BFS-based Topological Sort):
1.  **Construct Graph**: Form the adjacency list representing directed dependencies: `prereq -> course`. Calculate the in-degree of each course.
2.  **Initialize Queue**: Push all courses with an in-degree of `0` into a `std::vector` that acts as both our BFS queue and our output array.
3.  **Process BFS**: Iterate through the vector using a cursor index (`front`). For each popped course, decrement the in-degree of its dependencies. If a dependency's in-degree reaches `0`, append it to the vector.
4.  **Verification**: If the size of the vector is equal to `numCourses`, return the vector. Otherwise, a cycle exists; return an empty vector `{}`.

### Standard C++ Production Code

```cpp
#include <vector>

class Solution {
public:
    std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>>& prerequisites) {
        std::vector<std::vector<int>> adj(numCourses);
        std::vector<int> inDegree(numCourses, 0);

        // Build the dependency graph
        for (const auto& edge : prerequisites) {
            int course = edge[0];
            int prereq = edge[1];
            adj[prereq].push_back(course);
            inDegree[course]++;
        }

        // We use a vector directly as our queue to avoid extra copies and memory allocations.
        // It will store the resulting topological order.
        std::vector<int> order;
        order.reserve(numCourses);

        for (int i = 0; i < numCourses; ++i) {
            if (inDegree[i] == 0) {
                order.push_back(i);
            }
        }

        // BFS traversal using a read cursor 'front'
        size_t front = 0;
        while (front < order.size()) {
            int current = order[front++];
            for (int neighbor : adj[current]) {
                if (--inDegree[neighbor] == 0) {
                    order.push_back(neighbor);
                }
            }
        }

        // If we processed all nodes, order is valid. Otherwise, there is a cycle.
        if (order.size() == static_cast<size_t>(numCourses)) {
            return order;
        }
        return {};
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
    def findOrder(self, numCourses: int, prerequisites: List[List[int]]) -> List[int]:
        """
        Finds a valid course ordering using Kahn's algorithm (BFS-based Topological Sort).
        
        Time Complexity: O(V + E)
        Space Complexity: O(V + E)
        """
        # Build dependency graph
        graph = {i: [] for i in range(numCourses)}
        in_degree = [0] * numCourses
        
        for course, prereq in prerequisites:
            graph[prereq].append(course)
            in_degree[course] += 1
            
        # Initialize queue with in-degree 0 elements
        queue = deque(i for i in range(numCourses) if in_degree[i] == 0)
        order: List[int] = []
        
        while queue:
            node = queue.popleft()
            order.append(node)
            
            for neighbor in graph[node]:
                in_degree[neighbor] -= 1
                if in_degree[neighbor] == 0:
                    queue.append(neighbor)
                    
        # Return order if all courses are visited, else empty list (cycle detected)
        return order if len(order) == numCourses else []
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Vector/List Pre-allocation
*   In Python, lists are dynamic arrays that dynamically resize as we append elements. Resizing has amortized $\mathcal{O}(1)$ time but can cause spikes in latency.
*   Unlike C++'s `std::vector::reserve`, Python lists do not have an explicit reservation API. However, we can initialize a list of fixed size `order = [0] * numCourses` and maintain a write pointer, or simply use `append()` since Python's dynamic array resizing growth factor (roughly 1.125x) is optimized for general use.

### 2. Hash Map vs Array for In-Degrees
*   Using a python `dict` to store in-degrees is possible but introduces hashing overhead. Because nodes are labelled from `0` to `numCourses - 1`, we should always use a contiguous list `[0] * numCourses` for constant-time lookup and update.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(V + E)$ | $V$ represents the number of courses, and $E$ is the number of prerequisite edges. Every vertex and edge is traversed once. |
| **Space Complexity** | $\mathcal{O}(V + E)$ | The adjacency list stores $E$ edges. The queue/order array and in-degree table require $\mathcal{O}(V)$ memory. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How would you find all possible topological sorts of the graph?
*   **Answer**: To find all valid schedules, we use backtracking combined with Kahn's algorithm:
    1.  Keep track of unvisited nodes and the current state of in-degrees.
    2.  At each step, find all nodes with in-degree `0`.
    3.  For each such node, add it to the current path, decrement neighbor in-degrees, and recurse.
    4.  Backtrack by removing the node from the path and restoring neighbor in-degrees.
*   This generates all valid topological sorts (which is $\mathcal{O}(V!)$ in the worst case for a completely disconnected graph).

### Q2: How can we implement the cycle detection and topological sort using DFS?
*   **Answer**: We can use DFS cycle detection with a post-order traversal:
    1.  Maintain a `visited` state array (0: unvisited, 1: visiting, 2: visited).
    2.  If we encounter a node in state 1, return `false` (cycle detected).
    3.  Perform DFS on all unvisited nodes. When a node's DFS is complete, push it to a stack (or prepend to a list).
    4.  Since we push a node to the stack only after visiting all its dependencies, the reverse of this stack gives the correct topological order.

---

## Pro-Tip: How to Impress the Interviewer

*   **Avoid Extra Queues in C++**: Point out that the output vector itself can serve as the queue in C++ Kahn's algorithm. By using a cursor index `front`, we eliminate the need for `std::queue` allocation. This guarantees $\mathcal{O}(1)$ auxiliary space if the output vector is not counted as auxiliary memory.
*   **Explain Memory Fragmentation**: Discuss how nested vectors in C++ (`std::vector<std::vector<int>>`) cause cache misses because each inner vector is allocated separately on the heap. Suggest using a flattened array or a custom allocator if maximum cache performance is required in low-latency systems.
