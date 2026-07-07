# License Key Formatting

- **Category**: Coding
- **Difficulty**: Easy
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 482, Glassdoor
- **Flashcards**: [String deck](../../flash_cards/coding/string.md)

---

## Question Description

You are given a license key represented as a string `s` that consists of only alphanumeric characters and dashes. The string is separated into $n + 1$ groups by $n$ dashes. You are also given an integer `k`.

We want to reformat the string `s` such that each group contains exactly `k` characters, except for the first group, which could be shorter than `k` but still must contain at least one character. Furthermore, there must be a dash inserted between two groups, and you should convert all lowercase letters to uppercase.

Return the reformatted license key.

### Examples

*   **Input**: `s = "5F3Z-2e-9-w"`, `k = 4`
    *   **Output**: `"5F3Z-2E9W"`
    *   **Explanation**: The string `s` has been split into two parts, each part has 4 characters. Note that the two extra dashes in the original string are not needed and can be removed.
*   **Input**: `s = "2-5g-3-J"`, `k = 2`
    *   **Output**: `"2-5G-3J"`
    *   **Explanation**: The string `s` has been split into three parts, each part has 2 characters except the first part as it could be shorter as mentioned above.

---

## Detailed Solution (C++)

A naive approach involves removing all dashes, converting letters to uppercase, and then slicing/grouping. However, this requires multiple allocations and string copies.

An optimized approach is to traverse the string **backwards**:
1. Since the first group is allowed to be shorter than $k$ and all subsequent groups must be exactly $k$ characters, we can build the groups from the end.
2. We loop through `s` from the last index down to `0`.
3. If the character is not a dash:
   * If we have already gathered `k` characters for the current group, we append a dash `-` to our result and reset the counter.
   * We convert the character to uppercase and append it to our result.
4. Once the loop completes, the generated string is in reverse order. We reverse it once before returning.

This algorithm achieves $\mathcal{O}(n)$ time complexity and uses only one allocation for the output string.

### Standard C++ Production Code

```cpp
#include <string>
#include <cctype>
#include <algorithm>

class Solution {
public:
    std::string licenseKeyFormatting(const std::string& s, int k) noexcept {
        std::string result;
        result.reserve(s.length());
        int char_count = 0;

        // Traverse the string in reverse to easily handle the shorter first group
        for (int i = static_cast<int>(s.length()) - 1; i >= 0; --i) {
            if (s[i] != '-') {
                // If we have completed a group of size k, insert a dash first
                if (char_count == k) {
                    result += '-';
                    char_count = 0;
                }
                // Append the uppercase character
                result += static_cast<char>(std::toupper(static_cast<unsigned char>(s[i])));
                char_count++;
            }
        }

        // The result is currently built backwards, so reverse it
        std::reverse(result.begin(), result.end());
        return result;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the Python implementation. We can use a simple backward traversal with a list of characters, or we can use Python's built-in string manipulation which runs very fast due to C-level optimizations.

```python
class Solution:
    def licenseKeyFormatting(self, s: str, k: int) -> str:
        """
        Formats a license key using backward traversal.
        
        Time Complexity: O(N)
        Space Complexity: O(N) to store the result list.
        """
        result = []
        char_count = 0
        
        # Traverse backwards
        for i in range(len(s) - 1, -1, -1):
            char = s[i]
            if char != '-':
                if char_count == k:
                    result.append('-')
                    char_count = 0
                result.append(char.upper())
                char_count += 1
                
        # Reconstruct the string in correct order
        return "".join(reversed(result))
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Direct String Manipulation (`replace` and Slicing)
*   An alternative Python approach is:
    ```python
    cleaned = s.replace("-", "").upper()
    first_len = len(cleaned) % k
    # build groups...
    ```
*   **Comparison**: `s.replace("-", "").upper()` runs highly optimized C-code inside Python's runtime. For typical LeetCode string lengths, it is often faster than a Python-level `for` loop because loops in Python have interpreter overhead.
*   However, in interviews, explaining the backward traversal is preferred because it generalizes to low-level, memory-restricted systems where you cannot allocate multiple intermediate copies of a string.

### 2. Avoiding Prepending to String
*   In Python, strings are immutable. Doing `result = char + result` inside a loop takes $\mathcal{O}(n^2)$ time because a new string is copied in memory each time.
*   Always use a `list` to append elements, then call `join()` at the end, which is an $\mathcal{O}(n)$ operation.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | We scan the string of length $n$ once. Reversing the output string also takes $\mathcal{O}(n)$ time. |
| **Space Complexity** | $\mathcal{O}(n)$ | We allocate memory for the formatted result string, which can be at most $n + \lfloor n/k \rfloor$ in length. Auxiliary space is $\mathcal{O}(1)$ beyond the output buffer. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if $k$ is larger than the number of alphanumeric characters in the string?
*   **Answer**: The modulo operation `len(cleaned) % k` or the backward traversal naturally handles this. If the count of characters is less than $k$, they will all form a single group without any dashes, which is correct (as the first group can be shorter than $k$).

### Q2: How would you optimize this for a system with strict memory limits (e.g. formatting a string in-place)?
*   **Answer**: If we are allowed to modify the input string `s` in-place, and we have enough space allocated at the end of `s`, we can use two pointers starting from the end of `s` and the end of the target size, moving characters backwards to avoid overwriting elements. Since `s` has dashes, the final string is usually shorter or equal in length to the original string (unless the original string has very few dashes, in which case we might need to expand it).

---

## Pro-Tip: How to Impress the Interviewer

*   **Highlight String Immutability Costs**: Discuss how string concatenation (`s = s + c`) in languages with immutable strings (like Python or Java) is an anti-pattern. Show your understanding of memory overhead by always using list appending or pre-allocating buffers.
*   **Identify the Backward Traversal Trick**: Point out that formatting from the front is complex because the size of the first group is variable (`n % k`). Traversing backwards simplifies the logic significantly because all groups built from the end are guaranteed to be of size `k`, leaving the remainder for the first group automatically.
