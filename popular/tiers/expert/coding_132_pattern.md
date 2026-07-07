# 132 Pattern

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 456, Glassdoor

---

## Question Description

Given an array of $n$ integers `nums`, a **132 pattern** is a subsequence of three integers `nums[i]`, `nums[j]` and `nums[k]` such that `i < j < k` and `nums[i] < nums[k] < nums[j]`.

Return `true` if there is a **132 pattern** in `nums`, otherwise, return `false`.

### Examples

*   **Input**: `nums = [1,2,3,4]`
    *   **Output**: `false`
    *   **Explanation**: There is no 132 pattern in the sequence.
*   **Input**: `nums = [3,1,4,2]`
    *   **Output**: `true`
    *   **Explanation**: There is a 132 pattern in the sequence: `[1, 4, 2]` (at indices 1, 2, and 3).
*   **Input**: `nums = [-1,3,2,0]`
    *   **Output**: `true`
    *   **Explanation**: There are multiple 132 patterns, such as `[-1, 3, 2]`, `[-1, 3, 0]`, and `[-1, 2, 0]`.

---

## Detailed Solution (C++)

To solve this problem in $\mathcal{O}(n)$ time, we can iterate from **right to left** (from index $n-1$ down to $0$) and maintain a monotonic stack of candidate values for `nums[k]` (the "2" in the 132 pattern).

We keep track of a variable `third` (representing `nums[k]`), initialized to `INT_MIN` / `LONG_MIN`.
1. If we find a `nums[i]` (the "1" in the 132 pattern) such that `nums[i] < third`, we immediately return `true`. Since `third` represents a valid `nums[k]` that is smaller than some `nums[j]` to its left, and now `nums[i]` is further to the left and smaller than `nums[k]`, the pattern `nums[i] < nums[k] < nums[j]` is satisfied.
2. While the stack is not empty and the current element `nums[i]` is greater than the stack's top element, the stack top becomes a candidate for `third`. We pop the stack and update `third` to be this popped value.
3. We then push `nums[i]` onto the stack.

By popping elements smaller than `nums[i]`, we ensure that `third` always holds the largest possible value of `nums[k]` that is smaller than some element to its left. This maximizes the likelihood of satisfying `nums[i] < third` later in the iteration.

### Standard C++ Production Code

```cpp
#include <vector>
#include <climits>
#include <algorithm>

class Solution {
public:
    bool find132pattern(std::vector<int>& nums) {
        // Edge Case: 132 pattern requires at least 3 elements
        if (nums.size() < 3) {
            return false;
        }

        // Use long to prevent integer overflow/underflow comparisons
        long third = LONG_MIN; 
        std::vector<int> stack;
        stack.reserve(nums.size());

        // Traverse from right to left
        for (int i = static_cast<int>(nums.size()) - 1; i >= 0; --i) {
            // Step 1: Check if nums[i] fits the "1" in "132"
            if (static_cast<long>(nums[i]) < third) {
                return true;
            }

            // Step 2: Maintain monotonic stack. If nums[i] is greater than top,
            // the top becomes the new candidate for "2" (third).
            while (!stack.empty() && stack.back() < nums[i]) {
                third = static_cast<long>(stack.back());
                stack.pop_back();
            }

            // Step 3: Push nums[i] as a candidate for "3"
            stack.push_back(nums[i]);
        }

        return false;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the iterative Python implementation traversing from right to left.

```python
from typing import List

class Solution:
    def find132pattern(self, nums: List[int]) -> bool:
        """
        Determines if there is a 132 pattern in nums.
        
        Time Complexity: O(N)
        Space Complexity: O(N)
        """
        if len(nums) < 3:
            return False

        # 'third' stores the value of the '2' in the '132' pattern (nums[k])
        third = float("-inf")
        stack: List[int] = []

        # Traverse the list in reverse order
        for num in reversed(nums):
            # If the current number is less than the largest available '2',
            # we have found a valid '1' (num < third)
            if num < third:
                return True
            
            # If current number is greater than the stack's top,
            # pop from the stack and update 'third'
            while stack and stack[-1] < num:
                third = stack.pop()
                
            stack.append(num)

        return False
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Representation of Negative Infinity
* In Python, `float("-inf")` is the standard way to represent negative infinity. Comparison operations like `num < third` work correctly with `float("-inf")` across both integer and floating-point types.
* Avoid using magic numbers like `-10**9 - 1` as bounds, since constraints might change or be exceeded in custom environments.

### 2. Space Optimization via In-Place Stack (Conceptual)
* In Python, lists are dynamic arrays. Modifying the list in-place while iterating is generally discouraged unless memory constraints are critical. If requested, Python's list slice or indexing can mimic an in-place stack, but standard list operations are cleaner and highly optimized.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | Each element is pushed to and popped from the stack at most once. |
| **Space Complexity** | $\mathcal{O}(n)$ | The stack stores up to $n$ elements in the worst case (e.g., when the array is sorted in ascending order). |

---

## Common Follow-Up Questions & How to Answer

### Q1: Can we solve this problem using a Left-to-Right traversal?
* **Answer**: Yes, we can precompute the prefix minimums of the array. Let `min_array[i]` be the minimum value from `nums[0]` to `nums[i]`. `min_array[i]` represents the best candidate for `nums[i]` (the "1").
* Then, traversing from right to left (index $j$), we maintain a stack of candidates for `nums[k]` (the "2"). For each `nums[j]`, we pop all elements from the stack that are less than or equal to `min_array[j]` (since they can't be greater than the prefix minimum). If the top of the stack is less than `nums[j]`, we return `true` (since it is also greater than `min_array[j]`). Otherwise, we push `nums[j]` to the stack.

### Q2: Can we optimize the space complexity to $\mathcal{O}(1)$?
* **Answer**: Yes, if we are allowed to modify the input array, we can use the suffix of the array as the stack itself. Since the stack size is always less than or equal to the number of elements processed, we can use a write pointer starting from the end of the array to overwrite processed values and act as a stack.
* **Code Example (C++)**:
    ```cpp
    bool find132pattern(std::vector<int>& nums) {
        int n = nums.size();
        int top = n; // Index of top of the stack
        int third = INT_MIN;
        for (int i = n - 1; i >= 0; i--) {
            if (nums[i] < third) return true;
            while (top < n && nums[i] > nums[top]) {
                third = nums[top++];
            }
            top--;
            nums[top] = nums[i]; // Use input array as stack
        }
        return false;
    }
    ```

---

## Pro-Tip: How to Impress the Interviewer

* **Propose the In-Place Stack Optimization Proactively**: Mention that the monotonic stack space can be reduced to $\mathcal{O}(1)$ auxiliary space if we are allowed to mutate the input array, using the array itself to store stack values.
* **Explain the Logical Duality**: Contrast the right-to-left traversal (tracking the largest potential `third`) with the left-to-right prefix-min traversal. Explaining both approaches demonstrates a deep understanding of monotonic stacks and search state tracking.
