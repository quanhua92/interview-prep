# 3Sum

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Algorithm Engineer
- **Source**: LeetCode 15, Glassdoor

---

## Question Description

Given an integer array `nums`, return all the triplets `[nums[i], nums[j], nums[k]]` such that $i \neq j$, $i \neq k$, and $j \neq k$, and $\text{nums}[i] + \text{nums}[j] + \text{nums}[k] == 0$.

Notice that the solution set must not contain duplicate triplets.

### Examples

*   **Input**: `nums = [-1,0,1,2,-1,-4]`
    *   **Output**: `[[-1,-1,2],[-1,0,1]]`
    *   **Explanation**: 
        *   `nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0`.
        *   `nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0`.
        *   `nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0`.
        *   The distinct triplets are `[-1,0,1]` and `[-1,-1,2]`. Note that the order of the output and the order of the triplets does not matter.
*   **Input**: `nums = [0,1,1]`
    *   **Output**: `[]`
    *   **Explanation**: The only possible triplet is `[0,1,1]`, which sums up to $2 \neq 0$.
*   **Input**: `nums = [0,0,0]`
    *   **Output**: `[[0,0,0]]`
    *   **Explanation**: The only possible triplet sums up to $0$.

---

## Detailed Solution (C++)

To solve 3Sum efficiently in $\mathcal{O}(n^2)$ time with $\mathcal{O}(1)$ auxiliary space (excluding sorting):

1. **Sort the Input Array**: Sorting allows us to use a two-pointer approach for the inner search and easily skip duplicate elements to satisfy the uniqueness constraint.
2. **Iterate the First Element**: Loop through the array with index $i$ representing the first element of our triplet, `nums[i]`.
   * **Early Pruning**: Since the array is sorted, if `nums[i] > 0`, the sum of any triplet starting with `nums[i]` will be strictly positive. We can terminate the loop early.
   * **Duplicate Elimination**: If `nums[i] == nums[i - 1]` (for $i > 0$), we skip to avoid generating duplicate triplets.
3. **Two-Pointer Search**: Set `left = i + 1` and `right = n - 1`. While `left < right`:
   * Calculate `sum = nums[i] + nums[left] + nums[right]`.
   * If `sum < 0`, we need a larger value, so we increment `left`.
   * If `sum > 0`, we need a smaller value, so we decrement `right`.
   * If `sum == 0`, we record the triplet `[nums[i], nums[left], nums[right]]`. Then:
     * Advance `left` while skipping duplicate values: `nums[left] == nums[left + 1]`.
     * Decelerate `right` while skipping duplicate values: `nums[right] == nums[right - 1]`.
     * Move both pointers (`left++`, `right--`) to search for other potentials.

### Standard C++ Production Code

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        if (nums.size() < 3) {
            return result;
        }

        // Sort the array to enable two-pointer approach and duplicate skipping
        std::sort(nums.begin(), nums.end());
        const int n = static_cast<int>(nums.size());

        for (int i = 0; i < n - 2; ++i) {
            // Early Pruning: If the current smallest value is positive, no sum can equal 0
            if (nums[i] > 0) {
                break;
            }

            // Skip duplicates for the first element
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            int left = i + 1;
            int right = n - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum < 0) {
                    left++;
                } else if (sum > 0) {
                    right--;
                } else {
                    result.push_back({nums[i], nums[left], nums[right]});

                    // Skip duplicates for the second element
                    while (left < right && nums[left] == nums[left + 1]) {
                        left++;
                    }
                    // Skip duplicates for the third element
                    while (left < right && nums[right] == nums[right - 1]) {
                        right--;
                    }

                    left++;
                    right--;
                }
            }
        }

        return result;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation using in-place list sorting.

```python
from typing import List

class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        """
        Finds all unique triplets in the array that sum to zero.
        
        Time Complexity: O(N^2)
        Space Complexity: O(log N) to O(N) depending on the sorting implementation
        """
        result: List[List[int]] = []
        if len(nums) < 3:
            return result

        # Sort in-place using Timsort
        nums.sort()
        n = len(nums)

        for i in range(n - 2):
            # Early Pruning
            if nums[i] > 0:
                break

            # Skip duplicates for the first element
            if i > 0 and nums[i] == nums[i - 1]:
                continue

            left: int = i + 1
            right: int = n - 1

            while left < right:
                total = nums[i] + nums[left] + nums[right]
                if total < 0:
                    left += 1
                elif total > 0:
                    right -= 1
                else:
                    result.append([nums[i], nums[left], nums[right]])
                    
                    # Skip duplicates for the second element
                    while left < right and nums[left] == nums[left + 1]:
                        left += 1
                    # Skip duplicates for the third element
                    while left < right and nums[right] == nums[right - 1]:
                        right -= 1
                        
                    left += 1
                    right -= 1

        return result
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. In-place Sorting vs. `sorted()`
* Using `nums.sort()` sorts the list in-place, modifying the original object and using $\mathcal{O}(1)$ additional memory pointer updates (Timsort still requires auxiliary memory for run-merge arrays up to $\mathcal{O}(n)$).
* In contrast, `sorted(nums)` makes a full copy of the list, which doubles the memory footprint of the input data structure. Always prefer in-place sorting in coding interviews unless modifying the input is forbidden.

### 2. Timsort Auxiliary Space Complexity
* Python’s built-in sort algorithm is Timsort. In the worst case, Timsort has a space complexity of $\mathcal{O}(n)$ to store temporary runs, whereas C++'s `std::sort` typically uses Introsort, requiring $\mathcal{O}(\log n)$ auxiliary stack frames. 

### 3. Hashing/Set Deduplication Overhead
* Some developers write a naive 3Sum search and clean up duplicates by adding results to a set of tuples: `result_set.add(tuple(sorted([nums[i], nums[j], nums[k]])))`.
* This approach creates large amounts of dynamic object allocations (tuples, lists) and is computationally expensive. Deduplicating on the fly using pointer increments avoids hash collisions, hashing calculations, and garbage collection overhead.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n^2)$ | Sorting takes $\mathcal{O}(n \log n)$. The outer loop runs $n - 2$ times, and the inner two-pointer loop runs in $\mathcal{O}(n)$ time per iteration, yielding $\mathcal{O}(n^2)$ total. |
| **Space Complexity** | $\mathcal{O}(\log n)$ to $\mathcal{O}(n)$ | $\mathcal{O}(\log n)$ auxiliary space in C++ (for recursion stack of quicksort/introsort) and up to $\mathcal{O}(n)$ in Python (for Timsort). |

---

## Common Follow-Up Questions & How to Answer

### Q1: How do you generalize this approach to solve $k$-Sum?
* **Answer**: We can solve $k$-Sum recursively. For any $k > 2$, we sort the array and iterate the first element from index $i$ to $n - k$. We recursively call the $(k-1)$-Sum algorithm on the remaining subarray to find elements that sum to `target - nums[i]`. When $k$ reaches $2$, we terminate with the standard two-pointer Two-Sum solver.
* **General Framework (Python)**:
  ```python
  def kSum(nums: List[int], target: int, k: int, start: int) -> List[List[int]]:
      res = []
      if start == len(nums):
          return res
      # The average value of remaining elements must be at least target/k
      if nums[start] * k > target or target > nums[-1] * k:
          return res
      if k == 2:
          # Two Sum
          left, right = start, len(nums) - 1
          while left < right:
              curr_sum = nums[left] + nums[right]
              if curr_sum < target:
                  left += 1
              elif curr_sum > target:
                  right -= 1
              else:
                  res.append([nums[left], nums[right]])
                  while left < right and nums[left] == nums[left + 1]: left += 1
                  while left < right and nums[right] == nums[right - 1]: right -= 1
                  left += 1
                  right -= 1
          return res
      
      for i in range(start, len(nums) - k + 1):
          if i > start and nums[i] == nums[i - 1]:
              continue
          for subset in kSum(nums, target - nums[i], k - 1, i + 1):
              res.append([nums[i]] + subset)
      return res
  ```

### Q2: Can we solve 3Sum in $\mathcal{O}(n^2)$ time without sorting (using Hash Set)?
* **Answer**: Yes, we can iterate through the array using $i$, and for each element, perform a Two-Sum check using a hash set. 
* To prevent duplicate triplets without sorting the main array, we can insert sorted versions of found triplets into a hash set. However, sorting each triplet takes constant $\mathcal{O}(1)$ time, but the overall hash operations are slower in practice than two pointers and require $\mathcal{O}(n)$ additional space.

---

## Pro-Tip: How to Impress the Interviewer

* **Leverage Dual-Pointer Short-Circuiting (Early Pruning)**: Mention that we can skip the loop if `nums[i] > 0` (as discussed) and also if `nums[i] + nums[i+1] + nums[i+2] > 0` (since it's the minimum possible sum starting from index $i$), or if `nums[i] + nums[n-2] + nums[n-1] < 0` (since it's the maximum possible sum starting from index $i$, meaning we must increment $i$).
* **Memory Locality & Cache Friendliness**: Discuss that while a hash table approach achieves the same $\mathcal{O}(n^2)$ time complexity, the two-pointer sorted array traversal is significantly faster on modern hardware. This is because contiguous array accesses trigger sequential hardware cache lines, whereas hash table lookups result in pointer chasing and frequent CPU cache misses.
* **Pass by Reference/Rvalue Semantics**: In C++, point out that passing `vector<int> nums` by value is fine if the caller wants to keep their original vector unsorted. However, if the signature allows, taking a reference or modifying the array in-place prevents duplicating the array container.
