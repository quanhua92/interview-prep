# Subarray Product Less Than K

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 713, Glassdoor
- **Flashcards**: [Prefix Sum deck](../../flash_cards/coding/prefix_sum.md)

---

## Question Description

Given an array of integers `nums` and an integer `k`, return the number of contiguous subarrays where the product of all the elements in the subarray is strictly less than `k`.

### Examples
*   **Input**: `nums = [10, 5, 2, 6]`, `k = 100`
    *   **Output**: `8`
    *   **Explanation**: The 8 subarrays that have product less than 100 are:
        `[10]`, `[5]`, `[2]`, `[6]`, `[10, 5]`, `[5, 2]`, `[2, 6]`, `[5, 2, 6]`.
        Note that `[10, 5, 2]` is not included as its product is 100, which is not strictly less than 100.
*   **Input**: `nums = [1, 2, 3]`, `k = 0`
    *   **Output**: `0`

---

## Detailed Solution (C++)

Since all elements in `nums` are strictly positive integers ($nums[i] \ge 1$), the product of any subarray is monotonically increasing as we expand it. This monotonic property allows us to use a **Sliding Window (Two Pointers)** approach:
1. Maintain a window `[left, right]` and a running `product` of elements inside the window.
2. Iterate `right` from `0` to `n - 1`, multiplying the running `product` by `nums[right]`.
3. If `product >= k`, shrink the window from the left by dividing `product` by `nums[left]` and incrementing `left`, until `product < k` or `left > right`.
4. For each valid window ending at `right`, the number of valid subarrays ending at `right` is `right - left + 1` (namely, `nums[right]`, `nums[right-1...right]`, ..., `nums[left...right]`).
5. Sum these counts over all iterations of `right`.

### Standard C++ Production Code

```cpp
#include <vector>

class Solution {
public:
    int numSubarrayProductLessThanK(const std::vector<int>& nums, int k) {
        // Since nums[i] >= 1, if k <= 1, no subarray product can be strictly less than k.
        if (k <= 1) {
            return 0;
        }

        int count = 0;
        long long product = 1; // Use long long to prevent potential overflow during multiplication
        int left = 0;
        int n = static_cast<int>(nums.size());

        for (int right = 0; right < n; ++right) {
            product *= nums[right];

            // Shrink the window until the product is strictly less than k
            while (product >= k && left <= right) {
                product /= nums[left];
                left++;
            }

            // All subarrays starting from any index in [left, right] and ending at right are valid
            count += (right - left + 1);
        }

        return count;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the Python sliding window implementation.

```python
from typing import List

class Solution:
    def numSubarrayProductLessThanK(self, nums: List[int], k: int) -> int:
        """
        Returns the number of contiguous subarrays where the product is strictly less than k.
        
        Time Complexity: O(N)
        Space Complexity: O(1)
        """
        if k <= 1:
            return 0

        count = 0
        product = 1
        left = 0

        for right, val in enumerate(nums):
            product *= val
            
            # Shrink window from the left if the product matches or exceeds k
            while product >= k and left <= right:
                product //= nums[left]
                left += 1
                
            count += (right - left + 1)

        return count
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Floor Division vs Standard Division
*   In Python, standard division (`/`) yields a float, which can lead to floating-point precision errors (e.g. `24.0 / 2` becoming `12.000000000000002`). 
*   Always use the floor division operator `//=` to maintain exact integer math, as all elements in `nums` are integers and the division is guaranteed to divide evenly.

### 2. Arbitrary Precision
*   While fixed-width systems might overflow when `product *= nums[right]` occurs before the loop contracts it, Python handles arbitrarily large integers, preventing integer overflow bugs naturally. Nonetheless, keeping the sliding window bounds correct prevents unnecessary growth of the integer sizes, which would slow down multiplications.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | Each element is visited at most twice: once by the `right` pointer and at most once by the `left` pointer. |
| **Space Complexity** | $\mathcal{O}(1)$ | We only maintain a few scalar pointers and product accumulators. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if nums[i] could be 0?
*   **Answer**: If `nums[i]` could be `0`, the product becomes `0`, which is always `< k` (for $k > 0$). However, division by `0` would crash our sliding window (`product /= nums[left]`).
*   **Solution**: If we encounter `0`, we must reset the window:
    1. A zero element resets the current product. All subarrays containing this `0` will have a product of `0`.
    2. We can split the array by zeros and solve the problem on each non-zero subarray separately. For subarrays containing the `0`, we can count their contributions directly.

### Q2: How is this related to Prefix Sums?
*   **Answer**: We can convert the product into a sum by taking the logarithm of each element:
    $$\prod_{i=left}^{right} \text{nums}[i] < k \iff \sum_{i=left}^{right} \log(\text{nums}[i]) < \log(k)$$
    If we construct a prefix sum array of $\log(\text{nums}[i])$, we can use binary search (`std::upper_bound`) on this sorted prefix sum array to find the valid `left` boundary for each `right` index.
*   **Trade-off**: The logarithmic prefix sum approach takes $\mathcal{O}(n \log n)$ time and $\mathcal{O}(n)$ space due to float operations and prefix arrays. It also introduces potential floating-point precision issues. However, it is useful if the array elements could be non-monotonic or if we wanted to support multiple random queries on subsegment product ranges.

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention Monotonicity explicitly**: State clearly that the sliding window works because the prefix product is *monotonically increasing* (since $nums[i] \ge 1$). If $nums[i]$ could be fractions between $(0, 1)$, the product would not be monotonic, and a simple sliding window would fail.
*   **Identify the k <= 1 edge case**: Point out immediately that if $k \le 1$ and all elements are $\ge 1$, the product of any subarray is at least $1$. Thus, no subarray can have a product strictly less than $k$. Checking this at the start prevents infinite loops where `left` tries to increment past `right` while trying to divide down a product to less than `1`.
