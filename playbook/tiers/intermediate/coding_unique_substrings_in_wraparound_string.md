# Unique Substrings in Wraparound String

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 467, Glassdoor
- **Flashcards**: [Dynamic Programming deck](../../flash_cards/coding/dynamic_programming.md)

---

## Question Description

We define the string `base` to be the infinite wraparound string of `"abcdefghijklmnopqrstuvwxyz"`, so `base` looks like this:
*   `"...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz..."`

Given a string `s`, return *the number of unique non-empty substrings of `s` that are present in `base`*.

### Examples
*   **Input**: `s = "a"`
    *   **Output**: `1`
    *   **Explanation**: Only the substring `"a"` of `s` is in `base`.
*   **Input**: `s = "cac"`
    *   **Output**: `2`
    *   **Explanation**: There are two substrings (`"a"`, `"c"`) of `s` in `base`. Note that the second `"c"` is a duplicate of the first one, and we only count unique substrings.
*   **Input**: `s = "zab"`
    *   **Output**: `6`
    *   **Explanation**: There are six substrings (`"z"`, `"a"`, `"b"`, `"za"`, `"ab"`, and `"zab"`) of `s` in `base`.

**Constraints**:
*   $1 \le s.\text{length} \le 10^5$
*   `s` consists of lowercase English letters.

---

## Detailed Solution (C++)

A brute-force solution would generate all substrings and check if they exist in `base`, which would be $\mathcal{O}(n^2)$ time and space, resulting in TLE/MLE.

To optimize:
1.  Any valid substring in `base` must consist of contiguous characters where the character $s[i]$ is the alphabetical successor of $s[i-1]$ (with `'a'` succeeding `'z'`). That is:
    $$\text{s}[i] - \text{s}[i-1] == 1 \quad \text{or} \quad \text{s}[i-1] - \text{s}[i] == 25$$
2.  If we find the longest valid wraparound substring ending at a specific character (e.g., `'c'`), say of length $L$, then there are exactly $L$ unique substrings ending with `'c'` in that window (e.g., if the substring is `"abc"`, the substrings ending in `'c'` are `"c"`, `"bc"`, and `"abc"`).
3.  Any other shorter substring ending at `'c'` found elsewhere in `s` is a suffix of this longest one and has already been accounted for.
4.  Therefore, we can track the maximum length of a valid wraparound substring ending at each of the 26 lowercase English letters using an array `max_len` of size 26.
5.  The total number of unique substrings is the sum of `max_len[i]` for all $0 \le i < 26$.

### Standard C++ Production Code

```cpp
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
public:
    int findSubstringInWraproundString(std::string s) {
        if (s.empty()) {
            return 0;
        }

        // max_len[i] stores the length of the longest valid substring ending with character ('a' + i)
        std::vector<int> max_len(26, 0);
        int curr_len = 0;
        int n = static_cast<int>(s.size());

        for (int i = 0; i < n; ++i) {
            // Check if s[i] is consecutive to s[i-1] in wraparound sense
            if (i > 0 && ((s[i] - s[i - 1] == 1) || (s[i - 1] - s[i] == 25))) {
                curr_len++;
            } else {
                curr_len = 1;
            }

            int idx = s[i] - 'a';
            max_len[idx] = std::max(max_len[idx], curr_len);
        }

        // The sum of all values in max_len gives the total number of unique substrings
        return std::accumulate(max_len.begin(), max_len.end(), 0);
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the clean Python implementation with type hints.

```python
class Solution:
    def findSubstringInWraproundString(self, s: str) -> int:
        """
        Finds the number of unique non-empty substrings of s that exist in base.
        
        Time Complexity: O(N)
        Space Complexity: O(1)
        """
        if not s:
            return 0

        max_len = [0] * 26
        curr_len = 0

        for i, ch in enumerate(s):
            # Check if current character continues the wraparound pattern
            if i > 0 and (
                ord(s[i]) - ord(s[i - 1]) == 1 or ord(s[i - 1]) - ord(s[i]) == 25
            ):
                curr_len += 1
            else:
                curr_len = 1
            
            idx = ord(ch) - ord("a")
            max_len[idx] = max(max_len[idx], curr_len)

        return sum(max_len)
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Character to Integer Conversion
*   In Python, we use the `ord()` function to get the ASCII value of a character (e.g., `ord('a') = 97`).
*   Unlike C++, we cannot directly subtract character objects like `s[i] - s[i-1]`. We must wrap them in `ord()`.

### 2. Space Optimization
*   The space footprint is strictly $\mathcal{O}(1)$ since the size of the tracking array is constant ($26$). This is extremely efficient and garbage collector-friendly.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | We iterate through the string `s` of length $n$ exactly once. |
| **Space Complexity** | $\mathcal{O}(1)$ | Auxiliary space is bounded by the size of the alphabet (26), which is constant. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Why does summing the maximum length of substrings ending at each character guarantee uniqueness?
*   **Answer**: By grouping substrings by their *ending character*, we partition the set of all valid substrings into 26 disjoint subsets. For any ending character `c`, a valid substring of length $L$ uniquely determines the string (it consists of the $L$ characters in `base` ending at `c`). Any valid substring of length $K < L$ ending at `c` is a suffix of the substring of length $L$, meaning it is entirely contained within it. Thus, only taking the maximum length $L$ for each character ensures we count every unique substring exactly once.

### Q2: What if the base string was not a wraparound string (e.g., `'z'` does not wrap to `'a'`)?
*   **Answer**: The logic remains identical, except we remove the wrap-around condition `s[i-1] - s[i] == 25` from the consecutive check.

---

## Pro-Tip: How to Impress the Interviewer

*   **Avoid Deduplication Collections**: A common sub-optimal approach is to store all valid substrings in a hash set (e.g., `std::unordered_set<std::string>` or Python `set()`) to deduplicate them. Point out that this uses $\mathcal{O}(n^2)$ space and time in the worst case (e.g., `"abcdefg..."` has $\mathcal{O}(n^2)$ unique substrings), causing Memory Limit Exceeded (MLE). Showcasing how grouping by ending character reduces the space complexity to $\mathcal{O}(1)$ exhibits excellent systems-level optimization skills.
*   **Mention Cache Locality**: Point out that the C++ version utilizes a small 26-element stack array which easily fits in L1 cache (and even registers), resulting in zero heap allocation overhead and maximum CPU execution speed.
