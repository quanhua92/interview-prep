# Longest Word in Dictionary through Deleting

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Algorithm Engineer
- **Source**: LeetCode 524, Glassdoor
- **Flashcards**: [Two Pointers deck](../../flash_cards/coding/two_pointers.md)

---

## Question Description

Given a string `s` and a string array `dictionary`, return *the longest string in the dictionary that can be formed by deleting some of the given string characters*. If there is more than one possible result, return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.

### Examples

*   **Input**: `s = "abpcplea"`, `dictionary = ["ale","apple","monkey","plea"]`
    *   **Output**: `"apple"`
    *   **Explanation**: Both `"ale"` and `"apple"` can be formed by deleting characters from `s`. Since `"apple"` is longer than `"ale"`, it is selected.
*   **Input**: `s = "abpcplea"`, `dictionary = ["a","b","c"]`
    *   **Output**: `"a"`
    *   **Explanation**: `"a"`, `"b"`, and `"c"` can all be formed. `"a"` is chosen because it is lexicographically smallest.

### Constraints
*   $1 \le \text{s.length} \le 1000$
*   $1 \le \text{dictionary.length} \le 1000$
*   $1 \le \text{dictionary}[i].\text{length} \le 1000$
*   `s` and `dictionary[i]` consist of lowercase English letters.

---

## Detailed Solution (C++)

A direct linear scan through the dictionary is highly efficient if we apply **early pruning**:

1. Initialize `best` to an empty string `""`.
2. For each `word` in the `dictionary`:
   * **Pruning Check**: Before checking if `word` is a subsequence of `s`, compare its length and lexicographical order with `best`. If `word` is shorter than `best`, or if it is of equal length but lexicographically greater than or equal to `best`, then even if it is a subsequence, it cannot become the new `best`. We can immediately `continue` to the next word.
   * **Subsequence Check**: If the word passes the pruning check, use the two-pointer technique to check if it is a subsequence of `s`.
   * If it is a subsequence, update `best = word`.
3. Return `best`.

### Standard C++ Production Code

```cpp
#include <vector>
#include <string>
#include <algorithm>
#include <cstddef>

class Solution {
private:
    // Helper function to check if 'word' is a subsequence of 's'
    bool isSubsequence(const std::string& word, const std::string& s) noexcept {
        const size_t w_len = word.length();
        const size_t s_len = s.length();

        // If the word is longer than the source string, it cannot be a subsequence
        if (w_len > s_len) {
            return false;
        }
        if (w_len == 0) {
            return true;
        }

        size_t w_idx = 0;
        for (const char c : s) {
            if (word[w_idx] == c) {
                w_idx++;
                if (w_idx == w_len) {
                    return true;
                }
            }
        }
        return false;
    }

public:
    std::string findLongestWord(const std::string& s, const std::vector<std::string>& dictionary) {
        std::string best = "";

        for (const std::string& word : dictionary) {
            // Pruning: Skip checking if the word cannot beat the current 'best'
            if (word.length() < best.length() || 
                (word.length() == best.length() && word >= best)) {
                continue;
            }

            if (isSubsequence(word, s)) {
                best = word;
            }
        }

        return best;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation, leveraging short-circuit logic to minimize subsequence checks.

```python
from typing import List

class Solution:
    def findLongestWord(self, s: str, dictionary: List[str]) -> str:
        """
        Finds the longest word in dictionary that is a subsequence of s.
        
        Time Complexity: O(N * L) where N = len(dictionary), L = len(s)
        Space Complexity: O(1) auxiliary space
        """
        def isSubsequence(word: str, target: str) -> bool:
            w_len = len(word)
            t_len = len(target)
            if w_len > t_len:
                return False
            if w_len == 0:
                return True
                
            w_idx = 0
            for char in target:
                if word[w_idx] == char:
                    w_idx += 1
                    if w_idx == w_len:
                        return True
            return False

        best = ""

        for word in dictionary:
            # Prune: Skip checks for words that cannot improve our result
            if len(word) < len(best) or (len(word) == len(best) and word >= best):
                continue
            
            if isSubsequence(word, s):
                best = word

        return best
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Sorting the Dictionary (Trade-off)
* An alternative implementation is to sort the dictionary beforehand:
  ```python
  dictionary.sort(key=lambda x: (-len(x), x))
  ```
  This sorts the dictionary by length descending, and then lexicographically ascending. The first word in the sorted dictionary that is a subsequence of `s` is the correct answer.
* **Trade-off**: Sorting takes $\mathcal{O}(n \log n \cdot W)$ time (where $W$ is the maximum word length). Our linear scan approach takes $\mathcal{O}(n \cdot L_s)$ time. Since $n \le 1000$ and $L_s \le 1000$, the linear scan with pruning is much faster in practice and avoids memory allocations for sorting.

### 2. Lexicographical Comparison
* In Python, string comparisons like `word >= best` are implemented at the C level in CPython and run very fast. Since it checks character-by-character, it will return as soon as a mismatch is found, saving execution cycles.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n \cdot L_s)$ | We perform at most $n$ subsequence checks. Each check scans string `s` of length $L_s$. Pruning makes the average case much faster. |
| **Space Complexity** | $\mathcal{O}(1)$ auxiliary | The algorithm uses only index pointers and variables to track the best word, requiring constant space. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if we have many queries of string `s`? How can we preprocess the dictionary?
* **Answer**: If the dictionary is static and we receive multiple source strings `s`, we can build a **Trie** from the dictionary.
* For each query string `s`, we perform a DFS search over the Trie, matching characters of `s`. This allows us to search multiple dictionary words simultaneously, pruning entire branches of words that do not match the character stream.

### Q2: What if the dictionary contains billions of words?
* **Answer**: If the dictionary is too large to fit in memory, we can stream the dictionary from external storage. 
* Because our linear scan maintains only a single `best` string of size up to $1000$ bytes, the space complexity remains $\mathcal{O}(1)$ auxiliary, making it highly suitable for streaming/out-of-core computation.

---

## Pro-Tip: How to Impress the Interviewer

* **Proactively Highlight Pruning Logic**:
  * Point out that checking `word.length() < best.length()` first saves substantial CPU cycles because it bypasses the linear character-matching loop for any word that is too short.
* **Explain Small String Optimization (SSO)**:
  * In C++, explain that if dictionary strings are small (less than 15 characters on most 64-bit systems), they are stored directly inside the string control block rather than on the heap. This prevents heap allocations during dictionary iteration and yields excellent L1/L2 cache hit ratios.
* **State Space Bounds of the Return String**:
  * If the interviewer asks about return-value copy overhead, explain that returning `std::string` from a function in C++11 and newer leverages **Move Semantics** or **Return Value Optimization (RVO)**, making the return operation $\mathcal{O}(1)$ instead of copying the string bytes.
