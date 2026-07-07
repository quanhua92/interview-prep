# Redundant Connection

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 684, Glassdoor
- **Flashcards**: [Union Find deck](../../flash_cards/coding/union_find.md)

---

## Question Description

In this problem, a tree is an undirected graph that is connected and has no cycles.

You are given a graph that started as a tree with `n` nodes labeled from `1` to `n`, with one additional edge added. The added edge has two different vertices chosen from `1` to `n`, and was not an edge that already existed. The graph is represented as an array `edges` of length `n` where `edges[i] = [ai, bi]` indicates that there is an edge between nodes `ai` and `bi` in the graph.

Return an edge that can be removed so that the resulting graph is a tree of `n` nodes. If there are multiple answers, return the answer that occurs last in the input.

### Examples
*   **Input**: `edges = [[1,2],[1,3],[2,3]]`
    *   **Output**: `[2,3]`
*   **Input**: `edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]`
    *   **Output**: `[1,4]`

---

## Detailed Solution (C++)

This problem asks us to find an edge that forms a cycle in an undirected graph. Since we want to return the *last* edge in the input that creates the cycle, we can process the edges one by one in the order they appear.

We use **Disjoint Set Union (DSU / Union-Find)**:
1.  Initialize a DSU structure for $n$ nodes, where each node is its own parent.
2.  Iterate through each edge `[u, v]`.
3.  Query `find(u)` and `find(v)`.
    *   If `find(u) == find(v)`, it means $u$ and $v$ are already connected in the same component. Adding the edge `[u, v]` would create a cycle. Since we process edges in the given order, this must be the redundant connection. We immediately return `[u, v]`.
    *   If they are in different components, we merge them using `unite(u, v)`.

### Standard C++ Production Code

```cpp
#include <vector>
#include <numeric>
#include <utility>

class UnionFind {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    UnionFind(int size) : parent(size), rank(size, 0) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) {
            return false; // Cycle detected (already connected)
        }

        // Union by rank
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            if (rank[rootX] == rank[rootY]) {
                rank[rootX]++;
            }
        }
        return true;
    }
};

class Solution {
public:
    std::vector<int> findRedundantConnection(std::vector<std::vector<int>>& edges) {
        int n = static_cast<int>(edges.size());
        // Nodes are labeled 1 to n, so size is n + 1
        UnionFind uf(n + 1);

        for (const auto& edge : edges) {
            if (!uf.unite(edge[0], edge[1])) {
                return edge; // This edge creates the cycle
            }
        }

        return {};
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

```python
from typing import List

class UnionFind:
    def __init__(self, size: int):
        self.parent = list(range(size))
        self.rank = [0] * size

    def find(self, x: int) -> int:
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x]) # Path compression
        return self.parent[x]

    def union(self, x: int, y: int) -> bool:
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x == root_y:
            return False
        
        if self.rank[root_x] < self.rank[root_y]:
            self.parent[root_x] = root_y
        else:
            self.parent[root_y] = root_x
            if self.rank[root_x] == self.rank[root_y]:
                self.rank[root_x] += 1
        return True

class Solution:
    def findRedundantConnection(self, edges: List[List[int]]) -> List[int]:
        """
        Finds the redundant connection that completes a cycle.
        
        Time Complexity: O(N * alpha(N))
        Space Complexity: O(N)
        """
        n = len(edges)
        uf = UnionFind(n + 1)
        
        for u, v in edges:
            if not uf.union(u, v):
                return [u, v]
                
        return []
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Pre-allocation of `parent` list size
*   Since the node labels are 1-indexed and we are given $n$ edges, the number of nodes is exactly $n$ (because a tree of $n$ nodes has $n-1$ edges, and adding one edge results in $n$ nodes and $n$ edges).
*   Allocating the `parent` list to `n + 1` elements prevents off-by-one errors when indexing.

### 2. Functional Closure vs OOP UnionFind Class
*   In Python, calling method on objects incurs minor overhead due to dynamic attribute lookup.
*   In highly constrained performance environments, you can define `parent` and `find` as local variables/closures within the outer function. However, the class-based structure is preferred in production code for clean separation of concerns and testability.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(N \cdot \alpha(N))$ | We process $N$ edges. Each Union-Find operation takes $\mathcal{O}(\alpha(N))$ time. |
| **Space Complexity** | $\mathcal{O}(N)$ | The DSU structure uses `parent` and `rank` arrays of size $N + 1$. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How would you solve this for a directed graph? (Redundant Connection II)
*   **Answer**: In a directed graph, the problem is more complex because a cycle is not the only way to violate tree properties; a node having two parents is also invalid.
    1.  First scan and check if any node has two parents (in-degree == 2). Record the two incoming edges.
    2.  If such a node exists, try removing the second edge and run Union-Find on the rest. If no cycle is detected, the second edge is the answer. If a cycle is detected, the first edge must be the answer.
    3.  If no node has two parents, then the graph contains a simple directed cycle. Use standard Union-Find to find the edge that closes the cycle.

### Q2: Can we solve Redundant Connection using DFS?
*   **Answer**: Yes, we can process edges one by one. For each edge `[u, v]`, run DFS starting from `u` to see if we can reach `v`.
    *   If `v` is reachable, then `[u, v]` is the redundant edge.
    *   If not, add the edge `[u, v]` to our adjacency list and continue.
    *   **Drawback**: DFS takes $\mathcal{O}(V + E)$ per edge, making the total complexity $\mathcal{O}(V(V + E)) = \mathcal{O}(V^2)$, which is slower than Union-Find's near-linear complexity.

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain the Incremental Connectivity Advantage**: Emphasize that Union-Find is an **online/incremental** algorithm. If edges were streamed to us one by one over a network socket, Union-Find could detect the cycle instantly without needing to traverse the historical graph. DFS, on the other hand, would have to re-traverse the entire graph from scratch for every incoming edge.
*   **Mention Space Locality Optimization**: In C++, explain that instead of two vectors (`parent` and `rank`), we can store both in a single `std::vector<int> parent` where the root nodes store their rank (or tree size) as a negative value (e.g. `parent[root] = -size`). This reduces allocations, cuts cache footprint by half, and improves processor cache efficiency.
