# Super Egg Drop

- **Category**: Coding
- **Difficulty**: Hard
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 887, Glassdoor
- **Flashcards**: [Dynamic Programming deck](../../flash_cards/coding/dynamic_programming.md)

---

## Question Description

You are given $k$ identical eggs and you have access to a building with $n$ floors numbered from $1$ to $n$.

There exists a critical floor $f$ where $0 \le f \le n$. Any egg dropped from a floor higher than $f$ will break, and any egg dropped from floor $f$ or below will survive.

Return *the minimum number of moves you need to determine $f$ with certainty*.

In each move, you may take an unbroken egg and drop it from any floor $x$ ($1 \le x \le n$). If the egg breaks, you cannot drop it again. You can only determine $f$ if you know with certainty that $f == x$ after some number of drops.

### Examples
*   **Input**: `k = 1`, `n = 2`
    *   **Output**: `2`
    *   **Explanation**:
        *   Drop the egg from floor 1. If it breaks, $f = 0$.
        *   If it does not break, drop it from floor 2. If it breaks, $f = 1$. Otherwise, $f = 2$.
        *   Thus, we need at most 2 moves.
*   **Input**: `k = 3`, `n = 14`
    *   **Output**: `4`
*   **Input**: `k = 2`, `n = 100`
    *   **Output**: `14`

**Constraints**:
*   $1 \le k \le 100$
*   $1 \le n \le 10^4$

---

## Detailed Solution (C++)

A traditional dynamic programming approach defines `dp[i][j]` as the minimum drops to test $j$ floors with $i$ eggs. This leads to the recurrence:
$$\text{dp}[i][j] = 1 + \min_{1 \le x \le j} \Big( \max(\text{dp}[i-1][x-1], \text{dp}[i][j-x]) \Big)$$
This takes $\mathcal{O}(k \cdot n^2)$ or $\mathcal{O}(k \cdot n \log n)$ time, which is too slow for very large $n$.

### Mathematical Re-framing (Dual DP)
Instead of asking "what is the minimum moves to test $n$ floors with $k$ eggs?", we ask:
**"Given $m$ moves and $k$ eggs, what is the maximum number of floors we can test?"**

Let `dp[m][k]` be the maximum number of floors we can test with $m$ moves and $k$ eggs.
Suppose we drop an egg from an optimal floor $X$.
1.  **The egg breaks**: We have $k-1$ eggs and $m-1$ moves left. The maximum floors we can check below $X$ is `dp[m-1][k-1]`.
2.  **The egg survives**: We have $k$ eggs and $m-1$ moves left. The maximum floors we can check above $X$ is `dp[m-1][k]`.

Including floor $X$ itself, the maximum number of floors we can cover is:
$$\text{dp}[m][k] = \text{dp}[m-1][k-1] + \text{dp}[m-1][k] + 1$$

We want to find the smallest number of moves $m$ such that `dp[m][k] >= n`.
Since the state `dp[m][k]` only depends on the previous move `m-1`, we can optimize space to $\mathcal{O}(k)$ by using a 1D array updated in-place from right to left.

### Standard C++ Production Code

```cpp
#include <vector>

class Solution {
public:
    int superEggDrop(int k, int n) {
        // dp[i] represents the maximum floors we can test with currently 'moves' moves and i eggs.
        std::vector<int> dp(k + 1, 0);
        int moves = 0;

        // Loop until the maximum testable floors with k eggs exceeds or equals n
        while (dp[k] < n) {
            moves++;
            // Update backward to use state from moves - 1
            for (int i = k; i >= 1; --i) {
                dp[i] = dp[i] + dp[i - 1] + 1;
            }
        }

        return moves;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the space-optimized Python implementation with type hints.

```python
class Solution:
    def superEggDrop(self, k: int, n: int) -> int:
        """
        Calculates the minimum number of moves to find the critical floor.
        
        Time Complexity: O(K * Moves) where Moves <= N
        Space Complexity: O(K)
        """
        # dp[i] is the maximum floors we can test with current moves and i eggs
        dp = [0] * (k + 1)
        moves = 0

        while dp[k] < n:
            moves += 1
            # Update backward to prevent overwriting values needed for the transition
            for i in range(k, 0, -1):
                dp[i] = dp[i] + dp[i - 1] + 1

        return moves
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. In-place Update Order
*   We must iterate the inner loop backward (`range(k, 0, -1)`). 
*   If we updated forward, `dp[i - 1]` would already represent the value for `moves` instead of `moves - 1`. This is identical to the space-compression mechanism in the 0-1 Knapsack problem.

### 2. Time-Limit Safety
*   When $k = 1$, the number of moves is $n$, so the outer loop runs $n$ times. With $n = 10^4$ and $k = 1$, the inner loop is small, and the total operations are around $10^4$, which is well within Python's safety margin.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(k \cdot m)$ | Where $m$ is the number of moves returned. Since $m \le \log_2 n$ for large $k$ and $m = n$ for $k=1$, worst-case time complexity is $\mathcal{O}(k \cdot \min(n, 2^{\text{something}}))$. For practical constraints, it is extremely fast. |
| **Space Complexity** | $\mathcal{O}(k)$ | We only maintain a 1D DP array of size $k + 1$. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What is the worst-case number of moves when $k=1$?
*   **Answer**: When we have only 1 egg, we cannot risk breaking it because we would have 0 eggs left to test the remaining floors. Thus, we must test floors sequentially from $1$ to $n$. The worst-case number of moves is exactly $n$.

### Q2: What is the optimal number of moves when we have an infinite number of eggs ($k \ge \log_2(n) + 1$)?
*   **Answer**: If we have sufficient eggs, we can perform a standard **binary search** on the floors. Each drop halves the search space. The maximum number of moves required is $\lceil \log_2(n + 1) \rceil$.

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain the Dual State Representation**: Most candidates only memorize the standard $O(k \cdot n \log n)$ DP with binary search. Explaining the dual state formulation (re-framing the problem to maximize floors for given moves) demonstrates a higher-order capacity for math and problem-solving.
*   **Connect to Pascal's Triangle**: Point out that the recurrence relation $\text{dp}[m][k] = \text{dp}[m-1][k-1] + \text{dp}[m-1][k] + 1$ resembles the recurrence of binomial coefficients (Pascal's Triangle):
    $$\binom{n}{k} = \binom{n-1}{k-1} + \binom{n-1}{k}$$
    In fact, $\text{dp}[m][k] = \sum_{i=1}^{k} \binom{m}{i}$. Discussing this closed-form mathematical representation shows deep structural intuition.
