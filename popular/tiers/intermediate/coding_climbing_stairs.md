# Climbing Stairs

- **Category**: Coding
- **Difficulty**: Easy
- **Target Role**: Software Engineer / QA & Test Engineer
- **Source**: LeetCode 70, Glassdoor

---

## Question Description

You are climbing a staircase. It takes $n$ steps to reach the top.

Each time you can either climb $1$ or $2$ steps. In how many distinct ways can you climb to the top?

### Examples
*   **Input**: `n = 2`
    *   **Output**: `2`
    *   **Explanation**: There are two ways to climb to the top:
        1. 1 step + 1 step
        2. 2 steps
*   **Input**: `n = 3`
    *   **Output**: `3`
    *   **Explanation**: There are three ways to climb to the top:
        1. 1 step + 1 step + 1 step
        2. 1 step + 2 steps
        3. 2 steps + 1 step

**Constraints**:
*   $1 \le n \le 45$

---

## Detailed Solution (C++)

The problem exhibits a **Fibonacci sequence** structure. To reach step $n$, you must come from either step $n-1$ (by taking 1 step) or step $n-2$ (by taking 2 steps).
Therefore, the recurrence relation is:
$$DP[i] = DP[i-1] + DP[i-2]$$
With base cases:
*   $DP[1] = 1$
*   $DP[2] = 2$

We optimize the space complexity from $\mathcal{O}(n)$ to $\mathcal{O}(1)$ by keeping track of only the last two steps using two variables `a` and `b`.

### Standard C++ Production Code

```cpp
#include <stdexcept>

class Solution {
public:
    int climbStairs(int n) {
        // Guard against non-positive input
        if (n <= 0) {
            return 0;
        }
        if (n <= 2) {
            return n;
        }

        int a = 1; // DP[i-2]
        int b = 2; // DP[i-1]

        for (int i = 3; i <= n; ++i) {
            int current = a + b;
            a = b;
            b = current;
        }

        return b;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the iterative space-optimized Python implementation with proper type hints.

```python
class Solution:
    def climbStairs(self, n: int) -> int:
        """
        Calculates the number of distinct ways to climb n stairs.
        
        Time Complexity: O(n)
        Space Complexity: O(1)
        """
        if n <= 0:
            return 0
        if n <= 2:
            return n

        a, b = 1, 2
        for _ in range(3, n + 1):
            a, b = b, a + b
            
        return b
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Python Integer Precision
Unlike languages with fixed-width integers (e.g., C++ where `int` can easily overflow if $n$ is large), Python handles arbitrary-precision integers out of the box. 
For $n = 45$, the result fits in a standard 32-bit integer, but for significantly larger $n$, C++ would overflow unless using a big integer library or returning modulo arithmetic, whereas Python would automatically scale up to handle the large number.

### 2. Tail-Call Optimization (TCO) Lack in Python
If you were to implement this recursively with memoization, Python does not support Tail-Call Optimization (TCO). This means a recursive implementation of $O(n)$ depth will allocate $n$ stack frames. For large $n$ (above Python's limit of ~1000), it will raise a `RecursionError`. The iterative approach is much safer and uses $\mathcal{O}(1)$ space instead of $\mathcal{O}(n)$ call stack memory.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | We perform a single loop from 3 to $n$. |
| **Space Complexity** | $\mathcal{O}(1)$ | We only maintain two variables (`a` and `b`) to track the previous states. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if you can climb 1, 2, or 3 steps at a time? (Tribonacci)
*   **Answer**: The recurrence relation shifts to $DP[i] = DP[i-1] + DP[i-2] + DP[i-3]$. The base cases will be $DP[1]=1, DP[2]=2, DP[3]=4$. We can still optimize space using three variables `a`, `b`, and `c`.

### Q2: What if we want to solve it in $\mathcal{O}(\log n)$ time?
*   **Answer**: We can represent the linear recurrence relation using **Matrix Exponentiation**:
    $$\begin{pmatrix} DP[i] \\ DP[i-1] \end{pmatrix} = \begin{pmatrix} 1 & 1 \\ 1 & 0 \end{pmatrix} \begin{pmatrix} DP[i-1] \\ DP[i-2] \end{pmatrix}$$
    By finding $\begin{pmatrix} 1 & 1 \\ 1 & 0 \end{pmatrix}^{n-1}$ via binary exponentiation (similar to fast power), we can obtain the result in $\mathcal{O}(\log n)$ time.

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention Matrix Exponentiation**: Even if the interviewer is happy with the $\mathcal{O}(n)$ space-optimized solution, mention that the time complexity can be reduced to $\mathcal{O}(\log n)$ using matrix exponentiation. This displays a strong mathematical foundation.
*   **Identify Overflow Limitations**: Explicitly mention that while $n \le 45$ keeps the Fibonacci value within standard 32-bit signed integer limits ($DP[45] = 1,836,311,903$, while max signed 32-bit int is $2,147,483,647$), if $n$ were $46$, it would overflow in C++ (`int`), requiring `long long` or standard big-integer handling.
