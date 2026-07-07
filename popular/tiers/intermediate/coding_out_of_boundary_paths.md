# Out of Boundary Paths

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 576, Glassdoor

---

## Question Description

There is an $m \times n$ grid with a ball. The ball is initially at the position `[startRow, startColumn]`. You are allowed to move the ball to one of the four adjacent cells in the grid (possibly out of the grid crossing the grid boundary). You can apply at most `maxMove` moves to the ball.

Given the five integers $m$, $n$, `maxMove`, `startRow`, `startColumn`, return *the number of paths to move the ball out of the grid boundary*. Since the answer can be very large, return it **modulo $10^9 + 7$**.

### Examples
*   **Input**: `m = 2`, `n = 2`, `maxMove = 2`, `startRow = 0`, `startColumn = 0`
    *   **Output**: `6`
*   **Input**: `m = 1`, `n = 3`, `maxMove = 3`, `startRow = 0`, `startColumn = 1`
    *   **Output**: `12`

**Constraints**:
*   $1 \le m, n \le 50$
*   $0 \le \text{maxMove} \le 50$
*   $0 \le \text{startRow} < m$
*   $0 \le \text{startColumn} < n$

---

## Detailed Solution (C++)

This problem can be modeled as finding the total number of paths on a 2D grid that escape the boundaries within `maxMove` steps. 

*   **State**: `dp[r][c]` represents the number of paths that can reach cell `(r, c)` at the current move number.
*   **Transition**: In each step, a ball at cell `(r, c)` can move to 4 adjacent directions `(nr, nc)`.
    *   If the adjacent cell is **inside** the grid boundaries, the paths at `dp[r][c]` propagate to `nxt[nr][nc]`.
    *   If the adjacent cell is **outside** the grid boundaries, the ball escapes. The paths at `dp[r][c]` are added to our total escape path count `result`.
*   **Space Optimization**: Since the states for `move + 1` only depend on states from `move`, we can use two 2D grids (or flattened 1D arrays of size $m \times n$) and swap them after each move. This reduces space complexity from $\mathcal{O}(\text{maxMove} \cdot m \cdot n)$ to $\mathcal{O}(m \cdot n)$.

### Standard C++ Production Code

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        if (maxMove <= 0) {
            return 0;
        }

        constexpr int MOD = 1'000'000'007;
        
        // Flattened 1D representation for 2D DP to optimize memory footprint and CPU cache usage
        std::vector<int> dp(m * n, 0);
        std::vector<int> nxt(m * n, 0);

        // Start position has 1 path initially
        dp[startRow * n + startColumn] = 1;

        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        long long result = 0;

        for (int move = 0; move < maxMove; ++move) {
            std::fill(nxt.begin(), nxt.end(), 0);

            for (int r = 0; r < m; ++r) {
                for (int c = 0; c < n; ++c) {
                    int val = dp[r * n + c];
                    if (val == 0) {
                        continue; // Skip unreachable states
                    }

                    for (int d = 0; d < 4; ++d) {
                        int nr = r + dirs[d][0];
                        int nc = c + dirs[d][1];

                        if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                            nxt[nr * n + nc] = (nxt[nr * n + nc] + val) % MOD;
                        } else {
                            result = (result + val) % MOD;
                        }
                    }
                }
            }
            std::swap(dp, nxt);
        }

        return static_cast<int>(result);
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the space-optimized Python implementation using two 1D lists of size $m \times n$.

```python
class Solution:
    def findPaths(self, m: int, n: int, maxMove: int, startRow: int, startColumn: int) -> int:
        """
        Calculates the number of paths to move the ball out of boundary in at most maxMove moves.
        
        Time Complexity: O(maxMove * m * n)
        Space Complexity: O(m * n)
        """
        if maxMove <= 0:
            return 0

        MOD = 10**9 + 7
        
        # Flattened representation of m x n grid
        dp = [0] * (m * n)
        dp[startRow * n + startColumn] = 1
        
        dirs = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        result = 0

        for _ in range(maxMove):
            nxt = [0] * (m * n)
            for r in range(m):
                for c in range(n):
                    val = dp[r * n + c]
                    if val == 0:
                        continue
                    
                    for dr, dc in dirs:
                        nr, nc = r + dr, c + dc
                        if 0 <= nr < m and 0 <= nc < n:
                            nxt[nr * n + nc] = (nxt[nr * n + nc] + val) % MOD
                        else:
                            result = (result + val) % MOD
            dp = nxt

        return result
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Flattening the 2D Grid
*   Instead of using lists of lists (e.g. `dp[r][c]`), we flatten the 2D grid of size $m \times n$ into a single 1D list of size $m \cdot n$.
*   Accessing `dp[r * n + c]` is much faster in CPython because it avoids double-indirection pointer lookups (which require searching the heap for two separate list objects). This micro-optimization reduces Python execution time by $20\text{--}30\%$.

### 2. Iterative Space-swapping vs DFS Recursion
*   A recursive solution with `@lru_cache` (top-down) is simple to write but requires $\mathcal{O}(\text{maxMove} \cdot m \cdot n)$ stack frames. For large moves, this risks hitting the Python recursion depth limit and has high call overhead.
*   The iterative bottom-up layout with state-swapping keeps auxiliary memory to $\mathcal{O}(m \cdot n)$ and executes extremely fast.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(N \cdot m \cdot n)$ | Where $N$ is `maxMove`, $m$ is grid height, and $n$ is grid width. We iterate $N$ times over $m \times n$ states, doing 4 lookups per cell. |
| **Space Complexity** | $\mathcal{O}(m \cdot n)$ | Due to space-swapping, we only maintain two grids of size $m \times n$ instead of a 3D table of size $N \times m \times n$. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if `maxMove` is very large but the grid is small?
*   **Answer**: Similar to other FSM and grid-walk problems, if `maxMove` is up to $10^{18}$ and $m \times n \le 100$, we can model the transition using **Matrix Exponentiation** over a transition matrix of size $(m \cdot n + 1) \times (m \cdot n + 1)$ (where the $+1$ represents the sink escape state). However, matrix exponentiation is slow if $m \cdot n$ is large because multiplying matrices takes $\mathcal{O}((m \cdot n)^3)$ operations.

### Q2: How can we optimize this if $m$ and $n$ are large but `maxMove` is very small?
*   **Answer**: If `maxMove` is small (e.g. 5) but the grid is $10^9 \times 10^9$, we can use a **hash map** to store only the reachable states rather than allocating a full grid. Starting with `{ (startRow, startColumn): 1 }`, we transition to a new hash map on each step. Since the number of reachable states grows by at most $O(\text{maxMove}^2)$, the time and space complexity becomes $\mathcal{O}(\text{maxMove}^2)$ instead of $\mathcal{O}(\text{maxMove} \cdot m \cdot n)$, which is an enormous speedup.

---

## Pro-Tip: How to Impress the Interviewer

*   **Propose Sparse Map DP**: Bringing up the hash map approach for extremely large grids (e.g., $m, n = 10^9$, `maxMove = 10`) shows you don't just write static arrays but think about sparsity and how to optimize algorithms based on input data scales.
*   **Highlight Cache Locality**: Discuss how flattening the 2D array into a 1D vector (`dp[r * n + c]`) places contiguous row values next to each other in physical memory. When the processor loads a value, it loads the adjacent columns into L1 cache, preventing memory stalls.
