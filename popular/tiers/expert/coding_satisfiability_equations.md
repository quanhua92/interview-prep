# Satisfiability of Equality Equations

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 990, Glassdoor

---

## Question Description

You are given an array of strings `equations` that represent relationships between variables where each string `equations[i]` is of length `4` and takes one of two different forms: `"xi==yi"` or `"xi!=yi"`. Here, `xi` and `yi` are lowercase letters (not necessarily different) that represent one-letter variable names.

Return `true` if it is possible to assign integers to variable names so as to satisfy all the given equations, or `false` otherwise.

### Examples
*   **Input**: `equations = ["a==b","b!=a"]`
    *   **Output**: `false`
    *   **Explanation**: If we assign $a = 1$ and $b = 1$, the first equation is satisfied, but not the second. There is no way to assign the variables to satisfy both.
*   **Input**: `equations = ["b==a","a==b"]`
    *   **Output**: `true`
    *   **Explanation**: We could assign $a = 1$ and $b = 1$ to satisfy both equations.

---

## Detailed Solution (C++)

The problem asks us to determine if a system of equality and inequality constraints is consistent.
1.  **Equality is an Equivalence Relation**: Equality is reflexive, symmetric, and transitive. This means we can group variables that are equal to each other into connected components (equivalence classes).
2.  **Disjoint Set Union (DSU)**:
    *   In the first pass, we process all equations of the form `xi == yi` and union the sets containing `xi` and `yi`.
    *   In the second pass, we process all equations of the form `xi != yi`. If `find(xi) == find(yi)`, they are in the same equivalence class, which means we have determined they must be equal. Since the equation states they are *not* equal, this is a contradiction. We return `false`.
    *   If no contradiction is found after checking all inequality equations, we return `true`.

Since all variables are lowercase letters (`'a'` to `'z'`), the total number of elements is fixed at $26$. This makes DSU extremely fast and space-efficient.

### Standard C++ Production Code

```cpp
#include <vector>
#include <string>
#include <numeric>
#include <utility>

class UnionFind {
private:
    int parent[26];
    int rank[26];

public:
    UnionFind() {
        for (int i = 0; i < 26; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            // Union by rank
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                if (rank[rootX] == rank[rootY]) {
                    rank[rootX]++;
                }
            }
        }
    }
};

class Solution {
public:
    bool equationsPossible(std::vector<std::string>& equations) {
        UnionFind uf;

        // First pass: Process all equality equations
        for (const auto& eq : equations) {
            if (eq[1] == '=') {
                int u = eq[0] - 'a';
                int v = eq[3] - 'a';
                uf.unite(u, v);
            }
        }

        // Second pass: Validate against inequality equations
        for (const auto& eq : equations) {
            if (eq[1] == '!') {
                int u = eq[0] - 'a';
                int v = eq[3] - 'a';
                if (uf.find(u) == uf.find(v)) {
                    return false; // Contradiction: u and v must be equal, but are declared unequal
                }
            }
        }

        return true;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

```python
from typing import List

class UnionFind:
    def __init__(self):
        self.parent = list(range(26))
        self.rank = [0] * 26

    def find(self, x: int) -> int:
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x]) # Path compression
        return self.parent[x]

    def union(self, x: int, y: int) -> None:
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x != root_y:
            if self.rank[root_x] < self.rank[root_y]:
                self.parent[root_x] = root_y
            else:
                self.parent[root_y] = root_x
                if self.rank[root_x] == self.rank[root_y]:
                    self.rank[root_x] += 1

class Solution:
    def equationsPossible(self, equations: List[str]) -> bool:
        """
        Determines the satisfiability of equality and inequality constraints.
        
        Time Complexity: O(N * alpha(26)) = O(N) where N is the number of equations.
        Space Complexity: O(1) auxiliary space (fixed at 26 variables).
        """
        uf = UnionFind()
        
        # Pass 1: Union variables that are equal
        for eq in equations:
            if eq[1] == '=':
                u = ord(eq[0]) - ord('a')
                v = ord(eq[3]) - ord('a')
                uf.union(u, v)
                
        # Pass 2: Check for contradictions against unequal variables
        for eq in equations:
            if eq[1] == '!':
                u = ord(eq[0]) - ord('a')
                v = ord(eq[3]) - ord('a')
                if uf.find(u) == uf.find(v):
                    return False
                    
        return True
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Fixed Range vs Map for Dynamic Variables
*   Because the variable set is constrained to lowercase letters `a`-`z`, we map variables directly to the integer range $0$–$25$ using `ord(char) - ord('a')`.
*   If variables were arbitrary alphanumeric strings or variable-length identifiers, we would use a Python `dict` to map strings to unique sequential IDs, or implement the parent/rank arrays directly using dictionaries:
    ```python
    self.parent = {}
    def find(self, x: str) -> str:
        if x not in self.parent:
            self.parent[x] = x
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    ```

### 2. String Slicing and String Indices
*   In Python, strings are immutable arrays of Unicode code points. Accessing a character by index, e.g., `eq[0]` and `eq[3]`, is an $\mathcal{O}(1)$ operation. 
*   Avoid using string slicing (like `eq[0:1]`) as it creates a new string object, which is slower and uses more heap memory.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(N)$ | $N$ is the number of equations. DSU operations on a set of size $26$ run in $\mathcal{O}(\alpha(26))$ which is $O(1)$ constant time. |
| **Space Complexity** | $\mathcal{O}(1)$ | The parent and rank arrays are fixed at size $26$, using constant auxiliary space. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if equations can be entered dynamically in a stream, and we need to validate query relationships on the fly?
*   **Answer**: 
    *   For equalities, Union-Find handles dynamic streaming perfectly.
    *   For inequalities, we can maintain an **adjacently list of inequalities** for each disjoint set representative.
    *   When we receive `A != B`, we find their representatives `root_A` and `root_B`. If `root_A == root_B`, we reject. Otherwise, we record `root_A` and `root_B` as mutually unequal by adding each to the other's "unequal" set.
    *   When we receive `A == B`, we find `root_A` and `root_B`. Before merging, we verify that `root_B` is not in the "unequal" set of `root_A`. If they are compatible, we union them and merge their "unequal" sets.

### Q2: Can we solve this problem using DFS/BFS?
*   **Answer**: Yes. We can treat equalities as undirected edges and build an adjacency list.
    1.  Perform DFS/BFS on all unvisited nodes to assign a unique component ID (or color) to each variable.
    2.  For each inequality `u != v`, verify if `u` and `v` have different component IDs. If they have the same ID, return `false`.
    *   **DSU vs DFS**: DSU is much cleaner here as it does not require building an explicit adjacency list and has a smaller memory overhead.

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention Compile-Time Array Sizes**: In C++, declare parent and rank arrays as fixed-size arrays on the stack (`int parent[26]`) rather than heap-allocated vectors (`std::vector<int>`). Stack allocation is instantaneous (essentially adjusting the stack pointer), avoids cache fragmentation, and does not require heap cleanups.
*   **Explain the Equivalence Partitioning concept**: Describe how equality relations partitions the variable space into disjoint equivalence classes. This connects the problem directly to the mathematical foundation of equivalence relations, showing a solid academic and theoretical background.
