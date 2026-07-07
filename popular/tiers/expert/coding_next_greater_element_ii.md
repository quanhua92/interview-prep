# Next Greater Element II

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 503, Glassdoor
- **Flashcards**: [Monotonic Stack deck](../../flash_cards/coding/monotonic_stack.md)

---

## Question Description

Given a circular integer array `nums` (i.e., the next element of `nums[nums.length - 1]` is `nums[0]`), return *the next greater number for every element in* `nums`.

The **next greater number** of a number `x` is the first greater number to its traversing-order next in the array, which means you could search circularly to find its next greater number. If it doesn't exist, return `-1` for this number.

### Examples

*   **Input**: `nums = [1,2,1]`
    *   **Output**: `[2,-1,2]`
    *   **Explanation**: 
        *   The first `1`'s next greater number is `2`.
        *   The number `2` has no greater number.
        *   The second `1`'s next greater number is found circularly, which is also `2`.
*   **Input**: `nums = [1,2,3,4,3]`
    *   **Output**: `[2,3,4,-1,4]`

---

## Detailed Solution (C++)

To handle the circular property, we can simulate an array duplicated to double its size (`2 * n` elements) without allocating additional memory. 

We maintain a **Monotonic Decreasing Stack** that stores the indices of elements:
1. We loop from `i = 0` to `2 * n - 1`. Let the current circular index be `idx = i % n`.
2. While the stack is not empty and the current element `nums[idx]` is greater than `nums[stack.back()]`, it means `nums[idx]` is the next greater element for the index at `stack.back()`. We pop the top index from the stack and store `nums[idx]` in `result[popped_index]`.
3. In the first pass (`i < n`), we push `idx` onto the stack. We do not push in the second pass since any element requiring a next greater element has already been placed in the stack during the first pass.

### Standard C++ Production Code

```cpp
#include <vector>
#include <cstddef>

class Solution {
public:
    std::vector<int> nextGreaterElements(std::vector<int>& nums) {
        // Edge Case: Handle empty input
        if (nums.empty()) {
            return {};
        }

        const int n = static_cast<int>(nums.size());
        std::vector<int> result(n, -1);
        std::vector<int> stack;
        stack.reserve(n); // Pre-allocate stack to avoid reallocation overhead

        // Traverse the array twice to simulate the circular array
        for (int i = 0; i < 2 * n; ++i) {
            int idx = i % n;

            // Maintain the monotonic decreasing stack
            while (!stack.empty() && nums[stack.back()] < nums[idx]) {
                result[stack.back()] = nums[idx];
                stack.pop_back();
            }

            // Only push indices to stack in the first pass
            if (i < n) {
                stack.push_back(idx);
            }
        }

        return result;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation using the two-pass monotonic stack.

```python
from typing import List

class Solution:
    def nextGreaterElements(self, nums: List[int]) -> List[int]:
        """
        Finds the next greater element for each index in a circular array.
        
        Time Complexity: O(N)
        Space Complexity: O(N)
        """
        if not nums:
            return []

        n = len(nums)
        result = [-1] * n
        stack: List[int] = []

        # Loop 2 * n times to simulate circular traversal
        for i in range(2 * n):
            idx = i % n
            
            # Pop elements from stack if the current element is greater
            while stack and nums[stack[-1]] < nums[idx]:
                result[stack.pop()] = nums[idx]
                
            # Only push indices from the first pass
            if i < n:
                stack.append(idx)

        return result
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Index Arithmetic and Modulo Operator
* In Python, `i % n` works identically to lower-level languages. However, modulo arithmetic incurs minor CPU interpreter overhead. 
* For performance-critical code on large datasets, you can write two separate loops: one for `i` from `0` to `n-1` (where you push to the stack), and a second for `i` from `0` to `n-1` (where you only pop and update without pushing). This eliminates the modulo operator entirely.

### 2. Pre-allocation of Python Lists
* Initiating `result = [-1] * n` is faster and uses less memory than calling `.append()` iteratively in Python, because it pre-allocates the exact memory needed in a single C-level allocation.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | We iterate $2n$ times. Each index is pushed onto the stack at most once and popped at most once. |
| **Space Complexity** | $\mathcal{O}(n)$ | The stack can store up to $n$ elements in the worst case (e.g., when the array is sorted in descending order). |

---

## Common Follow-Up Questions & How to Answer

### Q1: Why do we only push indices to the stack when `i < n`?
* **Answer**: Pushing to the stack during the second pass (`i >= n`) is redundant. The second pass is only performed to resolve elements that were pushed during the first pass but did not find a next greater element to their right. Any element visited in the second pass has already had its own opportunity to be pushed and resolved during the first pass.

### Q2: Can we solve this problem by traversing from right to left?
* **Answer**: Yes, we can traverse from $2n - 1$ down to $0$. We maintain a monotonic stack of values (or indices) in descending order. For each element `nums[idx]` (where `idx = i % n`), we pop elements from the stack that are less than or equal to `nums[idx]`. If the stack is not empty, its top element is the next greater element. We record this in our result vector (only when `i < n`), and then push `nums[idx]` onto the stack.
* **Code Example (C++)**:
    ```cpp
    std::vector<int> nextGreaterElements(std::vector<int>& nums) {
        int n = nums.size();
        std::vector<int> result(n, -1);
        std::vector<int> stack;
        for (int i = 2 * n - 1; i >= 0; --i) {
            int idx = i % n;
            while (!stack.empty() && stack.back() <= nums[idx]) {
                stack.pop_back();
            }
            if (i < n) {
                result[idx] = stack.empty() ? -1 : stack.back();
            }
            stack.push_back(nums[idx]);
        }
        return result;
    }
    ```

---

## Pro-Tip: How to Impress the Interviewer

* **Propose Modulo Elimination**: Mention that replacing the `i % n` operator with two distinct loops (first pass with push/pop, second pass with pop-only) is a cache-friendly and instruction-friendly optimization that avoids the hardware division instruction required for modulo.
* **Memory Safety & Pre-sizing**: Emphasize using `reserve(n)` on the stack vector. In production C++, dynamic reallocation of std::vector triggers memory copies, which degrades execution speed on large datasets.
