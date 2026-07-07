# Sum of Subarray Minimums

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 907, Glassdoor

---

## Question Description

Given an array of integers `arr`, find the sum of `min(b)`, where `b` ranges over every (contiguous) subarray of `arr`. Since the answer may be large, return the answer **modulo** $10^9 + 7$.

### Examples

*   **Input**: `arr = [3,1,2,4]`
    *   **Output**: `17`
    *   **Explanation**: 
        *   Subarrays are `[3]`, `[1]`, `[2]`, `[4]`, `[3,1]`, `[1,2]`, `[2,4]`, `[3,1,2]`, `[1,2,4]`, `[3,1,2,4]`.
        *   Minimums are `3, 1, 2, 4, 1, 1, 2, 1, 1, 1`.
        *   Sum of minimums is `17`.
*   **Input**: `arr = [11,81,94,43,3]`
    *   **Output**: `444`

---

## Detailed Solution (C++)

To solve this problem in linear time, we compute the contribution of each element `arr[i]` to the final sum. An element `arr[i]` acts as the minimum for any subarray that:
1. Starts after the **previous smaller element** on its left (index `left[i]`).
2. Ends before the **next smaller element** on its right (index `right[i]`).

Thus, the number of choices for the left boundary is `i - left[i]` and the number of choices for the right boundary is `right[i] - i`. The total number of subarrays where `arr[i]` is the minimum is `(i - left[i]) * (right[i] - i)`.

To avoid double-counting subarrays when there are duplicate elements, we define strict inequality on one side and non-strict inequality on the other:
*   On the left: we find the index of the first element that is **strictly smaller or equal** (`arr[left[i]] <= arr[i]`).
*   On the right: we find the index of the first element that is **strictly smaller** (`arr[right[i]] < arr[i]`).

We can find both the `left` and `right` boundary indices in $\mathcal{O}(n)$ time using a Monotonic Stack.

### Standard C++ Production Code (Single-Pass with Sentinel)

Instead of using two separate arrays and passes, we can compute the sum in a **single pass** using a sentinel value of `0` (since `arr[i] >= 1`).

```cpp
#include <vector>
#include <cstddef>

class Solution {
public:
    int sumSubarrayMins(std::vector<int>& arr) {
        const int n = static_cast<int>(arr.size());
        const long long MOD = 1000000007LL;
        
        std::vector<int> stack;
        stack.reserve(n + 1);
        long long total_sum = 0;

        // Iterate up to n to process the sentinel element (0) at index n
        for (int i = 0; i <= n; ++i) {
            // Use 0 as a sentinel to force-flush all remaining elements in the stack
            int current_val = (i == n) ? 0 : arr[i];

            while (!stack.empty() && arr[stack.back()] >= current_val) {
                int mid = stack.back();
                stack.pop_back();

                // Find left smaller boundary index (top of stack after popping)
                int left_boundary = stack.empty() ? -1 : stack.back();
                
                // Count of subarrays where arr[mid] is the minimum
                long long count_left = mid - left_boundary;
                long long count_right = i - mid;

                total_sum = (total_sum + static_cast<long long>(arr[mid]) * count_left * count_right) % MOD;
            }
            stack.push_back(i);
        }

        return static_cast<int>(total_sum);
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation using the single-pass sentinel approach.

```python
from typing import List

class Solution:
    def sumSubarrayMins(self, arr: List[int]) -> int:
        """
        Calculates the sum of minimums of all contiguous subarrays.
        
        Time Complexity: O(N)
        Space Complexity: O(N)
        """
        MOD = 10**9 + 7
        n = len(arr)
        total_sum = 0
        stack: List[int] = []

        # We append a sentinel 0 to the end of the array to flush the stack
        extended_arr = arr + [0]

        for i, val in enumerate(extended_arr):
            while stack and extended_arr[stack[-1]] >= val:
                mid = stack.pop()
                left_boundary = stack[-1] if stack else -1
                
                count_left = mid - left_boundary
                count_right = i - mid
                
                total_sum = (total_sum + extended_arr[mid] * count_left * count_right) % MOD
                
            stack.append(i)

        return total_sum
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Integer Modulo Behavior
* In Python, integer overflow is not a concern due to arbitrary-precision integers. However, applying `% (10**9 + 7)` in each iteration keeps the numbers small and fits standard performance targets.

### 2. Space Optimization
* Appending `[0]` to `arr` takes $\mathcal{O}(n)$ time and space because it copies the list. To optimize this, you can iterate over `range(n + 1)` and use a conditional check like `arr[i] if i < n else 0` to retrieve the current value, keeping auxiliary space limited strictly to the stack.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | Each element is pushed onto the stack once and popped at most once. |
| **Space Complexity** | $\mathcal{O}(n)$ | The stack requires at most $n$ elements in the worst case (e.g. if the array is sorted in ascending order). |

---

## Common Follow-Up Questions & How to Answer

### Q1: How does this problem relate to "Sum of Subarray Ranges" (LeetCode 2104)?
* **Answer**: LeetCode 2104 asks for the sum of `max(b) - min(b)` for all subarrays. This is mathematically equivalent to:
  $$\sum \text{max}(b) - \sum \text{min}(b)$$
  We can compute the sum of subarray minimums (using this algorithm) and the sum of subarray maximums (using a monotonic stack with the opposite comparison operators), and subtract the two sums to get the result in $\mathcal{O}(n)$ time.

### Q2: Can we solve this problem using Dynamic Programming?
* **Answer**: Yes, we can define `dp[i]` as the sum of the minimums of all subarrays ending at index `i`.
* If we know the index of the first smaller element to the left (let it be `j`), then:
  * For subarrays starting after `j`, the minimum element is `arr[i]` (there are `i - j` such subarrays).
  * For subarrays starting at or before `j`, the minimum element is determined by the minimums of subarrays ending at `j`. The sum of these minimums is exactly `dp[j]`.
* This yields the recurrence:
  `dp[i] = dp[j] + arr[i] * (i - j)`
* We can use a monotonic stack to find `j` for each `i`, resulting in a very clean $\mathcal{O}(n)$ DP + Stack solution.
* **Code Example (C++)**:
    ```cpp
    int sumSubarrayMins(std::vector<int>& arr) {
        int n = arr.size();
        std::vector<int> dp(n, 0);
        std::vector<int> stack;
        long long total = 0, MOD = 1e9 + 7;
        for (int i = 0; i < n; ++i) {
            while (!stack.empty() && arr[stack.back()] >= arr[i]) {
                stack.pop_back();
            }
            int prev_smaller = stack.empty() ? -1 : stack.back();
            dp[i] = (prev_smaller == -1 ? 0 : dp[prev_smaller]) + arr[i] * (i - prev_smaller);
            dp[i] %= MOD;
            total = (total + dp[i]) % MOD;
            stack.push_back(i);
        }
        return total;
    }
    ```

---

## Pro-Tip: How to Impress the Interviewer

* **Demonstrate Single-Pass Sentinel Flushing**: Presenting the single-pass sentinel flushing technique shows high-level fluency with stacks, simplifying standard 3-pass solutions into a single loop.
* **State DP Duality**: Mentioning that the problem can be reformulated as a Dynamic Programming state recurrence optimized by a Monotonic Stack shows that you can bridge the gap between different algorithmic paradigms (DP and stack-based parsing).
