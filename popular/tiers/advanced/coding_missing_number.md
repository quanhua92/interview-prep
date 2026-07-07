# Missing Number

- **Category**: Coding
- **Difficulty**: Easy
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 268, Glassdoor

---

## Question Description

Given an array `nums` containing $n$ distinct numbers in the range $[0, n]$, return *the only number in the range that is missing from the array.*

### Examples
*   **Input**: `nums = [3,0,1]`
    *   **Output**: `2`
    *   **Explanation**: $n = 3$ since there are 3 numbers, so all numbers are in the range $[0,3]$. `2` is the missing number in the range since it does not appear in `nums`.
*   **Input**: `nums = [0,1]`
    *   **Output**: `2`
    *   **Explanation**: $n = 2$ since there are 2 numbers, so all numbers are in the range $[0,2]$. `2` is the missing number in the range since it does not appear in `nums`.
*   **Input**: `nums = [9,6,4,2,3,5,7,0,1]`
    *   **Output**: `8`
    *   **Explanation**: $n = 9$ since there are 9 numbers, so all numbers are in the range $[0,9]$. `8` is the missing number in the range since it does not appear in `nums`.

---

## Detailed Solution (C++)

The core algorithm is **Cyclic Sort**. The key idea is that since the array contains numbers in the range $[0, n]$, each number $v$ should ideally be placed at index $v$ (except for $n$, which has no valid index in a 0-indexed array of size $n$).

We iterate through the array:
1. If the current number `nums[i]` is less than $n$ and is not at its correct index (i.e., `nums[i] != nums[nums[i]]`), we swap `nums[i]` with the element at its correct index `nums[nums[i]]`.
2. We repeat the check for the new element swapped into `nums[i]` without advancing the loop index $i$.
3. If `nums[i] >= n` or is already at its correct index, we advance $i$.

After placing all possible elements in their correct indices, we make a final linear pass: the first index $i$ where `nums[i] != i` represents the missing number. If all numbers from $0$ to $n-1$ are present at their matching indices, then the missing number must be $n$.

### Standard C++ Production Code

```cpp
#include <vector>
#include <utility>

class Solution {
public:
    int missingNumber(std::vector<int>& nums) noexcept {
        int n = static_cast<int>(nums.size());
        int i = 0;
        
        // Phase 1: Cyclic Sort in-place
        while (i < n) {
            int correct = nums[i];
            // Swap to correct position if nums[i] is in the range [0, n - 1]
            // and it is not already at its correct position
            if (correct < n && nums[i] != nums[correct]) {
                std::swap(nums[i], nums[correct]);
            } else {
                i++;
            }
        }
        
        // Phase 2: Find the missing element
        for (i = 0; i < n; ++i) {
            if (nums[i] != i) {
                return i;
            }
        }
        
        return n;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation using Cyclic Sort.

```python
from typing import List

class Solution:
    def missingNumber(self, nums: List[int]) -> int:
        """
        Finds the missing number in the range [0, n] using Cyclic Sort.
        
        Time Complexity: O(n)
        Space Complexity: O(1)
        """
        i = 0
        n = len(nums)
        
        # Phase 1: Cyclic Sort
        while i < n:
            correct = nums[i]
            # Verify correct index is within boundary and the value is not already sorted
            if correct < n and nums[i] != nums[correct]:
                nums[i], nums[correct] = nums[correct], nums[i]
            else:
                i += 1
                
        # Phase 2: Identify mismatch
        for i in range(n):
            if nums[i] != i:
                return i
                
        return n
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. The Trap of Dynamic Index Reassignment
*   A common Python gotcha is trying to swap in a single line using: `nums[i], nums[nums[i]] = nums[nums[i]], nums[i]`.
*   In Python, the expressions on the right-hand side are evaluated first, but the assignments on the left-hand side are done sequentially from left to right. Because `nums[i]` is updated in the first assignment, the second target index `nums[i]` changes, leading to an incorrect swap or infinite loop.
*   *Solution*: Always store the target index in a local variable (e.g., `correct = nums[i]`) before executing the swap, or use a temporary variable.

### 2. Space Optimization & Garbage Collection Overhead
*   Using built-in Python constructs like `set(nums)` or sorting with `nums.sort()` violates the strict $\mathcal{O}(1)$ auxiliary space constraint. 
*   `set(nums)` creates a hash table under the hood, allocating memory proportional to the size of the array. The cyclic sort implementation operates purely in-place, preventing dynamic allocations and reducing memory pressure on Python's garbage collector.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | Each element is swapped at most once to its correct index. The loop index is incremented at most $n$ times. The final linear scan takes $\mathcal{O}(n)$ time. |
| **Space Complexity** | $\mathcal{O}(1)$ | The sort is performed completely in-place, requiring constant auxiliary storage. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How do you solve this problem if the array is read-only (immutable)?
*   **The Problem**: Cyclic sort requires modifying the input array in-place. If the input is immutable, cyclic sort cannot be applied.
*   **The Solutions**:
    1.  **Math Formula**: Calculate the expected sum of the numbers $[0, n]$ using $S = \frac{n(n+1)}{2}$. Subtract the sum of the array from $S$ to obtain the missing number.
        ```python
        def missingNumberMath(nums: List[int]) -> int:
            n = len(nums)
            return (n * (n + 1)) // 2 - sum(nums)
        ```
    2.  **Bitwise XOR**: XOR all indices and elements. Because $x \oplus x = 0$, every present element cancels out its index counterpart, leaving only the missing number.
        ```python
        def missingNumberXOR(nums: List[int]) -> int:
            missing = len(nums)
            for i, num in enumerate(nums):
                missing ^= i ^ num
            return missing
        ```

### Q2: What are the trade-offs between the Math and XOR solutions?
*   **Integer Overflow**: In low-level languages (C++ or Java), if $n$ is very large (e.g., $n \approx 2^{31} - 1$), the term $n(n+1)$ will overflow a standard 32-bit signed or unsigned integer. The XOR solution does not suffer from overflow since bitwise operations do not accumulate magnitude.
*   **Hardware Efficiency**: XOR operations execute in a single CPU cycle on modern hardware and do not require multiplication or division, making it highly optimal at the machine level.

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention Cache Line Thrashing**: Highlight that cyclic sort performs arbitrary memory swaps across the array. While it achieves optimal theoretical time complexity, it can cause cache misses and line thrashing on large datasets. If memory is not constrained, a linear-scan math approach has much better spatial locality and will run faster on modern CPUs.
*   **Avoid the Unsigned Underflow on Empty Checks**: In C++, always be mindful of unsigned arithmetic when working with `std::vector::size()`. Even though this specific problem guarantees $n \ge 1$, explicitly casting `size()` to a signed integer (`int`) shows defensive programming hygiene.
