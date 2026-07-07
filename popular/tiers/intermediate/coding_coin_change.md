# Coin Change

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 322, Glassdoor
- **Flashcards**: [Dynamic Programming deck](../../flash_cards/coding/dynamic_programming.md)

---

## Question Description

You are given an integer array `coins` representing coins of different denominations and an integer `amount` representing a total amount of money.

Return *the fewest number of coins that you need to make up that amount*. If that amount of money cannot be made up by any combination of the coins, return `-1`.

You may assume that you have an infinite number of each kind of coin.

### Examples
*   **Input**: `coins = [1,2,5]`, `amount = 11`
    *   **Output**: `3`
    *   **Explanation**: $11 = 5 + 5 + 1$
*   **Input**: `coins = [2]`, `amount = 3`
    *   **Output**: `-1`
*   **Input**: `coins = [1]`, `amount = 0`
    *   **Output**: `0`

**Constraints**:
*   $1 \le \text{coins.length} \le 12$
*   $1 \le \text{coins}[i] \le 2^{31} - 1$
*   $0 \le \text{amount} \le 10^4$

---

## Detailed Solution (C++)

This problem represents the classic **unbounded knapsack** variation. Since we want to find the *minimum* number of coins to reach a target `amount`, we can construct a bottom-up Dynamic Programming table `dp` of size `amount + 1`.

*   **State**: `dp[i]` represents the minimum number of coins required to make up amount `i`.
*   **Initialization**: `dp[0] = 0` (zero coins needed for amount 0), and all other entries are initialized to a large value `INF = amount + 1` representing an unreachable state.
*   **Transition**: For each amount `i` from $1$ to `amount` and for each coin `c` in `coins`:
    $$\text{dp}[i] = \min(\text{dp}[i], \text{dp}[i - c] + 1) \quad (\text{if } c \le i)$$

### Standard C++ Production Code

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int coinChange(std::vector<int>& coins, int amount) {
        if (amount < 0) {
            return -1;
        }

        // Initialize table with amount + 1 (representing infinity)
        int INF = amount + 1;
        std::vector<int> dp(amount + 1, INF);
        dp[0] = 0;

        for (int i = 1; i <= amount; ++i) {
            for (int c : coins) {
                // Safely handle coin values that exceed current amount,
                // and guard against integer overflow in comparison.
                if (c <= i) {
                    dp[i] = std::min(dp[i], dp[i - c] + 1);
                }
            }
        }

        return dp[amount] < INF ? dp[amount] : -1;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the iterative bottom-up Python implementation.

```python
from typing import List

class Solution:
    def coinChange(self, coins: List[int], amount: int) -> int:
        """
        Computes the fewest number of coins needed to make up the given amount.
        
        Time Complexity: O(N * Amount) where N is coins.length
        Space Complexity: O(Amount)
        """
        if amount < 0:
            return -1

        INF = amount + 1
        dp = [INF] * (amount + 1)
        dp[0] = 0

        for i in range(1, amount + 1):
            for coin in coins:
                if coin <= i:
                    dp[i] = min(dp[i], dp[i - coin] + 1)

        return dp[amount] if dp[amount] != INF else -1
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Loop Order Optimization
*   In the solution above, we loop over the `amount` in the outer loop and `coins` in the inner loop. 
*   Because `coins.length` is very small ($\le 12$), this loop order allows `dp` array lookups to have good temporal locality.
*   In Python, swapping the loops:
    ```python
    for coin in coins:
        for i in range(coin, amount + 1):
            dp[i] = min(dp[i], dp[i - coin] + 1)
    ```
    can actually be slightly faster due to less conditional check overhead inside the inner loop and more efficient execution in the interpreter.

### 2. Large Coin Values
*   Since $\text{coins}[i] \le 2^{31} - 1$, some coin values could be far larger than `amount` (which is $\le 10^4$). Checking `if coin <= i` is essential to prevent accessing negative indices or allocating an unnecessarily large table.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(A \cdot N)$ | Where $A$ is the target `amount` and $N$ is the number of coin denominations (`coins.length`). |
| **Space Complexity** | $\mathcal{O}(A)$ | We allocate a dynamic programming state table of size `amount + 1`. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How would you return the actual coins used to form the amount, rather than just the count?
*   **Answer**: We can maintain an additional array `parent` of size `amount + 1`, where `parent[i]` stores the coin value used to transition to state `i` (i.e., the coin `c` that minimized `dp[i - c] + 1`). After filling the table, if `dp[amount]` is valid, we can backtrack from `amount` using `amount = amount - parent[amount]` until we reach $0$.

### Q2: What if we wanted to solve this using BFS?
*   **Answer**: Since all transition steps have a uniform edge weight of 1 coin, we can model the search space as a graph where each vertex is an amount and each edge is a coin transition. BFS can find the shortest path from $0$ to `amount`. However, because we can visit the same state multiple times, we must keep a `visited` set. For large amounts, BFS could use more memory than the DP array due to queue sizes.

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention Cache Line Exploitation**: Mention that the alternative loop ordering (`for coin in coins` as the outer loop) is highly cache-friendly. It sweeps sequentially through the `dp` array, accessing contiguous elements (`dp[i]` and `dp[i-coin]`), which makes excellent use of the CPU cache line prefetching.
*   **Discuss BFS vs. DP Trade-offs**: In practice, if the target amount is small but there are many large coins, BFS might terminate very early when it reaches `amount` on the first few layers. Pointing out this transition from DP to BFS under specific input distributions shows you possess strong analytical design skills.
