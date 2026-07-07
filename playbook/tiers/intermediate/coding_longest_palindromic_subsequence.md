# Longest Palindromic Subsequence

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 516, Glassdoor
- **Flashcards**: [Dynamic Programming deck](../../flash_cards/coding/dynamic_programming.md)

---

## Question Description

Given a string `s`, find *the longest palindromic subsequence's length in `s`*.

A **subsequence** is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.

### Examples
*   **Input**: `s = "bbbab"`
    *   **Output**: `4`
    *   **Explanation**: One possible longest palindromic subsequence is `"bbbb"`.
*   **Input**: `s = "cbbd"`
    *   **Output**: `2`
    *   **Explanation**: One possible longest palindromic subsequence is `"bb"`.

**Constraints**:
*   $1 \le s.\text{length} \le 1000$
*   `s` consists only of lowercase English letters.

---

## Detailed Solution (C++)

This is a classical 2D Dynamic Programming problem.

*   **State**: `dp[i][j]` represents the length of the longest palindromic subsequence in the substring `s[i...j]`.
*   **Base Cases**:
    *   Single characters: `dp[i][i] = 1` for all $i$.
    *   Double characters: If `s[i] == s[i+1]`, `dp[i][i+1] = 2`, else `dp[i][i+1] = 1`.
*   **Transition**: For a substring from index `i` to `j` (where $j - i \ge 1$):
    *   If `s[i] == s[j]`:
        $$\text{dp}[i][j] = \text{dp}[i+1][j-1] + 2$$
    *   If `s[i] != s[j]`:
        $$\text{dp}[i][j] = \max(\text{dp}[i+1][j], \text{dp}[i][j-1])$$

To compute this bottom-up, we can iterate over the length of the substring from $2$ to $n$, and then sweep the starting index `i`.

### Standard C++ Production Code

```cpp
#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int longestPalindromeSubseq(std::string s) {
        int n = static_cast<int>(s.size());
        if (n == 0) {
            return 0;
        }

        // dp[i][j] stores the length of LPS in s[i...j]
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));

        // Base cases: single character substrings
        for (int i = 0; i < n; ++i) {
            dp[i][i] = 1;
        }

        // Process substrings of length 2 to n
        for (int length = 2; length <= n; ++length) {
            for (int i = 0; i <= n - length; ++i) {
                int j = i + length - 1;
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                } else {
                    dp[i][j] = std::max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }

        return dp[0][n - 1];
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the space-optimized 1D Python implementation. Because calculating `dp[i][j]` only requires values from the previous column/row, we can optimize space to $\mathcal{O}(n)$.

```python
class Solution:
    def longestPalindromeSubseq(self, s: str) -> int:
        """
        Computes the length of the longest palindromic subsequence.
        
        Time Complexity: O(N^2)
        Space Complexity: O(N)
        """
        n = len(s)
        if n == 0:
            return 0

        # dp[j] stores the LPS value for current i and ending index j.
        # We process i from n-1 down to 0, updating in-place.
        dp = [0] * n

        for i in range(n - 1, -1, -1):
            dp[i] = 1  # Base Case: s[i...i] has length 1
            prev_diagonal = 0  # Represents dp[i+1][j-1]
            
            for j in range(i + 1, n):
                temp = dp[j]  # Store dp[i+1][j] before it gets overwritten
                if s[i] == s[j]:
                    dp[j] = prev_diagonal + 2
                else:
                    dp[j] = max(dp[j], dp[j - 1])
                prev_diagonal = temp

        return dp[n - 1]
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Space Optimization to 1D Array
*   In C++, a 2D array of size $1000 \times 1000$ uses about 4MB of memory, which is negligible.
*   In Python, lists of lists are collections of pointers to integers, incurring higher memory overhead (~8 bytes per pointer + ~28 bytes per integer object). Thus, a 2D grid of size $1000 \times 1000$ can consume up to 8-10MB and add GC pressure.
*   By collapsing the 2D DP array into a single 1D array `dp` and updating it from right to left (or dynamically tracking the diagonal element), we reduce space complexity to a single array of size $1000$, which is highly optimal.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n^2)$ | We fill out the DP table of size $n \times n$ using nested loops. |
| **Space Complexity** | $\mathcal{O}(n^2)$ or $\mathcal{O}(n)$ | $\mathcal{O}(n^2)$ for the standard 2D table, optimized to $\mathcal{O}(n)$ using a 1D state array. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How does this relate to Longest Common Subsequence (LCS)?
*   **Answer**: The Longest Palindromic Subsequence of a string `s` is equivalent to the Longest Common Subsequence of `s` and its reverse `s' = reverse(s)`.
    $$\text{LPS}(s) = \text{LCS}(s, \text{reverse}(s))$$
    This is an elegant alternative implementation that also runs in $\mathcal{O}(n^2)$ time and $\mathcal{O}(n)$ space.

### Q2: How can we reconstruct the actual longest palindromic subsequence string?
*   **Answer**: Using the 2D DP table `dp`, we can backtrack from `(0, n-1)`:
    *   If `s[i] == s[j]`, then `s[i]` and `s[j]` are part of the palindrome. We append `s[i]` to our result and move to `(i+1, j-1)`.
    *   If `s[i] != s[j]`, we compare `dp[i+1][j]` and `dp[i][j-1]` and move in the direction of the larger value.
    *   Finally, we assemble the left and right halves to build the full palindrome string.

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain LCS Duality**: Mentioning that $\text{LPS}(s) = \text{LCS}(s, \text{reverse}(s))$ immediately shows you see deep connections between different dynamic programming problems rather than just memorizing code.
*   **Implement Space Compression**: Demonstrating the transition from a 2D state table to a 1D state table by tracking the `prev_diagonal` variable is an advanced technique that demonstrates strong algorithmic prowess.
