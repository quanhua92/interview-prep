# K-diff Pairs in an Array

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Algorithm Engineer
- **Source**: LeetCode 532, Glassdoor

---

## Question Description

Given an array of integers `nums` and an integer `k`, return *the number of **unique** k-diff pairs in the array*.

A **k-diff pair** is an integer pair `(nums[i], nums[j])`, where the following are true:
*   $0 \le i, j < \text{nums.length}$
*   $i \neq j$
*   $|\text{nums}[i] - \text{nums}[j]| == k$

Notice that $|val|$ denotes the absolute value of $val$.

### Examples

*   **Input**: `nums = [3,1,4,1,5]`, `k = 2`
    *   **Output**: `2`
    *   **Explanation**: There are two 2-diff pairs in the array, `(1, 3)` and `(3, 5)`. Although we have two `1`s in the input, we should only return the number of unique pairs.
*   **Input**: `nums = [1,2,3,4,5]`, `k = 1`
    *   **Output**: `4`
    *   **Explanation**: There are four 1-diff pairs in the array: `(1, 2)`, `(2, 3)`, `(3, 4)`, and `(4, 5)`.
*   **Input**: `nums = [1,3,1,5,4]`, `k = 0`
    *   **Output**: `1`
    *   **Explanation**: There is one 0-diff pair in the array, `(1, 1)`.

### Constraints
*   $1 \le \text{nums.length} \le 10^4$
*   $-10^7 \le \text{nums}[i] \le 10^7$
*   $0 \le k \le 10^7$

---

## Detailed Solution (C++)

To solve this problem with $\mathcal{O}(1)$ auxiliary space, we sort the array and apply the **Two-Pointer technique**:

1. **Edge Case**: If $k < 0$, it is impossible for absolute differences to be negative. Return `0`.
2. **Sort the Array**: Sorting makes it easy to find target differences and skip duplicates.
3. **Initialize Pointers**: Place `left = 0` and `right = 1`. Both pointers must be distinct (`left < right`).
4. **Iterate**:
   * Calculate `diff = nums[right] - nums[left]`.
   * If `diff < k`, we need a larger difference, so we increment `right`.
   * If `diff > k`, we need a smaller difference, so we increment `left`.
   * If `diff == k`, we have found a valid pair. We increment `count` and skip duplicate elements:
     * Save the values of `nums[left]` and `nums[right]`, then advance both `left` and `right` past all occurrences of these values.
   * **Collision Safety**: If `left == right`, we must increment `right` to maintain the constraint $i \neq j$.

### Standard C++ Production Code

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int findPairs(std::vector<int>& nums, int k) {
        // Absolute differences cannot be negative
        if (k < 0) {
            return 0;
        }

        // Sort the array in-place to use two pointers
        std::sort(nums.begin(), nums.end());
        
        int count = 0;
        int left = 0;
        int right = 1;
        const int n = static_cast<int>(nums.size());

        while (right < n) {
            int diff = nums[right] - nums[left];

            if (diff < k) {
                right++;
            } else if (diff > k) {
                left++;
            } else {
                // Found a unique k-diff pair
                count++;

                // Skip all duplicates for the current pair to avoid double counting
                int left_val = nums[left];
                int right_val = nums[right];
                
                while (left < n && nums[left] == left_val) {
                    left++;
                }
                while (right < n && nums[right] == right_val) {
                    right++;
                }
            }

            // Ensure pointers don't overlap (since we need distinct indices i != j)
            if (left == right) {
                right++;
            }
        }

        return count;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation using sorting and two pointers.

```python
from typing import List

class Solution:
    def findPairs(self, nums: List[int], k: int) -> int:
        """
        Returns the number of unique k-diff pairs in nums.
        
        Time Complexity: O(N log N)
        Space Complexity: O(1) auxiliary (excluding sorting space)
        """
        if k < 0:
            # Absolute difference cannot be negative
            return 0

        # Sort in-place to avoid copying overhead
        nums.sort()
        
        count = 0
        left, right = 0, 1
        n = len(nums)

        while right < n:
            diff = nums[right] - nums[left]
            
            if diff < k:
                right += 1
            elif diff > k:
                left += 1
            else:
                count += 1
                left_val, right_val = nums[left], nums[right]
                
                # Advance pointers past duplicates
                while left < n and nums[left] == left_val:
                    left += 1
                while right < n and nums[right] == right_val:
                    right += 1
            
            # Pointers cannot point to the same index
            if left == right:
                right += 1

        return count
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Hash Map Alternative (Pythonic Solution)
* In Python, hash map lookups are extremely fast. We can trade space for time by using a frequency dictionary (`Counter`):
  ```python
  from collections import Counter
  
  class Solution:
      def findPairs(self, nums: List[int], k: int) -> int:
          if k < 0:
              return 0
          counts = Counter(nums)
          if k == 0:
              return sum(1 for x in counts if counts[x] > 1)
          return sum(1 for x in counts if (x + k) in counts)
  ```
* **Pros**: This reduces time complexity to $\mathcal{O}(n)$ and is very clean and readable.
* **Cons**: It increases auxiliary space complexity to $\mathcal{O}(n)$ to store the frequencies.

### 2. Large List Memory Footprint
* Python's `Counter` allocates hash tables with bucket overheads. For $10^5$ elements, the two-pointer approach on a sorted list uses significantly less memory than allocating hash maps, making sorting preferable when memory is constrained.

---

## Complexity Analysis

| Metric | Two-Pointer | Hash Map / Set | Description |
| :--- | :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n)$ | Sorting dominates two-pointer time, whereas hash map lookups take average $\mathcal{O}(1)$ time per element. |
| **Space Complexity** | $\mathcal{O}(1)$ | $\mathcal{O}(n)$ | Two-pointer uses only loop counters. Hash Map stores frequencies for all unique numbers. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if we have a stream of incoming numbers and need to query the count of unique pairs dynamically?
* **Answer**: We should maintain a hash map of counts of the elements we have seen so far, along with a `pair_count` counter.
* When a new number `x` is added:
  1. If `k == 0`:
     * Increment `counts[x]`. If `counts[x] == 2`, increment `pair_count` by 1.
  2. If `k > 0`:
     * If `x` is seen for the first time (`counts[x] == 0`):
       * If `x - k` is in `counts`, increment `pair_count`.
       * If `x + k` is in `counts`, increment `pair_count`.
     * Increment `counts[x]`.
* This allows updates and queries to be performed in $\mathcal{O}(1)$ average time.

### Q2: What if we want to return the actual pairs rather than just their count?
* **Answer**:
  * In the two-pointer approach, we can simply store `(nums[left_val], nums[right_val])` in a list before skipping duplicates.
  * In the Hash Map approach, we collect `(x, x + k)` for all valid keys.

---

## Pro-Tip: How to Impress the Interviewer

* **Propose the Space-Time Trade-off Early**:
  * Don't just implement one solution. State both the $\mathcal{O}(n)$ time / $\mathcal{O}(n)$ space Hash Map solution and the $\mathcal{O}(n \log n)$ time / $\mathcal{O}(1)$ space Two-Pointer solution. Let the interviewer choose which resource constraint (CPU vs. RAM) to prioritize.
* **Explain Integer Safety Range**:
  * In C++, point out that the subtraction `nums[right] - nums[left]` is safe from integer overflow because values are between $-10^7$ and $10^7$. The maximum difference is $2 \times 10^7$, which fits comfortably in a standard 32-bit signed integer.
* **Address Cache Line Coherence**:
  * Explain that sorting the array and running the two-pointer scan has excellent spatial locality. The CPU can fetch sequential memory addresses into cache line buffers, whereas Hash Map bucket pointers cause random memory jumps and potential cache thrashing.
