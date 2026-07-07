# Longest Substring Without Repeating Characters

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 3, Glassdoor
- **Flashcards**: [Sliding Window deck](../../flash_cards/coding/sliding_window.md)

---

## Question Description

Given a string `s`, find the length of the **longest substring** without duplicate characters.

A **substring** is a contiguous, non-empty sequence of characters within a string.

### Examples

*   **Input**: `s = "abcabcbb"`
    *   **Output**: `3`
    *   **Explanation**: The answer is `"abc"`, with the length of 3.
*   **Input**: `s = "bbbbb"`
    *   **Output**: `1`
    *   **Explanation**: The answer is `"b"`, with the length of 1.
*   **Input**: `s = "pwwkew"`
    *   **Output**: `3`
    *   **Explanation**: The answer is `"wke"`, with the length of 3. Note that the answer must be a substring, `"pwke"` is a subsequence and not a substring.

---

## Detailed Solution (C++)

The core algorithm uses a **Sliding Window** optimized with a direct lookup structure. Rather than maintaining a hash set of characters in the current window and shrinking the left pointer incrementally (which can lead to multiple operations per character), we store the last seen 0-based index of each character.

As we iterate with the right pointer `i`:
1. If the character `c = s[i]` was already seen and its last recorded index is within the current window (i.e. $\ge \text{left}$), we jump the `left` boundary of our window directly to `last_index + 1`. This safely excludes the duplicate.
2. We update the last seen index of `c` to `i`.
3. The size of the current window is `i - left + 1`. We update the maximum length if the current size is larger.

Using a fixed-size array or `std::vector<int>` instead of `std::unordered_map` prevents hash collisions and dynamic memory allocation overhead, yielding optimal cache locality and performance.

### Standard C++ Production Code

```cpp
#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int lengthOfLongestSubstring(const std::string& s) noexcept {
        // Optimize lookup by using a fixed-size vector for all 256 possible byte values
        // Initializing with -1 to indicate that no character has been seen yet
        std::vector<int> last_seen(256, -1);
        
        int left = 0;
        int max_len = 0;
        const int n = static_cast<int>(s.length());

        for (int i = 0; i < n; ++i) {
            // Get ASCII value of the character safely
            unsigned char c = s[i]; 
            
            // If the character is inside the current window, move the left pointer past it
            if (last_seen[c] >= left) {
                left = last_seen[c] + 1;
            }
            
            // Record/update the index of the current character
            last_seen[c] = i;
            
            // Update the maximum substring length found so far
            max_len = std::max(max_len, i - left + 1);
        }

        return max_len;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the optimized sliding window Python implementation. It uses a dictionary to store the last seen index of each character, allowing constant-time jumps for the left pointer.

```python
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        """
        Finds the length of the longest substring without repeating characters.
        
        Time Complexity: O(N)
        Space Complexity: O(min(N, M)) where M is the character set size.
        """
        char_index: dict[str, int] = {}
        left = 0
        max_len = 0
        
        for right, ch in enumerate(s):
            # If the character is duplicate and within the current active window
            if ch in char_index and char_index[ch] >= left:
                left = char_index[ch] + 1
            
            # Update the character's last seen position
            char_index[ch] = right
            
            # Calculate window size and update max_len
            max_len = max(max_len, right - left + 1)
            
        return max_len
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Dictionary Lookup and Memory Overhead
*   Python's built-in `dict` uses a hash table implementation that has a relatively high memory overhead per key-value pair compared to a primitive array in C++.
*   However, since the character set is bounded (e.g., standard ASCII has 128 characters, unicode character space is also bounded in typical tests), the dictionary size will not grow indefinitely.

### 2. Space Optimization using Lists
*   If we know the string contains only standard ASCII characters, we can replace the dictionary with a list of size 128 initialized to `-1` (e.g. `char_index = [-1] * 128` and using `ord(ch)` to index).
*   In Python, direct list indexing (`char_index[ord(ch)]`) is often slightly faster than dictionary lookups due to the lack of hashing operations, though Python's dynamic string hashing is heavily optimized in CPython.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | We scan the string of length $n$ exactly once using the right pointer. Each character update is $\mathcal{O}(1)$. |
| **Space Complexity** | $\mathcal{O}(\min(n, m))$ | Auxiliary space is bounded by the size of the alphabet $m$ or the length of the string $n$. For ASCII, $m \le 128$, making it $\mathcal{O}(1)$ auxiliary space. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if the character set is extended to Unicode?
*   **Answer**: The C++ implementation using `std::vector<int> last_seen(256, -1)` will handle all 256 single-byte (Extended ASCII/UTF-8 byte) values, but will not correctly track multi-byte UTF-8 sequences as individual characters or handle wider Unicode code points.
*   **Modification**: In C++, we should use a `std::unordered_map<wchar_t, int>` or `std::unordered_map<char32_t, int>` to handle Unicode characters dynamically, or decode the UTF-8 input string to UTF-32 first. In Python, strings are natively Unicode, so the `dict` implementation works seamlessly without changes.

### Q2: Can you return the actual longest substring instead of just the length?
*   **Answer**: Yes, we can track the starting index and length of the longest substring.
*   **Code Addition (C++)**:
    ```cpp
    int max_len = 0, start_idx = 0;
    // Inside the loop:
    if (i - left + 1 > max_len) {
        max_len = i - left + 1;
        start_idx = left;
    }
    // Return:
    return s.substr(start_idx, max_len);
    ```

---

## Pro-Tip: How to Impress the Interviewer

*   **Avoid Suboptimal Set Shrinking**: Many candidates write a sliding window using a `std::unordered_set` or `std::set`. When a duplicate is encountered, they increment `left` one-by-one and erase characters from the set until the duplicate is removed. Explain to the interviewer that while this is technically $\mathcal{O}(n)$, it does unnecessary operations. Storing the indices lets us perform an **instant $\mathcal{O}(1)$ jump**.
*   **C++ Vector vs Unordered Map**: Highlight that `std::unordered_map` is implemented as a closed-addressing hash table (linked lists on bucket collisions). This causes heap allocations and bad cache-locality. Using a contiguous `std::vector<int>` (or a fixed-size stack array `int last_seen[256]`) eliminates allocation overhead and guarantees $\mathcal{O}(1)$ lookup times.
*   **Unicode/UTF-8 Awareness**: Demonstrate real-world software engineering depth by asking the interviewer about the encoding of `s`. If the string is UTF-8 encoded, characters can occupy multiple bytes. Treating a single byte as a character is incorrect. Showing you are aware of localization and encoding is a massive green flag.
