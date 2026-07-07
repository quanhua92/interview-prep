# Construct Quad Tree

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 427, Glassdoor

---

## Question Description

Given an $n \times n$ matrix `grid` of `0`s and `1`s only, represent the grid using a **Quad-Tree**. Return the root of the Quad-Tree.

A Quad-Tree is a tree data structure in which each internal node has exactly four children: `topLeft`, `topRight`, `bottomLeft`, and `bottomRight`. In addition, each node contains two attributes:
*   `val`: `True` if the node represents a grid of all `1`s, or `False` if the node represents a grid of all `0`s. (Can be any value if the node is not a leaf).
*   `isLeaf`: `True` if the node is a leaf node, or `False` if the node has four children.

### Quad-Tree Construction Algorithm
1. If the current grid has the same value (all `1`s or all `0`s), set `isLeaf` to `True`, set `val` to the value of the grid, and set all four children to `NULL`.
2. If the current grid has different values, set `isLeaf` to `False`, set `val` to any value (usually `True`), and divide the grid into four sub-grids of size $n/2 \times n/2$. Recursively construct the four children nodes.

### Examples
*   **Input**: `grid = [[0,1],[1,0]]`
    *   **Output**: `[[0,1],[1,0],[1,1],[1,1],[1,0]]`
    *   **Explanation**: The grid contains different values, so we split it into 4 quadrants. Each quadrant of size $1 \times 1$ becomes a leaf node.
*   **Input**: `grid = [[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0]]`
    *   **Output**: `[[0,1],[1,1],[0,1],[1,1],[1,0],null,null,null,null,[1,0],[1,0],[1,1],[1,1]]`

---

## Detailed Solution (C++)

The recursive **Divide and Conquer** approach is natural for Quad-Tree construction. We can implement it in two ways:
1. **Top-Down with Prefix Sums ($\mathcal{O}(n^2)$)**: We precompute a 2D prefix sum array. To check if a region is uniform, we query its sum in $\mathcal{O}(1)$ time. If the sum is $0$ or $\text{size}^2$, the region is uniform.
2. **Bottom-Up Optimization ($\mathcal{O}(n^2)$)**: We recursively build the four quadrants first. If all four quadrants are leaves and share the same value, we merge them into a single leaf node. Otherwise, we keep them as separate children. This avoids any redundant checks or prefix sum tables.

### Standard C++ Production Code (Bottom-Up $\mathcal{O}(n^2)$)

```cpp
#include <vector>

// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;
    
    Node() : val(false), isLeaf(false), topLeft(nullptr), topRight(nullptr), bottomLeft(nullptr), bottomRight(nullptr) {}
    
    Node(bool _val, bool _isLeaf) 
        : val(_val), isLeaf(_isLeaf), topLeft(nullptr), topRight(nullptr), bottomLeft(nullptr), bottomRight(nullptr) {}
    
    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) 
        : val(_val), isLeaf(_isLeaf), topLeft(_topLeft), topRight(_topRight), bottomLeft(_bottomLeft), bottomRight(_bottomRight) {}
};

class Solution {
public:
    Node* construct(std::vector<std::vector<int>>& grid) {
        if (grid.empty()) return nullptr;
        return build(grid, 0, 0, static_cast<int>(grid.size()));
    }

private:
    Node* build(std::vector<std::vector<int>>& grid, int r, int c, int size) {
        if (size == 1) {
            return new Node(grid[r][c] == 1, true);
        }
        
        int half = size / 2;
        Node* tl = build(grid, r, c, half);
        Node* tr = build(grid, r, c + half, half);
        Node* bl = build(grid, r + half, c, half);
        Node* br = build(grid, r + half, c + half, half);
        
        // If all four children are leaf nodes and have the same value, merge them
        if (tl->isLeaf && tr->isLeaf && bl->isLeaf && br->isLeaf &&
            tl->val == tr->val && tr->val == bl->val && bl->val == br->val) {
            bool value = tl->val;
            delete tl; delete tr; delete bl; delete br; // Prevent memory leaks
            return new Node(value, true);
        }
        
        return new Node(true, false, tl, tr, bl, br);
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code (Bottom-Up $\mathcal{O}(n^2)$)

```python
from typing import List

# Definition for a QuadTree node.
class Node:
    def __init__(self, val: bool, isLeaf: bool, topLeft: 'Node' = None, topRight: 'Node' = None, bottomLeft: 'Node' = None, bottomRight: 'Node' = None):
        self.val = val
        self.isLeaf = isLeaf
        self.topLeft = topLeft
        self.topRight = topRight
        self.bottomLeft = bottomLeft
        self.bottomRight = bottomRight

class Solution:
    def construct(self, grid: List[List[int]]) -> 'Node':
        """
        Constructs a Quad-Tree from a 2D grid using a bottom-up divide and conquer approach.
        
        Time Complexity: O(n^2)
        Space Complexity: O(log n) call stack space
        """
        if not grid:
            return None
        return self._build(grid, 0, 0, len(grid))

    def _build(self, grid: List[List[int]], r: int, c: int, size: int) -> 'Node':
        if size == 1:
            return Node(grid[r][c] == 1, True)
        
        half = size // 2
        tl = self._build(grid, r, c, half)
        tr = self._build(grid, r, c + half, half)
        bl = self._build(grid, r + half, c, half)
        br = self._build(grid, r + half, c + half, half)
        
        # Check if all four children are leaf nodes and have the same value
        if tl.isLeaf and tr.isLeaf and bl.isLeaf and br.isLeaf:
            if tl.val == tr.val == bl.val == br.val:
                return Node(tl.val, True)
                
        return Node(True, False, tl, tr, bl, br)
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Object Allocation Overhead
*   Python's class instantiation (`Node(...)`) has significantly higher CPU overhead compared to C++ because it creates dictionary entries for `__dict__` dynamically. For large grids, memory footprint increases fast. 
*   Adding `__slots__ = ['val', 'isLeaf', 'topLeft', 'topRight', 'bottomLeft', 'bottomRight']` to the `Node` definition restricts dynamic attribute creation, reducing memory footprint by up to 50-70%.

### 2. Tail Call Elimination
*   Python doesn't optimize tail-recursive calls, meaning the stack frames grow proportional to the height of the tree ($\mathcal{O}(\log n)$). Since $n \le 64$, the maximum depth is $\approx 6$, so it is perfectly safe from stack overflow.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n^2)$ | Bottom-up compares and merges adjacent blocks. Each element in the $n \times n$ grid is visited once. |
| **Space Complexity** | $\mathcal{O}(\log n)$ | Auxiliary stack space is proportional to tree depth ($\log n$). |

---

## Common Follow-Up Questions & How to Answer

### Q1: What is the benefit of a Quad-Tree over a flat grid?
*   **Answer**: Quad-Trees are highly effective for **spatial partitioning** and **image compression**. If an image has large regions of uniform color (e.g. background sky), a Quad-Tree collapses millions of pixels into single leaf nodes, saving significant memory and accelerating spatial queries like collision detection.

### Q2: How can we implement this iteratively?
*   **Answer**: An iterative approach involves maintaining a stack or queue, but bottom-up merges are difficult to schedule iteratively. A top-down approach with 2D prefix sums allows us to easily push grid coordinates `(r, c, size)` onto a queue, query uniformity in $\mathcal{O}(1)$, and construct nodes level-by-level without recursive backtracking.

---

## Pro-Tip: How to Impress the Interviewer

*   **Prevent Memory Leaks in C++**: Point out that when merging four child nodes in C++, you must explicitly call `delete` on the child pointers to avoid memory leaks. Python has automatic garbage collection, but in systems languages like C++, neglecting to deallocate merged child nodes results in memory leaks.
*   **2D Prefix Sum Formula**: Explain how to compute the sum of any subarray in $\mathcal{O}(1)$:
    $$\text{Sum} = P[r_2][c_2] - P[r_1-1][c_2] - P[r_2][c_1-1] + P[r_1-1][c_1-1]$$
    This demonstrates advanced structural understanding of multidimensional algorithms.
