# Diagonal Traverse

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 498, Glassdoor

---

## Question Description

Given an $m \times n$ matrix `mat`, return an array of all the elements of the array in a **diagonal order**.

### Examples
*   **Input**: `mat = [[1,2,3],[4,5,6],[7,8,9]]`
    *   **Output**: `[1,2,4,7,5,3,6,8,9]`
*   **Input**: `mat = [[1,2],[3,4]]`
    *   **Output**: `[1,2,3,4]`

---

## Detailed Solution (C++)

There are two primary approaches to traverse a matrix diagonally:

### Method 1: Diagonal Grouping (Hash Map / Bucket Sort style)
Every element in cell $(r, c)$ belongs to the diagonal $d = r + c$.
*   There are $m + n - 1$ diagonals.
*   We can group elements into buckets indexed by their diagonal index $d$.
*   For even-indexed diagonals, we reverse the elements before appending to the result.
*   *Downside*: Requires storing the entire matrix elements in intermediate lists, taking $\mathcal{O}(m \cdot n)$ auxiliary space.

### Method 2: In-Place Boundary Simulation (Optimal $\mathcal{O}(1)$ Space)
We maintain a coordinate pointer `(r, c)` and a direction flag `up` (representing up-right movement).
*   If `up == true` (direction is up-right: `r--, c++`):
    *   If we reach the rightmost column (`c == n - 1`), we must step down to the next row (`r++`) and flip the direction.
    *   If we reach the topmost row (`r == 0`), we step right to the next column (`c++`) and flip the direction.
    *   Otherwise, we move diagonally up-right: `r--, c++`.
*   If `up == false` (direction is down-left: `r++, c--`):
    *   If we reach the bottommost row (`r == m - 1`), we step right to the next column (`c++`) and flip the direction.
    *   If we reach the leftmost column (`c == 0`), we step down to the next row (`r++`) and flip the direction.
    *   Otherwise, we move diagonally down-left: `r++, c--`.

This method runs in $\mathcal{O}(m \cdot n)$ time and requires strictly $\mathcal{O}(1)$ auxiliary space.

### Standard C++ Production Code

```cpp
#include <vector>

class Solution {
public:
    std::vector<int> findDiagonalOrder(std::vector<std::vector<int>>& mat) {
        if (mat.empty() || mat[0].empty()) {
            return {};
        }

        int m = static_cast<int>(mat.size());
        int n = static_cast<int>(mat[0].size());
        
        std::vector<int> result;
        result.reserve(m * n);

        int r = 0, c = 0;
        bool up = true; // True for up-right direction, false for down-left

        for (int i = 0; i < m * n; ++i) {
            result.push_back(mat[r][c]);

            if (up) {
                // If moving up-right
                if (c == n - 1) {
                    // Reached right boundary -> move down and switch direction
                    r++;
                    up = false;
                } else if (r == 0) {
                    // Reached top boundary -> move right and switch direction
                    c++;
                    up = false;
                } else {
                    r--;
                    c++;
                }
            } else {
                // If moving down-left
                if (r == m - 1) {
                    // Reached bottom boundary -> move right and switch direction
                    c++;
                    up = true;
                } else if (c == 0) {
                    // Reached left boundary -> move down and switch direction
                    r++;
                    up = true;
                } else {
                    r++;
                    c--;
                }
            }
        }

        return result;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

```python
from typing import List

class Solution:
    def findDiagonalOrder(self, mat: List[List[int]]) -> List[int]:
        """
        Traverses a matrix diagonally in-place.
        
        Time Complexity: O(M * N)
        Space Complexity: O(1) auxiliary space (excluding the output array).
        """
        if not mat or not mat[0]:
            return []
            
        m, n = len(mat), len(mat[0])
        result: List[int] = []
        
        r, c = 0, 0
        up = True
        
        for _ in range(m * n):
            result.append(mat[r][c])
            
            if up:
                if c == n - 1:
                    r += 1
                    up = False
                elif r == 0:
                    c += 1
                    up = False
                else:
                    r -= 1
                    c += 1
            else:
                if r == m - 1:
                    c += 1
                    up = True
                elif c == 0:
                    r += 1
                    up = True
                else:
                    r += 1
                    c -= 1
                    
        return result
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Hash Map Dictionary grouping overhead
*   A common Python approach uses a dictionary of lists: `diagonals = collections.defaultdict(list)`.
*   While simple, this performs $\mathcal{O}(m \cdot n)$ lookups, inserts, and list-appends. In Python, dictionary hashing and dynamic list growth add significant runtime overhead and trigger high garbage collection frequency.
*   The in-place pointer simulation method avoids any dictionary lookups and handles all updates via primitive pointer manipulations, making it significantly faster in Python.

### 2. Boundary Condition Ordering
*   In the simulation, the order of boundary checks is critical. 
*   When moving up-right, we must check the right boundary (`c == n - 1`) **before** the top boundary (`r == 0`). If we hit the top-right corner of the matrix, both conditions are met. If we incorrectly process the top boundary first, we would increment `c` (getting `c == n`), resulting in an immediate out-of-bounds error on the next access.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(m \times n)$ | We visit every coordinate $(r, c)$ in the matrix exactly once. |
| **Space Complexity** | $\mathcal{O}(1)$ | The in-place pointer simulation operates with only a few scalar variables. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How would you generalize this to a 3D Tensor?
*   **Answer**: In a 3D matrix (dimensions $X \times Y \times Z$), a diagonal slice corresponds to cells where the sum of indices $i + j + k = d$ is constant.
*   We can group cells by their index sum $d \in [0, X + Y + Z - 3]$. For each diagonal level $d$, we traverse the 2D plane slice, reversing the order on alternating steps to create a serpentine 3D diagonal traverse.

### Q2: What if the matrix is too large to fit in memory?
*   **Answer**: To process the matrix in a streaming fashion (e.g. from disk), we don't need the entire matrix in memory at once.
*   Observe that a diagonal $d$ only accesses cells where $r + c = d$, which corresponds to rows $r \in [\max(0, d - n + 1), \min(m - 1, d)]$.
*   Thus, we only need to keep at most $\min(m, n)$ rows in memory at any point. We can load and discard rows dynamically as the active diagonal window slides forward.

---

## Pro-Tip: How to Impress the Interviewer

*   **Highlight Corner Bug Avoidance**: Explicitly point out the top-right and bottom-left corner overlap scenarios to the interviewer. Showing that you consciously ordered the check `if c == n - 1` before `elif r == 0` demonstrates deep attention to detail and proactive defense against out-of-bounds errors.
*   **Discuss CPU Pipeline Friendliness**: Explain that while Method 2 is optimal in space, Method 1 (grouping) has simpler branching structures inside the loops. Method 2 has multiple branch points which can cause CPU **branch mispredictions**. For small matrices, Method 1 might actually execute faster due to predictable branch instructions, although it uses more memory.
