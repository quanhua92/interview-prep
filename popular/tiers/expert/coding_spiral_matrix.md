# Spiral Matrix

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 54, Glassdoor

---

## Question Description

Given an $m \times n$ `matrix`, return all elements of the `matrix` in **spiral order**.

### Examples
*   **Input**: `matrix = [[1,2,3],[4,5,6],[7,8,9]]`
    *   **Output**: `[1,2,3,6,9,8,7,4,5]`
*   **Input**: `matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]`
    *   **Output**: `[1,2,3,4,8,12,11,10,9,5,6,7]`

---

## Detailed Solution (C++)

To traverse a matrix spirally, we can simulate the trajectory directly using **four boundaries/pointers**:
1.  `top`: Initialized to `0` (index of the top row).
2.  `bottom`: Initialized to `m - 1` (index of the bottom row).
3.  `left`: Initialized to `0` (index of the leftmost column).
4.  `right`: Initialized to `n - 1` (index of the rightmost column).

In each iteration of the outer loop:
1.  Traverse from `left` to `right` along the `top` row. Then increment `top`.
2.  Traverse from `top` to `bottom` along the `right` column. Then decrement `right`.
3.  **Check Condition**: If `top <= bottom`, traverse from `right` to `left` along the `bottom` row. Then decrement `bottom`.
4.  **Check Condition**: If `left <= right`, traverse from `bottom` to `top` along the `left` column. Then increment `left`.

We repeat this loop until the boundaries overlap (`top > bottom` or `left > right`). The conditional checks inside the loop are crucial to prevent double-processing elements when the remaining subgrid is a single row or a single column.

### Standard C++ Production Code

```cpp
#include <vector>

class Solution {
public:
    std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return {};
        }

        int m = static_cast<int>(matrix.size());
        int n = static_cast<int>(matrix[0].size());
        
        std::vector<int> result;
        result.reserve(m * n); // Pre-allocate memory to avoid vector reallocations

        int top = 0;
        int bottom = m - 1;
        int left = 0;
        int right = n - 1;

        while (top <= bottom && left <= right) {
            // 1. Traverse Right (along the top boundary)
            for (int col = left; col <= right; ++col) {
                result.push_back(matrix[top][col]);
            }
            top++;

            // 2. Traverse Down (along the right boundary)
            for (int row = top; row <= bottom; ++row) {
                result.push_back(matrix[row][right]);
            }
            right--;

            // 3. Traverse Left (along the bottom boundary)
            if (top <= bottom) {
                for (int col = right; col >= left; --col) {
                    result.push_back(matrix[bottom][col]);
                }
                bottom--;
            }

            // 4. Traverse Up (along the left boundary)
            if (left <= right) {
                for (int row = bottom; row >= top; --row) {
                    result.push_back(matrix[row][left]);
                }
                left++;
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
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        """
        Traverses a matrix in spiral order.
        
        Time Complexity: O(M * N)
        Space Complexity: O(1) auxiliary space (excluding the output array).
        """
        if not matrix or not matrix[0]:
            return []
            
        m, n = len(matrix), len(matrix[0])
        result: List[int] = []
        
        top, bottom = 0, m - 1
        left, right = 0, n - 1
        
        while top <= bottom and left <= right:
            # 1. Traverse Right
            for col in range(left, right + 1):
                result.append(matrix[top][col])
            top += 1
            
            # 2. Traverse Down
            for row in range(top, bottom + 1):
                result.append(matrix[row][right])
            right -= 1
            
            # 3. Traverse Left (Only if a valid row remains)
            if top <= bottom:
                for col in range(right, left - 1, -1):
                    result.append(matrix[bottom][col])
                bottom -= 1
                
            # 4. Traverse Up (Only if a valid column remains)
            if left <= right:
                for row in range(bottom, top - 1, -1):
                    result.append(matrix[row][left])
                left += 1
                
        return result
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Pythonic One-Liner (Rotation Trick)
*   Python allows an extremely concise solution using matrix transposition and vertical reversal:
    ```python
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        return matrix and list(matrix.pop(0)) + self.spiralOrder(list(zip(*matrix))[::-1])
    ```
*   **How it works**: It pops the first row, transposes the rest of the matrix, and reverses it vertically (which rotates the rest of the matrix 90 degrees counter-clockwise). This rotation brings the next spiral segment (the rightmost column) to the top row.
*   **Production Note**: While clever, this approach is **unsuitable** for production. `matrix.pop(0)` is an $\mathcal{O}(m)$ operation because list elements must be shifted in memory. Additionally, zipping and slicing creates full copies of the subgrid in each step, taking $\mathcal{O}(m^2 n)$ time and $\mathcal{O}(m \cdot n)$ auxiliary space. Stick to boundary pointers for performance-critical systems.

### 2. Using `range` with Negative Step
*   In Python, looping backwards is done using `range(start, stop, step)` where `step = -1`. Remember that the `stop` parameter is exclusive. 
*   To loop from `right` down to `left` inclusively, write `range(right, left - 1, -1)`.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(m \times n)$ | Every element of the matrix is visited exactly once. |
| **Space Complexity** | $\mathcal{O}(1)$ | Auxiliary space is $\mathcal{O}(1)$ as we only maintain boundary pointers. The output list is not counted. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How would you solve Spiral Matrix II (LeetCode 59)?
*   **Question**: Given a positive integer $n$, generate an $n \times n$ matrix filled with elements from $1$ to $n^2$ in spiral order.
*   **Answer**: 
    1.  Initialize an $n \times n$ grid with zeros.
    2.  Maintain a counter starting at $1$.
    3.  Run the exact same boundary traversal simulation. Instead of reading from the matrix, set `matrix[r][c] = counter` and increment the counter.

### Q2: What happens if the direction is counter-clockwise?
*   **Answer**: Modify the sequence of transitions:
    1.  Traverse Down along the left boundary (`top` to `bottom`).
    2.  Traverse Right along the bottom boundary (`left` to `right`).
    3.  Traverse Up along the right boundary (`bottom` to `top`).
    4.  Traverse Left along the top boundary (`right` to `left`).
*   Adjust boundary increments/decrements accordingly.

---

## Pro-Tip: How to Impress the Interviewer

*   **Pre-allocate Output Vectors**: In C++, always call `result.reserve(m * n)` before beginning the traversal. This prevents the vector from triggering multiple internal reallocations and memory copies as it grows.
*   **Walk Through Single Row/Column Edge Cases**: Proactively trace your code with a $1 \times 5$ matrix or a $5 \times 1$ matrix. Explain how your `top <= bottom` and `left <= right` safety checks prevent the algorithm from traversing the same row or column in reverse, which is the most common bug candidates make.
