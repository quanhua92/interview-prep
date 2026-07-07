# Binary Search

- **Category**: Coding
- **Difficulty**: Easy
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 704, Glassdoor

---

## Question Description

Given an array of integers `nums` which is sorted in ascending order, and an integer `target`, write a function to search `target` in `nums`. If `target` exists, then return its index. Otherwise, return `-1`.

You must write an algorithm with $\mathcal{O}(\log n)$ runtime complexity.

### Examples

*   **Input**: `nums = [-1,0,3,5,9,12]`, `target = 9`
    *   **Output**: `4`
    *   **Explanation**: `9` exists in `nums` and its index is `4`.
*   **Input**: `nums = [-1,0,3,5,9,12]`, `target = 2`
    *   **Output**: `-1`
    *   **Explanation**: `2` does not exist in `nums` so return `-1`.

### Constraints
*   $1 \le \text{nums.length} \le 10^4$
*   $-10^4 < \text{nums}[i], \text{target} < 10^4$
*   All the integers in `nums` are **unique**.
*   `nums` is sorted in ascending order.

---

## Detailed Solution (C++)

The standard **Binary Search** algorithm divides the search interval in half recursively or iteratively:
1.  Initialize pointer boundaries `left = 0` and `right = nums.size() - 1`.
2.  While `left <= right`:
    *   Find the middle index using `mid = left + (right - left) / 2`.
    *   If `nums[mid] == target`, return `mid`.
    *   If `nums[mid] < target`, discard the left half by setting `left = mid + 1`.
    *   If `nums[mid] > target`, discard the right half by setting `right = mid - 1`.
3.  If the loop terminates without finding the target, return `-1`.

### Standard C++ Production Code

```cpp
#include <vector>
#include <cstddef>

class Solution {
public:
    int search(const std::vector<int>& nums, int target) noexcept {
        // Edge Case: Handle empty collection explicitly to prevent unsigned underflow
        if (nums.empty()) {
            return -1;
        }

        int left = 0;
        int right = static_cast<int>(nums.size()) - 1; // Safely cast size to int

        while (left <= right) {
            int mid = left + (right - left) / 2; // Prevent integer overflow (left + right) / 2

            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                left = mid + 1; // Target lies in the right half
            } else {
                right = mid - 1; // Target lies in the left half
            }
        }

        return -1; // Target not found
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the iterative, type-hinted Python implementation. It avoids recursion overhead and ensures true constant space.

```python
from typing import List

class Solution:
    def search(self, nums: List[int], target: int) -> int:
        """
        Searches for a target in a sorted array using binary search.
        
        Time Complexity: O(log N)
        Space Complexity: O(1)
        """
        # Edge Case: Handle empty collection explicitly
        if not nums:
            return -1

        left, right = 0, len(nums) - 1

        while left <= right:
            mid = left + (right - left) // 2

            if nums[mid] == target:
                return mid
            elif nums[mid] < target:
                left = mid + 1
            else:
                right = mid - 1

        return -1
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Python Built-In Alternative: `bisect`
* Python provides the `bisect` library which implements binary search. For finding an exact value, we can use `bisect.bisect_left`:
  ```python
  import bisect
  
  idx = bisect.bisect_left(nums, target)
  if idx < len(nums) and nums[idx] == target:
      return idx
  return -1
  ```
* Under the hood, Python's `bisect` is implemented in C, making it faster than a pure-Python `while` loop. Mentioning this built-in utility in Python interviews shows familiarity with library optimizations.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(\log n)$ | The search space is halved in each step of the binary search loop. |
| **Space Complexity** | $\mathcal{O}(1)$ | Only a few integer variables are maintained, requiring constant auxiliary memory. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How does the algorithm behave if we search for a value that is missing?
* **Answer**: If the target is missing, the binary search converges to the position where the target *should* be inserted. Specifically:
  * `left` will point to the index of the first element larger than target (equivalent to C++ `std::lower_bound` or Python `bisect_left`).
  * `right` will point to `left - 1`.

### Q2: What is the difference between `lower_bound` and `upper_bound`?
* **Answer**: 
  * `lower_bound` finds the first element that is **greater than or equal to** target (first position where target can be inserted without violating sorted order).
  * `upper_bound` finds the first element that is **strictly greater than** target.

---

## Pro-Tip: How to Impress the Interviewer

* **Overflow Prevention Explanation**: Explain why `left + (right - left) / 2` is used instead of `(left + right) / 2`. In 32-bit signed integers, `left + right` can exceed $2^{31} - 1$, causing overflow and resulting in a negative value, leading to out-of-bounds array access.
* **Cache and Branch Predictor Optimization**: Mention that for small arrays ($n \le 64$), linear search is often faster than binary search due to sequential memory access and spatial cache locality. Discussing this shows hardware-level engineering competence.
