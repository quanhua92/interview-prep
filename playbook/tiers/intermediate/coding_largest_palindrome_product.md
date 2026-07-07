# Largest Palindrome Product

- **Category**: Coding
- **Difficulty**: Hard
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 479, Glassdoor
- **Flashcards**: [Math deck](../../flash_cards/coding/math.md)

---

## Question Description

Given an integer `n`, return the **largest palindromic integer** that can be represented as the product of two `n`-digit integers. Since the answer can be very large, return it **modulo 1337**.

### Examples
*   **Input**: `n = 2`
    *   **Output**: `987`
    *   **Explanation**: The largest palindrome product of two 2-digit numbers is $99 \times 91 = 9009$. $9009 \bmod 1337 = 987$.
*   **Input**: `n = 1`
    *   **Output**: `9`
    *   **Explanation**: $3 \times 3 = 9$.

---

## Detailed Solution (C++)

To find the largest palindrome product of two $n$-digit numbers:
1. **Edge Case**: For $n = 1$, the largest single-digit product is $3 \times 3 = 9$, which we return directly.
2. **Search Space**: The largest possible $n$-digit number is $U = 10^n - 1$, and the smallest is $L = 10^{n-1}$.
3. **Palindrome Generation**: The product of two $n$-digit numbers will have either $2n$ or $2n - 1$ digits. Since we want the largest palindrome, we search for palindromes of length $2n$.
4. We can iterate through the left half of the palindrome, `left`, starting from $U$ down to $L$.
5. For each `left`, we construct the full palindrome by reversing the digits of `left` and appending them to `left`. For example, if $n=3$ and `left = 998`, the palindrome is `998899`.
6. **Factorization Search**: To check if the generated palindrome is a product of two $n$-digit numbers:
   * We search for a divisor `right` starting from $U$ down to $\lceil \sqrt{\text{palindrome}} \rceil$.
   * If `palindrome % right == 0`, we have found the largest palindrome.
   * If `right * right < palindrome`, we can stop searching for this palindrome because any factor we find would be paired with a factor larger than $U$, which is invalid.
7. Return `palindrome % 1337`.

### Standard C++ Production Code

We must use `long long` in C++ because for $n = 8$, the palindrome has $16$ digits, which exceeds the limit of a standard 32-bit signed integer (`int`) but fits safely inside a 64-bit integer (`long long` max $\approx 9.22 \times 10^{18}$).

```cpp
#include <cmath>

class Solution {
public:
    int largestPalindrome(int n) {
        // Special case: for n = 1, largest product is 9 (3 * 3)
        if (n == 1) {
            return 9;
        }

        long long upper = 1;
        for (int i = 0; i < n; ++i) {
            upper *= 10;
        }
        long long lower = upper / 10;
        upper -= 1; // e.g. 99 for n = 2

        // Iterate through the left half of the palindrome from largest to smallest
        for (long long left = upper; left >= lower; --left) {
            long long palindrome = left;
            long long tmp = left;
            
            // Construct the palindrome by reversing 'left' and appending it
            while (tmp > 0) {
                palindrome = palindrome * 10 + (tmp % 10);
                tmp /= 10;
            }

            // Search for a factor 'right'
            for (long long right = upper; right >= lower; --right) {
                // If the square of right is less than the palindrome,
                // any remaining factors would have to be larger than upper (which is invalid)
                if (right * right < palindrome) {
                    break;
                }

                if (palindrome % right == 0) {
                    return static_cast<int>(palindrome % 1337);
                }
            }
        }

        return 0;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the Python implementation.

```python
class Solution:
    def largestPalindrome(self, n: int) -> int:
        """
        Finds the largest palindrome product of two n-digit numbers modulo 1337.
        """
        if n == 1:
            return 9

        upper = 10**n - 1
        lower = 10**(n - 1)

        # Iterate left half downwards
        for left in range(upper, lower - 1, -1):
            # Construct the palindrome
            palindrome = int(str(left) + str(left)[::-1])
            
            # Find a divisor 'right' in range [sqrt(palindrome), upper]
            # We iterate right from upper downwards
            right = upper
            while right * right >= palindrome:
                if palindrome % right == 0:
                    return palindrome % 1337
                right -= 1
                
        return 0
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Palindrome Generation: Arithmetic vs String Reversal
*   In Python, string concatenation and slicing (`str(left) + str(left)[::-1]`) is implemented in highly optimized C and is generally faster and more readable than manual math loops (`palindrome = palindrome * 10 + tmp % 10`).
*   In C++, math operations are faster than string conversions to avoid heap allocation overhead.

### 2. Large Integer Arithmetic
*   Python handles arbitrary-precision integers automatically. However, since the maximum palindrome for $n = 8$ fits within a 64-bit integer, standard integer operations run quickly on the CPU without shifting to slow big-integer libraries.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(10^{2n})$ worst-case | In practice, the largest palindrome is found very quickly near the top. For example, for $n=8$, the search takes less than a second because we only check a small fraction of the space. |
| **Space Complexity** | $\mathcal{O}(1)$ | We only maintain a few scalar loop variables. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Why do we start the search from upper and go downwards?
*   **Answer**: Since we want the *largest* palindrome, generating the palindromes in descending order guarantees that the first one we successfully factor into two $n$-digit numbers is the global maximum. This allows us to terminate the entire algorithm immediately upon finding the first match.

### Q2: Why does right * right < palindrome allow us to break early?
*   **Answer**: 
    *   If `palindrome = A * B`, then one of the factors must be $\ge \sqrt{\text{palindrome}}$ and the other must be $\le \sqrt{\text{palindrome}}$.
    *   We search for the larger factor `right` starting from `upper` downwards. If `right` drops below $\sqrt{\text{palindrome}}$ (i.e. `right * right < palindrome`), it is mathematically impossible to find a larger factor. Any divisor we find from that point onward would be paired with a factor larger than `upper`, which is not an $n$-digit number.

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention Modulo Math Properties**: Explain why the modulo 1337 is applied *only* at the end. In some problems, we apply `% M` at each step of arithmetic to prevent overflow. Here, doing so would destroy the value of the palindrome, making it impossible to check for factorizability. We must compute the full product (up to 16 digits) and apply modulo 1337 only to the final result.
*   **Discuss Math vs. String Performance**: Discuss how C++ handles mathematical loops faster because of register-level operations, whereas Python's VM overhead makes string operations faster. This indicates you write code optimized for the runtime environment.
