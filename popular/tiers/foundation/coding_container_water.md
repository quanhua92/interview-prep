# Container With Most Water

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 11, Glassdoor

---

## Question Description

You are given an integer array `height` of length $n$. There are $n$ vertical lines drawn such that the two endpoints of the $i$-th line are $(i, 0)$ and $(i, \text{height}[i])$.

Find two lines that together with the $x$-axis form a container, such that the container contains the most water.

Return *the maximum amount of water a container can store*.

**Notice** that you may not slant the container.

### Examples

*   **Input**: `height = [1,8,6,2,5,4,8,3,7]`
    *   **Output**: `49`
    *   **Explanation**: The vertical lines are represented by array `[1,8,6,2,5,4,8,3,7]`. The max area of water is formed between the vertical line at index 1 ($\text{height} = 8$) and the vertical line at index 8 ($\text{height} = 7$). The width of the container is $8 - 1 = 7$, and the height is $\min(8, 7) = 7$. Thus, the maximum area is $7 \times 7 = 49$.
*   **Input**: `height = [1,1]`
    *   **Output**: `1`
    *   **Explanation**: The width is $1$, height is $1$. The area is $1 \times 1 = 1$.

---

## Detailed Solution (C++)

The problem can be solved in linear time $\mathcal{O}(n)$ using the **Two-Pointer Greedy Approach**. 

1. Initialize two pointers: `left` at the beginning of the array ($0$) and `right` at the end of the array ($n - 1$).
2. Compute the area formed by the vertical lines at `left` and `right`. The area is defined as:
   $$\text{Area} = \min(\text{height}[left], \text{height}[right]) \times (right - left)$$
3. Update the `max_area` found so far.
4. **Greedy Decision Rule**: To maximize the area, we must decide which pointer to move.
   * If $\text{height}[left] < \text{height}[right]$, we increment `left`.
   * If $\text{height}[left] \ge \text{height}[right]$, we decrement `right`.
   * *Rationale*: The width of the container $(right - left)$ will always decrease by $1$ when we move a pointer. To compensate for this decrease in width and potentially find a larger area, we must find a larger height. If we move the pointer that points to the larger height, the maximum height of the new container is still capped by the smaller height, meaning the area is guaranteed to decrease. Thus, the only path to a larger area is to move the pointer pointing to the shorter height.

### Standard C++ Production Code

```cpp
#include <vector>
#include <algorithm>
#include <cstddef>

class Solution {
public:
    int maxArea(const std::vector<int>& height) noexcept {
        // Edge Case: A container requires at least two lines
        if (height.size() < 2) {
            return 0;
        }

        int left = 0;
        int right = static_cast<int>(height.size()) - 1;
        int max_area = 0;

        while (left < right) {
            int h_left = height[left];
            int h_right = height[right];
            
            // Calculate height constrained by the shorter line
            int h = std::min(h_left, h_right);
            int area = h * (right - left);
            
            if (area > max_area) {
                max_area = area;
            }

            // Move the pointer representing the shorter vertical line inward
            if (h_left < h_right) {
                left++;
            } else {
                right--;
            }
        }

        return max_area;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted, iterative Python implementation using standard boundary pointers.

```python
from typing import List

class Solution:
    def maxArea(self, height: List[int]) -> int:
        """
        Calculates the maximum water a container can store.
        
        Time Complexity: O(N)
        Space Complexity: O(1)
        """
        # Edge Case: A container requires at least two lines
        if len(height) < 2:
            return 0

        left: int = 0
        right: int = len(height) - 1
        max_area: int = 0

        while left < right:
            h_left = height[left]
            h_right = height[right]
            
            # Determine the bottleneck height and compute area
            h = min(h_left, h_right)
            area = h * (right - left)
            
            if area > max_area:
                max_area = area
            
            # Greedy step: move the pointer pointing to the shorter bar
            if h_left < h_right:
                left += 1
            else:
                right -= 1

        return max_area
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Built-in Function Overhead vs. Inline Comparisons
* In Python, invoking built-in functions like `min()` and `max()` within a tight loop introduces function call overhead (due to stack frame allocation and argument parsing). 
* For performance-critical code paths, replacing `min(h_left, h_right)` and `max(max_area, area)` with manual `if-else` comparisons can result in a $20\text{–}30\%$ speedup:
  ```python
  # Instead of min/max:
  h = h_left if h_left < h_right else h_right
  area = h * (right - left)
  if area > max_area:
      max_area = area
  ```

### 2. Slicing Operations Avoidance
* Slicing lists in Python via `height[left:right]` copies references, incurring $\mathcal{O}(k)$ time and space overhead. 
* A common pitfall is attempting to find subarrays using slicing. Using index pointers `left` and `right` guarantees true $\mathcal{O}(1)$ auxiliary space complexity.

### 3. Large Integer Representation
* Python 3 handles arbitrary-precision integers natively. Therefore, the multiplication `h * (right - left)` will never result in integer overflow, even for massive data structures.
* However, in C++ or other compiled languages, one must be cautious. Given the constraints $n \le 10^5$ and $\text{height}[i] \le 10^4$, the maximum possible area is $10^9$, which fits safely within standard 32-bit signed integers (up to $\approx 2 \times 10^9$).

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | The algorithm processes each element at most once. In each iteration, either `left` is incremented or `right` is decremented. |
| **Space Complexity** | $\mathcal{O}(1)$ | Only standard pointer index variables and a running maximum area variable are maintained in memory. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Can you mathematically prove that the greedy strategy is correct?
* **Answer**: Yes. Suppose at some step, $\text{height}[left] < \text{height}[right]$. The current area is $\text{height}[left] \times (right - left)$. 
* If we keep `left` fixed and move `right` inward to any new index $k$ (where $left < k < right$), the new width is smaller than the original width ($k - left < right - left$). The new height will be $\min(\text{height}[left], \text{height}[k])$, which is at most $\text{height}[left]$.
* Therefore, the area for any container formed between `left` and $k$ is bounded by:
  $$\text{Area} = \min(\text{height}[left], \text{height}[k]) \times (k - left) \le \text{height}[left] \times (k - left) < \text{height}[left] \times (right - left)$$
* This proves that no container starting at `left` and ending at any index before `right` can yield a larger area than the current one. Thus, we can safely prune all those options by advancing `left` to `left + 1`.

### Q2: How can we skip redundant states in the two-pointer loop?
* **Answer**: If we move `left` or `right` inward, we only care about new heights that are strictly taller than the boundary height we just discarded. If a new element is shorter than or equal to the previous height, it cannot form a larger area because both the height is smaller/equal and the width has shrunk.
* **Optimization (C++)**:
  ```cpp
  if (h_left < h_right) {
      while (left < right && height[left] <= h_left) {
          left++;
      }
  } else {
      while (left < right && height[right] <= h_right) {
          right--;
      }
  }
  ```
* This reduces the number of area recalculations, improving runtime on average cases.

---

## Pro-Tip: How to Impress the Interviewer

* **Proactively Propose the Skip Optimization**: Showing the interviewer the skip optimization loop demonstrates that you understand the geometry of the problem and care about reducing unnecessary computations (e.g., memory lookups and math operations).
* **Discuss CPU Branch Predictor Friendliness**: Note that the standard two-pointer step contains a branch conditional check (`h_left < h_right`). In modern superscalar processors, if the input values are random, this branch is highly mispredicted. If performance is critical, we can analyze how skipping redundant elements limits the number of times we enter the outer loop's branch, maximizing CPU throughput.
* **Explicit Array Size and Signed Cast Checks**: In C++, `height.size() - 1` can lead to unsigned underflow if the input vector is empty. Casting size safely or explicitly handling size checks (`height.size() < 2`) indicates strong defensive coding and attention to system safety.
