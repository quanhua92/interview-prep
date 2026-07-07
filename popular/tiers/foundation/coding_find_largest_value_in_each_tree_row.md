# Find Largest Value in Each Tree Row

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 515, Glassdoor
- **Flashcards**: [BFS deck](../../flash_cards/coding/bfs.md)

---

## Question Description

Given the `root` of a binary tree, return an array of the largest value in each row of the tree (0-indexed).

### Examples
*   **Input**: `root = [1,3,2,5,3,null,9]`
    *   **Output**: `[1,3,9]`
*   **Input**: `root = [1,2,3]`
    *   **Output**: `[1,3]`

---

## Detailed Solution (C++)

The standard solution uses **Breadth-First Search (BFS)**. We traverse the tree level by level. For each level, we find the maximum node value by iterating through the current queue elements, and then push its children to the queue for the next level.

### Standard C++ Production Code

```cpp
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

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
    std::vector<int> largestValues(TreeNode* root) {
        std::vector<int> result;
        if (!root) {
            return result;
        }

        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int level_size = static_cast<int>(q.size());
            int max_val = INT_MIN; // Initialize with the lowest possible signed 32-bit integer

            for (int i = 0; i < level_size; ++i) {
                TreeNode* node = q.front();
                q.pop();

                max_val = std::max(max_val, node->val);

                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
            result.push_back(max_val);
        }

        return result;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation using `collections.deque`.

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
    def largestValues(self, root: Optional[TreeNode]) -> List[int]:
        """
        Finds the largest value in each row of a binary tree.
        Uses BFS to process the tree level by level.
        
        Time Complexity: O(N)
        Space Complexity: O(N)
        """
        if not root:
            return []

        result: List[int] = []
        queue = deque([root])

        while queue:
            level_size = len(queue)
            max_val = float('-inf')

            for _ in range(level_size):
                node = queue.popleft()
                
                # Check for new max value
                if node.val > max_val:
                    max_val = node.val
                
                # Push children
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
            
            result.append(max_val)

        return result
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Initializing Negative Infinity in Python
*   In Python, do not use a hardcoded value like `-999999` to initialize a minimum value checker. 
*   Use `float('-inf')`, which is mathematically guaranteed to be smaller than any numeric value. Alternatively, initialize `max_val` with the first element of the level: `max_val = queue[0].val`.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | Every node is visited exactly once. |
| **Space Complexity** | $\mathcal{O}(n)$ | The queue size peaks at the tree's maximum width $w$, which is at most $\lceil n/2 \rceil$ nodes (for a full binary tree). |

---

## Common Follow-Up Questions & How to Answer

### Q1: How can you implement this using DFS?
*   **The Approach**: We can perform a preorder DFS traversal while tracking the current level `depth`. If the depth is equal to the size of the results list, it means this is our first time reaching this row, so we append the current node's value. Otherwise, we update the existing value at index `depth` with the maximum of its current value and the new node's value.
*   **Python Code**:
    ```python
    def largestValuesDFS(root: Optional[TreeNode]) -> List[int]:
        result = []
        
        def dfs(node: Optional[TreeNode], depth: int):
            if not node:
                return
            
            if depth == len(result):
                result.append(node.val)
            else:
                result[depth] = max(result[depth], node.val)
                
            dfs(node.left, depth + 1)
            dfs(node.right, depth + 1)
            
        dfs(root, 0)
        return result
    ```
*   **Complexity**: Time complexity is $\mathcal{O}(n)$. Space complexity is $\mathcal{O}(h)$ (height of the tree, due to recursion stack frames). This makes DFS more space-efficient for balanced trees.

### Q2: How can we implement this without using `std::max` in C++ for branchless optimization?
*   **The Approach**: We can use ternary operators, which compilers optimize into branchless conditional moves (`CMOV`).
*   **C++ Snippet**:
    ```cpp
    max_val = (node->val > max_val) ? node->val : max_val;
    ```

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention INT_MIN Bound Safety**: Point out that you initialized the maximum checker with `INT_MIN` in C++ and `float('-inf')` in Python because binary tree node values can legally be negative (down to $-2^{31}$). Using `0` as an initial value would fail on trees consisting entirely of negative numbers.
*   **Double-Buffering for High Performance**: Discuss that for real-time systems, avoiding dynamic memory allocations inside the `while` loop is crucial. Instead of standard `std::queue`, using two pre-allocated vectors (`std::vector<TreeNode*>`) and swapping them eliminates heap allocations during traversal.
