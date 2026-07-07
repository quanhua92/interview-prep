# Split Array Largest Sum

- **Category**: Coding
- **Difficulty**: Hard
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 410, Glassdoor

---

## Question Description

Given an integer array `nums` and an integer `k`, split `nums` into `k` non-empty subarrays such that the largest sum of any subarray is minimized.

Return *the minimized largest sum of the split*.

A **subarray** is a contiguous part of the array.

### Examples
*   **Input**: `nums = [7,2,5,10,8]`, `k = 2`
    *   **Output**: `18`
    *   **Explanation**: There are four ways to split `nums` into two subarrays. The best way is to split it into `[7,2,5]` and `[10,8]`, where the largest sum among the two subarrays is only `18`.
*   **Input**: `nums = [1,2,3,4,5]`, `k = 2`
    *   **Output**: `9`
    *   **Explanation**: The best way is to split it into `[1,2,3]` and `[4,5]`, where the largest sum among the two subarrays is only `9`.

---

## Detailed Solution (C++)

The problem asks us to find a value $S$ (the maximum subarray sum) such that we can partition the array into $k$ contiguous subarrays where no subarray has a sum greater than $S$. 

This is a classic example of **Binary Search on the Answer**.

1.  **Define the search space `[left, right]`**:
    *   `left` (minimum possible maximum sum): This must be at least the maximum single element in the array (`max(nums)`), because the element with the maximum value must belong to some subarray, and subarray sizes must be $\ge 1$.
    *   `right` (maximum possible maximum sum): This is the sum of all elements in the array (`sum(nums)`), which corresponds to the case where $k = 1$ (the entire array is a single subarray).
2.  **Binary Search**:
    *   Find the midpoint `mid = left + (right - left) / 2`.
    *   Check if it is feasible to partition `nums` into $\le k$ subarrays such that no subarray's sum exceeds `mid`.
3.  **Feasibility Check (Greedy)**:
    *   Iterate through `nums` and accumulate elements into a `current` sum.
    *   If `current` exceeds `mid`, we must start a new subarray. We increment our subarray count `count` and reset `current` to the current element.
    *   If `count` exceeds `k`, then `mid` is too small, and we must increase the lower bound (`left = mid + 1`).
    *   If the loop finishes within $k$ subarrays, then `mid` is feasible, and we try to find a smaller maximum sum (`right = mid`).

### Standard C++ Production Code

```cpp
#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
private:
    // Helper function to check if a max sum is feasible with k splits
    bool feasible(const std::vector<int>& nums, long long max_sum, int k) noexcept {
        int count = 1;
        long long current = 0;
        
        for (int v : nums) {
            current += v;
            if (current > max_sum) {
                // Cannot fit in the current subarray, start a new one
                count++;
                current = v;
                if (count > k) {
                    return false; // Requires more than k subarrays
                }
            }
        }
        return true;
    }

public:
    int splitArray(const std::vector<int>& nums, int k) {
        if (nums.empty()) {
            return 0;
        }

        // Use long long to prevent integer overflow during accumulation
        long long left = *std::max_element(nums.begin(), nums.end());
        long long right = std::accumulate(nums.begin(), nums.end(), 0LL);

        while (left < right) {
            long long mid = left + (right - left) / 2;
            
            if (feasible(nums, mid, k)) {
                right = mid;      // Mid is feasible, try to find a smaller maximum sum
            } else {
                left = mid + 1;   // Mid is too small, increase target sum
            }
        }

        return static_cast<int>(left);
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation using Binary Search on the Answer.

```python
from typing import List

class Solution:
    def splitArray(self, nums: List[int], k: int) -> int:
        """
        Finds the minimized largest sum of split subarrays using Binary Search.
        
        Time Complexity: O(n * log(S)) where S is the sum of nums.
        Space Complexity: O(1) auxiliary
        """
        # Establish the range boundaries
        left, right = max(nums), sum(nums)

        def feasible(max_sum: int) -> bool:
            count = 1
            current = 0
            for n in nums:
                current += n
                if current > max_sum:
                    count += 1
                    current = n
                    if count > k:
                        return False
            return True

        # Binary search on range [max(nums), sum(nums)]
        while left < right:
            mid = left + (right - left) // 2
            if feasible(mid):
                right = mid      # mid is feasible, check for smaller solutions
            else:
                left = mid + 1   # mid is too small, increase minimum sum target
                
        return left
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Closures vs Helper Methods
*   In Python, nesting `feasible` inside `splitArray` creates a **closure**. This allows `feasible` to directly read `nums` and `k` from the parent stack frame without passing them as arguments.
*   While closures are highly readable, lookups of variables in enclosing scopes in Python are slightly slower than local variable lookups. For performance-critical code or very large loops, passing the variables explicitly or refactoring to a class method can yield micro-optimizations.

### 2. Large Range Precision
*   Python automatically handles arbitrary-precision integers, so variables like `right = sum(nums)` will never overflow. 
*   However, we still write `mid = left + (right - left) // 2` to emphasize code portability to low-level target environments.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n \log S)$ | The search space size is $S = \text{sum}(nums) - \text{max}(nums)$. The binary search takes $\mathcal{O}(\log S)$ iterations. In each iteration, we scan the array of size $n$ in $\mathcal{O}(n)$ time. |
| **Space Complexity** | $\mathcal{O}(1)$ | We only maintain pointers and accumulators, using constant auxiliary space. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How can this problem be solved if elements can be negative?
*   **The Problem**: If the array contains negative numbers, the prefix sum is no longer monotonically increasing. A greedy packing strategy in the feasibility check will fail (for example, adding an element might decrease the current subarray sum, which breaks the monotonic greedy assumption).
*   **The Solution**: We must use **Dynamic Programming (DP)**.
    *   Let $DP[i][j]$ be the minimized largest sum when splitting the first $i$ elements into $j$ subarrays.
    *   The recurrence relations:
        $$DP[i][j] = \min_{0 \le m < i} \left\{ \max(DP[m][j-1], \sum_{p=m+1}^{i} nums[p]) \right\}$$
    *   **Complexity**: Time complexity becomes $\mathcal{O}(n^2 \cdot k)$, and space complexity is $\mathcal{O}(n \cdot k)$.

### Q2: What are the similarities between this problem and LeetCode 1011 (Capacity To Ship Packages Within D Days)?
*   **The Answer**: They are isomorphic. "Shipping packages within $D$ days" maps exactly to "splitting the array into $D$ subarrays" where the cargo weight is `nums` and we want to minimize the maximum daily weight. The exact same binary search on answer template solves both.

---

## Pro-Tip: How to Impress the Interviewer

*   **Define Monotonicity Formally**: Clarify that Binary Search on Answer is only possible because the feasibility function $f(S)$ is **monotonic**:
    $$\text{If } f(S_0) = \text{True, then } f(S) = \text{True for all } S \ge S_0.$$
    This formal framing shows you understand the mathematical foundations of binary search beyond simple sorted array indices.
*   **Identify Cache Friendliness**: Point out that the feasibility function performs a simple, contiguous linear scan of the input array. This means it benefits from $100\%$ hardware L1/L2 cache prefetching, which executes extremely fast on modern CPUs, making it far superior to the Dynamic Programming solution even when $k$ is large.
