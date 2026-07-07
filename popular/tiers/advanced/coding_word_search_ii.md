# Word Search II

- **Category**: Coding
- **Difficulty**: Hard
- **Target Role**: Software Engineer / AI Systems Architect / QA & Test Engineer
- **Source**: LeetCode 212, Glassdoor

---

## Question Description

Given an $m \times n$ board of characters and a list of strings `words`, return *all words on the board*.

Each word must be constructed from letters of sequentially adjacent cells, where **adjacent cells** are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

### Examples

*   **Input**:
    ```json
    board = [
      ["o","a","a","n"],
      ["e","t","a","e"],
      ["i","h","k","r"],
      ["i","f","l","v"]
    ],
    words = ["oath","pea","eat","rain"]
    ```
    *   **Output**: `["eat","oath"]`
*   **Input**:
    ```json
    board = [
      ["a","b"],
      ["c","d"]
    ],
    words = ["abcb"]
    ```
    *   **Output**: `[]`

### Constraints
*   $m == \text{board.length}$
*   $n == \text{board}[i].\text{length}$
*   $1 \le m, n \le 12$
*   `board[i][j]` is a lowercase English letter.
*   $1 \le \text{words.length} \le 3 \times 10^4$
*   $1 \le \text{words}[i].\text{length} \le 10$
*   `words[i]` consists of lowercase English letters.
*   All strings in `words` are unique.

---

## Detailed Solution (C++)

Running a standard depth-first search for each word individually on the board results in $O(W \cdot M \cdot N \cdot 4^L)$ complexity (where $W$ is the number of words and $L$ is word length), which triggers a Time Limit Exceeded (TLE) error.

Instead, we can search all words simultaneously by loading them into a **Trie** and traversing the board and the Trie together.

### Essential Performance Optimizations
1.  **Store the Whole Word at the Leaf**: Instead of building the prefix character-by-character as we traverse the board, we store the full string at the terminal node (`node->word = word`). Once matched, we add it to the results and clear it to prevent duplicates.
2.  **Backtracking with In-Place Visited Marks**: We temporarily write `#` to `board[r][c]` to indicate it is visited, avoiding the overhead of allocating a separate `visited` set or grid. We restore it before backtracking.
3.  **Trie Pruning (The Game Changer)**: Once a word is found, its node is no longer needed. If a leaf node has no remaining children, we can delete it and prune the pointer in its parent node. This prevents future searches from traversing dead-ends on the board.

### Standard C++ Production Code

```cpp
#include <vector>
#include <string>
#include <array>
#include <utility>

class Solution {
private:
    struct TrieNode {
        TrieNode* children[26] = {nullptr};
        std::string word = "";

        // Recursive destructor safely cleans up all remaining children on destruction
        ~TrieNode() {
            for (TrieNode* child : children) {
                delete child;
            }
        }
    };

    int rows = 0;
    int cols = 0;
    std::vector<std::string> result;

    void dfs(std::vector<std::vector<char>>& board, int r, int c, TrieNode* parent, int idx) {
        TrieNode* curr = parent->children[idx];
        if (!curr) return;

        // Found a word
        if (!curr->word.empty()) {
            result.push_back(curr->word);
            curr->word.clear(); // Mark as found to avoid duplicate results
        }

        // Cache character and mark cell as visited
        char ch = board[r][c];
        board[r][c] = '#';

        // 4-Directional DFS
        static constexpr int dr[] = {0, 0, 1, -1};
        static constexpr int dc[] = {1, -1, 0, 0};

        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                char next_ch = board[nr][nc];
                if (next_ch != '#') {
                    dfs(board, nr, nc, curr, next_ch - 'a');
                }
            }
        }

        // Backtrack: restore character
        board[r][c] = ch;

        // Trie Pruning: If this node has no children left, prune it from parent
        bool has_children = false;
        for (const TrieNode* child : curr->children) {
            if (child) {
                has_children = true;
                break;
            }
        }

        if (!has_children) {
            delete curr; // Free memory of this branch
            parent->children[idx] = nullptr;
        }
    }

public:
    std::vector<std::string> findWords(std::vector<std::vector<char>>& board, std::vector<std::string>& words) {
        if (board.empty() || board[0].empty() || words.empty()) {
            return {};
        }

        rows = static_cast<int>(board.size());
        cols = static_cast<int>(board[0].size());
        result.clear();

        // 1. Build the Trie
        TrieNode root;
        for (const std::string& word : words) {
            TrieNode* cur = &root;
            for (char ch : word) {
                int idx = ch - 'a';
                if (!cur->children[idx]) {
                    cur->children[idx] = new TrieNode();
                }
                cur = cur->children[idx];
            }
            cur->word = word;
        }

        // 2. Search starting from each cell
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                char ch = board[r][c];
                int idx = ch - 'a';
                if (root.children[idx]) {
                    dfs(board, r, c, &root, idx);
                }
            }
        }

        return result;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the optimized Python version. It leverages dictionary key checks for fast lookups and prunes child nodes dynamically using `.pop()`.

```python
from typing import List, Optional

class TrieNode:
    __slots__ = ("children", "word")
    
    def __init__(self) -> None:
        self.children: dict[str, TrieNode] = {}
        self.word: Optional[str] = None

class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        if not board or not board[0] or not words:
            return []

        rows, cols = len(board), len(board[0])
        result: List[str] = []

        # 1. Build the Trie
        root = TrieNode()
        for word in words:
            node = root
            for ch in word:
                if ch not in node.children:
                    node.children[ch] = TrieNode()
                node = node.children[ch]
            node.word = word

        # 2. DFS Backtracking
        def dfs(r: int, c: int, parent: TrieNode, ch: str) -> None:
            curr = parent.children.get(ch)
            if not curr:
                return

            # Match found
            if curr.word is not None:
                result.append(curr.word)
                curr.word = None  # Clear to avoid duplicates

            # Mark cell as visited
            board[r][c] = "#"

            # Explore neighbors
            for dr, dc in ((0, 1), (0, -1), (1, 0), (-1, 0)):
                nr, nc = r + dr, c + dc
                if 0 <= nr < rows and 0 <= nc < cols:
                    next_ch = board[nr][nc]
                    if next_ch != "#" and next_ch in curr.children:
                        dfs(nr, nc, curr, next_ch)

            # Backtrack
            board[r][c] = ch

            # 3. Trie Pruning: Remove leaf nodes
            if not curr.children:
                parent.children.pop(ch)

        # 3. Scan the grid
        for r in range(rows):
            for c in range(cols):
                ch = board[r][c]
                if ch in root.children:
                    dfs(r, c, root, ch)

        return result
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Dynamic Garbage Collection & Pruning
*   In Python, doing `parent.children.pop(ch)` cuts off reference paths to `curr`. Since Python uses reference counting combined with a cyclic garbage collector, removing this reference automatically schedules `curr` (and any unreferenced sub-children) for garbage collection. This provides painless dynamic memory management without manual cleanup.

### 2. Eliminating Result Sorting
*   Some implementations sort the output array (`return sorted(result)`) before returning. This is a waste of CPU cycles; LeetCode accepts results in any order. For a result list containing thousands of matches, sorting adds unnecessary $\mathcal{O}(K \log K)$ overhead.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(M \cdot N \cdot 4 \cdot 3^{L-1})$ | Worst-case where we check all directions at each step. $M \times N$ is the grid size, and $L$ is the maximum word length (up to 10). In practice, Trie pruning dramatically reduces actual operations to a small fraction of the worst-case. |
| **Space Complexity** | $\mathcal{O}(K \cdot L)$ | Memory used by the Trie, where $K$ is the number of words and $L$ is the maximum word length. The stack frame depth for DFS takes $\mathcal{O}(L)$ auxiliary space. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Why not use a hash set of words and check all grid prefixes?
*   **The Problem**: Searching prefixes in a Set of strings requires doing string slice checks. To check if `oat` is a prefix of any word in a Set, we must scan the set or pre-populate it with all prefix slices.
*   **The Difference**: A Trie naturally nests common prefixes. Most importantly, a Set does not support **pruning**. If we find a word in a Set, we cannot easily mark a branch as dead and prevent future board scans from exploring it. A Trie allows immediate node deletions.

### Q2: How would you handle this problem on a massive grid (e.g. $1000 \times 1000$)?
*   **Grid Partitioning**: Divide the grid into overlapping sub-grids and search them in parallel using multiple threads.
*   **Filtering Start Coordinates**: Pre-scan the grid to index start coordinates of matching Trie root characters. If root characters are sparse, we only invoke DFS on those specific coordinates instead of visiting every single cell in a double loop.

---

## Pro-Tip: How to Impress the Interviewer

*   **Implement Trie Pruning**: Writing the pruning step (`parent.children.pop(ch)` or `delete curr`) proves you design code with performance constraints in mind. It shows you understand tree restructuring on the fly to bound search complexity.
*   **Leverage Heap Space Optimization (C++)**: Discussing `new` and `delete` allocation costs. Explain how dynamically allocating millions of tiny nodes causes memory fragmentation. Suggest pre-allocating an array of `TrieNode` structures (using a flat vector pool) to achieve contiguous memory layout, maximizing cash hits.
