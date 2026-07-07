# Largest Rectangle in Histogram

- **Category**: Coding
- **Difficulty**: Hard
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 84, Glassdoor

---

## Question Description

Given an array of integers `heights` representing the histogram's bar height where the width of each bar is `1`, return the area of the largest rectangle in the histogram.

### Examples

*   **Input**: `heights = [2,1,5,6,2,3]`
    *   **Output**: `10`
    *   **Explanation**: The largest rectangle is formed by the bars `[5, 6]` with a height of `5` and a width of `2`, yielding an area of $5 \times 2 = 10$ units.
*   **Input**: `heights = [2,4]`
    *   **Output**: `4`
    *   **Explanation**: The largest rectangle is formed by the bar `[4]` with a height of `4` and a width of `1` (or two bars of height `2` and width `2`), yielding an area of `4` units.

---

## Detailed Solution (C++)

The optimal approach utilizes a **Monotonic Stack**. We maintain a stack that stores indices of the bars in a strictly increasing order of their heights. 

When we encounter a bar that is shorter than the bar at the top of the stack, we know that the bar at the top of the stack cannot extend further to the right. We then pop the top elements from the stack and compute the area of the rectangles that can be formed using each popped bar as the height:
1. The **height** of the rectangle is the height of the popped bar.
2. The **width** of the rectangle is determined by the current index `i` (which is the right boundary) and the index of the new top element of the stack (which is the left boundary). If the stack becomes empty after popping, the width is simply `i`.
3. To avoid cleanup code after the loop, we process a virtual sentinel element of height `0` at index `n` (where `n` is the length of `heights`). This forces all remaining elements in the stack to be popped and processed.

### Standard C++ Production Code

```cpp
#include <vector>
#include <algorithm>
#include <cstddef>

class Solution {
public:
    int largestRectangleArea(std::vector<int>& heights) {
        // Edge Case: Explicitly handle empty input to prevent unsigned underflow
        if (heights.empty()) {
            return 0;
        }

        const int n = static_cast<int>(heights.size());
        std::vector<int> stack;
        stack.reserve(n); // Pre-allocate memory to prevent reallocation overhead
        int max_area = 0;

        for (int i = 0; i <= n; ++i) {
            // Use 0 as a sentinel value at i == n to flush the stack
            int current_height = (i < n) ? heights[i] : 0;

            while (!stack.empty() && current_height < heights[stack.back()]) {
                int height = heights[stack.back()];
                stack.pop_back();

                // If stack is empty, the popped bar was the shortest bar seen so far,
                // so it can span from index 0 to i - 1 (width = i)
                int width = stack.empty() ? i : i - stack.back() - 1;
                max_area = std::max(max_area, height * width);
            }
            stack.push_back(i);
        }

        return max_area;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation using the monotonic stack with a sentinel value.

```python
from typing import List

class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        """
        Calculates the area of the largest rectangle in a histogram.
        
        Time Complexity: O(N)
        Space Complexity: O(N)
        """
        if not heights:
            return 0

        # Append a sentinel height 0 to flush out all indices from the stack at the end
        extended_heights = heights + [0]
        stack: List[int] = []
        max_area = 0

        for i, h in enumerate(extended_heights):
            while stack and h < extended_heights[stack[-1]]:
                height = extended_heights[stack.pop()]
                # If stack is empty, this bar was the smallest so far, so width is i.
                # Otherwise, the width is the distance between current index i and the 
                # new top element on the stack minus 1.
                width = i if not stack else i - stack[-1] - 1
                max_area = max(max_area, height * width)
            stack.append(i)

        return max_area
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Sentinel List Concatenation vs. Explicit Flushing
* In Python, `heights + [0]` creates a new list, which takes $\mathcal{O}(n)$ time and auxiliary space. While this is clean and concise, in memory-constrained environments or with extremely large inputs, it is better to avoid copying.
* Alternatively, we can iterate up to `len(heights)` and dynamically return `0` for the out-of-bound index to avoid creating a new list.

### 2. Efficiency of Stack Operations
* Python `list` acts as a dynamic array. Popping from the end via `pop()` and appending via `append()` are amortized $\mathcal{O}(1)$ operations.
* Avoid using `list.pop(0)` or `collections.deque` if only accessing the end, as `deque` has higher constant factor allocation overhead in Python compared to a pre-allocated/dynamic list.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | Each index is pushed onto the stack exactly once and popped at most once. |
| **Space Complexity** | $\mathcal{O}(n)$ | The stack can store up to $n$ elements in the worst case (e.g., when the heights are in strictly increasing order). |

---

## Common Follow-Up Questions & How to Answer

### Q1: Can we solve the problem using a Divide and Conquer approach? What is its complexity?
* **Answer**: Yes, we can find the minimum bar in the current range, compute the area with that minimum bar as the height, and recursively solve for the left and right sub-histograms.
* **Complexity**: The recurrence is $T(n) = 2T(n/2) + \mathcal{O}(n)$ in the best case (when the minimum bar is in the middle), giving $\mathcal{O}(n \log n)$ time. However, in the worst case (already sorted heights), it degrades to $\mathcal{O}(n^2)$. We can optimize the range minimum query to $\mathcal{O}(\log n)$ using a **Segment Tree**, ensuring $\mathcal{O}(n \log n)$ time complexity in the worst case.

### Q2: How is this problem related to "Maximal Rectangle" in a 2D binary matrix (LeetCode 85)?
* **Answer**: LeetCode 85 can be solved by reducing it to LeetCode 84. For each row in the 2D matrix, we can treat the number of consecutive `1`s above it as a histogram height. We can update these heights in $\mathcal{O}(\text{cols})$ time for each row, and then run the Largest Rectangle in Histogram algorithm on the current row's histogram heights. Overall time complexity becomes $\mathcal{O}(\text{rows} \times \text{cols})$ instead of the naive $\mathcal{O}(\text{rows}^3 \times \text{cols}^3)$.

### Q3: What if the widths of the bars are not 1, but are given in another array `widths`?
* **Answer**: If we have an array `widths` where `widths[i]` represents the width of the $i$-th bar, the prefix sum of widths can be precomputed. Specifically, we define `prefix_widths[i]` as the sum of widths of all bars up to $i-1$. Then, when popped, the width of the rectangle is `prefix_widths[i] - prefix_widths[stack.back()]` (or `prefix_widths[i]` if the stack is empty).

---

## Pro-Tip: How to Impress the Interviewer

* **Catch the Vector Size Underflow**: In C++, always check if `heights` is empty before performing operations like `heights.size() - 1` to prevent underflow of unsigned `size_t`.
* **Stack Memory Pre-allocation**: Mentioning `stack.reserve(n)` in C++ shows optimization awareness. It prevents multiple allocations/deallocations as the vector grows dynamically.
* **Real-world Analogy (Skyline Queries)**: Explain that monotonic stack patterns are widely used in databases and GIS systems for computing 2D skyline queries, visibility polygons, and terrain rendering.
