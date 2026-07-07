# Matchsticks to Square

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect / QA & Test Engineer
- **Source**: LeetCode 473, Glassdoor

---

## Question Description

You are given an integer array `matchsticks` where `matchsticks[i]` is the length of the $i$-th matchstick. You want to use **all** the matchsticks to make one square. You should not break any stick, but you can link them up, and each matchstick must be used **exactly one time**.

Return `true` if you can make this square and `false` otherwise.

### Examples

*   **Input**: `matchsticks = [1,1,2,2,2]`
    *   **Output**: `true`
    *   **Explanation**: You can form a square of length 2: one side is formed by the two sticks of length 1, and the other three sides are formed by the three sticks of length 2.
*   **Input**: `matchsticks = [3,3,3,3,4]`
    *   **Output**: `false`
    *   **Explanation**: You cannot find a way to form a square using all the matchsticks.

### Constraints
*   $1 \le \text{matchsticks.length} \le 15$
*   $1 \le \text{matchsticks}[i] \le 10^8$

---

## Detailed Solution (C++)

The problem is equivalent to partitioning an array into 4 subsets of equal sum. This is a variation of the Bin Packing / Partition problem, which is NP-complete. We can solve it using backtracking.

To pass within strict execution time limits, we must apply key pruning strategies:
1.  **Sum Divisibility Check**: If the sum of all matchsticks is not divisible by 4, it is impossible to form a square. Return `false` immediately.
2.  **Descending Sort**: Sort the matchsticks in descending order. Placing larger matchsticks first fills up the sides quickly, triggering failure conditions much earlier in the recursion tree.
3.  **Symmetry Breaking**: If we fail to place `matchsticks[idx]` on `sides[i]`, and `sides[i]` is currently `0`, we can `break` and stop trying to place it on subsequent empty sides. Since all empty sides are symmetric, if placing it on `sides[i]` fails, it will also fail on any other empty side.

### Standard C++ Production Code

```cpp
#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
private:
    bool backtrack(const std::vector<int>& matchsticks, int idx, int side, std::vector<int>& sides) {
        if (idx == matchsticks.size()) {
            // Check if all four sides are equal to the target side length
            return sides[0] == side && sides[1] == side &&
                   sides[2] == side && sides[3] == side;
        }

        for (int i = 0; i < 4; ++i) {
            // Check if placing the matchstick exceeds target side length
            if (sides[i] + matchsticks[idx] <= side) {
                sides[i] += matchsticks[idx];
                if (backtrack(matchsticks, idx + 1, side, sides)) {
                    return true;
                }
                sides[i] -= matchsticks[idx]; // Backtrack

                // Symmetry Breaking: if this side becomes empty after backtracking,
                // and trying it failed, trying subsequent empty sides will also fail.
                if (sides[i] == 0) {
                    break;
                }
            }
        }
        return false;
    }

public:
    bool makesquare(std::vector<int>& matchsticks) {
        if (matchsticks.empty()) {
            return false;
        }

        long long total = std::accumulate(matchsticks.begin(), matchsticks.end(), 0LL);
        if (total % 4 != 0) {
            return false;
        }

        int side = static_cast<int>(total / 4);

        // Sort descending to optimize search space
        std::sort(matchsticks.begin(), matchsticks.end(), std::greater<int>());
        if (matchsticks[0] > side) {
            return false;
        }

        std::vector<int> sides(4, 0);
        return backtrack(matchsticks, 0, side, sides);
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

```python
from typing import List

class Solution:
    def makesquare(self, matchsticks: List[int]) -> bool:
        """
        Determines if matchsticks can be partitioned into 4 equal sides to form a square.
        
        Time Complexity: O(4^N) in the worst case, but heavily pruned in practice.
        Space Complexity: O(N)
        """
        if not matchsticks:
            return False

        total = sum(matchsticks)
        if total % 4 != 0:
            return False

        side = total // 4
        
        # Sort in descending order to prune early
        matchsticks.sort(reverse=True)
        if matchsticks[0] > side:
            return False

        sides = [0, 0, 0, 0]

        def backtrack(idx: int) -> bool:
            if idx == len(matchsticks):
                return sides[0] == sides[1] == sides[2] == side

            for i in range(4):
                if sides[i] + matchsticks[idx] <= side:
                    sides[i] += matchsticks[idx]
                    if backtrack(idx + 1):
                        return True
                    sides[i] -= matchsticks[idx] # Backtrack
                    
                    # Symmetry Breaking: if sides[i] is 0, trying subsequent empty buckets
                    # will also fail because empty buckets are identical.
                    if sides[i] == 0:
                        break
            return False

        return backtrack(0)
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Recursion Stack Limit
*   The maximum size of `matchsticks` is 15. The recursion depth is bounded by $N = 15$, which is negligible and will not trigger a stack overflow in Python.

### 2. Python Loop and Sort Performance
*   Sorting descending (`matchsticks.sort(reverse=True)`) is exceptionally fast in Python because the Timsort algorithm is implemented in C.
*   Python function lookup overhead inside recursion can be slightly optimized by using a nested function `backtrack(idx)`, which allows direct access to the `sides` list and `side` variable in the outer scope, avoiding the overhead of passing them as arguments.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(4^N)$ | Where $N$ is the number of matchsticks. Each matchstick has 4 choices. In practice, the search space is heavily reduced by descending sort and symmetry breaking. |
| **Space Complexity** | $\mathcal{O}(N)$ | The height of the recursion tree is $N$, requiring $\mathcal{O}(N)$ space on the stack. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Can we solve this using Dynamic Programming with Bitmask?
*   **The Answer**: Yes, since $N \le 15$, we can represent the subset of chosen matchsticks using a bitmask. Let `dp[mask]` represent the current side's accumulated length if we use the subset of matchsticks represented by the set bits in `mask`.
*   **Bitmask DP (Python) Implementation**:
    ```python
    def makesquareDP(matchsticks: List[int]) -> bool:
        n = len(matchsticks)
        total = sum(matchsticks)
        if total % 4 != 0: return False
        side = total // 4
        
        # dp[mask] stores the current side's length. -1 means invalid/unreachable state
        dp = [-1] * (1 << n)
        dp[0] = 0
        
        for mask in range(1 << n):
            if dp[mask] == -1:
                continue
            for i in range(n):
                # If the i-th matchstick is not used yet
                if not (mask & (1 << i)):
                    next_mask = mask | (1 << i)
                    # If it fits in the current side
                    if dp[mask] + matchsticks[i] <= side:
                        # If we complete one side, reset next state's current sum to 0
                        dp[next_mask] = (dp[mask] + matchsticks[i]) % side
                    
        return dp[(1 << n) - 1] == 0
    ```
*   **Complexity**: Time complexity becomes $\mathcal{O}(N \cdot 2^N)$ and Space Complexity becomes $\mathcal{O}(2^N)$. This is faster for worst-case inputs where backtracking doesn't prune well.

### Q2: What if we want to partition the matchsticks into $K$ equal sides instead of 4? (Partition to K Equal Sum Subsets)
*   **The Answer**: The problem becomes LeetCode 698. The backtracking algorithm can be generalized by replacing the hardcoded `4` sides with `K` sides (`std::vector<int> sides(K, 0)`). The symmetry breaking condition `if (sides[i] == 0) break;` becomes even more critical because the number of symmetric empty buckets increases.

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain the Mathematics of Symmetry Breaking**: Clearly explain that `sides[i] == 0` is a classic symmetry-breaking optimization. Explain that if we fail to place a matchstick into an empty bucket, placing it into another empty bucket is guaranteed to fail because the state of the buckets is indistinguishable.
*   **Discuss Backtracking vs. Bitmask DP**: Demonstrate a deep understanding of trade-offs. Backtracking works best when there is a solution or when early pruning is highly effective (saving memory and average-case CPU cycles). Bitmask DP is more robust against worst-case adversarial inputs because it prevents recalculating overlapping subproblems at the cost of $\mathcal{O}(2^N)$ memory.
