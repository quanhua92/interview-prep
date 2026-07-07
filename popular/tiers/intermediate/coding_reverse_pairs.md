# Reverse Pairs

- **Category**: Coding
- **Difficulty**: Hard
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 493, Glassdoor

---

## Question Description

Given an integer array `nums`, return the number of **reverse pairs** in the array.

A reverse pair is a pair $(i, j)$ where:
1. $0 \le i < j < \text{nums.length}$
2. $\text{nums}[i] > 2 \times \text{nums}[j]$

### Examples
*   **Input**: `nums = [1,3,2,3,1]`
    *   **Output**: `2`
    *   **Explanation**: The reverse pairs are:
        *   $(1, 4) \implies \text{nums}[1] = 3 > 2 \times \text{nums}[4] = 2 \times 1$
        *   $(3, 4) \implies \text{nums}[3] = 3 > 2 \times \text{nums}[4] = 2 \times 1$
*   **Input**: `nums = [2,4,3,5,1]`
    *   **Output**: `3`
    *   **Explanation**: The reverse pairs are:
        *   $(1, 4) \implies 4 > 2 \times 1$
        *   $(2, 4) \implies 3 > 2 \times 1$
        *   $(3, 4) \implies 5 > 2 \times 1$

---

## Detailed Solution (C++)

This problem can be efficiently solved using a modified **Merge Sort** (Divide and Conquer). 

### Algorithm Logic
1. **Divide**: Split the array into two halves, `left` and `right`.
2. **Conquer**: Recursively solve the problem for the left and right halves to count the reverse pairs internal to each half.
3. **Combine**: Count the cross-boundary reverse pairs where element $i$ is in the left half and element $j$ is in the right half.
   * Since both halves are sorted after the recursive steps, we can use a **Two-Pointer** approach to count the pairs.
   * Initialize a pointer `j` at the start of the right half.
   * For each element `nums[i]` in the left half, advance `j` until `nums[i] <= 2 * nums[j]`. 
   * All elements in the right half before `j` form a valid reverse pair with `nums[i]`. So, we add `j - mid` to our total count.
   * Merge the two sorted halves in-place to complete the sort.

### Standard C++ Production Code

```cpp
#include <vector>

class Solution {
public:
    int reversePairs(std::vector<int>& nums) {
        if (nums.size() <= 1) return 0;
        std::vector<int> temp(nums.size());
        return mergeSort(nums, temp, 0, static_cast<int>(nums.size()) - 1);
    }

private:
    int mergeSort(std::vector<int>& nums, std::vector<int>& temp, int left, int right) {
        if (left >= right) return 0;
        
        int mid = left + (right - left) / 2;
        int count = mergeSort(nums, temp, left, mid) + mergeSort(nums, temp, mid + 1, right);
        
        // Count reverse pairs crossing mid
        int j = mid + 1;
        for (int i = left; i <= mid; ++i) {
            // Cast to long long to prevent integer overflow when multiplying by 2
            while (j <= right && static_cast<long long>(nums[i]) > 2LL * nums[j]) {
                j++;
            }
            count += (j - (mid + 1));
        }
        
        // Standard merge step
        int p1 = left;
        int p2 = mid + 1;
        int k = left;
        
        while (p1 <= mid && p2 <= right) {
            if (nums[p1] <= nums[p2]) {
                temp[k++] = nums[p1++];
            } else {
                temp[k++] = nums[p2++];
            }
        }
        
        while (p1 <= mid) temp[k++] = nums[p1++];
        while (p2 <= right) temp[k++] = nums[p2++];
        
        // Copy back to original array
        for (int i = left; i <= right; ++i) {
            nums[i] = temp[i];
        }
        
        return count;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

```python
from typing import List

class Solution:
    def reversePairs(self, nums: List[int]) -> int:
        """
        Calculates the number of reverse pairs using merge sort.
        
        Time Complexity: O(n log n)
        Space Complexity: O(n)
        """
        if not nums:
            return 0
        return self._merge_sort(nums, 0, len(nums) - 1)

    def _merge_sort(self, nums: List[int], left: int, right: int) -> int:
        if left >= right:
            return 0
            
        mid = left + (right - left) // 2
        count = self._merge_sort(nums, left, mid) + self._merge_sort(nums, mid + 1, right)
        
        # Count cross-boundary reverse pairs
        j = mid + 1
        for i in range(left, mid + 1):
            while j <= right and nums[i] > 2 * nums[j]:
                j += 1
            count += (j - (mid + 1))
            
        # Merge in-place using Python's list slicing/sorting
        # Note: Merging in-place avoids extra allocation inside recursion
        nums[left:right + 1] = sorted(nums[left:right + 1])
        
        return count
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Arithmetic Overflow
*   In C++, doing `2 * nums[j]` can lead to integer overflow if `nums[j]` is large. This must be handled by casting to `long long`. 
*   In Python, integers have arbitrary precision (they do not overflow), so `2 * nums[j]` is completely safe.

### 2. Timsort Optimizations
*   The Python code uses `nums[left:right+1] = sorted(nums[left:right+1])`. While using `sorted()` looks like it defeats the purpose of the merge step, Python's built-in Timsort is implemented in C and runs extremely fast. Since the left and right halves are already sorted, Timsort can merge them in $\mathcal{O}(k)$ time, which is highly efficient.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n \log n)$ | The array is halved at each level of the recursion tree ($\log n$ levels). At each level, the two-pointer counting and merging takes linear time $\mathcal{O}(n)$. |
| **Space Complexity** | $\mathcal{O}(n)$ | We allocate a temporary array of size $n$ to assist with merging. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Can we solve this using Binary Indexed Tree (BIT) / Fenwick Tree?
*   **Answer**: Yes. We can coordinate coordinate-compression to map the values in `nums` to their ranks. Then, we scan the array from right to left:
    1. Query the BIT for how many elements seen so far are strictly smaller than `nums[i] / 2.0`.
    2. Insert `nums[i]` into the BIT.
*   **BIT Complexity**: Time complexity remains $\mathcal{O}(n \log n)$, but the implementation is non-trivial and space is $\mathcal{O}(n)$ for the tree.

### Q2: What are the differences between Inversion Count and Reverse Pairs?
*   **Answer**: In a standard Inversion Count, the condition is `nums[i] > nums[j]`. This allows counting *during* the merge step directly since `nums[i] > nums[j]` implies all remaining elements in the left half are also greater than `nums[j]`. 
*   For Reverse Pairs, the condition is `nums[i] > 2 * nums[j]`. Because of the factor of 2, we cannot merge and count simultaneously. Thus, we must perform the two-pointer counting step *before* merging.

---

## Pro-Tip: How to Impress the Interviewer

*   **Avoid Vector Reallocation**: Point out that allocating a new `temp` vector at each recursive call creates $\mathcal{O}(n)$ dynamic memory allocations, which hurts heap allocation performance. Allocating a single `temp` buffer of size $n$ in the entry function and passing its reference down keeps execution fast and cache-friendly.
*   **Explain C++ Long Long Literals**: Explain why you used `2LL` instead of `2`. In C++, `2` is a standard `int`. If `nums[j]` is `1073741824`, then `2 * nums[j]` overflows. Using `2LL` forces promotion to `long long` *before* multiplication, avoiding undefined behavior.
