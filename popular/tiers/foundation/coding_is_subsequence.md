# Is Subsequence

- **Category**: Coding
- **Difficulty**: Easy
- **Target Role**: Software Engineer / ML Engineer
- **Source**: LeetCode 392, Glassdoor
- **Flashcards**: [Two Pointers deck](../../flash_cards/coding/two_pointers.md)

---

## Question Description

Given two strings `s` and `t`, return `true` *if* `s` *is a subsequence of* `t`*, or* `false` *otherwise*.

A **subsequence** of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., `"ace"` is a subsequence of `"abcde"` while `"aec"` is not).

### Examples

*   **Input**: `s = "abc"`, `t = "ahbgdc"`
    *   **Output**: `true`
*   **Input**: `s = "axc"`, `t = "ahbgdc"`
    *   **Output**: `false`

### Constraints
*   $0 \le \text{s.length} \le 100$
*   $0 \le \text{t.length} \le 10^4$
*   `s` and `t` consist only of lowercase English letters.

---

## Detailed Solution (C++)

The problem asks if we can find all characters of `s` in `t` in their respective order. We can solve this in linear time using a **two-pointer approach**:

1. Initialize a pointer `s_idx = 0` to track the current character in `s` we need to match.
2. Iterate through each character `c` in `t`.
3. If `s[s_idx] == c`, we have found a match for the current character, so we increment `s_idx`.
4. **Early Termination**: If `s_idx` equals the length of `s`, it means all characters of `s` have been matched in order. We can return `true` immediately, avoiding processing the rest of `t`.
5. If the loop completes and `s_idx < s.length()`, return `false`.

### Standard C++ Production Code

```cpp
#include <string>
#include <cstddef>

class Solution {
public:
    bool isSubsequence(const std::string& s, const std::string& t) noexcept {
        // Edge Case: An empty string is always a subsequence of any string
        if (s.empty()) {
            return true;
        }

        size_t s_idx = 0;
        const size_t s_len = s.length();

        for (const char c : t) {
            if (s[s_idx] == c) {
                s_idx++;
                // Early return if s is fully matched
                if (s_idx == s_len) {
                    return true;
                }
            }
        }

        return false;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation. It features early termination to optimize performance.

```python
class Solution:
    def isSubsequence(self, s: str, t: str) -> bool:
        """
        Determines if s is a subsequence of t.
        
        Time Complexity: O(len(t))
        Space Complexity: O(1)
        """
        # Edge Case: An empty string is always a subsequence of any string
        if not s:
            return True

        s_idx = 0
        s_len = len(s)

        for char in t:
            if s[s_idx] == char:
                s_idx += 1
                # Early return if s is fully matched
                if s_idx == s_len:
                    return True

        return False
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. The Iterator-Based Pythonic Trick
* Python allows a highly optimized, one-liner solution using the `iter()` function and the `all()` generator:
  ```python
  def isSubsequence(self, s: str, t: str) -> bool:
      t_iter = iter(t)
      return all(char in t_iter for char in s)
  ```
* **How it works**: `iter(t)` creates an iterator over `t`. The expression `char in t_iter` advances the iterator until it finds `char`. Because the iterator state is preserved across checks, `all(...)` ensures each character of `s` is matched in sequence.
* **Pros**: It runs at C-speed internally in CPython, requiring minimal memory allocations.
* **Cons**: It is harder to debug and explain in an interview. Interviewers typically prefer the explicit two-pointer loop.

### 2. Character Hashing Overhead
* Because python characters are string objects of length 1, doing index-based lookup `s[s_idx]` or iterating has slightly more overhead than traversing raw character arrays in C++. However, this is negligible unless handling extremely large scale strings.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(|t|)$ | In the worst case, we scan the entire string `t` once. |
| **Space Complexity** | $\mathcal{O}(1)$ | Only index pointers and length variables are allocated. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if there are many incoming strings ($k \approx 10^9$) and we want to check if each is a subsequence of a single, giant string $t$ ($|t| \le 10^6$)?
* **Answer**: Running the $\mathcal{O}(|t|)$ two-pointer scan for each query would take $\mathcal{O}(k \cdot |t|)$ time, which is too slow.
* **Optimal Solution**: Preprocess $t$ to build an index lookup map. 
  1. Construct a hash map (or array of 26 lists) where the keys are characters and the values are lists of indices where that character appears in $t$ (sorted in ascending order).
  2. For a query string $s$, initialize a variable `prev_idx = -1`.
  3. For each character `c` in `s`, look up its list of indices in the map.
  4. Perform a **Binary Search** (e.g., `std::upper_bound` in C++ or `bisect_right` in Python) on the list to find the smallest index `curr_idx` that is strictly greater than `prev_idx`.
  5. If no such index exists, then `s` is not a subsequence. Otherwise, update `prev_idx = curr_idx` and proceed.
* **Complexity**: Preprocessing takes $\mathcal{O}(|t|)$ time. Each query now takes $\mathcal{O}(|s| \log |t|)$ time. This is a massive improvement when $|s| \ll |t|$ and $k$ is large.

---

## Pro-Tip: How to Impress the Interviewer

* **Proactively Discuss the Multi-Query Variant**: Start by proposing the basic two-pointer algorithm. Once written, ask: *"Is this going to be called repeatedly on the same target string `t` for many different input strings `s`?"* and then explain the index-lookup binary-search pre-processing optimization.
* **Highlight Cache Friendliness**: String search involves sequential array traversal. Explain that C++'s `std::string` stores data contiguously in virtual memory. This triggers spatial locality in CPU L1/L2 caches, resulting in near-instant memory loads compared to node-based data structures.
* **Explicit Constant References**: Always pass string arguments as `const std::string&` in C++ to prevent deep copies. If the string is short, explain how Small String Optimization (SSO) in C++ standard libraries avoids heap allocation entirely.
