# Longest Uncommon Subsequence I

- **Category**: Coding
- **Difficulty**: Easy
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 521, Glassdoor

---

## Question Description

Given two strings `a` and `b`, return the length of the **longest uncommon subsequence** between `a` and `b`. If no such uncommon subsequence exists, return `-1`.

An **uncommon subsequence** between two strings is a string that is a subsequence of **exactly one** of them.

A **subsequence** of a string is a new string generated from the original string by deleting some (or no) characters without changing the relative order of the remaining characters. For example, `"ace"` is a subsequence of `"abcde"` while `"aec"` is not.

### Examples

*   **Input**: `a = "aba"`, `b = "cdc"`
    *   **Output**: `3`
    *   **Explanation**: One longest uncommon subsequence is `"aba"` because `"aba"` is a subsequence of `"aba"` but not `"cdc"`. Note that `"cdc"` is also a longest uncommon subsequence.
*   **Input**: `a = "aaa"`, `b = "bbb"`
    *   **Output**: `3`
    *   **Explanation**: The longest uncommon subsequences are `"aaa"` and `"bbb"`.
*   **Input**: `a = "aaa"`, `b = "aaa"`
    *   **Output**: `-1`
    *   **Explanation**: Every subsequence of string `a` is also a subsequence of string `b`. Similarly, every subsequence of string `b` is also a subsequence of string `a`. So the answer is `-1`.

---

## Detailed Solution (C++)

This is a **logical riddle** rather than a complex algorithm problem. Let's break down the logic:

1. **If the strings are identical (`a == b`)**:
   * Any subsequence of `a` is also a subsequence of `b`.
   * Therefore, there is no subsequence that belongs to exactly one of them. The answer is `-1`.

2. **If the strings are different (`a != b`)**:
   * If `a.length() != b.length()`, let's assume `a` is the longer string. The entire string `a` is a subsequence of itself, but it **cannot** be a subsequence of `b` because a shorter string (`b`) cannot contain a longer string (`a`) as a subsequence. Thus, the longest uncommon subsequence is `a` itself, and its length is `a.length()`.
   * If `a.length() == b.length()` but they are not equal, then `a` cannot be a subsequence of `b`. (If it were, they would have to be identical, which contradicts `a != b`). Thus, `a` is an uncommon subsequence of length `a.length()`.

In summary:
*   If `a == b`, return `-1`.
*   Otherwise, return `std::max(a.length(), b.length())`.

### Standard C++ Production Code

```cpp
#include <string>
#include <algorithm>

class Solution {
public:
    int findLUSlength(const std::string& a, const std::string& b) noexcept {
        // If both strings are equal, no uncommon subsequence can exist
        if (a == b) {
            return -1;
        }
        
        // Otherwise, the longer string itself is the longest uncommon subsequence
        return static_cast<int>(std::max(a.length(), b.length()));
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the Python implementation matching the mathematical logic.

```python
class Solution:
    def findLUSlength(self, a: str, b: str) -> int:
        """
        Finds the length of the longest uncommon subsequence.
        
        Time Complexity: O(min(N, M)) where N and M are the lengths of a and b.
        Space Complexity: O(1)
        """
        if a == b:
            return -1
        return max(len(a), len(b))
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. String Equality Complexity
*   The comparison `a == b` first checks if the string lengths are equal. If the lengths differ, it returns `False` in $\mathcal{O}(1)$ time.
*   If the lengths are equal, it compares character by character in $\mathcal{O}(d)$ time (where $d$ is the length of the strings). This is highly efficient.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(\min(n, m))$ | The equality comparison `a == b` takes at most $\mathcal{O}(\min(n, m))$ operations (as it exits immediately if lengths differ, and compares characters up to length $n$ otherwise). |
| **Space Complexity** | $\mathcal{O}(1)$ | No additional memory is allocated. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What is the Longest Uncommon Subsequence II? (LeetCode 522)
*   **The Problem**: Given an array of strings, return the length of the longest uncommon subsequence among them. An uncommon subsequence is a string that is a subsequence of exactly one of the given strings.
*   **The Solution**: We can sort the strings by length in descending order. For each string, we check if it is a subsequence of any other string in the list. The first string (from longest to shortest) that is not a subsequence of any other string is our answer. If we check all and find none, we return `-1`.
*   **Subsequence Check function (C++)**:
    ```cpp
    bool isSubsequence(const std::string& s1, const std::string& s2) {
        const int n1 = static_cast<int>(s1.length());
        const int n2 = static_cast<int>(s2.length());
        int i = 0, j = 0;
        while (i < n1 && j < n2) {
            if (s1[i] == s2[j]) i++;
            j++;
        }
        return i == n1;
    }
    ```

---

## Pro-Tip: How to Impress the Interviewer

*   **Avoid Suboptimal DP**: Many candidates immediately jump to Dynamic Programming (similar to Longest Common Subsequence - LCS) which is $\mathcal{O}(n \cdot m)$ time and space. Pointing out the logical simplification *before* writing any code shows you analyze the mathematical properties of a problem instead of blindly applying templates.
*   **Verify Length Checks**: Mention that checking string equality in C++ (`std::string::operator==`) first checks the sizes of the strings. If they differ, the check is an $\mathcal{O}(1)$ operation. This shows you understand library implementation details.
