# Smallest Good Base

- **Category**: Coding
- **Difficulty**: Hard
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 483, Glassdoor
- **Flashcards**: [Binary Search deck](../../flash_cards/coding/binary_search.md)

---

## Question Description

Given an integer $n$ represented as a string, return the *smallest good base* of $n$.

We call $k \ge 2$ a **good base** of $n$ if all digits of $n$ base $k$ are $1$'s.

### Examples

*   **Input**: `n = "13"`
    *   **Output**: `"3"`
    *   **Explanation**: $13$ base $3$ is $111$ ($3^2 + 3^1 + 3^0 = 9 + 3 + 1 = 13$).
*   **Input**: `n = "4681"`
    *   **Output**: `"8"`
    *   **Explanation**: $4681$ base $8$ is $11111$ ($8^4 + 8^3 + 8^2 + 8^1 + 8^0 = 4096 + 512 + 64 + 8 + 1 = 4681$).
*   **Input**: `n = "1000000000000000000"`
    *   **Output**: `"999999999999999999"`
    *   **Explanation**: $10^{18}$ base $10^{18}-1$ is $11$ ($k^1 + k^0 = (n-1) + 1 = n$).

### Constraints
*   $n$ is an integer in the range $[3, 10^{18}]$.
*   $n$ does not contain any leading zeros.

---

## Detailed Solution (C++)

A base $k \ge 2$ is a good base of $n$ if there exists an integer $m \ge 2$ (representing the number of digits) such that:
$$n = k^{m-1} + k^{m-2} + \dots + k + 1 = \sum_{i=0}^{m-1} k^i$$

We want to find the **smallest** base $k$. Since $k$ and $m$ are inversely proportional, minimizing the base $k$ is equivalent to maximizing the number of digits $m$.

### Key Mathematical Boundaries:
1.  **Maximum number of digits $m$**:
    The smallest possible base is $k = 2$. Therefore, $n \ge 2^{m-1}$, which means $m \le \log_2(n) + 1 \approx 62$ for $n \le 10^{18}$.
2.  **Evaluating for a fixed $m$**:
    For a fixed digit count $m$, we can search for a valid base $k$ in the range $[2, n^{1/(m-1)}]$. Since $\sum_{i=0}^{m-1} k^i$ is strictly increasing with respect to $k$, we can use **Binary Search** to find the base $k$.
3.  **Upper Bound for Binary Search**:
    To prevent floating-point precision issues when estimating $n^{1/(m-1)}$, we set $hi = \lfloor n^{1/(m-1)} \rfloor + 2$.
4.  **Iteration Order**:
    We iterate $m$ from the maximum possible value ($\approx 62$) down to $2$. The first base $k$ we find is guaranteed to be the smallest good base. If no base is found for $m \ge 3$, the fallback is $m=2$, which corresponds to $k = n-1$.

### Standard C++ Production Code

```cpp
#include <string>
#include <cmath>
#include <algorithm>

class Solution {
private:
    // Helper function to calculate sum_{i=0}^{m-1} k^i while preventing overflow
    unsigned long long calculateSum(unsigned long long k, int m, unsigned long long limit) noexcept {
        unsigned long long sum = 0;
        for (int i = 0; i < m; ++i) {
            // Check for multiplication overflow
            if (sum > (limit - 1) / k) {
                return limit + 1; // Return a value larger than limit to signal overflow
            }
            sum = sum * k + 1;
        }
        return sum;
    }

public:
    std::string smallestGoodBase(const std::string& n) {
        unsigned long long num = std::stoull(n);
        
        // Find the maximum potential number of digits m
        // 64 - clzll yields the number of bits in num
        int max_m = 64 - __builtin_clzll(num);

        // Iterate from largest digit count to smallest (to minimize base k)
        for (int m = max_m; m >= 3; --m) {
            unsigned long long lo = 2;
            // Approximate upper bound using pow to avoid search space explosion
            unsigned long long hi = static_cast<unsigned long long>(std::pow(static_cast<double>(num), 1.0 / (m - 1))) + 2;

            while (lo <= hi) {
                unsigned long long mid = lo + (hi - lo) / 2;
                unsigned long long sum = calculateSum(mid, m, num);

                if (sum == num) {
                    return std::to_string(mid);
                } else if (sum < num) {
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
        }

        // Fallback case: m = 2, where n = k + 1 -> k = n - 1
        return std::to_string(num - 1);
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the iterative, type-hinted Python implementation. Python handles arbitrarily large integers natively, simplifying sum calculations.

```python
import math

class Solution:
    def smallestGoodBase(self, n: str) -> str:
        """
        Finds the smallest good base of n using binary search over the number of digits.
        
        Time Complexity: O(log^2 N)
        Space Complexity: O(1)
        """
        num = int(n)
        
        # Max bit length represents the maximum possible value of m (base 2)
        max_m = num.bit_length()

        # Helper function to evaluate the geometric sum
        def evaluate_base(k: int, m: int) -> int:
            total = 0
            for _ in range(m):
                total = total * k + 1
                if total > num:
                    return total
            return total

        # Iterate from largest possible digit count to smallest
        for m in range(max_m, 2, -1):
            lo = 2
            hi = int(num ** (1.0 / (m - 1))) + 2
            
            while lo <= hi:
                mid = (lo + hi) // 2
                val = evaluate_base(mid, m)
                
                if val == num:
                    return str(mid)
                elif val < num:
                    lo = mid + 1
                else:
                    hi = mid - 1

        # Fallback: for m = 2, the base is always num - 1
        return str(num - 1)
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Integer Division and Large Power Calculations
* The expression `num ** (1.0 / (m - 1))` converts `num` to a float in Python. For numbers close to $10^{18}$, standard double-precision floats have 53 bits of precision (up to $9 \times 10^{15}$), which can introduce precision errors. 
* To safeguard against float precision loss, we add a buffer of `+ 2` to `hi` to ensure the correct base is never excluded from the search range.

### 2. Large Integers
* Python dynamically handles integer overflow, meaning we do not need to check for integer wrap-around (like in C++'s `stoull`). However, calculating large powers of `k` can still grow exponentially in execution time if unchecked. The early exit check `if total > num:` inside `evaluate_base` is critical to prevent redundant execution.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(\log^2 n)$ | Outer loop runs $\approx \log n$ times. The binary search runs $\approx \log n$ times, with each evaluation taking $\mathcal{O}(\log n)$ multiplication steps. |
| **Space Complexity** | $\mathcal{O}(1)$ | Only standard integer variables are used. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Why do we search from $m = \text{max\_m}$ down to $2$, rather than $2$ up to $\text{max\_m}$?
* **Answer**: We are looking for the **smallest** base $k$. Since a smaller base $k$ results in a larger number of digits $m$, we must find the **largest** $m$ that satisfies the condition. Iterating from largest $m$ downwards allows us to return the first matching base immediately, optimizing execution time.

### Q2: What mathematical approximation can we use to skip binary search?
* **Answer**: For a fixed $m$, the equation is $n \approx k^{m-1}$. Thus, $k \approx n^{1/(m-1)}$. We can directly check if $k = \lfloor n^{1/(m-1)} \rfloor$ is a good base. This reduces the time complexity from $\mathcal{O}(\log^2 n)$ to $\mathcal{O}(\log n)$ since we only evaluate a single candidate base for each $m$.

---

## Pro-Tip: How to Impress the Interviewer

* **Use Bitwise Helpers**: Demonstrating knowledge of compiler intrinsics (e.g. `__builtin_clzll` in GCC/Clang) or the `bit_length()` method in Python to quickly determine the number of active bits shows that you write optimized, platform-aware system code.
* **Proactively Prevent Overflow**: Discussing how to prevent overflow in the accumulator `sum = sum * k + 1` in C++ *before* multiplying (i.e. checking `sum > (limit - 1) / k`) proves your depth in low-level safety and arithmetic robustness.
