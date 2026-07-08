# Optimal Division

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 553, Glassdoor
- **Flashcards**: [Dynamic Programming deck](../../flash_cards/coding/dynamic_programming.md)

---

## Question Description

You are given an integer array `nums`. The adjacent integers in `nums` will perform float division.
*   For example, if `nums = [2, 3, 4]`, we evaluate the expression `2 / 3 / 4`.

However, you can add any number of parentheses at any position to change the priority of operations. You want to add these parentheses such that the value of the expression after the evaluation is **maximum**.

Return *the corresponding expression that has the maximum value in string format*.

**Note**: Your expression should not contain redundant parentheses.

### Examples
*   **Input**: `nums = [1000,100,10,2]`
    *   **Output**: `"1000/(100/10/2)"`
    *   **Explanation**:
        `1000/(100/10/2) = 1000/((100/10)/2) = 1000/(10/2) = 1000/5 = 200`
        The parenthesized version `"1000/((100/10)/2)"` contains redundant outer parentheses in the denominator, so we return `"1000/(100/10/2)"`.
        Other groupings yield smaller results:
        *   `1000 / 100 / 10 / 2 = 0.5`
        *   `1000 / (100 / 10) / 2 = 50`
        *   `1000 / (100 / (10 / 2)) = 50`
        *   `1000 / 100 / (10 / 2) = 2`
*   **Input**: `nums = [2,3,4]`
    *   **Output**: `"2/(3/4)"`
    *   **Explanation**: `2 / (3 / 4) = 8 / 3 = 2.667`.

**Constraints**:
*   $1 \le \text{nums.length} \le 10$
*   $2 \le \text{nums}[i] \le 1000$
*   There is only one optimal division for the given input.

---

## Detailed Solution (C++)

While this problem is categorized under **Dynamic Programming**, a mathematical analysis reveals an optimal $\mathcal{O}(n)$ greedy solution.

### Mathematical Proof of Greedy Optimality
For any expression of the form:
$$X = \text{nums}[0] / \text{nums}[1] / \text{nums}[2] / \dots / \text{nums}[n-1]$$
1.  Since all $\text{nums}[i] \ge 2$, multiplying by any number increases the value, and dividing by any number decreases it.
2.  Regardless of how parentheses are placed, the first number $\text{nums}[0]$ will always remain in the **numerator** (since no operator precedes it).
3.  The second number $\text{nums}[1]$ will always remain in the **denominator** (since it is directly divided by $\text{nums}[0]$, and any parentheses group starting at index 1 is still placed in the denominator).
4.  For any subsequent number $\text{nums}[i]$ ($i \ge 2$), it can either be in the numerator or denominator. To maximize the overall expression, we should place all subsequent numbers in the **numerator** if possible.
5.  By grouping the entire denominator together:
    $$\text{nums}[0] / (\text{nums}[1] / \text{nums}[2] / \dots / \text{nums}[n-1])$$
    We mathematically evaluate this as:
    $$\frac{\text{nums}[0]}{\frac{\text{nums}[1]}{\text{nums}[2] \times \dots \times \text{nums}[n-1]}} = \frac{\text{nums}[0] \times \text{nums}[2] \times \dots \times \text{nums}[n-1]}{\text{nums}[1]}$$
    This maximizes the numerator and minimizes the denominator. Thus, this single parenthesization is mathematically guaranteed to be the unique optimal division.

### Standard C++ Production Code (Greedy $\mathcal{O}(n)$)

```cpp
#include <string>
#include <vector>

class Solution {
public:
    std::string optimalDivision(std::vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        if (n == 0) {
            return "";
        }
        if (n == 1) {
            return std::to_string(nums[0]);
        }
        if (n == 2) {
            return std::to_string(nums[0]) + "/" + std::to_string(nums[1]);
        }

        // For n > 2: nums[0] / (nums[1] / nums[2] / ... / nums[n-1])
        std::string result = std::to_string(nums[0]) + "/(" + std::to_string(nums[1]);
        for (int i = 2; i < n; ++i) {
            result += "/" + std::to_string(nums[i]);
        }
        result += ")";
        
        return result;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the concise, Pythonic implementation using `join()`.

```python
from typing import List

class Solution:
    def optimalDivision(self, nums: List[int]) -> str:
        """
        Formats the optimal division to maximize the evaluated expression value.
        
        Time Complexity: O(N)
        Space Complexity: O(N)
        """
        n = len(nums)
        if n == 0:
            return ""
        if n == 1:
            return str(nums[0])
        if n == 2:
            return f"{nums[0]}/{nums[1]}"

        # Join the numbers from index 1 to end with '/', wrap in parentheses,
        # and prepend the first number.
        denominator = "/".join(map(str, nums[1:]))
        return f"{nums[0]}/({denominator})"
```

---

## Dynamic Programming Alternative (Conceptual)

If constraints were different (e.g. numbers could be fractions or negative, where greedy logic fails), we would use Dynamic Programming similar to Matrix Chain Multiplication:
*   **State**: For subarray `nums[i...j]`, store both `max_val` (with its string representation) and `min_val` (with its string representation).
*   **Transition**: 
    $$\text{maxVal}(i, j) = \max_{i \le k < j} \left( \frac{\text{maxVal}(i, k)}{\text{minVal}(k+1, j)} \right)$$
    $$\text{minVal}(i, j) = \min_{i \le k < j} \left( \frac{\text{minVal}(i, k)}{\text{maxVal}(k+1, j)} \right)$$
*   Time complexity of this DP approach would be $\mathcal{O}(n^3)$. Given $N \le 10$, this DP is highly feasible but mathematically redundant here.

---

## Python-Specific Complexities & Implementation Considerations

### 1. Fast String Interpolation with f-Strings
*   In Python, using f-strings (e.g., `f"{nums[0]}/({denominator})"`) is faster and cleaner than concatenation (`str(nums[0]) + "/(" + ...`) because f-strings are evaluated at runtime as optimized bytecode.

### 2. Standard `map` and `join`
*   `"/".join(map(str, nums[1:]))` is highly optimized in CPython, running the loop and conversion in native C, which is faster than manual string accumulation loops.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | We iterate through the array once to convert integers to strings and join them. |
| **Space Complexity** | $\mathcal{O}(n)$ | Auxiliary memory is used to store the output string. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if the elements in `nums` could be float values between 0 and 1?
*   **Answer**: The greedy solution fails because dividing by a value between 0 and 1 increases the result (e.g., $X / 0.5 = 2X$). We would have to fall back to the $\mathcal{O}(n^3)$ Dynamic Programming approach (outlined in the DP Alternative section) to find the exact combinations of max/min values for all intervals.

### Q2: How do you prove that `nums[1]` must always be in the denominator?
*   **Answer**: The expression is evaluated from left to right by default. The division operator immediately following `nums[0]` is `/`. Since it acts on `nums[0]` and whatever follows it (either `nums[1]` alone or a parenthesized expression starting with `nums[1]`), `nums[1]` will always act as a divisor to `nums[0]`. There is no way to place parentheses such that `nums[1]` is multiplied by `nums[0]`.

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain the DP fallback**: Even if you know the greedy $O(n)$ math shortcut, explain the general $O(n^3)$ Dynamic Programming solution first to show that you recognize the problem structure. Then, present the greedy mathematical optimization as a special-case optimization enabled by the constraint $\text{nums}[i] \ge 2$. This demonstrates superb domain expertise and flexibility.
*   **Prevent String Reallocation Overhead**: In languages like C++, appending to strings in a loop causes frequent reallocations. Mention that using `std::string::reserve()` with an estimated size based on digits and slashes is a good system-level hygiene optimization.
