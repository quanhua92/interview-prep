# Find the Closest Palindrome

- **Category**: Coding
- **Difficulty**: Hard
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 564, Glassdoor
- **Flashcards**: [Math deck](../../flash_cards/coding/math.md)

---

## Question Description

Given a string `n` representing an integer, return the **closest integer (not including itself)**, which is a palindrome. If there is a tie, return the **smaller one**.

The closest is defined as the absolute difference minimized between two integers.

### Examples
*   **Input**: `n = "123"`
    *   **Output**: `"121"`
*   **Input**: `n = "1"`
    *   **Output**: `"0"`
    *   **Explanation**: `0` and `2` are the closest palindromes, but we return the smaller one, which is `0`.

---

## Detailed Solution (C++)

This problem is solved efficiently by generating a small set of potential palindrome candidates and choosing the one with the minimum absolute difference:
1. Let $L$ be the length of the string `n`.
2. Extract the prefix representing the left half of the string. The prefix has length `half = (L + 1) / 2`.
3. Generate three primary candidates based on the prefix:
   * **Candidate 1**: Replicate the prefix. (e.g. for prefix $12$, we make $1221$).
   * **Candidate 2**: Replicate the prefix decremented by $1$. (e.g. for prefix $12$, we make $1111$).
   * **Candidate 3**: Replicate the prefix incremented by $1$. (e.g. for prefix $12$, we make $1331$).
4. Generate two structural boundary candidates:
   * **Candidate 4 (Lower Boundary)**: $10^{L-1} - 1$ (consists of $L-1$ nines, e.g., `999` for length 4). This handles numbers like `1000`.
   * **Candidate 5 (Upper Boundary)**: $10^L + 1$ (e.g., `10001` for length 4). This handles numbers like `9999`.
5. Insert all candidates into a set to deduplicate, and remove the original number `num` itself (since the answer must be a different integer).
6. Find the candidate that minimizes the absolute difference $|candidate - num|$. In case of a tie, choose the smaller candidate.

### Standard C++ Production Code

All operations must be performed using 64-bit integers (`long long` in C++) because the input string can represent numbers up to $10^{18} - 1$.

```cpp
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>

class Solution {
private:
    // Helper function to construct a palindrome from a given prefix
    std::string makePalindrome(long long prefix, bool isEvenLength) {
        std::string p = std::to_string(prefix);
        std::string rev = p;
        if (isEvenLength) {
            std::reverse(rev.begin(), rev.end());
            return p + rev;
        } else {
            rev.pop_back();
            std::reverse(rev.begin(), rev.end());
            return p + rev;
        }
    }

public:
    std::string nearestPalindromic(std::string n) {
        long long num = std::stoll(n);
        int len = static_cast<int>(n.size());
        
        // Edge case: single-digit numbers <= 10
        if (num <= 10) {
            return std::to_string(num - 1);
        }

        std::set<long long> candidates;
        
        // Extract prefix (left half)
        int half = (len + 1) / 2;
        long long prefix = std::stoll(n.substr(0, half));
        bool isEvenLength = (len % 2 == 0);

        // Generate candidates from prefix - 1, prefix, and prefix + 1
        for (long long d = -1; d <= 1; ++d) {
            candidates.insert(std::stoll(makePalindrome(prefix + d, isEvenLength)));
        }

        // Add boundary candidates
        long long p10_lower = 1;
        for (int i = 0; i < len - 1; ++i) {
            p10_lower *= 10;
        }
        candidates.insert(p10_lower - 1);       // e.g. 999
        candidates.insert(p10_lower * 10 + 1);   // e.g. 10001
        
        // Remove the original number from potential answers
        candidates.erase(num);

        long long best = -1;
        long long best_diff = -1;

        for (long long c : candidates) {
            if (c < 0) continue;
            
            long long diff = std::abs(c - num);
            if (best_diff == -1 || diff < best_diff || (diff == best_diff && c < best)) {
                best = c;
                best_diff = diff;
            }
        }

        return std::to_string(best);
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the Python implementation.

```python
class Solution:
    def nearestPalindromic(self, n: str) -> str:
        """
        Finds the closest palindrome to a given number string, excluding the number itself.
        
        Time Complexity: O(L) where L is the length of string n (L <= 18)
        Space Complexity: O(L)
        """
        num = int(n)
        if num <= 10:
            return str(num - 1)

        length = len(n)
        half = (length + 1) // 2
        prefix = int(n[:half])
        
        candidates = set()
        
        # Generate prefix candidates
        for p in (prefix - 1, prefix, prefix + 1):
            p_str = str(p)
            if length % 2 == 0:
                candidate = int(p_str + p_str[::-1])
            else:
                candidate = int(p_str + p_str[:-1][::-1])
            candidates.add(candidate)
            
        # Add boundary candidates
        candidates.add(10 ** (length - 1) - 1)  # Lower digit boundary (e.g. 999)
        candidates.add(10 ** length + 1)         # Upper digit boundary (e.g. 10001)
        
        # Remove original number
        candidates.discard(num)
        
        # Find candidate with minimum absolute difference; tie-break with smaller value
        closest = min(candidates, key=lambda x: (abs(x - num), x))
        return str(closest)
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Large Integer Conversions
*   Python converts integers to strings and vice-versa seamlessly. Since Python integers have arbitrary precision, we do not have to worry about overflow when computing $10^{\text{length}} + 1$.
*   In C++, using standard `std::stoll` (string to long long) and checking the 64-bit limits is necessary to avoid runtime errors.

### 2. Custom Key Sorting with `min()`
*   The use of `min(candidates, key=lambda x: (abs(x - num), x))` is a highly expressive Python pattern. By returning a tuple `(abs(x - num), x)`, Python first compares the absolute differences, and if they are equal, it compares the values of `x` directly to favor the smaller candidate.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(L)$ | $L$ is the number of digits in the string $n$. Since $L \le 18$, the algorithm executes in a few microseconds ($\approx \mathcal{O}(1)$ time in practice). |
| **Space Complexity** | $\mathcal{O}(L)$ | For storing string buffers of the candidates. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Why do we need the prefix - 1 and prefix + 1 candidates?
*   **Answer**: 
    *   Consider $n = 129$. The prefix is $12$. If we only replicate the prefix, we get $121$.
    *   If we increment the prefix to $13$, we get $131$.
    *   The absolute differences are $|121 - 129| = 8$ and $|131 - 129| = 2$.
    *   By modifying the middle digit (incrementing/decrementing prefix), we ensure we check the nearest palindromes that cross the midpoint boundary.

### Q2: Why are the boundary candidates 99...9 and 10...01 necessary?
*   **Answer**:
    *   They handle changes in digit length.
    *   For $n = 1000$ (length 4), the prefix is $10$. Decrementing it gives $9$. Replicating $9$ yields $99$. But the closest palindrome is actually $999$ (length 3). The candidate $10^{L-1} - 1$ ensures we test $999$.
    *   For $n = 9999$ (length 4), the prefix is $99$. Incrementing it gives $100$. Replicating $100$ yields $100001$ (length 6). But the closest palindrome is $10001$ (length 5). The candidate $10^L + 1$ ensures we test $10001$.

---

## Pro-Tip: How to Impress the Interviewer

*   **Deconstruct the Math of Palindromic Proximity**: Explain to the interviewer that the closest palindrome must match the original number as closely as possible starting from the most significant digits. Therefore, the first half of the digits of the closest palindrome *must* be either equal to, one less than, or one greater than the first half of the original number. This mathematical observation limits the candidate pool to at most 5 values, transforming a potentially complex search problem into a simple $\mathcal{O}(1)$ comparison.
*   **Prevent std::pow Float Issues**: In C++, `std::pow` returns a `double`. Casting it directly to `long long` can introduce minor precision errors on some compilers (e.g. `pow(10, 2)` returning `99.9999...` which casts to `99`). Mentioning this and using an integer power loop or adding a small epsilon proves real-world engineering diligence.
