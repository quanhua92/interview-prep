# Longest Substring with At Least K Repeating Characters

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 395, Glassdoor

---

## Question Description

Given a string `s` and an integer `k`, return the length of the longest substring of `s` such that the frequency of each character in this substring is greater than or equal to `k`. If no such substring exists, return `0`.

### Examples

*   **Input**: `s = "aaabb"`, `k = 3`
    *   **Output**: `3`
    *   **Explanation**: The longest substring is `"aaa"`, as `'a'` is repeated 3 times.
*   **Input**: `s = "ababbc"`, `k = 2`
    *   **Output**: `5`
    *   **Explanation**: The longest substring is `"ababb"`, as `'a'` is repeated 2 times and `'b'` is repeated 3 times.

---

## Detailed Solution (C++)

There are two primary paradigms to solve this problem: **Sliding Window** and **Divide and Conquer**.

### 1. Sliding Window (Iterative Fixed-Alphabet Approach)
A traditional sliding window doesn't work directly because the validity condition is non-monotonic (expanding the window might make a invalid substring valid, and shrinking it could also make a valid substring invalid). 
To make it monotonic, we constrain the number of unique characters allowed in the sliding window. Since the string consists only of lowercase English letters, the number of unique characters $T$ can range from $1$ to $26$.
For each target $T \in [1, 26]$:
*   We slide a window `[left, right]`.
*   We count the number of `unique` characters in the window, and the number of characters that have a frequency of at least `k` (`at_least_k`).
*   If `unique > T`, we shrink the window from the left until `unique <= T`.
*   If `unique == T` and `at_least_k == T`, the window is valid, and we update the maximum length.

### 2. Divide and Conquer
If a character `c` in `s` has a total frequency in the current substring that is less than `k`, then `c` cannot be part of any valid substring. Therefore, any valid substring must lie either completely to the left of the first occurrence of `c`, or completely to the right. 
We can split the string using `c` as a delimiter and recursively solve for the resulting segments, returning the maximum length obtained.

### Standard C++ Production Code

```cpp
#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    // Sliding Window Approach: O(26 * N) time, O(1) space
    int longestSubstring(const std::string& s, int k) noexcept {
        int max_len = 0;
        const int n = static_cast<int>(s.length());

        // Iterate through all possible number of unique characters in the window
        for (int t = 1; t <= 26; ++t) {
            int freq[26] = {0};
            int left = 0;
            int unique = 0;
            int at_least_k = 0;

            for (int right = 0; right < n; ++right) {
                int idx = s[right] - 'a';
                if (freq[idx] == 0) {
                    unique++;
                }
                freq[idx]++;
                if (freq[idx] == k) {
                    at_least_k++;
                }

                // Shrink the window if the unique character count exceeds t
                while (unique > t) {
                    int lidx = s[left] - 'a';
                    if (freq[lidx] == k) {
                        at_least_k--;
                    }
                    freq[lidx]--;
                    if (freq[lidx] == 0) {
                        unique--;
                    }
                    left++;
                }

                // If current state matches the target uniqueness and frequency criteria
                if (unique == t && at_least_k == t) {
                    max_len = std::max(max_len, right - left + 1);
                }
            }
        }
        return max_len;
    }

    // Divide and Conquer Approach: O(N^2) worst case, O(N log N) average, O(N) space
    int longestSubstringDC(const std::string& s, int k) {
        return longestSubstringHelperDC(s, k, 0, static_cast<int>(s.length()));
    }

private:
    int longestSubstringHelperDC(const std::string& s, int k, int start, int end) {
        if (end - start < k) {
            return 0;
        }

        int freq[26] = {0};
        for (int i = start; i < end; ++i) {
            freq[s[i] - 'a']++;
        }

        // Find the first character that occurs more than 0 but fewer than k times
        int bad_char = -1;
        for (int i = 0; i < 26; ++i) {
            if (freq[i] > 0 && freq[i] < k) {
                bad_char = 'a' + i;
                break;
            }
        }

        // If no bad character exists, the whole substring is valid
        if (bad_char == -1) {
            return end - start;
        }

        int max_len = 0;
        int seg_start = start;

        for (int i = start; i <= end; ++i) {
            if (i == end || s[i] == bad_char) {
                max_len = std::max(max_len, longestSubstringHelperDC(s, k, seg_start, i));
                seg_start = i + 1;
            }
        }

        return max_len;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below are the Python solutions representing both the sliding window approach and the divide-and-conquer strategy.

```python
from collections import Counter

class Solution:
    def longestSubstring(self, s: str, k: int) -> int:
        """
        Sliding window implementation with a fixed target of unique characters.
        
        Time Complexity: O(26 * N) = O(N)
        Space Complexity: O(1) as we use fixed-size tables
        """
        max_len = 0
        n = len(s)
        
        for t in range(1, 27):
            freq: dict[str, int] = {}
            left = 0
            unique = 0
            at_least_k = 0
            
            for right in range(n):
                ch = s[right]
                freq[ch] = freq.get(ch, 0) + 1
                if freq[ch] == 1:
                    unique += 1
                if freq[ch] == k:
                    at_least_k += 1
                
                # Shrink left pointer if we have too many unique characters
                while unique > t:
                    lc = s[left]
                    if freq[lc] == k:
                        at_least_k -= 1
                    freq[lc] -= 1
                    if freq[lc] == 0:
                        unique -= 1
                    left += 1
                
                # Check validity
                if unique == t and at_least_k == t:
                    max_len = max(max_len, right - left + 1)
                    
        return max_len

    def longestSubstringDC(self, s: str, k: int) -> int:
        """
        Divide and Conquer implementation.
        
        Time Complexity: O(N log N) average, O(N^2) worst case
        Space Complexity: O(N) due to recursion stack and split strings
        """
        if len(s) < k:
            return 0
            
        freq = Counter(s)
        for char, count in freq.items():
            if count < k:
                # Split s on the bad character and recursively solve for all parts
                return max(self.longestSubstringDC(sub, k) for sub in s.split(char))
                
        return len(s)
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Recursion Overhead and `split()` in Python
*   The divide-and-conquer code in Python is highly elegant because of `s.split(char)`. However, `split()` creates new strings on the heap, which leads to $\mathcal{O}(n)$ dynamic allocation per split.
*   For deep recursion, this creates high GC (Garbage Collection) pressure. In memory-constrained or high-throughput systems, the iterative sliding window or a custom index-based split is preferred.

### 2. Time-Complexity Overhead of Python's Dictionary
*   In the sliding window approach, using `dict` instead of a list of size 26 creates minor runtime overhead due to dictionary hashing. Replacing the lookup table with `freq = [0] * 26` and mapping characters via `ord(ch) - 97` can yield a significant constant-factor speedup in Python.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity (Sliding Window)** | $\mathcal{O}(n)$ | We repeat a standard sliding window $26$ times (once for each possible count of unique characters). Each pass takes $\mathcal{O}(n)$ time. |
| **Space Complexity (Sliding Window)** | $\mathcal{O}(1)$ | We only store frequency counts for the English alphabet (size 26), which requires constant space. |
| **Time Complexity (Divide & Conquer)** | $\mathcal{O}(n \log n)$ average | On average, splits happen near the center, leading to a recurrence of $T(n) = 2T(n/2) + \mathcal{O}(n)$. In the worst-case, it can degrade to $\mathcal{O}(n^2)$ if splits occur at the ends. |
| **Space Complexity (Divide & Conquer)**| $\mathcal{O}(n)$ | Due to recursion stack depth and substring storage during splitting. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What is the optimal approach when $k$ is very large?
*   **Answer**: If $k$ is greater than the length of $s$, we can return `0` immediately. If $k$ is large, the Divide and Conquer approach tends to find "bad" characters very quickly near the root of the recursion, causing it to prune early. Thus, for large $k$, Divide and Conquer typically runs faster than the sliding window.

### Q2: How can we optimize the Divide and Conquer code to use $\mathcal{O}(1)$ auxiliary space?
*   **Answer**: Instead of copying substrings using slicing or `.split()`, we can pass `start` and `end` index boundaries to the recursive helper function (similar to our C++ implementation). This avoids creating copies of string slices in memory, reducing space complexity from $\mathcal{O}(n)$ to $\mathcal{O}(d)$ where $d$ is the recursion depth (worst-case $\mathcal{O}(n)$, average $\mathcal{O}(\log n)$ stack frames).

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain Why Simple Sliding Window Fails**: Start your solution by explaining *why* a naive sliding window doesn't work. The fact that the validity condition is not monotonic is a key observation that most candidates miss. Pointing this out shows you understand the theoretical limits of greedy sliding windows.
*   **Pruning in Divide and Conquer**: Mention that you can optimize the divide-and-conquer approach by returning early if the length of the string segment is less than `k`, or if the segment does not contain enough characters to satisfy the condition.
*   **Alphabet Size Invariance**: Discuss how the sliding window complexity $\mathcal{O}(\Sigma \cdot n)$ (where $\Sigma$ is the alphabet size) scales. If the alphabet is generic Unicode rather than lowercase English characters, $\Sigma \approx 2^{16}$ or $2^{21}$, making the sliding window approach impractical compared to Divide and Conquer. This shows deep system-design awareness.
