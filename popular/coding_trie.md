# Implement Trie (Prefix Tree)

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI System Developer
- **Source**: LeetCode 208, Glassdoor

---

## Question Description

A **trie** (pronounced as "try") or **prefix tree** is a tree data structure used to efficiently store and retrieve keys in a dataset of strings. There are various applications of this data structure, such as autocomplete and spellchecker.

Implement the `Trie` class:
*   `Trie()` Initializes the trie object.
*   `void insert(String word)` Inserts the string `word` into the trie.
*   `boolean search(String word)` Returns `true` if the string `word` is in the trie (i.e., was inserted before), and `false` otherwise.
*   `boolean startsWith(String prefix)` Returns `true` if there is a previously inserted string `word` that has the prefix `prefix`, and `false` otherwise.

### Constraints
*   $1 \le \text{word.length}, \text{prefix.length} \le 2000$
*   `word` and `prefix` consist only of lowercase English letters.
*   At most $3 \times 10^4$ calls in total will be made to `insert`, `search`, and `startsWith`.

---

## Detailed Solution (C++)

Using raw pointers for custom tree structures in C++ often leads to memory leaks or complex destructor logic. In modern C++ (C++11 and above), **smart pointers** (specifically `std::unique_ptr`) are preferred because they enforce **Resource Acquisition Is Initialization (RAII)**. A `std::unique_ptr` represents exclusive ownership of a resource, automatically deallocating its children when it goes out of scope.

Below is the clean C++ implementation of a Trie using `std::unique_ptr` with added validation bounds to ensure memory safety.

```cpp
#include <string>
#include <memory>
#include <vector>
#include <stdexcept>

class Trie {
private:
    struct TrieNode {
        // std::unique_ptr for automatic memory management
        std::unique_ptr<TrieNode> children[26];
        bool isEndOfWord{false};

        TrieNode() = default;
    };

    std::unique_ptr<TrieNode> root;

    // Helper: Validates input characters to prevent out-of-bound array indexing
    static bool isValidChar(char ch) noexcept {
        return ch >= 'a' && ch <= 'z';
    }

public:
    Trie() {
        root = std::make_unique<TrieNode>();
    }

    // Rule of 5: Prevent resource leaks and double deletions via copying/moving
    ~Trie() noexcept = default;
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
    Trie(Trie&&) noexcept = default;
    Trie& operator=(Trie&&) noexcept = default;

    // Insert a word into the trie
    void insert(const std::string& word) {
        TrieNode* curr = root.get(); // Get raw pointer for traversal (does not transfer ownership)
        
        for (char ch : word) {
            if (!isValidChar(ch)) {
                throw std::invalid_argument("Trie only supports lowercase English letters.");
            }
            int idx = ch - 'a';
            if (!curr->children[idx]) {
                curr->children[idx] = std::make_unique<TrieNode>();
            }
            curr = curr->children[idx].get();
        }
        curr->isEndOfWord = true;
    }

    // Returns true if the word is in the trie
    bool search(const std::string& word) const {
        TrieNode* curr = root.get();
        
        for (char ch : word) {
            if (!isValidChar(ch)) {
                return false;
            }
            int idx = ch - 'a';
            if (!curr->children[idx]) {
                return false;
            }
            curr = curr->children[idx].get();
        }
        return curr->isEndOfWord;
    }

    // Returns true if there is any word in the trie that starts with the given prefix
    bool startsWith(const std::string& prefix) const {
        TrieNode* curr = root.get();
        
        for (char ch : prefix) {
            if (!isValidChar(ch)) {
                return false;
            }
            int idx = ch - 'a';
            if (!curr->children[idx]) {
                return false;
            }
            curr = curr->children[idx].get();
        }
        return true; // Reached end of prefix, matching path exists
    }
};
```

---

## Detailed Solutions (Python)

We provide two implementation patterns in Python:
1. **Class-based TrieNode (Recommended)**: Utilizes a custom class with `__slots__` for production-grade object-oriented design.
2. **Nested Dictionary Trie (Ultra-compact)**: Leverages native dictionary hashing for maximum speed and simplicity.

### Method 1: Class-Based TrieNode (Interview Standard)

```python
from typing import Dict

class TrieNode:
    # __slots__ eliminates __dict__ generation, saving up to 70% memory per node
    __slots__ = ('children', 'is_end_of_word')
    
    def __init__(self):
        self.children: Dict[str, TrieNode] = {}
        self.is_end_of_word: bool = False


class Trie:
    def __init__(self):
        self.root: TrieNode = TrieNode()

    def insert(self, word: str) -> None:
        """
        Inserts a word into the trie.
        """
        curr = self.root
        for ch in word:
            # Safe character boundary check
            if not ('a' <= ch <= 'z'):
                raise ValueError("Trie only supports lowercase English letters.")
            
            # Using 'if not in' is faster than setdefault() due to object instantiation rules
            if ch not in curr.children:
                curr.children[ch] = TrieNode()
            curr = curr.children[ch]
        curr.is_end_of_word = True

    def search(self, word: str) -> bool:
        """
        Returns True if the word is in the trie.
        """
        curr = self.root
        for ch in word:
            if ch not in curr.children:
                return False
            curr = curr.children[ch]
        return curr.is_end_of_word

    def startsWith(self, prefix: str) -> bool:
        """
        Returns True if there is any word in the trie that starts with the given prefix.
        """
        curr = self.root
        for ch in prefix:
            if ch not in curr.children:
                return False
            curr = curr.children[ch]
        return True
```

### Method 2: Nested Dictionary Trie (Compact/Pythonic)

Using a special character (e.g., `'#'`) as the end-of-word sentinel marker.

```python
class TrieNestedDict:
    def __init__(self):
        self.root = {}

    def insert(self, word: str) -> None:
        curr = self.root
        for ch in word:
            # setdefault returns the dictionary for key 'ch', creating it if absent
            curr = curr.setdefault(ch, {})
        curr['#'] = True  # End of word sentinel

    def search(self, word: str) -> bool:
        curr = self.root
        for ch in word:
            if ch not in curr:
                return False
            curr = curr[ch]
        return '#' in curr

    def startsWith(self, prefix: str) -> bool:
        curr = self.root
        for ch in prefix:
            if ch not in curr:
                return False
            curr = curr[ch]
        return True
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Object Memory Overhead
*   **The Problem**: Python objects are heavy. In CPython, a basic user-defined object instance takes 56 bytes. A dictionary starts at 64 to 240 bytes. In a Trie with millions of letters, this leads to massive memory overhead (up to $10\times$ more than C++).
*   **The Solution**: Declaring `__slots__ = ('children', 'is_end_of_word')` in the node definition prevents the creation of the instance `__dict__`, reducing the per-node overhead by up to **$70\%$**.

### 2. The `setdefault()` Performance Trap
*   Doing `curr.children.setdefault(ch, TrieNode())` looks clean but is a major performance bottleneck. 
*   Because Python evaluates function arguments *before* invoking the function, `TrieNode()` is instantiated on **every single character lookup**, regardless of whether the character already exists. This wastes CPU cycles and triggers frequent garbage collection sweeps.
*   Always use `if ch not in curr.children: curr.children[ch] = TrieNode()` to ensure lazy node creation.

### 3. Destruction Stack Frame Safety
*   Unlike C++, where deleting a deeply nested `std::unique_ptr` tree can lead to a call stack overflow from cascading destructors, CPython's garbage collector operates iteratively when reference cycles or deep structures are destroyed, preventing stack overflows during reclamation.

### 4. Dynamic Alphabet Scaling
*   Python's dictionary-based children node representation automatically handles Unicode, wide characters, and dynamic alphabets without manual indexing (`ch - 'a'`) or wasting memory on unused fixed-size array pointers.

---

## Complexity Analysis

| Operation | Time Complexity | Space Complexity | Description |
| :--- | :--- | :--- | :--- |
| `insert()` | $\mathcal{O}(L)$ | $\mathcal{O}(L \cdot A)$ | Where $L$ is the word length and $A$ is alphabet size (26). We create up to $L$ nodes. |
| `search()` | $\mathcal{O}(L)$ | $\mathcal{O}(1)$ | We perform up to $L$ comparisons. |
| `startsWith()` | $\mathcal{O}(L)$ | $\mathcal{O}(1)$ | We perform up to $L$ comparisons. |
| Total Space | - | $\mathcal{O}(N \cdot L \cdot A)$ | In the worst case (no common prefixes), where $N$ is the number of words. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How do you delete a word from the Trie?
*   **Answer**: Deleting a word involves backtracking:
    1. Traverse down the tree to the end of the word.
    2. Set `isEndOfWord = false` at the target node.
    3. Backtrack up. If a parent node has a child that has no other children and is not marked as `isEndOfWord`, we delete that child node to reclaim memory.
    
    ```cpp
    bool remove(TrieNode* curr, const std::string& word, std::size_t depth) {
        if (!curr) return false;
        
        if (depth == word.length()) {
            if (!curr->isEndOfWord) return false;
            curr->isEndOfWord = false;
            // Check if node has no children; if so, it can be deleted
            for (int i = 0; i < 26; ++i) {
                if (curr->children[i]) return false;
            }
            return true; // Parent should delete this node
        }
        
        int idx = word[depth] - 'a';
        if (remove(curr->children[idx].get(), word, depth + 1)) {
            curr->children[idx].reset(); // Deallocates the child node
            // Check if current node has other children or is the end of another word
            if (curr->isEndOfWord) return false;
            for (int i = 0; i < 26; ++i) {
                if (curr->children[i]) return false;
            }
            return true;
        }
        return false;
    }
    ```

### Q2: What if we need to support Unicode / UTF-8 characters instead of lowercase English?
*   **Answer**: Storing a 65,536-size pointer array per node for full Unicode support is prohibitively expensive.
    *   **Alternative 1 - Hash Map**: Change `std::unique_ptr<TrieNode> children[26]` to `std::unordered_map<char32_t, std::unique_ptr<TrieNode>>`. This saves space for sparse nodes but incurs hash overhead.
    *   **Alternative 2 - Sorted Vector**: Use `std::vector<std::pair<char32_t, std::unique_ptr<TrieNode>>>` and perform binary search (`std::lower_bound`) to find the matching character. This maintains memory density and CPU cache alignment.

### Q3: How do you design a thread-safe Trie for parallel search and insert?
*   **Answer**:
    *   **Fine-Grained Locking (Hand-over-Hand)**: Instead of locking the entire Trie, place a read-write lock (`std::shared_mutex`) on each individual `TrieNode`. Read traversals acquire shared locks as they move down the tree and release them immediately (hand-over-hand). Write operations acquire exclusive locks only when allocating a new child node.
    *   **Lock-Free Trie**: Use atomic pointer operations (`std::atomic<TrieNode*>`) and Compare-And-Swap (CAS) loops when inserting a new child node to avoid locking overhead entirely.

---

## Pro-Tip: How to Impress the Interviewer

*   **Highlight the Nested Destructor Stack Overflow Vulnerability**: Mention that if a Trie contains long paths (e.g., 2000 nodes deep) and we delete the root node, the recursive destruction of nested `std::unique_ptr`s can exceed the OS stack frame limit, causing a **Stack Overflow on Deallocation**. Discuss how this can be resolved by writing a custom, iterative destructor that deletes nodes bottom-up or level-by-level using a queue.
*   **Prevent Out-of-Bounds Indices**: Point out that doing `ch - 'a'` without verifying that `ch` is within the range `['a', 'z']` is a dangerous security vulnerability (e.g., inputting `'A'` or `'-'` results in negative indices, corrupting heap memory).
*   **Compare Smart Pointers in Tree Structures**: Highlight why `std::unique_ptr` is the optimal choice for tree structures: it is a **zero-cost abstraction** that matches exclusive parent-child ownership. Contrast this with `std::shared_ptr`, which carries atomic reference-counting overhead and introduces cache-line bouncing (due to atomic write instructions to the control block) under multi-threaded read environments.
