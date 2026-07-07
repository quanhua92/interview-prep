# Concatenated Words

- **Category**: Coding
- **Difficulty**: Hard
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 472, Glassdoor
- **Flashcards**: [Trie deck](../../flash_cards/coding/trie.md)

---

## Question Description

Given an array of strings `words` (without duplicates), return *all the **concatenated words** in the given list of words*.

A **concatenated word** is defined as a string that is comprised entirely of at least two shorter words (not necessarily distinct) in the given array.

### Examples

*   **Input**:
    ```json
    words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
    ```
    *   **Output**: `["catsdogcats","dogcatsdog","ratcatdogcat"]`
    *   **Explanation**: 
        *   `"catsdogcats"` can be concatenated by `"cats"`, `"dog"` and `"cats"`.
        *   `"dogcatsdog"` can be concatenated by `"dog"`, `"cats"` and `"dog"`.
        *   `"ratcatdogcat"` can be concatenated by `"rat"`, `"cat"`, `"dog"` and `"cat"`.
*   **Input**:
    ```json
    words = ["cat","dog","catdog"]
    ```
    *   **Output**: `["catdog"]`

### Constraints
*   $1 \le \text{words.length} \le 10^4$
*   $1 \le \text{words}[i].\text{length} \le 30$
*   `words[i]` consists of only lowercase English letters.
*   All strings in `words` are unique.
*   $1 \le \sum \text{words}[i].\text{length} \le 10^5$

---

## Detailed Solution (C++)

A naive search for partitions would result in exponential time complexity due to redundant path calculations. We can solve this efficiently using a combination of **Sorting**, **Trie**, and **DFS with Memoization**:

1.  **Sort Words by Length**: We sort the words in ascending order of their length. By doing this, we guarantee that when we process a word, all potential component words (which must be strictly shorter) have already been analyzed and inserted into the Trie.
2.  **DFS with Memoization**: For each word, we check if it can be formed by the shorter words currently in the Trie.
    *   To prevent worst-case exponential backtracking (e.g., matching `aaaa...ab`), we maintain a `memo` array of size `L` where `memo[start]` caches whether the suffix starting at index `start` can be successfully concatenated.
3.  **Insert into Trie**: After evaluating the word, we insert it into the Trie so it can be used to form even longer words.

### Standard C++ Production Code

```cpp
#include <vector>
#include <string>
#include <algorithm>

class Solution {
private:
    struct TrieNode {
        TrieNode* children[26] = {nullptr};
        bool is_end = false;

        // Recursive destructor to prevent memory leaks
        ~TrieNode() {
            for (TrieNode* child : children) {
                delete child;
            }
        }
    };

    TrieNode* root;

    void insert(const std::string& word) {
        TrieNode* cur = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (!cur->children[idx]) {
                cur->children[idx] = new TrieNode();
            }
            cur = cur->children[idx];
        }
        cur->is_end = true;
    }

    // DFS with Memoization to check if a suffix can be formed from Trie words
    bool canConcatenate(const std::string& word, size_t start, std::vector<int>& memo) const noexcept {
        if (start == word.size()) {
            return true;
        }
        if (memo[start] != -1) {
            return memo[start];
        }

        TrieNode* cur = root;
        for (size_t i = start; i < word.size(); ++i) {
            int idx = word[i] - 'a';
            if (!cur->children[idx]) {
                break; // No matching prefix in Trie, prune branch
            }
            cur = cur->children[idx];
            if (cur->is_end) {
                if (canConcatenate(word, i + 1, memo)) {
                    return memo[start] = 1; // Cache success
                }
            }
        }
        return memo[start] = 0; // Cache failure
    }

public:
    Solution() : root(new TrieNode()) {}

    ~Solution() {
        delete root;
    }

    // Disable copy operations to maintain strict RAII safety
    Solution(const Solution&) = delete;
    Solution& operator=(const Solution&) = delete;

    std::vector<std::string> findAllConcatenatedWordsInADict(std::vector<std::string>& words) {
        // Sort words by length in ascending order
        std::sort(words.begin(), words.end(), [](const std::string& a, const std::string& b) {
            return a.size() < b.size();
        });

        std::vector<std::string> result;
        for (const std::string& word : words) {
            if (word.empty()) continue;

            // memo: -1 = unvisited, 0 = False, 1 = True
            std::vector<int> memo(word.size(), -1);
            if (canConcatenate(word, 0, memo)) {
                result.push_back(word);
            }
            // Always insert the word to allow it to form longer words
            insert(word);
        }
        return result;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the Python equivalent using `__slots__` for Trie memory efficiency and a simple list for fast state memoization.

```python
from typing import List

class TrieNode:
    __slots__ = ("children", "is_end")
    
    def __init__(self) -> None:
        self.children: dict[str, TrieNode] = {}
        self.is_end: bool = False

class Solution:
    def findAllConcatenatedWordsInADict(self, words: List[str]) -> List[str]:
        # Sort by length: guarantees only shorter words exist in the Trie
        words.sort(key=len)
        
        root = TrieNode()

        def insert(word: str) -> None:
            node = root
            for ch in word:
                if ch not in node.children:
                    node.children[ch] = TrieNode()
                node = node.children[ch]
            node.is_end = True

        def can_concatenate(word: str, start: int, memo: List[int]) -> bool:
            if start == len(word):
                return True
            if memo[start] != -1:
                return memo[start] == 1

            node = root
            for i in range(start, len(word)):
                ch = word[i]
                if ch not in node.children:
                    break
                node = node.children[ch]
                if node.is_end:
                    if can_concatenate(word, i + 1, memo):
                        memo[start] = 1
                        return True

            memo[start] = 0
            return False

        result: List[str] = []
        for word in words:
            if not word:
                continue
            # Memo table initialized to -1 (unvisited)
            memo = [-1] * len(word)
            if can_concatenate(word, 0, memo):
                result.append(word)
            insert(word)

        return result
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Memoization with Flat Lists vs `@lru_cache`
*   Python's `@lru_cache` from `functools` is a convenient way to cache function results, but it introduces substantial lookup and function-call overhead.
*   Since word lengths are small ($L \le 30$), allocating a simple list `memo = [-1] * len(word)` is far faster. List indexing `memo[start]` runs at C-speed and avoids hashing arguments.

### 2. Recursion Limit
*   Python's default recursion limit is $1000$. Because the maximum length of a word is constrained to $30$, our recursion depth will never exceed $30$, making recursive DFS safe and free of `RecursionError` risks.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(N \log N \cdot L + N \cdot L^2)$ | $N$ is the number of words, $L$ is the maximum length of a word. Sorting takes $\mathcal{O}(N \log N \cdot L)$ time. For each word, memoized DFS visits at most $L$ indices, performing at most $L$ character lookups. |
| **Space Complexity** | $\mathcal{O}(N \cdot L)$ | Memory used to store words in the Trie. The recursion stack and memo table require $\mathcal{O}(L)$ auxiliary space. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Can we solve this problem without sorting the words first?
*   **The Answer**: Yes, we can. We can insert all words into a Trie or a Hash Set first.
*   **The Catch**: During the search for `word`, we must ensure it doesn't match itself as a single piece (since a concatenated word requires at least two component words). 
*   To do this, we pass a `count` parameter in the DFS:
    ```python
    def dfs(word, start, count):
        # ...
        # At the end of the string, return True only if count >= 2
    ```
*   **Comparison**: Sorting by length is cleaner because we only check if a word is formed by strictly shorter words, naturally preventing a word from matching itself.

### Q2: How does a Hash Set approach compare to the Trie approach?
*   **The Hash Set Solution**: We store all words in a Hash Set. To check if a word is concatenated, we run a DP/DFS similar to Word Break, slicing the string at different indices and looking up slices in the Set.
*   **Trie Advantage**: A Trie is more efficient when words share prefixes because we scan character-by-character. If a prefix is not in the Trie, we break immediately. In contrast, checking slices in a Set (e.g. `word[start:i]`) forces us to copy sub-strings, incurring copying overhead.

---

## Pro-Tip: How to Impress the Interviewer

*   **Discuss DP Memoization explicitly**: Explain how checking `memo` avoids exponential branching on pathological inputs like `aaaa...aaaab`. Showing that you proactively identify exponential worst-cases and apply memoization is a hallmark of a senior candidate.
*   **Analyze String Copy Costs**: Point out that using a Trie to match characters sequentially avoids creating intermediate substring copies (which would occur if you used string slicing with a Hash Set). This highlights your awareness of garbage collection and allocation costs.
