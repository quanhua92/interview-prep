# Detect Capital

- **Category**: Coding
- **Difficulty**: Easy
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 520, Glassdoor

---

## Question Description

We define the usage of capitals in a word to be right when one of the following cases holds:
1. All letters in this word are capitals, like `"USA"`.
2. All letters in this word are not capitals, like `"leetcode"`.
3. Only the first letter in this word is capital, like `"Google"`.

Given a string `word`, return `true` if the usage of capitals in it is right.

### Examples

*   **Input**: `word = "USA"`
    *   **Output**: `true`
*   **Input**: `word = "FlaG"`
    *   **Output**: `false`

---

## Detailed Solution (C++)

The rules can be consolidated by counting the total number of uppercase letters in the word:
*   If **all** letters are uppercase, it is valid (`upper == len`).
*   If **zero** letters are uppercase, it is valid (`upper == 0`).
*   If **exactly one** letter is uppercase and it is the **first** letter, it is valid (`upper == 1 && isupper(word[0])`).
*   In all other cases, the capital usage is invalid.

We can solve this in a single pass over the string in $\mathcal{O}(n)$ time and $\mathcal{O}(1)$ auxiliary space.

### Standard C++ Production Code

```cpp
#include <string>
#include <cctype>

class Solution {
public:
    bool detectCapitalUse(const std::string& word) noexcept {
        const int len = static_cast<int>(word.size());
        if (len <= 1) {
            return true;
        }

        int upper_count = 0;
        for (const char c : word) {
            if (std::isupper(static_cast<unsigned char>(c))) {
                upper_count++;
            }
        }

        // Case 1: All letters are capitals
        // Case 2: No letters are capitals
        // Case 3: Only the first letter is capital
        return (upper_count == len) || 
               (upper_count == 0) || 
               (upper_count == 1 && std::isupper(static_cast<unsigned char>(word[0])));
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below are two approaches to solve the problem in Python. The first approach is an elegant pythonic one-liner, and the second is an optimized single-pass loop that avoids string slicing.

```python
class Solution:
    def detectCapitalUse(self, word: str) -> bool:
        """
        Pythonic approach using built-in methods.
        
        Time Complexity: O(N)
        Space Complexity: O(N) due to string slicing.
        """
        # word.isupper() -> all uppercase
        # word.islower() -> all lowercase
        # word[1:].islower() -> handles "Google" and all lowercase
        return word.isupper() or word.islower() or word[1:].islower()

    def detectCapitalUseOptimized(self, word: str) -> bool:
        """
        Optimized approach avoiding slicing to achieve O(1) auxiliary space.
        
        Time Complexity: O(N)
        Space Complexity: O(1)
        """
        n = len(word)
        if n <= 1:
            return True
            
        upper_count = 0
        for ch in word:
            if ch.isupper():
                upper_count += 1
                
        return (upper_count == n) or \
               (upper_count == 0) or \
               (upper_count == 1 and word[0].isupper())
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Slicing Memory Overhead
*   The expression `word[1:]` creates a **shallow copy** of the substring. In Python, this requires memory allocation proportional to the length of the string ($n-1$).
*   For constraints where $n \le 100$, this overhead is negligible. However, for huge strings, slicing should be avoided to prevent garbage collection load.

### 2. Early-Exit Optimization
*   We can optimize the search by exiting early as soon as we detect a violation.
*   For example, if the first letter is lowercase, all subsequent letters *must* be lowercase. The moment we find an uppercase letter after the first character, we can return `False` immediately.
*   Similarly, if the first two letters are uppercase, all subsequent letters must be uppercase. The moment we find a lowercase letter, we can return `False`.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | We scan the string of length $n$ at most once. |
| **Space Complexity** | $\mathcal{O}(1)$ | Only a count accumulator is maintained, requiring constant memory. (Or $\mathcal{O}(n)$ for the pythonic slicing approach). |

---

## Common Follow-Up Questions & How to Answer

### Q1: Can you write this using a regular expression?
*   **Answer**: Yes, the rules map directly to a simple regex pattern.
*   **Regex Pattern**: `^[A-Z]+$|^[a-z]+$|^[A-Z][a-z]*$`
*   **Explanation**: This matches either a string of all capitals, a string of all lowercase, or a string starting with a capital followed by zero or more lowercase letters. Note that regex engines typically run slower than manual loops because of state machine overhead.

### Q2: How can we implement this with an early-exit check to minimize character scans?
*   **Answer**: We can inspect the first two characters to set our expectation:
    *   If the first character is lowercase, all remaining characters must be lowercase.
    *   If the first two characters are uppercase, all remaining characters must be uppercase.
    *   Otherwise (first is uppercase, second is lowercase), all remaining characters must be lowercase.
*   **C++ Early-Exit Code**:
    ```cpp
    bool detectCapitalUse(const std::string& word) {
        const int n = static_cast<int>(word.length());
        if (n <= 1) return true;
        
        const bool expect_upper = std::isupper(static_cast<unsigned char>(word[0])) && 
                                  std::isupper(static_cast<unsigned char>(word[1]));
        
        for (int i = 1; i < n; ++i) {
            if (expect_upper && std::islower(static_cast<unsigned char>(word[i]))) return false;
            if (!expect_upper && std::isupper(static_cast<unsigned char>(word[i]))) return false;
        }
        return true;
    }
    ```

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain Python's String Copying Behavior**: Point out that slicing strings in Python (`word[1:]`) creates a copy, and explain how an interviewer's question on memory constraints might make a slicing approach unacceptable despite its simplicity.
*   **Highlight Early Exit / Branching**: Discussing the early-exit optimization shows you care about average-case performance. In typical english text, most words are lowercase or capitalized ("Google"), so setting expectations early allows the processor to skip scanning the whole string for the majority of inputs.
