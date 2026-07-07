# Longest Uncommon Subsequence II

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Algorithm Engineer
- **Source**: LeetCode 522, Glassdoor

---

## Question Description

Given an array of strings `strs`, return *the length of the longest uncommon subsequence between them*. If the longest uncommon subsequence does not exist, return `-1`.

An **uncommon subsequence** between an array of strings is a string that is a subsequence of one string but **not** the others.

A **subsequence** of a string `s` is a string that can be obtained after deleting any number of characters from `s` without changing the relative order of the remaining characters. (e.g., `"abc"` is a subsequence of `"aebdc"` while `"axc"` is not).

### Examples

*   **Input**: `strs = ["aba","cdc","eae"]`
    *   **Output**: `3`
    *   **Explanation**: The longest uncommon subsequence could be `"aba"`, `"cdc"`, or `"eae"`. Each of these has length 3 and is not a subsequence of any other string in the list.
*   **Input**: `strs = ["aaa","aaa","aa"]`
    *   **Output**: `-1`
    *   **Explanation**: 
        *   `"aaa"` appears twice, so it is a subsequence of another `"aaa"`.
        *   `"aa"` is a subsequence of `"aaa"`.
        *   Therefore, no uncommon subsequence exists, and we return `-1`.

### Constraints
*   $2 \le \text{strs.length} \le 50$
*   $1 \le \text{strs}[i].\text{length} \le 10$
*   `strs[i]` consists of lowercase English letters.

---

## Detailed Solution (C++)

To solve this problem:
1. **Mathematical Observation**: The longest uncommon subsequence must be one of the original strings in the array. If a subsequence $X$ of string $A$ is uncommon, then string $A$ itself must also be uncommon, and since $A$ is at least as long as $X$, we only need to check the strings in `strs` as candidates.
2. **Sort by Length Descending**: Sort the array of strings by their lengths in descending order. This ensures that the first valid uncommon string we find will be the longest one.
3. **Subsequence Check**: For each candidate string `strs[i]`, verify if it is a subsequence of any other string `strs[j]` (where $i \neq j$).
   * A string $A$ is a subsequence of $B$ if we can match all characters of $A$ sequentially in $B$ using a two-pointer scan.
4. **Early Termination**: Since the array is sorted by length, the first candidate string `strs[i]` that is **not** a subsequence of any other string is immediately returned as the longest uncommon subsequence length.

### Standard C++ Production Code

```cpp
#include <vector>
#include <string>
#include <algorithm>
#include <cstddef>

class Solution {
private:
    // Helper function to check if string 'a' is a subsequence of string 'b'
    bool isSubsequence(const std::string& a, const std::string& b) noexcept {
        const size_t len_a = a.length();
        const size_t len_b = b.length();
        if (len_a > len_b) {
            return false;
        }
        if (len_a == 0) {
            return true;
        }

        size_t i = 0;
        for (const char c : b) {
            if (a[i] == c) {
                i++;
                if (i == len_a) {
                    return true;
                }
            }
        }
        return false;
    }

public:
    int findLUSlength(std::vector<std::string>& strs) {
        // Sort strings by length in descending order
        std::sort(strs.begin(), strs.end(), [](const std::string& a, const std::string& b) {
            return a.length() > b.length();
        });

        const int n = static_cast<int>(strs.size());

        for (int i = 0; i < n; ++i) {
            bool is_uncommon = true;
            for (int j = 0; j < n; ++j) {
                if (i != j && isSubsequence(strs[i], strs[j])) {
                    is_uncommon = false;
                    break; // Candidate is a subsequence of another string, so it cannot be uncommon
                }
            }
            if (is_uncommon) {
                return static_cast<int>(strs[i].length());
            }
        }

        return -1; // No uncommon subsequence found
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation, which sorts in-place using list sorting.

```python
from typing import List

class Solution:
    def findLUSlength(self, strs: List[str]) -> int:
        """
        Finds the length of the longest uncommon subsequence.
        
        Time Complexity: O(N^2 * L) where N = len(strs), L = max length of strs[i]
        Space Complexity: O(1) auxiliary space (excluding sorting memory)
        """
        def isSubsequence(s1: str, s2: str) -> bool:
            len1, len2 = len(s1), len(s2)
            if len1 > len2:
                return False
            if len1 == 0:
                return True
            i = 0
            for char in s2:
                if s1[i] == char:
                    i += 1
                    if i == len1:
                        return True
            return False

        # Sort strings by length in descending order
        strs.sort(key=len, reverse=True)
        n = len(strs)

        for i in range(n):
            is_uncommon = True
            for j in range(n):
                if i != j and isSubsequence(strs[i], strs[j]):
                    is_uncommon = False
                    break
            if is_uncommon:
                return len(strs[i])

        return -1
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. In-place Sorting with `key=len`
* Python allows sorting lists of strings using a custom key like `key=len`. The sort is executed in compiled C code, which is highly efficient. By setting `reverse=True`, we perform descending sorting.

### 2. Frequency Optimization
* If a string is duplicated in the input (e.g., `["aaa", "aaa"]`), it can never be an uncommon subsequence because it is a subsequence of its duplicate.
* We can optimize the check by pre-calculating the frequency of each string:
  ```python
  from collections import Counter
  counts = Counter(strs)
  # When checking candidate, we can skip if counts[candidate] > 1
  ```
* This is extremely useful if the input has many duplicate strings.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n^2 \cdot L)$ | There are $n$ strings, and for each we check if it is a subsequence of the other $n-1$ strings. Each subsequence check takes $\mathcal{O}(L)$ time, where $L \le 10$ is the max string length. |
| **Space Complexity** | $\mathcal{O}(1)$ auxiliary | The algorithm uses constant auxiliary variables. Space is only consumed by the sorting algorithm stack. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Why must the longest uncommon subsequence be one of the strings in the array?
* **Answer**: Suppose the longest uncommon subsequence is a string $S$ that is *not* in the array. 
* By definition, $S$ must be a subsequence of some string $T$ in the array.
* If $T$ were a subsequence of some other string in the array, then $S$ (being a subsequence of $T$) would also be a subsequence of that other string, which contradicts the definition of $S$ being uncommon.
* Therefore, $T$ itself must be uncommon. Since $S$ is a subsequence of $T$, the length of $T$ is greater than or equal to the length of $S$. Thus, testing the elements of the array themselves is sufficient to find the maximum possible length.

### Q2: How can we optimize this if $n$ is large ($n \approx 10^5$) but string lengths remain small ($L \le 10$)?
* **Answer**: If $n$ is very large, the $\mathcal{O}(n^2)$ pairwise comparison is too slow. We can group identical strings and filter out duplicates. 
* Then, we can represent each string as a path in a Trie or use a hash map to skip strings that are sub-parts of previously verified strings.

---

## Pro-Tip: How to Impress the Interviewer

* **Use the Duplicate Frequency Filter Proactively**:
  * Point out that duplicate strings can be filtered out. In C++, we can use a hash map `std::unordered_map<std::string, int>` to count occurrences. If a string has a frequency $> 1$, we mark it as invalid. This shows that you are thinking about real-world database inputs where duplicates are common.
* **Explain the Subsequence Search Early Termination**:
  * If checking if string $A$ is a subsequence of $B$, we can immediately return `false` if `A.length() > B.length()`. In our nested loop, since strings are sorted by length descending, for any $j < i$, `strs[j]` is longer than or equal to `strs[i]`. So the check is only needed for $j < i$. If $j > i$, `strs[i]` cannot be a subsequence of `strs[j]` unless they are identical, which we already filter out. This reduces the number of subsequence checks by half!
