# Student Attendance Record II

- **Category**: Coding
- **Difficulty**: Hard
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 552, Glassdoor
- **Flashcards**: [Dynamic Programming deck](../../flash_cards/coding/dynamic_programming.md)

---

## Question Description

An attendance record for a student can be represented as a string where each character signifies whether the student was absent (`'A'`), late (`'L'`), or present (`'P'`) on that day.

A student is eligible for an attendance award if they meet **both** of the following criteria:
1.  The student was absent (`'A'`) for **strictly fewer than 2 days** in total.
2.  The student was late (`'L'`) for **fewer than 3 consecutive days** (i.e., they were never late 3 or more days in a row).

Given an integer `n`, return *the number of possible attendance records of length `n` that make a student eligible for an attendance award*. The answer may be very large, so return it **modulo $10^9 + 7$**.

### Examples
*   **Input**: `n = 2`
    *   **Output**: `8`
    *   **Explanation**: There are 8 records with length 2 that are eligible for an award:
        `"PP", "AP", "PA", "LP", "PL", "AL", "LA", "LL"`
        Only `"AA"` is not eligible because there are 2 absences.
*   **Input**: `n = 1`
    *   **Output**: `3`
*   **Input**: `n = 10101`
    *   **Output**: `183236316`

**Constraints**:
*   $1 \le n \le 10^5$

---

## Detailed Solution (C++)

This problem can be represented as a finite state machine (FSM) where the state is defined by:
1.  The total count of absences (`a`): either `0` or `1`. (If $\ge 2$, it is invalid).
2.  The count of consecutive late days at the end of the current record (`l`): either `0`, `1`, or `2`. (If $\ge 3$, it is invalid).

Thus, we have $2 \times 3 = 6$ valid states:
*   `dp[i][a][l]`: the number of eligible records of length `i` with `a` total absences and `l` consecutive late days at the end.

### Transitions
For each state `(a, l)` at length `i`, we can transition to length `i + 1` by appending one of:
1.  **Present (`'P'`)**: Resets consecutive late days to 0. Total absences `a` remains the same.
    *   `dp[i+1][a][0] += dp[i][a][l]`
2.  **Absent (`'A'`)**: Resets consecutive late days to 0. Increments total absences to `a + 1` (valid if $a < 1$).
    *   `dp[i+1][a+1][0] += dp[i][a][l]` (if $a < 1$)
3.  **Late (`'L'`)**: Increments consecutive late days to `l + 1` (valid if $l < 2$). Total absences `a` remains the same.
    *   `dp[i+1][a][l+1] += dp[i][a][l]` (if $l < 2$)

### Space Optimization
Since `dp[i+1]` only depends on `dp[i]`, we can compress the space complexity from $\mathcal{O}(n)$ to $\mathcal{O}(1)$ by using a rolling array of size $2$ along the first dimension (index `i % 2`).

### Standard C++ Production Code

```cpp
#include <vector>
#include <numeric>

class Solution {
public:
    int checkRecord(int n) {
        constexpr int MOD = 1'000'000'007;

        // dp[2][a][l] space-optimized DP table
        // dp[i % 2][a][l]: a in {0, 1}, l in {0, 1, 2}
        long long dp[2][2][3] = {};

        // Base case: at length 0, there is 1 way (empty string)
        dp[0][0][0] = 1;

        for (int i = 0; i < n; ++i) {
            int cur = i % 2;
            int nxt = 1 - cur;

            // Clear the next state's row
            for (int a = 0; a < 2; ++a) {
                for (int l = 0; l < 3; ++l) {
                    dp[nxt][a][l] = 0;
                }
            }

            // Distribute values to next states
            for (int a = 0; a < 2; ++a) {
                for (int l = 0; l < 3; ++l) {
                    long long val = dp[cur][a][l];
                    if (val == 0) {
                        continue;
                    }

                    // 1. Append 'P'
                    dp[nxt][a][0] = (dp[nxt][a][0] + val) % MOD;

                    // 2. Append 'A' (only if we currently have 0 absences)
                    if (a < 1) {
                        dp[nxt][a + 1][0] = (dp[nxt][a + 1][0] + val) % MOD;
                    }

                    // 3. Append 'L' (only if we have fewer than 2 consecutive late days)
                    if (l < 2) {
                        dp[nxt][a][l + 1] = (dp[nxt][a][l + 1] + val) % MOD;
                    }
                }
            }
        }

        int last = n % 2;
        long long result = 0;
        for (int a = 0; a < 2; ++a) {
            for (int l = 0; l < 3; ++l) {
                result = (result + dp[last][a][l]) % MOD;
            }
        }

        return static_cast<int>(result);
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the space-optimized Python implementation using an $\mathcal{O}(1)$ space array.

```python
class Solution:
    def checkRecord(self, n: int) -> int:
        """
        Returns the number of possible attendance records of length n eligible for award.
        
        Time Complexity: O(N)
        Space Complexity: O(1)
        """
        MOD = 10**9 + 7

        # dp[a][l] stores the count of records for current day
        # a in {0, 1}, l in {0, 1, 2}
        dp = [[0] * 3 for _ in range(2)]
        dp[0][0] = 1

        for _ in range(n):
            new_dp = [[0] * 3 for _ in range(2)]
            
            for a in range(2):
                for l in range(3):
                    val = dp[a][l]
                    if val == 0:
                        continue
                    
                    # 1. Append 'P'
                    new_dp[a][0] = (new_dp[a][0] + val) % MOD
                    
                    # 2. Append 'A'
                    if a < 1:
                        new_dp[a + 1][0] = (new_dp[a + 1][0] + val) % MOD
                        
                    # 3. Append 'L'
                    if l < 2:
                        new_dp[a][l + 1] = (new_dp[a][l + 1] + val) % MOD
            dp = new_dp

        # Sum up all valid states
        result = sum(sum(row) for row in dp) % MOD
        return result
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Multi-Dimensional Lists vs Flattening
*   In Python, initializing multi-dimensional lists (e.g. `[[0] * 3 for _ in range(2)]`) is simple. 
*   Since the size is extremely small ($2 \times 3$), we do not need to flatten the list into a 1D list of size 6. The overhead of multi-dimensional indexing in Python is negligible for a fixed small state space.

### 2. Time Limit Exceeded (TLE) Risks in Python
*   Python code execution is slower than compiled languages like C++. For $N = 10^5$, a triple loop with modulo arithmetic inside can run close to the time limit if not written cleanly.
*   By using the space-optimized structure and checking `if val == 0: continue`, we prune unvisited states and significantly accelerate runtime.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | We loop $n$ times. For each step, we perform at most $2 \times 3 \times 3$ transitions, which is a constant number of operations. |
| **Space Complexity** | $\mathcal{O}(1)$ | The DP state is maintained using a fixed table of size $2 \times 3$, resulting in constant auxiliary memory. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if $n$ is up to $10^{18}$?
*   **Answer**: Since the state transitions are linear, we can represent them using **Matrix Exponentiation**.
    Let our state vector of size 6 be:
    $$V_i = [dp_i[0][0], dp_i[0][1], dp_i[0][2], dp_i[1][0], dp_i[1][1], dp_i[1][2]]^T$$
    The transition can be represented as:
    $$V_{i+1} = M \times V_i$$
    where $M$ is a $6 \times 6$ transition matrix. We can calculate $M^n$ in $\mathcal{O}(6^3 \log n)$ time using binary exponentiation, which makes solving for $n = 10^{18}$ extremely fast.

### Q2: How does the transition matrix $M$ look?
*   **Answer**: Let state indices be $0 \to (0,0)$, $1 \to (0,1)$, $2 \to (0,2)$, $3 \to (1,0)$, $4 \to (1,1)$, $5 \to (1,2)$.
    The transition matrix $M$ would be:
    $$M = \begin{pmatrix}
    1 & 1 & 1 & 0 & 0 & 0 \\
    1 & 0 & 0 & 0 & 0 & 0 \\
    0 & 1 & 0 & 0 & 0 & 0 \\
    1 & 1 & 1 & 1 & 1 & 1 \\
    0 & 0 & 0 & 1 & 0 & 0 \\
    0 & 0 & 0 & 0 & 1 & 0 
    \end{pmatrix}$$
    Multiplying this matrix by the state vector gives the exact transitions.

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention Matrix Exponentiation**: Proactively bringing up matrix exponentiation for large $n$ (like $n = 10^{15}$) immediately sets you apart as a candidate with deep algebraic computer science knowledge.
*   **Prune Zero-Value States**: Explain that checking `if (val == 0) continue;` is a standard micro-optimization that avoids executing expensive modulo operations for unreached states, which is critical in competitive programming and high-performance computing.
