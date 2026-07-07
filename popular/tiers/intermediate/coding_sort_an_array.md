# Sort an Array

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 912, Glassdoor

---

## Question Description

Given an array of integers `nums`, sort the array in ascending order and return it.

You must solve the problem without using any built-in sorting functions, in $\mathcal{O}(n \log n)$ time complexity, and with the smallest space complexity possible.

### Examples
*   **Input**: `nums = [5,2,3,1]`
    *   **Output**: `[1,2,3,5]`
*   **Input**: `nums = [5,1,1,2,0,0]`
    *   **Output**: `[0,0,1,1,2,5]`

---

## Detailed Solution (C++)

To sort an array in $\mathcal{O}(n \log n)$ time, the classic choices are **Merge Sort**, **Heap Sort**, and **Quick Sort**. 

### Why Merge Sort?
Merge Sort is a **Divide and Conquer** algorithm that guarantees stable $\mathcal{O}(n \log n)$ time. 
1. **Divide**: Find the midpoint of the subarray.
2. **Conquer**: Recursively sort the left and right halves.
3. **Combine**: Merge the two sorted halves back together in-place or into a temp buffer.

To optimize, we allocate a single temporary helper vector of size $N$ at the beginning. This avoids overhead from recurring mallocs/deallocations.

### Standard C++ Production Code (Merge Sort)

```cpp
#include <vector>

class Solution {
public:
    std::vector<int> sortArray(std::vector<int>& nums) {
        if (nums.size() <= 1) return nums;
        std::vector<int> temp(nums.size());
        mergeSort(nums, temp, 0, static_cast<int>(nums.size()) - 1);
        return nums;
    }

private:
    void mergeSort(std::vector<int>& nums, std::vector<int>& temp, int left, int right) {
        if (left >= right) return;
        
        int mid = left + (right - left) / 2;
        mergeSort(nums, temp, left, mid);
        mergeSort(nums, temp, mid + 1, right);
        
        // Merge the two halves
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
        
        // Copy back sorted values
        for (int i = left; i <= right; ++i) {
            nums[i] = temp[i];
        }
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code (Merge Sort)

```python
from typing import List

class Solution:
    def sortArray(self, nums: List[int]) -> List[int]:
        """
        Sorts the array in ascending order using Merge Sort.
        
        Time Complexity: O(n log n)
        Space Complexity: O(n)
        """
        if len(nums) <= 1:
            return nums
        
        temp = [0] * len(nums)
        self._merge_sort(nums, temp, 0, len(nums) - 1)
        return nums

    def _merge_sort(self, nums: List[int], temp: List[int], left: int, right: int) -> None:
        if left >= right:
            return
            
        mid = left + (right - left) // 2
        self._merge_sort(nums, temp, left, mid)
        self._merge_sort(nums, temp, mid + 1, right)
        
        # Merge Step
        p1, p2, k = left, mid + 1, left
        while p1 <= mid and p2 <= right:
            if nums[p1] <= nums[p2]:
                temp[k] = nums[p1]
                p1 += 1
            else:
                temp[k] = nums[p2]
                p2 += 1
            k += 1
            
        while p1 <= mid:
            temp[k] = nums[p1]
            p1 += 1
            k += 1
            
        while p2 <= right:
            temp[k] = nums[p2]
            p2 += 1
            k += 1
            
        # Copy back to nums
        for i in range(left, right + 1):
            nums[i] = temp[i]
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. In-place vs. Out-of-place Slicing
*   Writing `left = self.sortArray(nums[:mid])` and `right = self.sortArray(nums[mid:])` creates temporary lists at every recursion level. This yields $\mathcal{O}(n \log n)$ total auxiliary space and can lead to Memory Limit Exceeded (MLE) on LeetCode. 
*   Always use array index boundaries (`left`, `right`) and a single pre-allocated auxiliary list to perform the merge step.

### 2. Timsort (Python's Built-in)
*   Python's built-in `list.sort()` and `sorted()` use **Timsort** (a hybrid of Merge Sort and Insertion Sort). In a real production codebase, Timsort should always be used as it is heavily optimized in C, handles partially sorted arrays in $\mathcal{O}(n)$, and has a worst-case of $\mathcal{O}(n \log n)$.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n \log n)$ | Guaranteed for best, average, and worst cases since we divide the array in half at each step. |
| **Space Complexity** | $\mathcal{O}(n)$ | Due to the auxiliary temporary buffer used for merging, plus $\mathcal{O}(\log n)$ stack space. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Why is Quick Sort preferred over Merge Sort for arrays, but Merge Sort is preferred for linked lists?
*   **Answer**: 
    *   **Arrays**: Quick Sort has better **cache locality** because it works in-place and accesses contiguous memory blocks. Merge Sort requires allocating a temporary array, which incurs allocation overhead and extra memory copies.
    *   **Linked Lists**: Elements in a linked list are scattered in memory, so cache locality is lost anyway. Merge Sort can be implemented on linked lists with $\mathcal{O}(1)$ auxiliary space (by changing pointers) and without allocating new nodes, making it highly efficient.

### Q2: What is the optimal sorting algorithm if values are highly bounded?
*   **Answer**: If constraints indicate that the range of numbers $K$ is small (e.g. $-50000 \le \text{nums}[i] \le 50000$), we can use **Counting Sort**. We count frequencies of each element using a frequency array of size $K$, and then write them back. This runs in $\mathcal{O}(n + K)$ time and $\mathcal{O}(K)$ space.

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention Dual-Pivot Quick Sort & Pivot Selection**: Mention that naive Quick Sort can degrade to $\mathcal{O}(n^2)$ if the pivot is chosen poorly (e.g. sorted arrays). Modern library implementations (like Java's `Arrays.sort` or C++ `std::sort` which uses Introsort) choose pivots using "Median-of-Three" or randomized pivot selection, and switch to Heap Sort if the recursion depth exceeds a threshold.
*   **Cache Friendliness of Block Merging**: In low-level programming, we can optimize Merge Sort by handling small subproblems ($N \le 16$) using **Insertion Sort**. Since small arrays fit entirely inside the L1 cache, Insertion Sort executes faster due to low overhead, which reduces recursion depth.
