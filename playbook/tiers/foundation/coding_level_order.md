# Binary Tree Level Order Traversal

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 102, Glassdoor
- **Flashcards**: [BFS deck](../../flash_cards/coding/bfs.md)

---

## Question Description

Given the `root` of a binary tree, return the level order traversal of its nodes' values (i.e., from left to right, level by level).

### Examples
*   **Input**: `root = [3,9,20,null,null,15,7]`
    *   **Output**: `[[3],[9,20],[15,7]]`
*   **Input**: `root = [1]`
    *   **Output**: `[[1]]`
*   **Input**: `root = []`
    *   **Output**: `[]`

---

## Detailed Solution (C++)

The core algorithm uses **Breadth-First Search (BFS)** with a queue. To separate the tree nodes level-by-level, we capture the queue's size at the beginning of each level iteration (`level_size`). This allows us to process exactly that number of nodes for the current level before moving to the next.

### Standard C++ Production Code

```cpp
#include <vector>
#include <queue>
#include <cstddef>
#include <utility>

// Definition for a binary tree node.
#ifdef LOCAL_TESTING
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
#endif

class Solution {
public:
    std::vector<std::vector<int>> levelOrder(TreeNode* root) {
        std::vector<std::vector<int>> result;
        if (!root) {
            return result;
        }

        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int level_size = static_cast<int>(q.size());
            std::vector<int> level;
            level.reserve(level_size); // Pre-allocate memory to avoid reallocations

            for (int i = 0; i < level_size; ++i) {
                TreeNode* node = q.front();
                q.pop();

                level.push_back(node->val);

                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
            result.push_back(std::move(level)); // Optimize via move semantics
        }

        return result;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the iterative BFS implementation utilizing `collections.deque` for efficient queue operations.

```python
from typing import List, Optional
from collections import deque

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        """
        Performs a level-order traversal (BFS) of a binary tree.
        
        Time Complexity: O(N)
        Space Complexity: O(N)
        """
        if not root:
            return []

        result: List[List[int]] = []
        queue = deque([root])

        while queue:
            level_size = len(queue)
            level = []
            
            for _ in range(level_size):
                node = queue.popleft()
                level.append(node.val)
                
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
            
            result.append(level)

        return result
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Deque vs. List for Queue Operations
*   In Python, using a standard `list` as a queue (e.g., `list.pop(0)`) is an $\mathcal{O}(n)$ operation because all subsequent elements must be shifted left in contiguous memory.
*   Always use `collections.deque` (double-ended queue) which provides $\mathcal{O}(1)$ time complexity for both `append()` and `popleft()`. It is implemented as a doubly-linked list of fixed-size blocks, maximizing memory locality while avoiding shifts.

### 2. Generator/Yield Pattern
*   For massive tree structures, instead of accumulating the full list in memory, we can yield levels lazily using Python generators:
    ```python
    def levelOrderGenerator(self, root: Optional[TreeNode]):
        if not root:
            return
        queue = deque([root])
        while queue:
            level_size = len(queue)
            yield [queue[i].val for i in range(level_size)]
            for _ in range(level_size):
                node = queue.popleft()
                if node.left: queue.append(node.left)
                if node.right: queue.append(node.right)
    ```
    This reduces the active memory footprint if the consumer only processes one level at a time.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | Every node is visited and queued exactly once. |
| **Space Complexity** | $\mathcal{O}(n)$ | The maximum space is occupied by the queue at the deepest level (leaf level), which can contain up to $\lceil n/2 \rceil$ nodes for a full binary tree. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How can you implement level-order traversal using DFS?
*   **The Approach**: We can perform standard pre-order DFS and pass a depth parameter. We maintain a list of lists. If the current `depth` equals the size of the result list, we create a new sublist. We then append the node's value to the sublist corresponding to the current depth.
*   **Python Code**:
    ```python
    def levelOrderDFS(root: Optional[TreeNode]) -> List[List[int]]:
        res = []
        def dfs(node: Optional[TreeNode], depth: int):
            if not node:
                return
            if depth == len(res):
                res.append([])
            res[depth].append(node.val)
            dfs(node.left, depth + 1)
            dfs(node.right, depth + 1)
        dfs(root, 0)
        return res
    ```
*   **Trade-off**: Time complexity remains $\mathcal{O}(n)$. Auxiliary space complexity drops to $\mathcal{O}(h)$ where $h$ is the tree height (call stack size), which is better than BFS for balanced trees ($\mathcal{O}(\log n)$ vs $\mathcal{O}(n)$), but worse for extremely skewed trees ($\mathcal{O}(n)$).

### Q2: How can we implement BFS without the memory allocation overhead of `std::queue` in C++?
*   **The Approach**: We can use two flat vectors representing the `current_level` and the `next_level`. 
*   **Code Example**:
    ```cpp
    std::vector<std::vector<int>> levelOrderFlat(TreeNode* root) {
        std::vector<std::vector<int>> res;
        if (!root) return res;
        std::vector<TreeNode*> cur = {root};
        while (!cur.empty()) {
            std::vector<int> level_vals;
            std::vector<TreeNode*> next_level;
            level_vals.reserve(cur.size());
            for (TreeNode* node : cur) {
                level_vals.push_back(node->val);
                if (node->left) next_level.push_back(node->left);
                if (node->right) next_level.push_back(node->right);
            }
            res.push_back(std::move(level_vals));
            cur = std::move(next_level);
        }
        return res;
    }
    ```
*   **Benefits**: Avoids the dynamic node allocation overhead of standard queue/deque, resulting in contiguity and superior cache prefetching.

---

## Pro-Tip: How to Impress the Interviewer

*   **Move Semantics**: In C++, explain how `std::move(level)` transfers ownership of the vector's internal memory buffer to `result` instead of performing a deep copy. This ensures $\mathcal{O}(1)$ transfer complexity.
*   **Contiguous Double-Buffering**: Mention that you are aware of hardware prefetching and CPU L1/L2 cache lines. A standard `std::queue` (which relies on `std::deque` allocations in chunks) has worse cache hit rates than a flat double-buffer vector approach because vectors guarantee contiguous memory layout.
*   **Pre-sizing Vectors**: Explicitly calling `level.reserve(level_size)` prevents the dynamic array reallocation pattern (typically doubling capacity: 1, 2, 4, 8, 16...) which can trigger multiple memory copy passes.
