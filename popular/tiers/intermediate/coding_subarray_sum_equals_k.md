# Subarray Sum Equals K

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 560, Glassdoor
- **Flashcards**: [Prefix Sum deck](../../flash_cards/coding/prefix_sum.md)

---

## Question Description

Given an array of integers `nums` and an integer `k`, return the total number of subarrays whose sum equals to `k`.

A subarray is a contiguous non-empty sequence of elements within an array.

### Examples
*   **Input**: `nums = [1, 1, 1]`, `k = 2`
    *   **Output**: `2` (subarrays are `nums[0..1]` and `nums[1..2]`)
*   **Input**: `nums = [1, 2, 3]`, `k = 3`
    *   **Output**: `2` (subarrays are `nums[0..1]` and `nums[2..2]`)

---

## Detailed Solution (C++)

This problem is solved efficiently using **Prefix Sums** combined with a **Hash Map**:
1. Let $S[i]$ be the prefix sum $\sum_{m=0}^{i} \text{nums}[m]$.
2. The sum of a subarray $\text{nums}[i \dots j]$ is given by $S[j] - S[i-1]$ (with $S[-1] = 0$).
3. We seek the number of pairs $(i, j)$ such that $S[j] - S[i-1] = k$, which rewriting gives:
   $$S[i-1] = S[j] - k$$
4. As we iterate through the array, we compute the running prefix sum `curr`. We check how many times the prefix sum `curr - k` has occurred so far. We add this count to our total, and then record the occurrence of the current prefix sum `curr` in our hash map.

### Standard C++ Production Code

```cpp
#include <vector>
#include <unordered_map>

class Solution {
public:
    int subarraySum(const std::vector<int>& nums, int k) {
        // Hash map to store prefix sum frequencies
        std::unordered_map<long long, int> prefix_freq;
        prefix_freq[0] = 1; // Base case: a prefix sum of 0 has occurred once (empty prefix)

        int count = 0;
        long long curr = 0;

        for (int num : nums) {
            curr += num;
            
            // Check if (curr - k) exists in the map
            auto it = prefix_freq.find(curr - k);
            if (it != prefix_freq.end()) {
                count += it->second;
            }

            // Increment frequency of the current prefix sum
            prefix_freq[curr]++;
        }

        return count;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the Python implementation using `defaultdict` for clean frequency updates.

```python
from typing import List
from collections import defaultdict

class Solution:
    def subarraySum(self, nums: List[int], k: int) -> int:
        """
        Calculates the number of subarrays that sum to k using prefix sum frequencies.
        
        Time Complexity: O(N)
        Space Complexity: O(N)
        """
        count = 0
        curr_sum = 0
        
        # Hash map containing prefix sum -> frequency
        prefix_freq = defaultdict(int)
        prefix_freq[0] = 1  # Base case for prefix sum starting from index 0
        
        for num in nums:
            curr_sum += num
            
            # If (curr_sum - k) is a prefix sum we have seen, it means
            # the subarray between that previous point and the current point sums to k.
            count += prefix_freq[curr_sum - k]
            
            # Record the current prefix sum
            prefix_freq[curr_sum] += 1
            
        return count
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Choice of Dictionary Implementation
*   Using `collections.defaultdict(int)` is highly idiomatic and avoids explicit key-check logic (e.g. `if key in map:` or `map.get(key, 0)`). 
*   However, be aware that accessing a missing key in a `defaultdict` automatically inserts that key with a default value of `0`. In memory-constrained scenarios or very large datasets, using `.get(curr_sum - k, 0)` is slightly more memory-efficient as it avoids inserting unused query keys into the dictionary.

### 2. Large Integer Precision
*   Python handles arbitrarily large integers natively, meaning `curr_sum` will never overflow, regardless of how large the values in `nums` are. In C++, we use `long long` for the running prefix sum `curr` to prevent potential integer overflows if constraints are larger (though standard 32-bit signed integers are usually sufficient for this problem's standard bounds).

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | We perform a single pass through the array. Hash map lookups and insertions take $\mathcal{O}(1)$ on average. |
| **Space Complexity** | $\mathcal{O}(n)$ | In the worst case, all prefix sums are unique, requiring $\mathcal{O}(n)$ entries in the hash map. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if all numbers in the array are non-negative?
*   **Answer**: If all elements are non-negative ($nums[i] \ge 0$), we can use a **Sliding Window (Two Pointers)** approach:
    1. Maintain `left` and `right` pointers representing a window.
    2. Expand the window by moving `right` and adding elements to `window_sum`.
    3. If `window_sum` exceeds `k`, contract the window by moving `left` until `window_sum <= k`.
    4. If `window_sum == k`, increment the count. (Careful handling is needed if `0` is allowed in the array).
*   **Complexity**: This optimization reduces the space complexity to $\mathcal{O}(1)$ while keeping the time complexity at $\mathcal{O}(n)$.

### Q2: What if we need to return the actual indices of the subarrays instead of the count?
*   **Answer**: Instead of storing the frequency of prefix sums in the hash map, we store the **list of indices** where each prefix sum occurred:
    *   `std::unordered_map<long long, std::vector<int>> prefix_indices;`
    *   When we find `curr - k` in the map, we iterate through its list of stored indices and output the range `[index + 1, current_index]`.
*   **Complexity**: The space complexity remains $\mathcal{O}(n)$ to store indices, but the worst-case time complexity becomes $\mathcal{O}(n^2)$ if we must output all matching pairs (e.g. for an array of all zeros and $k=0$).

---

## Pro-Tip: How to Impress the Interviewer

*   **Initialize the Base Case**: Emphasize why `prefix_freq[0] = 1` is necessary. Explain that this represents the empty prefix sum before the first element. Without this, any subarray starting at index `0` that sums to `k` would not be counted since `curr - k` would be `0` and wouldn't be found in the map.
*   **Discuss Hash Map Collisions and Load Factor**: In C++, `std::unordered_map` uses chaining for collision resolution. If the hash function is poor or there are many collisions, lookup time can degrade to $\mathcal{O}(n)$. Mentioning `reserve()` or custom hashers (like custom `splitmix64` hashers) shows deep knowledge of standard library internals and real-world system optimization.
