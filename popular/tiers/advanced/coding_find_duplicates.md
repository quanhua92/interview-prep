# Find All Duplicates in an Array

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 442, Glassdoor

---

## Question Description

Given an integer array `nums` of length $n$ where all the integers of `nums` are in the range $[1, n]$ and each integer appears **at most twice**, return *an array of all the integers that appear twice*.

You must write an algorithm that runs in $\mathcal{O}(n)$ time and uses only constant auxiliary space, excluding the space needed to store the output.

### Examples
*   **Input**: `nums = [4,3,2,7,8,2,3,1]`
    *   **Output**: `[2,3]`
*   **Input**: `nums = [1,1,2]`
    *   **Output**: `[1]`
*   **Input**: `nums = [1]`
    *   **Output**: `[]`

---

## Detailed Solution (C++)

There are two main ways to solve this problem in-place using constant auxiliary space: **Index Negation** and **Cyclic Sort**.

### Method 1: Index Negation (Sign Flips)
Since all numbers in the array are in the range $[1, n]$, each number can be mapped to a valid index in the array: $idx = |num| - 1$.
1. We iterate through the array, and for each number `num`, we look at the element at index $idx = |num| - 1$.
2. If `nums[idx]` is positive, we negate it (`nums[idx] = -nums[idx]`) to mark that we have seen the number $idx + 1$.
3. If `nums[idx]` is already negative, it means we have visited this index before. Thus, $|num|$ must be a duplicate, and we add it to our result list.

### Method 2: Cyclic Sort
We try to place each number $x$ at its correct index $x - 1$.
1. While `nums[i]` is not at its correct position (i.e. `nums[i] != nums[nums[i] - 1]`), we swap `nums[i]` with the element at index `nums[i] - 1`.
2. If the element at the target index is already correct, we stop swapping to avoid an infinite loop and increment $i$.
3. After sorting, we iterate through the array: any element where `nums[i] != i + 1` is a duplicate.

### Standard C++ Production Code

The following implementation uses the **Index Negation** technique, which is extremely compact and avoids swaps.

```cpp
#include <vector>
#include <cmath>
#include <cstdlib>

class Solution {
public:
    std::vector<int> findDuplicates(std::vector<int>& nums) {
        std::vector<int> result;
        
        // Optimizing allocation: pre-allocate memory to avoid multiple reallocations
        result.reserve(nums.size() / 2);
        
        for (int num : nums) {
            int idx = std::abs(num) - 1;
            
            if (nums[idx] < 0) {
                // Already visited, meaning this number is a duplicate
                result.push_back(std::abs(num));
            } else {
                // Mark as visited by negating
                nums[idx] = -nums[idx];
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
    def findDuplicates(self, nums: List[int]) -> List[int]:
        """
        Finds all duplicate numbers in-place.
        
        Time Complexity: O(n)
        Space Complexity: O(1) auxiliary
        """
        result = []
        
        for num in nums:
            idx = abs(num) - 1
            if nums[idx] < 0:
                result.append(abs(num))
            else:
                nums[idx] = -nums[idx]
                
        return result
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. In-Place Mutation Side Effects
*   Python variables are references. When you pass `nums` to `findDuplicates`, the function modifies the original list in place. 
*   If the caller expects the input list to remain unchanged, mutating the array in-place is a side effect. It is a good practice during interviews to ask the interviewer: *"Is it acceptable to modify the input list, or should I restore it before returning?"* (See follow-up questions below for how to restore the array).

### 2. Built-in `abs()` Performance
*   Using Python's built-in `abs()` is highly efficient because it is implemented in C at the interpreter level. It is faster than manual ternary-based signs checks.

### 3. List Comprehension and Auxiliary Space
*   We could attempt to build the result list using a comprehension or filters, but doing so without mutating `nums` requires tracking seen numbers in a `set` or auxiliary list, raising the space complexity to $\mathcal{O}(n)$. Modifying the list in-place remains the only way to satisfy the $\mathcal{O}(1)$ space requirement.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | We perform a single linear scan of the array. All lookups and updates at `nums[idx]` are $\mathcal{O}(1)$. |
| **Space Complexity** | $\mathcal{O}(1)$ | The space complexity is $\mathcal{O}(1)$ auxiliary since we mutate the input array in-place. The output list is excluded from the auxiliary space complexity per the problem constraints. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How do you solve this using Cyclic Sort instead of Index Negation?
*   **The Solution**: Place each number $x$ at its correct index $x - 1$ using swaps.
*   **C++ Code**:
    ```cpp
    std::vector<int> findDuplicatesCyclic(std::vector<int>& nums) {
        int n = nums.size();
        int i = 0;
        while (i < n) {
            int correct = nums[i] - 1;
            if (nums[i] != nums[correct]) {
                std::swap(nums[i], nums[correct]);
            } else {
                i++;
            }
        }
        std::vector<int> result;
        for (i = 0; i < n; i++) {
            if (nums[i] != i + 1) {
                result.push_back(nums[i]);
            }
        }
        return result;
    }
    ```

### Q2: What if we are required to restore the input array to its original state before returning?
*   **The Solution**: We can perform a second pass to restore all negative values back to positive.
*   **Python Code**:
    ```python
    def findDuplicatesAndRestore(nums: List[int]) -> List[int]:
        result = []
        for num in nums:
            idx = abs(num) - 1
            if nums[idx] < 0:
                result.append(abs(num))
            else:
                nums[idx] = -nums[idx]
        
        # Restore the array
        for i in range(len(nums)):
            if nums[i] < 0:
                nums[i] = -nums[i]
        return result
    ```
    This maintains $\mathcal{O}(n)$ time and $\mathcal{O}(1)$ auxiliary space.

### Q3: What if numbers can appear more than twice?
*   **The Problem**: If a number can appear three or more times, Index Negation will fail because the third occurrence will see a negative number and flip it back to positive (or misidentify it as a duplicate again).
*   **The Solution**: Using Cyclic Sort is robust here. If we find that `nums[i]` is not in its correct position but `nums[nums[i] - 1]` already contains the correct value, we simply advance `i`. In a final pass, any element `nums[i]` where `nums[i] != i + 1` is a duplicate. We can deduplicate the results using a hash set or checking if the duplicate has already been added.

---

## Pro-Tip: How to Impress the Interviewer

*   **Design for API Safety**: Highlight that mutating inputs without restoring them violates the principle of least surprise in API design. Showing the interviewer that you know how to restore the array in $\mathcal{O}(n)$ time demonstrates production-grade thinking.
*   **Prevent Vector Reallocations**: In C++, `std::vector` resizes dynamically, which can double its capacity and copy elements during execution. Reserving memory upfront using `result.reserve(nums.size() / 2)` prevents costly allocations and copies.
*   **Mention Cache Performance**: Cyclic sort requires multiple random memory writes (swaps), which can lead to high L1/L2 cache miss rates. The Index Negation approach reads the array sequentially and writes only once per index, making it significantly more cache-friendly and faster in practice.
