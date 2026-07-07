# Find All Anagrams in a String

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 438, Glassdoor

---

## Question Description

Given two strings `s` and `p`, return an array of all the start indices of `p`'s anagrams in `s`. You may return the answer in any order.

An **Anagram** is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

### Examples

*   **Input**: `s = "cbaebabacd"`, `p = "abc"`
    *   **Output**: `[0, 6]`
    *   **Explanation**:
        *   The substring with start index = `0` is `"cba"`, which is an anagram of `"abc"`.
        *   The substring with start index = `6` is `"bac"`, which is an anagram of `"abc"`.
*   **Input**: `s = "abab"`, `p = "ab"`
    *   **Output**: `[0, 1, 2]`
    *   **Explanation**:
        *   The substring with start index = `0` is `"ab"`, which is an anagram of `"ab"`.
        *   The substring with start index = `1` is `"ba"`, which is an anagram of `"ab"`.
        *   The substring with start index = `2` is `"ab"`, which is an anagram of `"ab"`.

---

## Detailed Solution (C++)

The core approach is a **Sliding Window of Fixed Size** matching the length of `p`.
We maintain the character frequency counts of `p` and the sliding window of `s`.
1. Initialize frequency count arrays (or `std::array<int, 26>`) for `p` and the first `plen` characters of `s`.
2. Compare the two tables. If they are identical, index `0` is a start position of an anagram.
3. Slide the window from left to right:
   * Add the new character at the right of the window.
   * Remove the character at the left of the window.
   * Compare the tables. If they are identical, add the new start index to the result.

### Standard C++ Production Code

```cpp
#include <string>
#include <vector>
#include <array>

class Solution {
public:
    std::vector<int> findAnagrams(const std::string& s, const std::string& p) noexcept {
        std::vector<int> result;
        const int slen = static_cast<int>(s.size());
        const int plen = static_cast<int>(p.size());

        // Edge Case: If pattern is longer than the string, no anagram can exist
        if (plen > slen) {
            return result;
        }

        std::array<int, 26> p_freq{};
        std::array<int, 26> s_freq{};

        // Initialize the count tables for the first window
        for (int i = 0; i < plen; ++i) {
            p_freq[p[i] - 'a']++;
            s_freq[s[i] - 'a']++;
        }

        // Compare the first window
        if (p_freq == s_freq) {
            result.push_back(0);
        }

        // Slide the window across the rest of the string
        for (int i = plen; i < slen; ++i) {
            // Include the new character entering the window
            s_freq[s[i] - 'a']++;
            // Exclude the character leaving the window
            s_freq[s[i - plen] - 'a']--;

            // Fast array comparison (takes O(26) operations)
            if (p_freq == s_freq) {
                result.push_back(i - plen + 1);
            }
        }

        return result;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the Python sliding window implementation. It uses a character frequency map and manually slides the window to avoid recreating the frequency maps at each step.

```python
from collections import Counter
from typing import List

class Solution:
    def findAnagrams(self, s: str, p: str) -> List[int]:
        """
        Finds all start indices of p's anagrams in s.
        
        Time Complexity: O(N) where N is the length of s.
        Space Complexity: O(1) as the frequency counters have at most 26 keys.
        """
        slen, plen = len(s), len(p)
        if plen > slen:
            return []

        p_count = Counter(p)
        s_count = Counter(s[:plen])
        result = []

        if s_count == p_count:
            result.append(0)

        for i in range(plen, slen):
            # Slide the window right: add current char, remove oldest char
            entering_char = s[i]
            leaving_char = s[i - plen]
            
            s_count[entering_char] = s_count.get(entering_char, 0) + 1
            s_count[leaving_char] -= 1
            
            # Clean up the key from dictionary if count drops to 0 to make dict comparisons accurate
            if s_count[leaving_char] == 0:
                del s_count[leaving_char]
                
            if s_count == p_count:
                result.append(i - plen + 1)
                
        return result
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Dictionary Comparison Overhead
*   In Python, comparing two `Counter` dictionaries (e.g. `s_count == p_count`) checks if both have identical keys and values.
*   To ensure accuracy, it is critical to **delete** keys when their count reaches zero (`del s_count[leaving_char]`). Otherwise, a key with count `0` in `s_count` will cause `s_count == p_count` to return `False` even if all other frequencies match.

### 2. Alternative: Using `list` with size 26
*   To optimize Python performance, you can use two lists of size 26 (`s_count = [0] * 26`) and compare them: `s_count == p_count`.
*   Comparing lists of size 26 in Python is highly optimized in C and avoids the overhead of dictionary key deletions.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | We iterate through `s` once. In each iteration, comparing two frequency maps of fixed size 26 takes $\mathcal{O}(26) = \mathcal{O}(1)$ time. |
| **Space Complexity** | $\mathcal{O}(1)$ | The frequency counters are bounded by the size of the English alphabet (26), which requires constant space. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Can we achieve true $\mathcal{O}(1)$ comparison time without comparing the full array/dict at each step?
*   **Answer**: Yes, by maintaining a `matches` count representing the number of unique characters that have the exact same frequency in both the window and the pattern `p`.
*   **Explanation**: When sliding the window, only two characters (entering and leaving) have their frequencies modified. We can check if their modified frequencies now match or no longer match the pattern's counts, updating the `matches` tracker accordingly. When `matches == 26`, we found an anagram.
*   **C++ Code Snippet**:
    ```cpp
    int matches = 0;
    for (int i = 0; i < 26; ++i) {
        if (s_freq[i] == p_freq[i]) matches++;
    }
    // During sliding window:
    // Update matches when s_freq[idx] changes to match/mismatch p_freq[idx]
    ```

### Q2: How does this generalize to find matches of any permutation of a pattern including wildcards?
*   **Answer**: If a wildcard character (e.g., `?`) matches any character, we can adjust our comparison logic to treat wildcards as a credit. The size of the window remains fixed at `plen`, and we match the frequency table allowing up to the wildcard count of discrepancies.

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention `del` for dict comparison**: In Python, point out that checking equality of two counters requires clearing keys with zero values. Explaining this details that you understand how Python's dictionary equality operator (`__eq__`) works under the hood (checking presence of all keys).
*   **Highlight Cache Locality**: Using `std::array<int, 26>` instead of `std::unordered_map` ensures that the frequency counters are stored contiguously on the stack. The comparison `sf == pf` compiles to highly efficient vector instructions (SIMD) on modern compilers, making it faster than custom checks in practice.
