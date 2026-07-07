# Find All Numbers Disappeared in an Array

- **Category**: Coding
- **Difficulty**: Easy
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 448, Glassdoor

---

## Question Description

Given an array `nums` of $n$ integers where `nums[i]` is in the range $[1, n]$, return *an array of all the integers in the range $[1, n]$ that do not appear in `nums`*.

### Examples
*   **Input**: `nums = [4,3,2,7,8,2,3,1]`
    *   **Output**: `[5,6]`
*   **Input**: `nums = [1,1]`
    *   **Output**: `[2]`

---

## Detailed Solution (C++)

Just like LeetCode 442, this problem restricts numbers to the range $[1, n]$, which allows us to map each number to a valid index $idx = |num| - 1$. We can solve it in-place using two different strategies: **Index Negation** and **Cyclic Sort**.

### Method 1: Index Negation (Sign Flips)
1. Iterate through the array. For each value `num`, calculate the target index $idx = |num| - 1$.
2. If `nums[idx]` is positive, flip its sign to negative (`nums[idx] = -nums[idx]`). This serves as a status flag indicating that the number $idx + 1$ exists in the array. If the number is already negative, do nothing.
3. Perform a second pass. For any index $i$ where `nums[i]` is positive, the number $i + 1$ was never seen. Append $i + 1$ to the results.

### Method 2: Cyclic Sort
1. Iterate through the array and try to place each number `nums[i]` at its correct index `nums[i] - 1` by swapping.
2. Advance the loop only when `nums[i]` is in the correct spot or if `nums[i] == nums[nums[i]-1]`.
3. In a second pass, any index $i$ where `nums[i] != i + 1` means the number $i + 1$ is missing.

### Standard C++ Production Code

The following implementation uses the **Index Negation** technique.

```cpp
#include <vector>
#include <cmath>
#include <cstdlib>

class Solution {
public:
    std::vector<int> findDisappearedNumbers(std::vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        
        // Phase 1: Mark present numbers by negating elements at corresponding indices
        for (int num : nums) {
            int index = std::abs(num) - 1;
            if (nums[index] > 0) {
                nums[index] = -nums[index];
            }
        }
        
        // Phase 2: Find all indices that remain positive
        std::vector<int> result;
        for (int i = 0; i < n; ++i) {
            if (nums[i] > 0) {
                result.push_back(i + 1);
            }
        }
        
        return result;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation using the Index Negation method.

```python
from typing import List

class Solution:
    def findDisappearedNumbers(self, nums: List[int]) -> List[int]:
        """
        Finds all missing numbers in the range [1, n] in O(n) time and O(1) auxiliary space.
        
        Time Complexity: O(n)
        Space Complexity: O(1) auxiliary
        """
        # Phase 1: Mark visited indices
        for num in nums:
            index = abs(num) - 1
            if nums[index] > 0:
                nums[index] = -nums[index]
                
        # Phase 2: Identify positive values and yield the missing numbers
        return [i + 1 for i in range(len(nums)) if nums[i] > 0]
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. High-Performance List Comprehension
*   The Python implementation uses a list comprehension `[i + 1 for i in range(len(nums)) if nums[i] > 0]` to construct the final list. List comprehensions run at C-speed in CPython and are faster than executing a manual `for` loop with `list.append()`.

### 2. Side-Effect Safety & Array Restoration
*   Modifying `nums` in-place alters the caller's array. If the interviewer requests a side-effect-free function while maintaining $\mathcal{O}(1)$ auxiliary space, we must restore the list before returning.
*   *Solution*: Perform a restorative pass before returning.
    ```python
    missing = [i + 1 for i in range(len(nums)) if nums[i] > 0]
    for i in range(len(nums)):
        if nums[i] < 0:
            nums[i] = -nums[i]
    return missing
    ```

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | We perform two sequential linear scans of the array. The runtime is linear. |
| **Space Complexity** | $\mathcal{O}(1)$ | Auxiliary space is $\mathcal{O}(1)$ as the input array is modified in-place and the output list does not count toward the space limit. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How do you implement this using Cyclic Sort?
*   **The Solution**: Place each number at its target index using swaps.
*   **Python Code**:
    ```python
    def findDisappearedNumbersCyclic(nums: List[int]) -> List[int]:
        i = 0
        n = len(nums)
        while i < n:
            correct = nums[i] - 1
            if nums[i] != nums[correct]:
                nums[i], nums[correct] = nums[correct], nums[i]
            else:
                i += 1
        return [i + 1 for i in range(n) if nums[i] != i + 1]
    ```

### Q2: What if the input array is completely read-only?
*   **The Problem**: If the array is read-only, in-place negation and cyclic sort are prohibited.
*   **The Solution**: We must use auxiliary memory.
    1.  **Hash Set**: Store all elements in a set, then scan $[1, n]$ to find elements not in the set. Time: $\mathcal{O}(n)$, Space: $\mathcal{O}(n)$.
    2.  **Bitset / Boolean Array**: If $n$ is large, we can use a bit array (e.g. `std::vector<bool>` in C++) to save memory (takes $\frac{n}{8}$ bytes instead of $4n$ bytes).

---

## Pro-Tip: How to Impress the Interviewer

*   **Highlight Write Amplification and Pipeline Stalls**: Compare Index Negation to Cyclic Sort. Negation only writes to memory once per element (if not already negative) and does not perform swaps. Cyclic sort executes random swaps which trigger memory writes and register operations, leading to higher **write amplification** and CPU cache invalidations in multi-core/concurrent settings.
*   **Vector Reallocation Avoidance**: Explicitly note that while we don't know the exact size of the output array, in C++ it is usually better to return the result by value. Modern C++ compilers will use **Return Value Optimization (RVO)** or move semantics to return the `std::vector` with zero copy overhead.
