# Two Sum II - Input Array Is Sorted

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 167, Glassdoor

---

## Question Description

Given a **1-indexed** array of integers `numbers` that is already **sorted in non-decreasing order**, find two numbers such that they add up to a specific `target` number. Let these two numbers be `numbers[index1]` and `numbers[index2]` where $1 \le \text{index1} < \text{index2} \le \text{numbers.length}$.

Return *the indices of the two numbers, `index1` and `index2`, added by one as an integer array `[index1, index2]` of length 2*.

The tests are generated such that there is **exactly one solution**. You may not use the same element twice.

Your solution must use only **constant extra space**.

### Examples

*   **Input**: `numbers = [2,7,11,15]`, `target = 9`
    *   **Output**: `[1,2]`
    *   **Explanation**: The sum of 2 and 7 is 9. Therefore, `index1 = 1`, `index2 = 2`. We return `[1, 2]`.
*   **Input**: `numbers = [2,3,4]`, `target = 6`
    *   **Output**: `[1,3]`
    *   **Explanation**: The sum of 2 and 4 is 6. Therefore, `index1 = 1`, `index2 = 3`. We return `[1, 3]`.
*   **Input**: `numbers = [-1,0]`, `target = -1`
    *   **Output**: `[1,2]`
    *   **Explanation**: The sum of -1 and 0 is -1. Therefore, `index1 = 1`, `index2 = 2`. We return `[1, 2]`.

---

## Detailed Solution (C++)

The array is already sorted, which allows us to use the **Two-Pointer technique**:

1. Place one pointer `left` at the start of the array ($0$) and another pointer `right` at the end of the array ($n - 1$).
2. Compute `sum = numbers[left] + numbers[right]`.
3. Compare the `sum` to the `target`:
   * If `sum == target`, we have found the solution. Return the 1-indexed values `{left + 1, right + 1}`.
   * If `sum < target`, we need a larger sum. Since the array is sorted, incrementing `left` moves us to a larger value, so we do `left++`.
   * If `sum > target`, we need a smaller sum. Decrementing `right` moves us to a smaller value, so we do `right--`.
4. Since the problem guarantees that exactly one solution exists, this loop is guaranteed to find it.

### Standard C++ Production Code

```cpp
#include <vector>

class Solution {
public:
    std::vector<int> twoSum(const std::vector<int>& numbers, int target) noexcept {
        int left = 0;
        int right = static_cast<int>(numbers.size()) - 1;

        while (left < right) {
            // Potential overflow warning: sum can overflow standard 32-bit int if elements are near INT_MAX.
            // Under LeetCode constraints (-1000 <= numbers[i] <= 1000), sum is safe from overflow.
            int sum = numbers[left] + numbers[right];

            if (sum == target) {
                return {left + 1, right + 1}; // 1-indexed output
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }

        return {}; // Fallback
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation using standard index boundaries.

```python
from typing import List

class Solution:
    def twoSum(self, numbers: List[int], target: int) -> List[int]:
        """
        Finds two numbers in a sorted array that sum up to target.
        Returns the 1-based indices of the two numbers.
        
        Time Complexity: O(N)
        Space Complexity: O(1)
        """
        left: int = 0
        right: int = len(numbers) - 1

        while left < right:
            curr_sum = numbers[left] + numbers[right]
            
            if curr_sum == target:
                return [left + 1, right + 1]
            elif curr_sum < target:
                left += 1
            else:
                right -= 1

        return []
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Zero-Based vs. One-Based Indexing
* Python arrays (lists) are zero-based. To meet the requirements of LeetCode 167 (1-based output), we must add `1` to both `left` and `right` indices before returning. This is a common point of confusion that is easy to get wrong under interview pressure.

### 2. Space Efficiency and List Creation
* Returning a list `[left + 1, right + 1]` in Python allocates a new list object containing two integers. This happens only once upon finding the solution, maintaining our overall constant auxiliary space complexity of $\mathcal{O}(1)$.

### 3. Native Large Integer Precision
* In Python, integer overflow is not a concern because standard integers are automatically promoted to arbitrary-precision long integers.
* If coding in C++ or Java, however, you should mention that if elements could be up to $2 \times 10^9$, computing `numbers[left] + numbers[right]` would overflow a 32-bit signed integer. A safe way to write this in lower-level languages is:
  ```cpp
  long long sum = static_cast<long long>(numbers[left]) + numbers[right];
  ```

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | Each iteration moves at least one pointer inward, inspecting at most $n$ elements. |
| **Space Complexity** | $\mathcal{O}(1)$ | The algorithm uses only two index variables, requiring constant auxiliary storage. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if the input array is not sorted?
* **Answer**: If the array is unsorted and we cannot sort it (or want to avoid the $\mathcal{O}(n \log n)$ sorting cost), we use a hash map to map each value to its index. We iterate through the array and check if `target - nums[i]` exists in the hash map.
* This takes $\mathcal{O}(n)$ time complexity, but increases space complexity to $\mathcal{O}(n)$ to store the hash map.

### Q2: Can we solve this problem using Binary Search instead of Two Pointers?
* **Answer**: Yes. For each element `numbers[i]`, we can binary search for `target - numbers[i]` in the remaining subarray `[i + 1, n - 1]`.
* **Complexity**: This approach takes $\mathcal{O}(n \log n)$ time and $\mathcal{O}(1)$ space. 
* **When is it better?**: If the array is extremely large and we can run searches in parallel, or if the target is such that we can prune the search range rapidly (for example, if one element is near the beginning and the other is guaranteed to be within a small range).

---

## Pro-Tip: How to Impress the Interviewer

* **Hybrid Pruning Using Binary Search**: 
  * If the array is huge ($n \approx 10^9$) but the target is relatively small, we can run a binary search to find the upper bound index of target (since elements greater than target/2 + offset cannot sum to target if all values are positive). This prunes the size of the array that the two pointers need to scan.
* **Discuss Cache Line Prefetching vs. Random Jump**:
  * Explain that the two-pointer approach accesses elements at the start and end of the array sequentially. The left pointer experiences high cache locality due to forward prefetching, while the right pointer can trigger backward prefetching.
* **Explain Branchless Index Updates**:
  * You can demonstrate how a compiler might eliminate branching to avoid pipeline flushes. 
  ```cpp
  // Conceptual branchless step
  int match = (sum == target);
  int less = (sum < target);
  left += (!match & less);
  right -= (!match & !less);
  ```
