# Next Greater Element III

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 556, Glassdoor

---

## Question Description

Given a positive integer `n`, find the smallest integer which has exactly the same digits existing in the integer `n` and is greater in value than `n`. If no such positive integer exists, return `-1`.

Note that the returned integer should fit in a **32-bit signed integer** (i.e., $\le 2^{31} - 1$). If there is a valid answer but it does not fit in a 32-bit signed integer, return `-1`.

### Examples
*   **Input**: `n = 12`
    *   **Output**: `21`
*   **Input**: `n = 21`
    *   **Output**: `-1`

---

## Detailed Solution (C++)

This problem is equivalent to finding the **next lexicographical permutation** of the digits of `n`:
1. Convert the integer `n` to a string representation.
2. Find the first pair of adjacent digits `digits[i]` and `digits[i+1]` from the right such that `digits[i] < digits[i+1]`.
   * If no such index `i` exists (i.e. the digits are sorted in descending order), then no larger permutation is possible. Return `-1`.
3. Find the smallest digit to the right of `i` that is strictly greater than `digits[i]`. Let this index be `j`.
4. Swap `digits[i]` and `digits[j]`.
5. Reverse the subsegment of digits from `i + 1` to the end. Reversing it converts the descending suffix into an ascending suffix, minimizing the value increase.
6. Convert the permuted string back to a number.
7. **Overflow Check**: Check if the resulting number fits in a 32-bit signed integer ($2147483647$). If it overflows, return `-1`.

### Standard C++ Production Code

In C++, we can write the manual two-pointer permutation algorithm or leverage `std::next_permutation` directly. Both are correct, but the manual implementation shows your understanding of the underlying STL mechanics.

```cpp
#include <string>
#include <algorithm>
#include <climits>

class Solution {
public:
    int nextGreaterElement(int n) {
        std::string digits = std::to_string(n);
        
        // Step 1: Find the first decreasing digit from the right
        int i = static_cast<int>(digits.size()) - 2;
        while (i >= 0 && digits[i] >= digits[i + 1]) {
            i--;
        }
        
        // If the digits are sorted descending, this is the largest permutation
        if (i < 0) {
            return -1;
        }
        
        // Step 2: Find the smallest digit larger than digits[i] to its right
        int j = static_cast<int>(digits.size()) - 1;
        while (digits[j] <= digits[i]) {
            j--;
        }
        
        // Step 3: Swap and reverse the suffix
        std::swap(digits[i], digits[j]);
        std::reverse(digits.begin() + i + 1, digits.end());
        
        // Step 4: Convert back and check for 32-bit signed integer overflow
        long long val = std::stoll(digits);
        if (val > INT_MAX) {
            return -1;
        }
        
        return static_cast<int>(val);
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the Python implementation.

```python
class Solution:
    def nextGreaterElement(self, n: int) -> int:
        """
        Finds the next greater integer with the same digits using the next permutation algorithm.
        
        Time Complexity: O(D) where D is the number of digits in n
        Space Complexity: O(D)
        """
        # Convert integer to a mutable list of character digits
        digits = list(str(n))
        length = len(digits)
        
        # Step 1: Find the first index i from the right such that digits[i] < digits[i+1]
        i = length - 2
        while i >= 0 and digits[i] >= digits[i + 1]:
            i -= 1
            
        if i < 0:
            return -1
            
        # Step 2: Find the first index j from the right such that digits[j] > digits[i]
        j = length - 1
        while digits[j] <= digits[i]:
            j -= 1
            
        # Step 3: Swap digits at i and j
        digits[i], digits[j] = digits[j], digits[i]
        
        # Step 4: Reverse the digits after index i
        digits[i + 1:] = reversed(digits[i + 1:])
        
        # Step 5: Convert back to integer and perform 32-bit overflow check
        result = int("".join(digits))
        
        # 32-bit signed integer limit is 2^31 - 1 = 2147483647
        if result > 2**31 - 1:
            return -1
            
        return result
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Mutable Strings
*   In Python, strings are immutable. Direct swap operations like `s[i], s[j] = s[j], s[i]` are not allowed on strings.
*   To perform character-level swaps and reversals efficiently, we must convert the string to a `list` of characters, perform in-place mutations, and then reconstruct the string using `"".join(digits)`.

### 2. Standard 32-bit Signed Integer Limits
*   Python integers have arbitrary precision (they do not overflow). Hence, the code must explicitly check if the final integer `result > 2**31 - 1` to respect LeetCode's constraints.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(\log_{10} n)$ | The number of digits $d$ in the number is proportional to $\log_{10} n$. The algorithm scans the digits at most a few times. |
| **Space Complexity** | $\mathcal{O}(\log_{10} n)$ | Auxiliary memory to store the string/list representation of the digits. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What is the underlying math of the next permutation algorithm?
*   **Answer**: 
    1. To get the next lexicographically larger sequence, we must increase the value at the rightmost possible position.
    2. Any suffix that is sorted in descending order (e.g. `5 4 3 2 1`) is already in its maximal lexicographical permutation.
    3. Thus, we scan leftward to find the first element `digits[i]` that is smaller than its successor. This is the rightmost digit we can increase.
    4. To minimize the increase, we replace `digits[i]` with the *smallest* digit to its right that is greater than `digits[i]`.
    5. After the swap, the suffix to the right of `i` is still in descending order. Reversing it sorts it in ascending order, which produces the smallest possible value for that suffix.

### Q2: Can we solve this problem without converting the number to a string?
*   **Answer**: Yes, we can extract the digits mathematically using `% 10` and `/ 10` operations, store them in a list/vector of integers, run the permutation steps, and reconstruct the number. This avoids string allocation overhead entirely.

---

## Pro-Tip: How to Impress the Interviewer

*   **Highlight STL `std::next_permutation`**: In C++, point out that the standard library provides `std::next_permutation`. Demonstrating familiarity with STL algorithms is excellent:
    ```cpp
    int nextGreaterElement(int n) {
        std::string s = std::to_string(n);
        if (!std::next_permutation(s.begin(), s.end())) return -1;
        long long val = std::stoll(s);
        return val > INT_MAX ? -1 : val;
    }
    ```
    This is extremely clean. In a real-world setting, using the standard library reduces surface area for bugs.
*   **Defensive Coding on Type Conversion**: Mention that using `std::stoll` (string to long long) is safer than `std::stoi` (string to int) because `std::stoi` throws an out-of-range exception if the permuted string exceeds `INT_MAX`, whereas `std::stoll` can easily accommodate up to $9 \times 10^{18}$ before throwing.
