# Coin Change II

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 518, Glassdoor

---

## Question Description

You are given an integer array `coins` representing coins of different denominations and an integer `amount` representing a total amount of money.

Return *the number of combinations that make up that amount*. If that amount of money cannot be made up by any combination of the coins, return `0`.

You may assume that you have an infinite number of each kind of coin.

The answer is guaranteed to fit into a signed 32-bit integer.

### Examples
*   **Input**: `amount = 5`, `coins = [1,2,5]`
    *   **Output**: `4`
    *   **Explanation**: There are four ways to make up the amount:
        1. 5 = 5
        2. 5 = 2 + 2 + 1
        3. 5 = 2 + 1 + 1 + 1
        4. 5 = 1 + 1 + 1 + 1 + 1
*   **Input**: `amount = 3`, `coins = [2]`
    *   **Output**: `0`
    *   **Explanation**: The amount of 3 cannot be made up just with coins of 2.
*   **Input**: `amount = 10`, `coins = [10]`
    *   **Output**: `1`

**Constraints**:
*   $1 \le \text{coins.length} \le 300$
*   $1 \le \text{coins}[i] \le 5000$
*   All the values of `coins` are **unique**.
*   $0 \le \text{amount} \le 5000$

---

## Detailed Solution (C++)

This is another variation of the **unbounded knapsack** problem. Unlike the original Coin Change problem where we seek the minimum number of coins, here we need to find the number of unique combinations.

### Transition and Loop Order
Let `dp[a]` be the number of combinations to make up amount `a`.
We initialize `dp[0] = 1` (there is exactly 1 way to make amount 0: using no coins).

To avoid counting permutations (e.g. counting `1 + 2` and `2 + 1` as separate combinations), **the outer loop must iterate over the coins**, and the inner loop must iterate over the amounts.
$$\text{dp}[a] \leftarrow \text{dp}[a] + \text{dp}[a - \text{coin}]$$
By processing one coin denomination at a time, we ensure that coins are used in a non-decreasing order of index, eliminating ordering duplicates.

### Standard C++ Production Code

```cpp
#include <vector>

class Solution {
public:
    int change(int amount, std::vector<int>& coins) {
        if (amount < 0) {
            return 0;
        }

        // dp[a] stores the number of combinations to form amount a
        std::vector<int> dp(amount + 1, 0);
        dp[0] = 1;

        // Loop over each coin first to prevent counting permutations as different combinations
        for (int coin : coins) {
            for (int a = coin; a <= amount; ++a) {
                dp[a] += dp[a - coin];
            }
        }

        return dp[amount];
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation.

```python
from typing import List

class Solution:
    def change(self, amount: int, coins: List[int]) -> int:
        """
        Computes the number of combinations that make up the given amount.
        
        Time Complexity: O(N * Amount) where N is coins.length
        Space Complexity: O(Amount)
        """
        if amount < 0:
            return 0

        dp = [0] * (amount + 1)
        dp[0] = 1

        for coin in coins:
            for a in range(coin, amount + 1):
                dp[a] += dp[a - coin]

        return dp[amount]
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Swapping Loop Order (The Permutations Trap)
*   A common Python mistake is to write the outer loop over the range of amounts:
    ```python
    # WARNING: THIS COMPUTES PERMUTATIONS, NOT COMBINATIONS
    for a in range(1, amount + 1):
        for coin in coins:
            if coin <= a:
                dp[a] += dp[a - coin]
    ```
    This computes the number of ordered sequences. For example, with `amount = 3` and `coins = [1, 2]`, this incorrect version would output `3` (for sequences `[1, 1, 1]`, `[1, 2]`, and `[2, 1]`). The correct combinations version outputs `2` (since `[1, 2]` and `[2, 1]` are the same combination).

### 2. Large Precision
*   While the problem constraints guarantee the answer fits in a 32-bit signed integer, Python automatically handles integer expansions so there's never any risk of overflow errors even if constraints are increased.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(N \cdot A)$ | Where $N$ is the number of coins and $A$ is the target `amount`. |
| **Space Complexity** | $\mathcal{O}(A)$ | We maintain a 1D DP table of size `amount + 1`. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How do we modify the algorithm to compute permutations (where order matters)?
*   **Answer**: As explained above, we simply swap the loops. We iterate over all amounts in the outer loop, and for each amount, we iterate over all coins:
    $$\text{dp}[a] = \sum_{\text{coin}} \text{dp}[a - \text{coin}]$$

### Q2: What if we are limited in the number of coins we can use (e.g. 0-1 Knapsack where each coin can only be used once)? (Coin Change II with single-use coins)
*   **Answer**: This changes from unbounded knapsack to 0-1 knapsack. To do this with $\mathcal{O}(A)$ space, we must iterate the inner amount loop **backward** (from `amount` down to `coin`):
    ```cpp
    for (int coin : coins) {
        for (int a = amount; a >= coin; --a) {
            dp[a] += dp[a - coin];
        }
    }
    ```
    Iterating backward prevents using the same coin multiple times, because we calculate `dp[a]` using the state of the *previous* iteration's `dp[a - coin]`.

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain the Order of Loops Clear-headedly**: The most important differentiator in this problem is explaining *why* the loop order controls combinations vs. permutations. Explaining that the outer loop forces a fixed lexicographical ordering of coin selections (e.g., we choose all 1s, then all 2s, then all 5s) shows a deep understanding of state space representations in Dynamic Programming.
*   **Highlight Cache Efficiency**: Mention that iterating the amount index sequentially in the inner loop (`for (int a = coin; a <= amount; a++)`) provides sequential memory access which maximizes CPU cache hit rates.
