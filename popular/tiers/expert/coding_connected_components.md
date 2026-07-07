# Number of Connected Components in an Undirected Graph

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 323, Glassdoor

---

## Question Description

You have a graph of `n` nodes. You are given an integer `n` and an array `edges` where `edges[i] = [ai, bi]` indicates that there is an undirected edge between `ai` and `bi` in the graph.

Return the number of connected components in the graph.

### Examples
*   **Input**: `n = 5`, `edges = [[0,1],[1,2],[3,4]]`
    *   **Output**: `2`
*   **Input**: `n = 5`, `edges = [[0,1],[1,2],[2,3],[3,4]]`
    *   **Output**: `1`

---

## Detailed Solution (C++)

While this problem can be solved using standard graph traversals (DFS or BFS), the **Disjoint Set Union (DSU / Union-Find)** data structure is particularly well-suited. DSU operates directly on edges without needing to construct an explicit adjacency list, saving heap allocation overhead.

**DSU Optimization Techniques**:
1.  **Path Compression**: In `find(x)`, we set the parent of `x` directly to the root of its set: `parent[x] = find(parent[x])`. This flattens the tree structure, ensuring subsequent queries run in near constant time.
2.  **Union by Rank (or Size)**: We attach the shorter tree (smaller rank) under the root of the taller tree. This keeps the tree height minimal.

We start with `n` individual components. For each edge, we attempt to `union` the two endpoints. If they belong to different components, we merge them and decrement the component count by $1$. If they are already in the same component, we ignore the edge.

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
    UnionFind(int n) : parent(n), rank(n, 0) {
        std::iota(parent.begin(), parent.end(), 0); // parent[i] = i
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
            return false; // Already in the same component
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
    int countComponents(int n, std::vector<std::vector<int>>& edges) {
        UnionFind uf(n);
        int components = n;

        for (const auto& edge : edges) {
            if (uf.unite(edge[0], edge[1])) {
                components--;
            }
        }

        return components;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

```python
from typing import List

class UnionFind:
    def __init__(self, n: int):
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, x: int) -> int:
        if self.parent[x] != x:
            # Recursive path compression
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x: int, y: int) -> bool:
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x == root_y:
            return False
        
        # Union by rank
        if self.rank[root_x] < self.rank[root_y]:
            self.parent[root_x] = root_y
        else:
            self.parent[root_y] = root_x
            if self.rank[root_x] == self.rank[root_y]:
                self.rank[root_x] += 1
        return True

class Solution:
    def countComponents(self, n: int, edges: List[List[int]]) -> int:
        """
        Calculates the number of connected components in an undirected graph using Union-Find.
        
        Time Complexity: O(V + E * alpha(V)) where alpha is the Inverse Ackermann function.
        Space Complexity: O(V) to store parent and rank.
        """
        uf = UnionFind(n)
        components = n
        
        for u, v in edges:
            if uf.union(u, v):
                components -= 1
                
        return components
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Recursion Limit during Path Compression
*   In Python, deep recursion can hit the system stack limit. However, because of Union by Rank, the height of any Union-Find tree is bounded by $\mathcal{O}(\log n)$, and with path compression, it is effectively $\mathcal{O}(\alpha(n)) \le 5$ in practice.
*   Therefore, the recursive implementation of `find` is safe and will not cause a `RecursionError` for any practical graph size.

### 2. Space Efficiency over DFS/BFS
*   DFS/BFS requires constructing an adjacency list representation of the graph (e.g. `dict[int, list[int]]`). In Python, this involves creating $V$ list objects and $2E$ references, introducing significant memory overhead.
*   The DSU implementation processes edges in-place and only requires two flat lists (`parent` and `rank`) of size $V$, resulting in a highly optimized memory footprint.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(V + E \cdot \alpha(V))$ | Union and find operations run in amortized $\mathcal{O}(\alpha(V))$ time, where $\alpha$ is the Inverse Ackermann function (practically constant, $\le 5$). |
| **Space Complexity** | $\mathcal{O}(V)$ | Requires $\mathcal{O}(V)$ space to maintain the parent and rank arrays. No adjacency list or recursion stack is needed. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What is the relative trade-off between DFS/BFS and Union-Find for this problem?
*   **Answer**:
    *   **DFS/BFS**: Best if we already have the graph represented as an adjacency list. The time complexity is strictly $\mathcal{O}(V + E)$. However, if we are given raw edges, constructing the adjacency list requires extra time and $\mathcal{O}(V + E)$ auxiliary memory.
    *   **Union-Find**: Best if we receive the edges in a stream or if memory is restricted. It processes edges directly, requiring only $\mathcal{O}(V)$ auxiliary memory. It is also easily parallelizable and supports dynamic graph updates.

### Q2: How can we track the size of the largest connected component during unions?
*   **Answer**: We can replace the `rank` array with a `size` array initialized to `1` for all nodes.
    *   When we perform `union(root_x, root_y)`, we update: `size[root_x] += size[root_y]` and set `parent[root_y] = root_x`.
    *   We track a global `max_size` variable that is updated to `max(max_size, size[root_x])` whenever a union occurs.

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain Inverse Ackermann $\alpha$**: Don't just say the time complexity is $\mathcal{O}(1)$ or $\mathcal{O}(\log^* n)$ (log-star). Clarify that path compression combined with union by rank gives $\mathcal{O}(\alpha(n))$, where $\alpha$ is the Inverse Ackermann function. Mention that for all practical values (up to $2^{2^{65536}}$), $\alpha(n) \le 5$, making it virtually constant.
*   **Demonstrate Direct Heap Savings**: Highlight that because Union-Find does not build an adjacency list, it avoids allocating many small container nodes (vector fragments in C++ or list/dict buckets in Python). This improves L1 cache spatial locality and drastically reduces GC (garbage collection) pressure in managed environments like Python or JVM.
