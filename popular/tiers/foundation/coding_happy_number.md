# Happy Number

- **Category**: Coding
- **Difficulty**: Easy
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 202, Glassdoor

---

## Question Description

Write an algorithm to determine if a number `n` is "happy".

A happy number is a number defined by the following process:
1.  Starting with any positive integer, replace the number by the sum of the squares of its digits.
2.  Repeat the process until the number equals $1$ (where it will stay), or it loops endlessly in a cycle which does not include $1$.
3.  Those numbers for which this process ends in $1$ are happy.

Return `true` if `n` is a happy number, and `false` if not.

### Examples
*   **Input**: `n = 19`
    *   **Output**: `true`
    *   **Explanation**:
        *   $1^2 + 9^2 = 82$
        *   $8^2 + 2^2 = 68$
        *   $6^2 + 8^2 = 100$
        *   $1^2 + 0^2 + 0^2 = 1$
*   **Input**: `n = 2`
    *   **Output**: `false`

---

## Detailed Solution (C++)

A naive approach uses a hash set to keep track of visited numbers. However, we can detect cycles with zero auxiliary space using **Floyd's Cycle-Finding Algorithm** (Slow and Fast pointers). 

We define a helper function `getNext(n)` to calculate the sum of the squares of the digits of `n`.
*   We initialize `slow` to `n` and `fast` to `getNext(n)`.
*   In each step, `slow` transitions to `getNext(slow)`, while `fast` transitions to `getNext(getNext(fast))`.
*   If `fast` reaches $1$, the number is happy. If `slow` and `fast` meet at any value other than $1$, we have detected a cycle, meaning the number is not happy.

### Standard C++ Production Code

```cpp
#include <cstddef>

class Solution {
private:
    // Helper function to calculate sum of squared digits
    int getNext(int num) const noexcept {
        int total = 0;
        while (num > 0) {
            int digit = num % 10;
            total += digit * digit;
            num /= 10;
        }
        return total;
    }

public:
    bool isHappy(int n) const noexcept {
        int slow = n;
        int fast = getNext(n);

        while (fast != 1 && slow != fast) {
            slow = getNext(slow);
            fast = getNext(getNext(fast));
        }

        return fast == 1;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation. It uses `divmod` to optimize the digit extraction loop.

```python
class Solution:
    def isHappy(self, n: int) -> bool:
        """
        Determines if a number is happy using Floyd's Cycle-Finding Algorithm.
        
        Time Complexity: O(log N)
        Space Complexity: O(1)
        """
        def get_next(num: int) -> int:
            total = 0
            while num > 0:
                # divmod returns (num // 10, num % 10) in a single optimized operation
                num, digit = divmod(num, 10)
                total += digit * digit
            return total

        slow = n
        fast = get_next(n)

        while fast != 1 and slow != fast:
            slow = get_next(slow)
            fast = get_next(get_next(fast))

        return fast == 1
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Optimizing Digit Extraction with `divmod`
*   In Python, performing division (`//`) and modulo (`%`) separately results in two bytecode lookups and operations.
*   The built-in function `divmod(x, y)` returns both the quotient and remainder as a tuple `(x // y, x % y)`. It is implemented in C and runs faster than performing the operations individually, which is a great trick for python performance tuning.

### 2. Space Benefits of Pointer Approach
*   A hash-set implementation in Python requires dynamic allocation of hash-table slots. In Python, each integer object occupies $28$ bytes of memory, and set entry overhead is high.
*   By using slow and fast pointers, we only store two integers, avoiding garbage collection overhead and heap allocation pressure.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(\log n)$ | The number of digits in $n$ is $\log_{10} n$. The time taken to calculate the next value is proportional to the number of digits. The sequence either reaches $1$ or enters a small, bounded cycle extremely quickly. |
| **Space Complexity** | $\mathcal{O}(1)$ | No extra memory or hash sets are used; only pointers/integers are stored. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Why is it guaranteed that the sequence of numbers will not grow infinitely?
*   **The Answer**: For any number $n$, let's analyze how the sum of the squares of its digits behaves.
    *   A $d$-digit number has a value of at least $10^{d-1}$.
    *   The maximum possible sum of squares of digits for a $d$-digit number is $d \times 9^2 = 81d$.
    *   For $d \ge 4$, $10^{d-1} > 81d$ (for example, if $d=4$, the minimum value is $1000$ and the maximum sum of squares is $4 \times 81 = 324$).
    *   This means any number $n \ge 1000$ will strictly shrink at each step until it is less than $1000$.
    *   For numbers below $1000$, the maximum value is $999$, which transitions to $3 \times 81 = 243$.
    *   Thus, the sequence is always trapped in a finite state space $[1, 243]$. Since the state space is finite, the sequence must eventually repeat a value, either entering a cycle or landing on $1$.

### Q2: What is the cycle that non-happy numbers fall into?
*   **The Answer**: All non-happy numbers eventually cycle through the same loop:
    $$4 \to 16 \to 37 \to 58 \to 89 \to 145 \to 42 \to 20 \to 4$$
*   Knowing this, we could optimize the solution for systems with extremely tight timing budgets by checking if the sequence ever hits `4` (or any other number in that cycle). If it does, we can return `false` immediately.

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain Mathematical Convergence**: Proactively explain the convergence proof shown in Q1. Showing that you can mathematically prove why an algorithm terminates (and does not stack overflow or run forever) demonstrates computer science maturity.
*   **Mention Lookup Tables**: Mention that for a high-throughput system processing millions of numbers, we can precompute the happiness of all integers up to $1000$ in a static bitset/lookup array. Any input number can then be reduced to a number $< 1000$ in a single digit-square step, followed by an $\mathcal{O}(1)$ lookup.
