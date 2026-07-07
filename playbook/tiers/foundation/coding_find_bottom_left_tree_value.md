# Find Bottom Left Tree Value

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 513, Glassdoor
- **Flashcards**: [BFS deck](../../flash_cards/coding/bfs.md)

---

## Question Description

Given the `root` of a binary tree, return the leftmost value in the last row of the tree.

### Examples
*   **Input**: `root = [2,1,3]`
    *   **Output**: `1`
*   **Input**: `root = [1,2,3,4,null,5,6,null,null,7]`
    *   **Output**: `7`

---

## Detailed Solution (C++)

While standard BFS level-by-level traversal works, a highly optimized approach is to perform a **Right-to-Left BFS**.

If we traverse the tree level by level starting from the **right** instead of the left (i.e., we push the `right` child before the `left` child to the queue), then the last node popped from the queue is guaranteed to be the leftmost node of the deepest level. This elegant trick simplifies the logic to a single loop, eliminating the need to track level sizes.

### Standard C++ Production Code

```cpp
#include <queue>

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
    int findBottomLeftValue(TreeNode* root) {
        // Guaranteed that root is not null by LeetCode constraints (1 <= nodes <= 10^4)
        std::queue<TreeNode*> q;
        q.push(root);
        TreeNode* node = nullptr;

        while (!q.empty()) {
            node = q.front();
            q.pop();

            // Push right child first, then left child.
            // This ensures that the left-most node of the lowest level is popped last.
            if (node->right) {
                q.push(node->right);
            }
            if (node->left) {
                q.push(node->left);
            }
        }

        return node->val;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the recursive/iterative Python implementation of the Right-to-Left BFS.

```python
from typing import Optional
from collections import deque

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def findBottomLeftValue(self, root: TreeNode) -> int:
        """
        Finds the leftmost value in the last row of the tree.
        Uses a right-to-left BFS traversal. The last popped node is the answer.
        
        Time Complexity: O(N)
        Space Complexity: O(W) where W is the maximum width of the tree
        """
        # Root is guaranteed to be non-null
        queue = deque([root])
        node = root

        while queue:
            node = queue.popleft()
            
            # Queue right first, then left.
            if node.right:
                queue.append(node.right)
            if node.left:
                queue.append(node.left)

        return node.val
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. BFS vs. DFS Recursion Stack Limit
*   A DFS implementation uses the Python call stack, which has a default recursion limit of $1000$. If the tree is highly skewed (e.g., $10^4$ nodes aligned in a single line), a DFS solution will raise a `RecursionError`.
*   The BFS solution runs iteratively and does not create call stack frames. The space is allocated on the heap inside `collections.deque`, which is bounded only by the machine's physical memory.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | Every node in the binary tree is visited exactly once. |
| **Space Complexity** | $\mathcal{O}(w)$ | The queue holds at most $\mathcal{O}(w)$ elements, where $w$ is the maximum width of the tree. In the worst-case of a complete binary tree, $w \approx n/2$. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How can you implement this using DFS?
*   **The Approach**: Use a pre-order traversal (which visits the left child before the right child). Keep track of both the maximum depth seen so far (`max_depth`) and the value of the leftmost node at that depth. Because we traverse left-to-right, the first node encountered at any new depth is guaranteed to be the leftmost node for that depth level.
*   **Python Code**:
    ```python
    def findBottomLeftValueDFS(root: TreeNode) -> int:
        max_depth = -1
        leftmost_val = root.val
        
        def dfs(node: Optional[TreeNode], depth: int):
            nonlocal max_depth, leftmost_val
            if not node:
                return
            
            if depth > max_depth:
                max_depth = depth
                leftmost_val = node.val
                
            dfs(node.left, depth + 1)
            dfs(node.right, depth + 1)
            
        dfs(root, 0)
        return leftmost_val
    ```

### Q2: Which is better, BFS or DFS, for a very wide tree vs. a very deep tree?
*   **Wide Tree (large width $w$, small height $h$)**: DFS is superior because DFS space complexity is $\mathcal{O}(h)$ (small stack), while BFS space complexity is $\mathcal{O}(w)$ (large queue).
*   **Deep Tree (small width $w$, large height $h$)**: BFS is superior because BFS space complexity is $\mathcal{O}(w)$ (small queue) and avoids stack overflow risks, while DFS space complexity is $\mathcal{O}(h)$ (large stack).

---

## Pro-Tip: How to Impress the Interviewer

*   **Offer Right-to-Left BFS Immediately**: Many candidates implement standard level-by-level BFS because they memorize it. Proposing the Right-to-Left BFS immediately signals a deep, intuitive understanding of queue ordering properties rather than simple rote memorization.
*   **Explain the Queue Invariant**: Explain *why* the Right-to-Left BFS works: "At any point in a BFS queue, the elements represent at most two adjacent levels, sorted from right to left. Therefore, the very last element in the queue must be the leftmost node of the deepest level."
