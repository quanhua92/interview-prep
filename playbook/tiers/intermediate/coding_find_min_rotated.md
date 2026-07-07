# Find Minimum in Rotated Sorted Array

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 153, Glassdoor
- **Flashcards**: [Binary Search deck](../../flash_cards/coding/binary_search.md)

---

## Question Description

Suppose an array of length $n$ sorted in ascending order is rotated between $1$ and $n$ times. For example, the array `nums = [0,1,2,4,5,6,7]` might become:
* `[4,5,6,7,0,1,2]` if it was rotated $4$ times.
* `[0,1,2,4,5,6,7]` if it was rotated $7$ times.

Notice that rotating an array `[a[0], a[1], a[2], ..., a[n-1]]` $1$ time results in the array `[a[n-1], a[0], a[1], a[2], ..., a[n-2]]`.

Given the sorted rotated array `nums` of **unique** elements, return the *minimum element* of this array.

You must write an algorithm that runs in $\mathcal{O}(\log n)$ time.

### Examples

*   **Input**: `nums = [3,4,5,1,2]`
    *   **Output**: `1`
    *   **Explanation**: The original array was `[1,2,3,4,5]` rotated 3 times.
*   **Input**: `nums = [4,5,6,7,0,1,2]`
    *   **Output**: `0`
    *   **Explanation**: The original array was `[0,1,2,4,5,6,7]` and it was rotated 4 times.
*   **Input**: `nums = [11,13,15,17]`
    *   **Output**: `11`
    *   **Explanation**: The original array was `[11,13,15,17]` and it was rotated 4 times.

---

## Detailed Solution (C++)

The core algorithm is a modified **Binary Search**. Because all elements are unique, we can identify which half contains the inflection point (the minimum element) by comparing the middle element `nums[mid]` to the rightmost element `nums[right]`:
1. If `nums[mid] > nums[right]`, the minimum must lie strictly to the right of `mid`. Thus, we can move our search window to the right: `left = mid + 1`.
2. If `nums[mid] <= nums[right]`, the minimum could be `nums[mid]` or lies to its left. Thus, we set `right = mid`.

This division narrows down the search space to exactly one element, which will be the minimum.

### Standard C++ Production Code

```cpp
#include <vector>
#include <cstddef>
#include <stdexcept>

class Solution {
public:
    int findMin(const std::vector<int>& nums) {
        // Edge Case: Handle empty collection explicitly to prevent unsigned underflow
        if (nums.empty()) {
            throw std::invalid_argument("Input array cannot be empty.");
        }

        int left = 0;
        int right = static_cast<int>(nums.size()) - 1; // Safely cast size to int

        while (left < right) {
            int mid = left + (right - left) / 2; // Prevent integer overflow

            if (nums[mid] > nums[right]) {
                // Minimum is in the right half (excluding mid)
                left = mid + 1;
            } else {
                // Minimum is at mid or in the left half
                right = mid;
            }
        }

        return nums[left];
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
    def findMin(self, nums: List[int]) -> int:
        """
        Finds the minimum element in a rotated sorted array using binary search.
        
        Time Complexity: O(log N)
        Space Complexity: O(1)
        """
        # Edge Case: Handle empty collection explicitly
        if not nums:
            raise ValueError("Input array cannot be empty.")

        left, right = 0, len(nums) - 1

        while left < right:
            mid = left + (right - left) // 2

            if nums[mid] > nums[right]:
                # Minimum must be in the right half
                left = mid + 1
            else:
                # Minimum is mid or to the left of mid
                right = mid

        return nums[left]
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Integer Division: `/` vs `//`
* In Python 3, using a single `/` produces a float (e.g., `5 / 2 = 2.5`). List indices must be integers. Ensure the double slash floor division operator `//` is used to maintain integer indices.

### 2. Handling of Empty Inputs
* In Python, passing an empty list to binary search logic without checks will cause an `IndexError` at `right = len(nums) - 1` (yielding `right = -1`, resulting in out-of-bound attempts or incorrect logic inside the loop). Explicitly validating inputs prevents silent failures.

### 3. Avoiding Slicing Overhead
* Do not slice the list like `findMin(nums[mid:])` during recursive or helper functions, as slicing copies references to new list containers, which takes $\mathcal{O}(k)$ time and space. Stick strictly to boundary indices `left` and `right`.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(\log n)$ | The search space is halved in each step of the binary search loop. |
| **Space Complexity** | $\mathcal{O}(1)$ | Only a few integer variables are maintained, requiring constant auxiliary memory. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if duplicates are allowed in the array? (LeetCode 154)
* **The Problem**: If `nums = [1, 0, 1, 1, 1]`, and we choose the middle index, `nums[mid] == nums[right]` (both are `1`). We cannot determine whether the minimum lies to the left or right of `mid`.
* **The Solution**: When `nums[mid] == nums[right]`, we cannot discard half the search space. Instead, we safely decrement the right boundary (`right--` or `right -= 1`) to eliminate the duplicate and continue the binary search.
* **Worst-case impact**: The time complexity degrades to $\mathcal{O}(n)$ when all elements are identical.

### Q2: How can we find the number of times the array was rotated?
* **The Solution**: The number of rotations is equivalent to the index of the minimum element in the array. For instance, in `[4, 5, 6, 7, 0, 1, 2]`, the minimum `0` is at index `4`, meaning the array was rotated `4` times. Once the minimum is found, we simply return its index `left`.

---

## Pro-Tip: How to Impress the Interviewer

* **Catch the Unsigned Underflow**: Emphasize how subtraction like `nums.size() - 1` on empty inputs causes unsigned underflow in languages like C++, resulting in a large positive boundary (`18446744073709551615`) and immediate segmentation faults. Demonstrating proactive checks for `nums.empty()` indicates production-grade safety awareness.
* **Explain Inflection Point Mechanics**: Rather than memorizing the comparisons, explain it in terms of the "sorted properties" of the left/right parts. In a rotated sorted array, the elements can be viewed as two sorted sub-segments. If `nums[mid] > nums[right]`, `mid` is on the higher first segment, and the inflection point is on the second segment to the right. If `nums[mid] <= nums[right]`, `mid` is on the lower second segment, meaning the minimum cannot be to the right of `mid`.
