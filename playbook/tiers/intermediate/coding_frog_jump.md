# Frog Jump

- **Category**: Coding
- **Difficulty**: Hard
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 403, Glassdoor
- **Flashcards**: [Dynamic Programming deck](../../flash_cards/coding/dynamic_programming.md)

---

## Question Description

A frog is crossing a river. The river is divided into some number of units, and at each unit, there may or may not exist a stone. The frog can jump on a stone, but it must not jump into the water.

Given a list of `stones` positions (in units) in sorted ascending order, determine if the frog can cross the river by landing on the last stone. Initially, the frog is on the first stone and assumes the first jump must be $1$ unit.

If the frog's last jump was $k$ units, its next jump must be either $k - 1$, $k$, or $k + 1$ units. The frog can only jump in the forward direction.

### Examples
*   **Input**: `stones = [0,1,3,5,6,8,12,17]`
    *   **Output**: `true`
    *   **Explanation**: The frog can jump to the last stone by jumping 1 unit to the 2nd stone, then 2 units to the 3rd stone, then 2 units to the 4th stone, then 3 units to the 6th stone, 4 units to the 7th stone, and 5 units to the 8th stone.
*   **Input**: `stones = [0,1,2,3,4,8,9,11]`
    *   **Output**: `false`
    *   **Explanation**: There is no way to jump to the last stone as the gap between the 5th and 6th stone is too large.

**Constraints**:
*   $2 \le \text{stones.length} \le 2000$
*   $0 \le \text{stones}[i] \le 2^{31} - 1$
*   `stones[0] == 0`
*   `stones` is sorted in a strictly increasing order.

---

## Detailed Solution (C++)

In C++, we can model this using a bottom-up Dynamic Programming table where `dp[i][k]` indicates whether the frog can reach the $i$-th stone with a last jump of size $k$.
Since the maximum number of stones $N$ is at most $2000$, and the maximum possible jump size cannot exceed $N$ (since the jump size increases by at most 1 each step starting from $0$), the maximum jump $k$ is bounded by $N$.

*   **State**: `dp[i][k]` is a boolean indicating if stone $i$ is reachable with a last jump of size $k$.
*   **Transition**: From a reachable state `dp[i][k] == true`, the next jump can be $step \in \{k-1, k, k+1\}$ (where $step > 0$). If there exists a stone $j$ at position `stones[i] + step`, we set `dp[j][step] = true`.
*   We can search for the target position `stones[i] + step` efficiently using **Binary Search** (`std::lower_bound` or manual binary search) on the sorted `stones` array.

### Standard C++ Production Code

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    bool canCross(std::vector<int>& stones) {
        int n = static_cast<int>(stones.size());
        
        // Edge Case: The first jump must be exactly 1 unit.
        // If the second stone is not at position 1, the frog cannot make the first jump.
        if (n < 2 || stones[1] != 1) {
            return false;
        }

        // dp[i][k]: can we reach stone i with a last jump of k?
        // Since maximum jump step is <= n, a size of (n) x (n + 1) is sufficient.
        std::vector<std::vector<bool>> dp(n, std::vector<bool>(n + 1, false));
        dp[0][0] = true;

        for (int i = 0; i < n; ++i) {
            for (int k = 0; k <= n; ++k) {
                if (!dp[i][k]) {
                    continue;
                }

                // If k == 0 (initial state), we must jump exactly 1 unit.
                int min_step = (k == 0) ? 1 : std::max(1, k - 1);
                int max_step = k + 1;

                for (int step = min_step; step <= max_step; ++step) {
                    long long target = static_cast<long long>(stones[i]) + step;

                    // Binary search to find if target stone exists
                    auto it = std::lower_bound(stones.begin() + i + 1, stones.end(), target);
                    if (it != stones.end() && *it == target) {
                        int dest_idx = static_cast<int>(std::distance(stones.begin(), it));
                        if (step <= n) {
                            dp[dest_idx][step] = true;
                        }
                    }
                }
            }
        }

        // Check if any jump size k can reach the last stone
        for (int k = 0; k <= n; ++k) {
            if (dp[n - 1][k]) {
                return true;
            }
        }

        return false;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the top-down memoized DFS implementation. We check existence of destination stones in $\mathcal{O}(1)$ average time using a set.

```python
from typing import List

class Solution:
    def canCross(self, stones: List[int]) -> bool:
        """
        Determines if the frog can cross the river by landing on the last stone.
        
        Time Complexity: O(N^2)
        Space Complexity: O(N^2)
        """
        if len(stones) < 2 or stones[1] != 1:
            return False

        stone_set = set(stones)
        target_stone = stones[-1]
        memo = {}

        def dfs(pos: int, last_jump: int) -> bool:
            # Base Case: Reached the last stone
            if pos == target_stone:
                return True
            
            state = (pos, last_jump)
            if state in memo:
                return memo[state]

            # Try jumps: last_jump - 1, last_jump, last_jump + 1
            # Initial state pos = 0, last_jump = 0 allows next jump of 1
            min_jump = max(1, last_jump - 1)
            for step in range(min_jump, last_jump + 2):
                next_pos = pos + step
                if next_pos in stone_set:
                    if dfs(next_pos, step):
                        memo[state] = True
                        return True

            memo[state] = False
            return False

        return dfs(0, 0)
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Hash Map (`memo`) vs 2D Array
*   In Python, using a dictionary `memo` with tuples `(pos, last_jump)` as keys is more memory-efficient than allocating a full $2000 \times 2000$ 2D list because many combinations of `(pos, last_jump)` are unreachable.
*   This also avoids pre-allocation overhead and maintains excellent readability.

### 2. Recursion Limit
*   The maximum depth of the call stack is bounded by the number of stones $N = 2000$. Python's default recursion limit is $1000$. 
*   In a real interview, you should mention that you might need to adjust the recursion limit using `sys.setrecursionlimit(3000)` if $N$ is large, or convert the DFS to an iterative stack-based solution to prevent `RecursionError`.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n^2)$ | In C++, there are $n$ positions, each with up to $n$ jump sizes. Binary search takes $\mathcal{O}(\log n)$ making it $\mathcal{O}(n^2 \log n)$ worst-case, but practically much faster. In Python, there are at most $n^2$ states visited, each taking $\mathcal{O}(1)$ due to set lookup. |
| **Space Complexity** | $\mathcal{O}(n^2)$ | To store the visited states (size of the DP table or the hash map). |

---

## Common Follow-Up Questions & How to Answer

### Q1: Can we use BFS instead of DFS?
*   **Answer**: Yes, we can use a Queue to store pairs of `(position, last_jump)`. We also maintain a `visited` set to avoid reprocessing the same state. BFS is often beneficial if a path exists early, but uses more memory for the queue in the worst-case.

### Q2: What happens if the positions in `stones` are not sorted?
*   **Answer**: We must sort the array first in $\mathcal{O}(n \log n)$ time. Sorting is required to perform binary searches and to easily identify the target last stone.

---

## Pro-Tip: How to Impress the Interviewer

*   **Proactively Catch Static State Bugs in C++**: Never use `static bool dp[2001][2001]` in shared application environments (like LeetCode or multi-threaded servers) without clearing it. Doing so will leak states from previous test runs, causing incorrect outputs. Utilizing `std::vector` ensures thread-safe, correct execution.
*   **Explain the Jump Bound**: Prove mathematically why the jump size $k$ cannot exceed $N$. Since we start with $k=0$ and each jump can increase the jump size by at most $1$, at the $i$-th stone, the maximum jump size is $i$. Since $i < n$, $k \le n$. This justifies the $\mathcal{O}(n^2)$ state space bounds.
