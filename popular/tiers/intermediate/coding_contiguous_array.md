# Contiguous Array

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 525, Glassdoor
- **Flashcards**: [Prefix Sum deck](../../flash_cards/coding/prefix_sum.md)

---

## Question Description

Given a binary array `nums`, return the maximum length of a contiguous subarray with an equal number of `0` and `1`.

### Examples
*   **Input**: `nums = [0, 1]`
    *   **Output**: `2`
    *   **Explanation**: `[0, 1]` is the longest contiguous subarray with an equal number of 0 and 1.
*   **Input**: `nums = [0, 1, 0]`
    *   **Output**: `2`
    *   **Explanation**: `[0, 1]` (or `[1, 0]`) is the longest contiguous subarray with an equal number of 0 and 1.

---

## Detailed Solution (C++)

To find the maximum length of a contiguous subarray with an equal number of `0` and `1`:
1. Treat every `0` in `nums` as a `-1` and every `1` as `+1`.
2. The problem then reduces to finding the longest subarray whose sum is exactly `0`.
3. The sum of a subarray from index $i+1$ to $j$ is $0$ if and only if the prefix sum at $i$ is equal to the prefix sum at $j$.
4. We maintain a running prefix sum `count`. We store the first index at which each `count` value is encountered in a hash map (or array) `first`.
5. We initialize `first[0] = -1` to handle subarrays that start at index `0`.
6. For each index `i`, we update `count`. If `count` is already in the map, the subarray from `first[count] + 1` to `i` has a sum of `0`. We update our maximum length with `i - first[count]`. If it is not in the map, we record `first[count] = i`.

### Standard C++ Production Code

```cpp
#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution {
public:
    int findMaxLength(const std::vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        
        // Key: running balance (count of 1s minus count of 0s)
        // Value: first index where this balance was achieved
        std::unordered_map<int, int> first;
        first[0] = -1; // Base case: balance is 0 before starting

        int max_len = 0;
        int count = 0;

        for (int i = 0; i < n; ++i) {
            count += (nums[i] == 1) ? 1 : -1;

            auto it = first.find(count);
            if (it != first.end()) {
                max_len = std::max(max_len, i - it->second);
            } else {
                first[count] = i;
            }
        }

        return max_len;
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
    def findMaxLength(self, nums: List[int]) -> int:
        """
        Finds the maximum length of a contiguous subarray with equal number of 0s and 1s.
        
        Time Complexity: O(N)
        Space Complexity: O(N)
        """
        # Map running balance to first index where it occurred
        first_occurrence = {0: -1}
        
        max_len = 0
        balance = 0
        
        for i, num in enumerate(nums):
            # Treat 1 as +1 and 0 as -1
            balance += 1 if num == 1 else -1
            
            if balance in first_occurrence:
                max_len = max(max_len, i - first_occurrence[balance])
            else:
                first_occurrence[balance] = i
                
        return max_len
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Hash Table Overhead vs Pre-allocated Arrays
*   In Python, dict searches are highly optimized but still carry the overhead of hashing. In a performance-critical situation or in lower-level languages like C++, we can replace the hash map with a single flat array.
*   Since the running balance `count` must lie within $[-n, n]$, we can offset the index by $n$ to map balances to a pre-allocated vector of size $2n + 1$. This eliminates hashing entirely and operates with $\mathcal{O}(1)$ direct array index accesses.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | We scan the array of size $n$ exactly once. Hash map operations take $\mathcal{O}(1)$ on average. |
| **Space Complexity** | $\mathcal{O}(n)$ | In the worst case, the running balance increases or decreases monotonically, resulting in $\mathcal{O}(n)$ unique balances in the map. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Can we solve this in O(1) space if we are allowed to modify the input or use some properties?
*   **Answer**: No. Unlike the sliding window technique which can achieve $\mathcal{O}(1)$ space for non-negative array elements, this problem requires tracking arbitrary balance differences. Because the balance can fluctuate up and down (non-monotonically), we cannot use a simple sliding window. The historical states must be stored, making $\mathcal{O}(n)$ space a theoretical lower bound for this problem.

### Q2: What if we want to find the maximum length subarray with equal numbers of three different values (e.g., 0, 1, and 2)?
*   **Answer**: 
    *   Let $C_0(i)$, $C_1(i)$, and $C_2(i)$ be the counts of 0s, 1s, and 2s up to index $i$.
    *   We want a subarray from $i+1$ to $j$ with equal counts of 0s, 1s, and 2s:
        $$C_0(j) - C_0(i) = C_1(j) - C_1(i) = C_2(j) - C_2(i)$$
    *   This can be rearranged into two independent equations:
        $$C_1(j) - C_0(j) = C_1(i) - C_0(i)$$
        $$C_2(j) - C_1(j) = C_2(i) - C_1(i)$$
    *   We can store the state as a pair of differences: `(count_1 - count_0, count_2 - count_1)`.
    *   We map this state tuple to the first index it occurred, using the same hash map logic.

---

## Pro-Tip: How to Impress the Interviewer

*   **Introduce the Branchless / Offset Array Optimization**: Explain to the interviewer that you can write a highly optimized C++ solution that replaces `std::unordered_map` with a flat array/vector of size $2n + 1$. This avoids memory allocation during the loop and keeps the entire lookup table cache-local:
    ```cpp
    int findMaxLength(const std::vector<int>& nums) {
        int n = nums.size();
        // Index offset is n. Balance range is [-n, n], mapped to [0, 2n]
        std::vector<int> first(2 * n + 1, -2); // Use -2 to represent uninitialized
        first[n] = -1; // balance 0 is at offset n

        int max_len = 0;
        int balance = 0;
        for (int i = 0; i < n; ++i) {
            balance += (nums[i] == 1) ? 1 : -1;
            int lookup_index = balance + n;
            if (first[lookup_index] >= -1) {
                max_len = std::max(max_len, i - first[lookup_index]);
            } else {
                first[lookup_index] = i;
            }
        }
        return max_len;
    }
    ```
    This shows a solid understanding of memory layouts, cache performance, and how to eliminate dynamic allocations in latency-sensitive systems.
