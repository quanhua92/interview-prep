# Design Add and Search Words Data Structure

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 211, Glassdoor

---

## Question Description

Design a data structure that supports adding new words and finding if a string matches any previously added string.

Implement the `WordDictionary` class:

*   `WordDictionary()` Initializes the object.
*   `void addWord(word)` Adds `word` to the data structure, it can be matched later.
*   `bool search(word)` Returns `true` if there is any string in the data structure that matches `word` or `false` otherwise. `word` may contain dots `.` where dots can be matched with any letter.

### Examples

*   **Input**:
    ```json
    ["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
    [[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
    ```
*   **Output**:
    ```json
    [null,null,null,null,false,true,true,true]
    ```
*   **Explanation**:
    ```cpp
    WordDictionary wordDictionary;
    wordDictionary.addWord("bad");
    wordDictionary.addWord("dad");
    wordDictionary.addWord("mad");
    wordDictionary.search("pad"); // return False
    wordDictionary.search("bad"); // return True
    wordDictionary.search(".ad"); // return True
    wordDictionary.search("b.."); // return True
    ```

### Constraints
*   $1 \le \text{word.length} \le 25$
*   `word` in `addWord` consists of lowercase English letters.
*   `word` in `search` consists of `.` or lowercase English letters.
*   There will be at most 2 dots in `word` for search queries.
*   At most $10^4$ calls in total will be made to `addWord` and `search`.

---

## Detailed Solution (C++)

To implement the wildcard search feature (`.`), we can build a Trie. Standard word insertions are identical to a regular Trie. For searching:
1. If the character is a lowercase English letter, we retrieve the corresponding child pointer `children[ch - 'a']`.
2. If the character is `.`, we perform a **Depth-First Search (DFS)**, recursively trying all non-null children pointers at the current depth.

### Standard C++ Production Code

```cpp
#include <string>
#include <string_view>
#include <utility>

class WordDictionary {
private:
    struct TrieNode {
        TrieNode* children[26] = {nullptr};
        bool is_end = false;

        // Cleanly deallocate child nodes recursively
        ~TrieNode() {
            for (TrieNode* child : children) {
                delete child;
            }
        }
    };

    TrieNode* root;

    // Helper recursive method for wildcard matching
    bool dfs(const TrieNode* node, std::string_view word, size_t index) const noexcept {
        if (index == word.size()) {
            return node->is_end;
        }

        char ch = word[index];
        if (ch == '.') {
            // Wildcard match: explore all possible paths
            for (const TrieNode* child : node->children) {
                if (child && dfs(child, word, index + 1)) {
                    return true;
                }
            }
            return false;
        } else {
            int idx = ch - 'a';
            const TrieNode* child = node->children[idx];
            return child != nullptr && dfs(child, word, index + 1);
        }
    }

public:
    WordDictionary() : root(new TrieNode()) {}

    ~WordDictionary() {
        delete root;
    }

    // Disable copy operations to ensure memory safety
    WordDictionary(const WordDictionary&) = delete;
    WordDictionary& operator=(const WordDictionary&) = delete;

    // Support move operations
    WordDictionary(WordDictionary&& other) noexcept : root(other.root) {
        other.root = nullptr;
    }

    WordDictionary& operator=(WordDictionary&& other) noexcept {
        if (this != &other) {
            delete root;
            root = other.root;
            other.root = nullptr;
        }
        return *this;
    }

    void addWord(const std::string& word) {
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

    bool search(const std::string& word) const noexcept {
        return dfs(root, word, 0);
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted, recursive Python implementation. It uses `__slots__` to optimize memory and avoids string slicing to maintain efficiency.

```python
class TrieNode:
    __slots__ = ("children", "is_end")
    
    def __init__(self) -> None:
        self.children: dict[str, TrieNode] = {}
        self.is_end: bool = False

class WordDictionary:
    def __init__(self) -> None:
        self.root = TrieNode()

    def addWord(self, word: str) -> None:
        """
        Adds a word to the trie.
        Time Complexity: O(L)
        """
        node = self.root
        for ch in word:
            if ch not in node.children:
                node.children[ch] = TrieNode()
            node = node.children[ch]
        node.is_end = True

    def search(self, word: str) -> bool:
        """
        Returns true if there is any string in the trie matching the word.
        '.' can match any lowercase English letter.
        """
        return self._dfs(self.root, word, 0)

    def _dfs(self, node: TrieNode, word: str, index: int) -> bool:
        # Base Case: We reached the end of the query string
        if index == len(word):
            return node.is_end

        ch = word[index]
        if ch == ".":
            # Wildcard branch: Try all available children
            for child in node.children.values():
                if self._dfs(child, word, index + 1):
                    return True
            return False
        
        # Exact character match
        if ch not in node.children:
            return False
        return self._dfs(node.children[ch], word, index + 1)
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Avoiding the String Slicing Trap
*   A common Python mistake during DFS searches is passing a sliced string to subsequent recursion frames: `self._dfs(child, word[1:])`.
*   Slicing a string of length $L$ creates a shallow copy, taking $\mathcal{O}(L)$ time and space. Doing this on every level of the recursive tree results in $\mathcal{O}(L^2)$ time/space overhead.
*   By passing the original string and a tracking index (`index + 1`), we keep string references constant and guarantee $\mathcal{O}(1)$ space per call frame.

### 2. Fast Wildcard Iteration with `.values()`
*   When evaluating `.`, iterating directly over `node.children.values()` is faster than doing key lookups `node.children[key]` because it avoids hashing keys and traverses the underlying dictionary table values directly in C-speed.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity (addWord)** | $\mathcal{O}(L)$ | We traverse the characters of the word and insert new nodes. |
| **Time Complexity (search)** | $\mathcal{O}(M^L)$ | In the worst case (query contains all `.` wildcards), we may visit all nodes in the Trie. $M$ is the branching factor (up to 26). For queries without wildcards, it is $\mathcal{O}(L)$. |
| **Space Complexity** | $\mathcal{O}(N \cdot L)$ | Dynamic heap memory for the Trie structure. Auxiliary space for the search stack is $\mathcal{O}(L)$ where $L$ is the length of the query. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How would you optimize the search if the dictionary contains millions of words, and we get queries with many dots?
*   **The Problem**: Searching for `.....` in a dense Trie containing millions of words requires examining almost every node, leading to severe slowdowns.
*   **The Solutions**:
    1.  **Length Pruning**: Keep track of the lengths of all added words. In Python, maintain a set of integer lengths (`self.lengths = set()`). Before executing a search, check if `len(word) in self.lengths`. If not, return `false` instantly.
    2.  **Separate Trees by Length**: Maintain a hash map of `word_length -> TrieRoot`. We only search the Trie corresponding to the exact length of the search word, pruning unrelated branches.

### Q2: What if we want to search words matching a regular expression beyond '.' (e.g. '*' or '[a-z]')?
*   **The Solution**: The Trie DFS structure can easily adapt to other patterns:
    *   For character classes like `[a-z]`: Extract the characters inside the brackets and recursively search only those children.
    *   For kleene star `*`: We can either remain at the current node (match 0 characters) or try matching the character multiple times.

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention length-filtering optimization upfront**: Interviewers love candidates who identify bottleneck cases (like a search query consisting of all dots) and immediately propose cheap checks like `length` filtering to bypass expensive traversals.
*   **Rule of Five (C++)**: Explicitly write a copy constructor and assignment operator deletion. This demonstrates your awareness of safe memory practices in C++ to prevent double-frees when local nodes go out of scope.
