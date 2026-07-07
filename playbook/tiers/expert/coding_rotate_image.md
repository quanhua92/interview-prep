# Rotate Image

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 48, Glassdoor
- **Flashcards**: [Matrix Traversal deck](../../flash_cards/coding/matrix_traversal.md)

---

## Question Description

You are given an $n \times n$ 2D `matrix` representing an image, rotate the image by **90 degrees (clockwise)**.

You have to rotate the image **in-place**, which means you have to modify the input 2D matrix directly. **DO NOT** allocate another 2D matrix and do the rotation.

### Examples
*   **Input**: `matrix = [[1,2,3],[4,5,6],[7,8,9]]`
    *   **Output**: `[[7,4,1],[8,5,2],[9,6,3]]`
*   **Input**: `matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]`
    *   **Output**: `[[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]`

---

## Detailed Solution (C++)

There are two primary ways to perform an in-place 90-degree clockwise rotation of an $n \times n$ matrix:

### Method 1: Transpose and Reverse (Elegant & Highly Readable)
1.  **Transpose the matrix**: Swap elements across the main diagonal (`matrix[i][j]` with `matrix[j][i]` for $j > i$).
2.  **Reverse each row**: Reverse the elements in each row horizontally.

Mathematically, transposing changes cell $(i, j)$ to $(j, i)$. Reversing the rows flips the columns, converting $(j, i)$ to $(j, n - 1 - i)$. This maps exactly to a 90-degree clockwise rotation: $(i, j) \to (j, n - 1 - i)$.

### Method 2: Shell/Ring-by-Ring Rotation (Single Pass)
Iterate layer by layer from the outermost boundary to the center. For each layer:
*   Perform a 4-way swap of corresponding elements:
    *   `top-left` $\to$ `top-right`
    *   `top-right` $\to$ `bottom-right`
    *   `bottom-right` $\to$ `bottom-left`
    *   `bottom-left` $\to$ `top-left`

This method avoids visiting cells multiple times and is more cache-friendly.

### Standard C++ Production Code

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    void rotate(std::vector<std::vector<int>>& matrix) {
        // Edge Case: 1x1 or empty matrix
        if (matrix.empty() || matrix[0].empty()) {
            return;
        }

        int n = static_cast<int>(matrix.size());

        // Step 1: Transpose the matrix
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }

        // Step 2: Reverse each row
        for (int i = 0; i < n; ++i) {
            std::reverse(matrix[i].begin(), matrix[i].end());
        }
    }

    // Alternative: Single-pass ring rotation
    void rotateSinglePass(std::vector<std::vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return;
        int n = static_cast<int>(matrix.size());

        for (int i = 0; i < n / 2; ++i) {
            int first = i;
            int last = n - 1 - i;
            for (int j = first; j < last; ++j) {
                int offset = j - first;
                
                int top = matrix[first][j]; // Save top
                
                // left -> top
                matrix[first][j] = matrix[last - offset][first];

                // bottom -> left
                matrix[last - offset][first] = matrix[last][last - offset];

                // right -> bottom
                matrix[last][last - offset] = matrix[j][last];

                // top -> right
                matrix[j][last] = top;
            }
        }
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

```python
from typing import List

class Solution:
    def rotate(self, matrix: List[List[int]]) -> None:
        """
        Rotates the matrix 90 degrees clockwise in-place.
        Do not return anything, modify matrix in-place instead.
        
        Time Complexity: O(N^2)
        Space Complexity: O(1)
        """
        if not matrix or not matrix[0]:
            return
            
        n = len(matrix)
        
        # Step 1: Transpose (swap across diagonal)
        for i in range(n):
            for j in range(i + 1, n):
                matrix[i][j], matrix[j][i] = matrix[j][i], matrix[i][j]
                
        # Step 2: Reverse each row
        for row in matrix:
            row.reverse()
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. In-Place Modification vs Reference Assignment
*   A common Python pitfall is reassigning the matrix variable: `matrix = [...]`. 
*   In LeetCode or standard APIs, the caller retains the reference to the original list object. Reassigning the local variable `matrix` only binds it to a new object within the local scope, leaving the caller's matrix unchanged.
*   To modify the list content while keeping the same object, use slice assignment `matrix[:] = ...`, or modify elements in-place using loops / built-in methods like `row.reverse()`.

### 2. Pythonic Short-Hand: `matrix[:] = zip(*matrix[::-1])`
*   In Python, you can write a one-liner to rotate the matrix:
    ```python
    matrix[:] = [list(row) for row in zip(*matrix[::-1])]
    ```
*   **How it works**: `matrix[::-1]` reverses the rows vertically. `zip(*...)` unpacks the rows and zips them together, transposing the vertically reversed rows.
*   **Production Note**: While elegant, this creates new tuple/list objects under the hood, violating the $\mathcal{O}(1)$ auxiliary space constraint. Explain this trade-off to the interviewer.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n^2)$ | We visit every cell in the $n \times n$ matrix a constant number of times (at most twice). |
| **Space Complexity** | $\mathcal{O}(1)$ | All swaps are performed in-place using constant auxiliary memory. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How would you rotate the matrix 90 degrees counter-clockwise?
*   **Answer**: 
    *   **Method 1**: Reverse each row horizontally first, then transpose.
    *   **Method 2**: Transpose first, then reverse the rows vertically (reverse the matrix order of rows).
    *   **Python Code (One-liner)**:
        ```python
        matrix[:] = [list(row) for row in zip(*matrix)][::-1]
        ```

### Q2: How would you rotate a non-square $m \times n$ matrix in-place?
*   **Answer**: In-place rotation of a non-square matrix is highly challenging because the dimensions change (e.g., $3 \times 4$ becomes $4 \times 3$), shifting the memory layout of rows.
*   If extra space is allowed, it is trivial: `new_matrix[j][m - 1 - i] = matrix[i][j]`.
*   To do it in-place, it requires cycle-following permutations on a flattened array representation, which is a mathematically intensive process (similar to in-place transposition of rectangular matrices).

---

## Pro-Tip: How to Impress the Interviewer

*   **Highlight Cache Locality and Strides**: 
    *   Explain that during transposition, accessing `matrix[j][i]` involves column-wise traversal. In C++ and Python (where 2D vectors are arrays of pointers/lists), this causes cache misses because the next element is not contiguous in memory.
    *   For large matrices, we can optimize cache locality using **blocked transposition** (processing the matrix in small sub-blocks of size $B \times B$, e.g., $16 \times 16$), which fits entirely within the L1/L2 cache lines.
*   **Avoid Temporary List Creation**: Point out that solutions using `zip(*matrix)` are not truly in-place as they allocate $\mathcal{O}(n^2)$ memory for the tuples. The explicit double-loop swap method is preferred for production-grade, memory-constrained environments.
