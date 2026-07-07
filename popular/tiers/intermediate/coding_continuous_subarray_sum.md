# Continuous Subarray Sum

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 523, Glassdoor
- **Flashcards**: [Prefix Sum deck](../../flash_cards/coding/prefix_sum.md)

---

## Question Description

Given an integer array `nums` and an integer `k`, return `true` if `nums` has a **good subarray** or `false` otherwise.

A **good subarray** is a subarray where:
*   Its length is **at least two**, and
*   The sum of the elements in the subarray is a multiple of `k` (i.e., sum $= n \times k$ where $n$ is an integer).

Note that:
*   A **subarray** is a contiguous part of the array.
*   An integer $x$ is a multiple of $k$ if there exists an integer $n$ such that $x = n \times k$. $0$ is always a multiple of $k$.

### Examples
*   **Input**: `nums = [23, 2, 4, 6, 7]`, `k = 6`
    *   **Output**: `true`
    *   **Explanation**: `[2, 4]` is a continuous subarray of size 2 whose elements sum up to 6, which is a multiple of 6.
*   **Input**: `nums = [23, 2, 6, 4, 7]`, `k = 6`
    *   **Output**: `true`
    *   **Explanation**: `[23, 2, 6, 4, 7]` is a continuous subarray of size 5 whose elements sum up to 42, which is $7 \times 6$.
*   **Input**: `nums = [23, 2, 6, 4, 7]`, `k = 13`
    *   **Output**: `false`

---

## Detailed Solution (C++)

This problem is solved in linear time using **Prefix Sums modulo $k$** combined with a **Hash Map**:
1. Let $S[i]$ be the prefix sum up to index $i$ modulo $k$:
   $$S[i] = \left( \sum_{j=0}^{i} \text{nums}[j] \right) \bmod k$$
2. The sum of a subarray $\text{nums}[i+1 \dots j]$ is a multiple of $k$ if and only if $S[j] = S[i]$.
3. Since we want a subarray of length **at least two**, we require the index difference to be strictly greater than $1$:
   $$j - i > 1$$
4. We store the first occurrence of each remainder modulo $k$ in a hash map `mod_index`.
5. We initialize `mod_index[0] = -1` to handle the case where a subarray starting from index `0` has a sum that is a multiple of $k$.
6. For each index `i`, we compute `prefix = (prefix + nums[i]) % k`. If `prefix` already exists in `mod_index`, we check if `i - mod_index[prefix] > 1`. If so, we have found a valid subarray and return `true`. If `prefix` does not exist in the map, we store `mod_index[prefix] = i`.
7. **Crucial point**: If `prefix` already exists, we do **not** update its index. Keeping the earliest index maximizes the chance that a subsequent element satisfies the length constraint of $\ge 2$.

### Standard C++ Production Code

```cpp
#include <vector>
#include <unordered_map>

class Solution {
public:
    bool checkSubarraySum(const std::vector<int>& nums, int k) {
        int n = static_cast<int>(nums.size());
        if (n < 2) {
            return false;
        }

        // Map to store (prefix_sum % k) -> first index where it occurred
        std::unordered_map<int, int> mod_index;
        
        // Base case: prefix sum of 0 at index -1
        mod_index[0] = -1;

        int prefix = 0;
        for (int i = 0; i < n; ++i) {
            // Compute mod k prefix sum safely. Use long long to prevent overflow before modulo.
            prefix = static_cast<int>((static_cast<long long>(prefix) + nums[i]) % k);

            auto it = mod_index.find(prefix);
            if (it != mod_index.end()) {
                // If we've seen this mod remainder before, check if length >= 2
                if (i - it->second > 1) {
                    return true;
                }
            } else {
                // Only record the first occurrence of a remainder
                mod_index[prefix] = i;
            }
        }

        return false;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the Python implementation.

```python
from typing import List

class Solution:
    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        """
        Determines if there is a subarray of length >= 2 whose sum is a multiple of k.
        
        Time Complexity: O(N)
        Space Complexity: O(min(N, k))
        """
        if len(nums) < 2:
            return False

        # Map to store prefix sum % k -> earliest index
        mod_index = {0: -1}
        prefix = 0

        for i, num in enumerate(nums):
            prefix = (prefix + num) % k
            
            if prefix in mod_index:
                # Check if the length of the subarray is at least 2
                if i - mod_index[prefix] > 1:
                    return True
            else:
                # Store the earliest index for this prefix remainder
                mod_index[prefix] = i

        return False
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Hash Map Space Limits
*   Since the remainder is always in range $[0, k - 1]$, the size of `mod_index` is bounded by $\mathcal{O}(\min(n, k))$. If $k$ is extremely large ($2^{31} - 1$), the space complexity is bounded by $\mathcal{O}(n)$. If $n$ is very large but $k$ is small, the space is bounded by $\mathcal{O}(k)$.

### 2. Modulo Arithmetic on Negative Numbers
*   In Python, the `%` operator on negative numbers yields a positive remainder (e.g. `-1 % 5 = 4`). In C++, `%` yields a negative or zero remainder (e.g. `-1 % 5 = -1`). 
*   Although the current problem constraints specify `nums[i] >= 0`, keeping mod arithmetic portable is standard best practice. If elements could be negative, the C++ code would need to normalize the remainder:
    ```cpp
    prefix = ((prefix + nums[i]) % k + k) % k;
    ```

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | We perform a single loop over `nums`. Dictionary lookups and insertions are $\mathcal{O}(1)$ average. |
| **Space Complexity** | $\mathcal{O}(\min(n, k))$ | The hash map can contain at most $\min(n, k)$ unique modulo remainders. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if k can be 0?
*   **Answer**: If $k = 0$, we cannot perform `% k` because of division by zero.
*   **Solution**: 
    *   Mathematically, a sum is a multiple of $0$ if and only if the sum is exactly $0$.
    *   If the question allowed $k = 0$ (as in older versions of this LeetCode problem), we would handle it by skipping the `% k` step and storing the actual prefix sums in the map. The condition for a multiple of $0$ then simply becomes `prefix_sum == previous_prefix_sum`, indicating a subarray sum of $0$.

### Q2: What if we want to find the longest good subarray?
*   **Answer**: The current algorithm already stores the *earliest* index of each remainder in `mod_index` (because we do not overwrite the value if the remainder is already present).
*   **Solution**: To find the longest subarray, instead of returning `true` immediately when we find a match, we compute the length `i - mod_index[prefix]`, track the maximum length seen so far, and return it at the end.

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain the `mod_index[0] = -1` Initialization**: Explicitly walk the interviewer through why `0: -1` is essential. If the array starts with `[23, 2, 4]` and $k = 6$, at index $2$ the prefix sum is $29 \bmod 6 = 5$. At index $4$, the sum is $42 \bmod 6 = 0$. Since `prefix = 0`, we look up `0` in our map. With `0: -1`, the length is $4 - (-1) = 5 \ge 2$, which is correct. Without `mod_index[0] = -1`, we would miss prefix sums that are multiples of $k$ starting at index `0`.
*   **Prevent Index Overwrite**: Make a strong point that `mod_index[prefix] = i` must **only** be executed if `prefix` is not already in the map. Overwriting the index would shrink subsequent subarray lengths, potentially failing the length $\ge 2$ check.
