# Longest Repeating Character Replacement

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 424, Glassdoor
- **Flashcards**: [Sliding Window deck](../../flash_cards/coding/sliding_window.md)

---

## Question Description

You are given a string `s` and an integer `k`. You can choose any character of the string and change it to any other uppercase English character. You can perform this operation at most `k` times.

Return the length of the longest substring containing the same letter you can get after performing the above operations.

### Examples

*   **Input**: `s = "ABAB"`, `k = 2`
    *   **Output**: `4`
    *   **Explanation**: Replace the two 'A's with two 'B's or vice versa.
*   **Input**: `s = "AABABBA"`, `k = 1`
    *   **Output**: `4`
    *   **Explanation**: Replace the one 'A' in the middle with 'B' and form `"AABBBBA"`. The substring `"BBBB"` has the longest repeating letters, which is 4.

---

## Detailed Solution (C++)

This problem is solved using the **Sliding Window** technique. We maintain a window `[left, right]` and a frequency table of characters inside the window.

The key observation is:
*   The total number of characters in the window is `right - left + 1`.
*   Let `max_freq` be the frequency of the most frequent character in the current window.
*   To make all characters in the window the same, we must replace the remaining `(right - left + 1) - max_freq` characters.
*   If this count is $\le k$, the window is valid, and we can potentially update our maximum length.
*   If this count $> k$, the window is invalid, so we increment `left` and decrement the frequency of the character leaving the window.

### Standard C++ Production Code

```cpp
#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int characterReplacement(const std::string& s, int k) noexcept {
        int freq[26] = {0};
        int max_freq = 0;
        int left = 0;
        int max_len = 0;
        const int n = static_cast<int>(s.length());

        for (int right = 0; right < n; ++right) {
            int idx = s[right] - 'A';
            freq[idx]++;
            
            // Track the frequency of the most common character in the current window
            max_freq = std::max(max_freq, freq[idx]);

            // If the number of characters to replace is greater than k, shrink the window
            while ((right - left + 1) - max_freq > k) {
                freq[s[left] - 'A']--;
                left++;
            }

            // Update the maximum length of a valid window
            max_len = std::max(max_len, right - left + 1);
        }

        return max_len;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the optimized sliding window implementation in Python using standard collections and dictionary lookups.

```python
class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        """
        Finds the length of the longest substring containing the same letter 
        after replacing at most k characters.
        
        Time Complexity: O(N)
        Space Complexity: O(1) as the frequency dictionary holds at most 26 keys.
        """
        freq: dict[str, int] = {}
        max_freq = 0
        left = 0
        max_len = 0
        
        for right, ch in enumerate(s):
            freq[ch] = freq.get(ch, 0) + 1
            max_freq = max(max_freq, freq[ch])
            
            # If replacement budget is exceeded, shrink the window from left
            while (right - left + 1) - max_freq > k:
                freq[s[left]] -= 1
                left += 1
                
            max_len = max(max_len, right - left + 1)
            
        return max_len
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Optimization of `max_freq` Recomputation
A common point of confusion is whether `max_freq` needs to be decremented when a character leaves the window (i.e. when `left` is incremented).
*   **No recomputation is required**: We are only looking for a window strictly *larger* than the current `max_len`. A larger window is only possible if we find a new character with a frequency higher than our historical `max_freq`. 
*   Therefore, `max_freq` only needs to track the historical maximum frequency inside any window we've seen. Not needing to scan the frequency dictionary for the new max value on every shrink keeps our inner loop extremely fast.

### 2. Contiguous Allocations vs Hash Map
*   In C++, `int freq[26]` is stack-allocated, which is extremely fast.
*   In Python, using `ord(ch) - 65` with a list `freq = [0] * 26` can run up to $2\times$ faster than a dictionary because it bypasses hashing, hash collision resolution, and dictionary resizing.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | We scan the string of length $n$ with a right pointer. The left pointer only moves forward. Each step does $\mathcal{O}(1)$ frequency map operations. |
| **Space Complexity** | $\mathcal{O}(1)$ | The character set is restricted to 26 uppercase English letters, requiring constant auxiliary space. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Can this be solved with a non-shrinking window?
*   **Answer**: Yes. Instead of shrinking the window with a `while` loop, we can keep the window size constant or growing. If the window becomes invalid, we simply shift the whole window (both `left` and `right` advance by 1).
*   **C++ Code (Non-shrinking)**:
    ```cpp
    int freq[26] = {0};
    int max_freq = 0, left = 0;
    for (int right = 0; right < s.length(); ++right) {
        max_freq = std::max(max_freq, ++freq[s[right] - 'A']);
        if ((right - left + 1) - max_freq > k) {
            freq[s[left] - 'A']--;
            left++; // Shift left by 1 without shrinking
        }
    }
    return s.length() - left;
    ```
*   **Benefit**: This eliminates the inner loop entirely, leading to cleaner branch prediction.

### Q2: What if the string can contain any ASCII character?
*   **Answer**: The logic remains exactly the same, but the frequency array size must be expanded from 26 to 128 (or 256 for extended ASCII) to prevent out-of-bounds indexing.

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain the Historical Max Frequency Intuition**: Proactively explain why `max_freq` does not need to be recomputed when the window shrinks. The fact that `max_freq` can represent a *historical* maximum rather than the *current* maximum is a brilliant mathematical optimization. Mentioning this demonstrates outstanding analytical depth.
*   **Branch Prediction Efficiency**: Explain how the non-shrinking window approach is more friendly to the CPU pipeline. Because the window only shifts or grows (the branching is highly predictable), there are fewer CPU pipeline stalls compared to the shrinking window approach where the inner `while` loop condition can be highly dynamic.
