# Implement Trie (Prefix Tree)

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 208, Glassdoor
- **Flashcards**: [Trie deck](../../flash_cards/coding/trie.md)

---

## Question Description

A **trie** (pronounced as "try") or **prefix tree** is a tree data structure used to efficiently store and retrieve keys in a dataset of strings. There are various applications of this data structure, such as autocomplete, spellcheckers, and IP routing tables.

Implement the `Trie` class:

*   `Trie()` Initializes the trie object.
*   `void insert(String word)` Inserts the string `word` into the trie.
*   `boolean search(String word)` Returns `true` if the string `word` is in the trie (i.e., was inserted before), and `false` otherwise.
*   `boolean startsWith(String prefix)` Returns `true` if there is a previously inserted string `word` that has the prefix `prefix`, and `false` otherwise.

### Examples

*   **Input**:
    ```json
    ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
    [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
    ```
*   **Output**:
    ```json
    [null, null, true, false, true, null, true]
    ```
*   **Explanation**:
    ```cpp
    Trie trie;
    trie.insert("apple");
    trie.search("apple");   // returns true
    trie.search("app");     // returns false
    trie.startsWith("app"); // returns true
    trie.insert("app");
    trie.search("app");     // returns true
    ```

### Constraints
*   $1 \le \text{word.length}, \text{prefix.length} \le 2000$
*   `word` and `prefix` consist only of lowercase English letters.
*   At most $3 \times 10^4$ calls in total will be made to `insert`, `search`, and `startsWith`.

---

## Detailed Solution (C++)

For lowercase English letters, using an array of 26 pointers (`TrieNode* children[26]`) is far more efficient than `std::unordered_map`. It avoids hash collision overhead, eliminates map metadata memory, and guarantees $\mathcal{O}(1)$ child lookup using simple pointer arithmetic.

We must also ensure proper memory management in C++ by implementing the **Rule of Five** (handling or deleting copy operations) to prevent double-free vulnerabilities when a `Trie` is copied.

### Standard C++ Production Code

```cpp
#include <string>
#include <string_view>
#include <utility>

class Trie {
private:
    struct TrieNode {
        TrieNode* children[26] = {nullptr};
        bool is_end = false;

        // Recursive destructor cleanly deallocates the entire trie tree
        ~TrieNode() {
            for (TrieNode* child : children) {
                delete child;
            }
        }
    };

    TrieNode* root;

    // Helper method to traverse the Trie and locate a prefix
    TrieNode* find(std::string_view prefix) const noexcept {
        TrieNode* cur = root;
        for (char ch : prefix) {
            int idx = ch - 'a';
            if (!cur->children[idx]) {
                return nullptr;
            }
            cur = cur->children[idx];
        }
        return cur;
    }

public:
    Trie() : root(new TrieNode()) {}

    ~Trie() {
        delete root;
    }

    // Disable copy semantics to prevent shallow-copy double-free issues
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;

    // Enable move semantics for transfer of ownership
    Trie(Trie&& other) noexcept : root(other.root) {
        other.root = nullptr;
    }

    Trie& operator=(Trie&& other) noexcept {
        if (this != &other) {
            delete root;
            root = other.root;
            other.root = nullptr;
        }
        return *this;
    }

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

    bool search(const std::string& word) const noexcept {
        const TrieNode* node = find(word);
        return node != nullptr && node->is_end;
    }

    bool startsWith(const std::string& prefix) const noexcept {
        return find(prefix) != nullptr;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation. It uses a Python `dict` for child lookups. To minimize memory, `__slots__` is declared on the `TrieNode` class.

```python
from typing import Optional

class TrieNode:
    # Use __slots__ to eliminate dynamic instance dictionary overhead
    __slots__ = ("children", "is_end")
    
    def __init__(self) -> None:
        self.children: dict[str, TrieNode] = {}
        self.is_end: bool = False

class Trie:
    def __init__(self) -> None:
        self.root = TrieNode()

    def insert(self, word: str) -> None:
        """
        Inserts a word into the trie.
        Time Complexity: O(L) where L is word length
        Space Complexity: O(L) in the worst case (new nodes created)
        """
        node = self.root
        for ch in word:
            if ch not in node.children:
                node.children[ch] = TrieNode()
            node = node.children[ch]
        node.is_end = True

    def search(self, word: str) -> bool:
        """
        Returns true if the word is in the trie.
        Time Complexity: O(L) where L is word length
        """
        node = self._find(word)
        return node is not None and node.is_end

    def startsWith(self, prefix: str) -> bool:
        """
        Returns true if there is any word in the trie that starts with the given prefix.
        Time Complexity: O(P) where P is prefix length
        """
        return self._find(prefix) is not None

    def _find(self, prefix: str) -> Optional[TrieNode]:
        """
        Helper method to search for a node matching a prefix.
        """
        node = self.root
        for ch in prefix:
            if ch not in node.children:
                return None
            node = node.children[ch]
        return node
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. The Power of `__slots__`
*   In Python, standard class instances store their attributes in a dynamic dictionary (`__dict__`). This incurs significant memory overhead (at least $104$ bytes per dictionary + pointer overhead).
*   A Trie typically contains thousands or millions of nodes. By defining `__slots__ = ("children", "is_end")` on `TrieNode`, we instruct Python to allocate space only for the declared references, decreasing the memory footprint of the trie by **up to 70%**.

### 2. Hash Map vs Fixed-Size List
*   Python's `dict` uses a highly optimized hash map internally. For $26$ elements, it is extremely fast and space-efficient because it only stores keys that actually exist.
*   In contrast, allocating a list of size 26 (`[None] * 26`) for every single node allocates 26 references upfront, which is memory-wasteful for sparse trees where nodes have low out-degrees.

### 3. Reusing Prefix Lookup Logic
*   Avoid duplicating the traversal loop in `search` and `startsWith`. Writing a helper `_find(prefix)` returns the exact node where the prefix ends, letting `search` simply inspect `.is_end` and `startsWith` check if the returned node is not `None`.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity (insert)** | $\mathcal{O}(L)$ | $L$ is the length of the word; we traverse or create at most $L$ nodes. |
| **Time Complexity (search)** | $\mathcal{O}(L)$ | $L$ is the length of the word; we trace the path in the trie. |
| **Time Complexity (startsWith)**| $\mathcal{O}(P)$ | $P$ is the length of the prefix. |
| **Space Complexity** | $\mathcal{O}(N \cdot L)$ | $N$ is the number of words, $L$ is the average length. Words with common prefixes share nodes, saving space. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How would you make this Trie thread-safe?
*   **The Problem**: Multiple threads inserting and searching concurrently can lead to race conditions (e.g., two threads inserting different words sharing the same prefix may overwrite each other's child nodes).
*   **The Solution**: 
    1.  **Coarse-grained Mutex**: Lock the entire Trie for write operations. This severely limits throughput under write-heavy workloads.
    2.  **Read-Write Mutex (`std::shared_mutex`)**: Allows concurrent reads (`search`, `startsWith`) but exclusive locks for writes (`insert`).
    3.  **Fine-grained Node Locking**: Put a mutex on each individual `TrieNode`. A thread only locks the child pointer array when modifying a specific node.
    4.  **Lock-Free Trie**: Implement using atomic pointer checks (`std::atomic<TrieNode*>`). When a thread wants to initialize a null child node, it uses a Compare-And-Swap (`compare_exchange_weak`) operation. If another thread beat it to initialization, it deletes its local allocation and uses the existing node.

### Q2: What if we want to store Unicode characters (e.g. UTF-8)?
*   **The Problem**: A raw array of size 26 is limited to ASCII lowercase English. Unicode characters have a vast space (over $1.1$ million code points).
*   **The Solution**: Change the node's representation of children.
    *   **Hash Map**: Use `std::unordered_map<char32_t, TrieNode*>` in C++ or standard `dict` in Python.
    *   **Ternary Search Tree (TST)**: Instead of multi-way nodes, each node contains a single character and three pointers (left, middle, right), balancing binary search tree lookup with Trie prefix sharing.

---

## Pro-Tip: How to Impress the Interviewer

*   **Highlight RAII and the Rule of Five**: In C++, explain how a custom recursive destructor in the node (`~TrieNode`) automatically handles the deletion of the entire sub-tree when the parent `Trie` goes out of scope. Explicitly deleting copy operations prevents double-frees.
*   **Discuss Memory Fragmentation & Cache Locality**: A standard pointer-based Trie is notorious for **cache misses** because each node is allocated dynamically on the heap (`new`), spreading them across arbitrary memory locations. Point out that allocating nodes contiguously inside a single `std::vector<TrieNode>` block (using indices instead of raw pointers) dramatically improves CPU cache hits.
