# Convert BST to Greater Tree

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 538, LeetCode 1038, Glassdoor
- **Flashcards**: [DFS deck](../../flash_cards/coding/dfs.md)

---

## Question Description

Given the root of a Binary Search Tree (BST), convert it to a **Greater Tree** such that every key of the original BST is changed to the original key plus the sum of all keys greater than the original key in the BST.

Recall the properties of a Binary Search Tree:
*   The left subtree of a node contains only nodes with keys **less than** the node's key.
*   The right subtree of a node contains only nodes with keys **greater than** the node's key.
*   Both the left and right subtrees must also be binary search trees.

### Examples
*   **Input**: `root = [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]`
    *   **Output**: `[30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]`
    *   **Explanation**: 
        *   Node `8` has no nodes greater than it: $8 + 0 = 8$.
        *   Node `7` has node `8` greater than it: $7 + 8 = 15$.
        *   Node `6` has nodes `7, 8` greater than it: $6 + 15 = 21$.
        *   Node `5` has nodes `6, 7, 8` greater than it: $5 + 21 = 26$.
        *   ... and so on.
*   **Input**: `root = [0,null,1]`
    *   **Output**: `[1,null,1]`

---

## Detailed Solution (C++)

In a Binary Search Tree, an **In-order traversal** (`Left -> Root -> Right`) visits elements in ascending order.
If we reverse the traversal order to `Right -> Root -> Left`, we will visit elements in **descending order**.
As we traverse, we can keep a running sum `sum` of all nodes visited so far. For each node, we add its value to `sum` and update its value to this new `sum`.

> [!IMPORTANT]
> Avoid using global/static variables for the running sum in C++. Global variables are not thread-safe and fail in parallelized test environments. Instead, pass the running sum by reference.

### Standard C++ Production Code

```cpp
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    void reverseInorder(TreeNode* node, int& sum) noexcept {
        if (!node) {
            return;
        }

        // 1. Visit the right child (larger values)
        reverseInorder(node->right, sum);

        // 2. Process current node
        sum += node->val;
        node->val = sum;

        // 3. Visit the left child (smaller values)
        reverseInorder(node->left, sum);
    }

public:
    TreeNode* convertBST(TreeNode* root) noexcept {
        int sum = 0;
        reverseInorder(root, sum);
        return root;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the recursive Python solution using a nested helper function with the `nonlocal` keyword to manage the state of the running sum.

```python
from typing import Optional

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def convertBST(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        """
        Converts BST to Greater Sum Tree.
        
        Time Complexity: O(N)
        Space Complexity: O(H) where H is the height of the tree.
        """
        running_sum = 0

        def reverse_inorder(node: Optional[TreeNode]) -> None:
            nonlocal running_sum
            if not node:
                return

            # 1. Visit right child
            reverse_inorder(node.right)

            # 2. Update current node val
            running_sum += node.val
            node.val = running_sum

            # 3. Visit left child
            reverse_inorder(node.left)

        reverse_inorder(root)
        return root
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. The `nonlocal` Keyword
*   In Python, helper nested functions can read variables from their outer scope but cannot modify them.
*   Declaring `nonlocal running_sum` tells Python to update the binding in the enclosing scope instead of creating a new local variable `running_sum`.

### 2. Space Limit and Deep Recursion
*   If the BST is highly unbalanced (skewed like a linked list), the recursion depth reaches $N$. 
*   If $N > 1000$, Python will raise a `RecursionError`. Using an iterative approach (using a stack) solves this concern.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | Every node is visited exactly once. |
| **Space Complexity** | $\mathcal{O}(h)$ | Where $h$ is the height of the tree ($\mathcal{O}(\log n)$ for a balanced tree, $\mathcal{O}(n)$ for a skewed tree) representing the stack depth. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How can we implement this iteratively?
*   **Answer**: We can use an explicit stack to perform the reverse in-order traversal iteratively.
*   **Python Iterative Implementation**:
    ```python
    def convertBST(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        running_sum = 0
        stack = []
        curr = root
        while stack or curr:
            while curr:
                stack.append(curr)
                curr = curr.right
            curr = stack.pop()
            running_sum += curr.val
            curr.val = running_sum
            curr = curr.left
        return root
    ```

### Q2: Can we achieve $\mathcal{O}(1)$ auxiliary space complexity?
*   **Answer**: Yes, by using **Reverse Morris In-order Traversal**. This algorithm temporarily modifies the tree structure by creating threads (pointers) from predecessor nodes back to the current node, allowing traversal without stacks or recursion.
*   **C++ Morris Traversal Implementation**:
    ```cpp
    TreeNode* convertBST(TreeNode* root) {
        int sum = 0;
        TreeNode* curr = root;
        while (curr) {
            if (!curr->right) {
                sum += curr->val;
                curr->val = sum;
                curr = curr->left;
            } else {
                TreeNode* successor = curr->right;
                while (successor->left && successor->left != curr) {
                    successor = successor->left;
                }
                if (!successor->left) {
                    successor->left = curr;
                    curr = curr->right;
                } else {
                    successor->left = nullptr;
                    sum += curr->val;
                    curr->val = sum;
                    curr = curr->left;
                }
            }
        }
        return root;
    }
    ```

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain Morris Traversal Space/Time Trade-off**: Explain that while Morris traversal reduces the auxiliary space to $\mathcal{O}(1)$, it temporarily mutates the tree structure by creating cycle pointers which are later restored. This might not be suitable for multi-threaded environments where readers traverse the tree concurrently. Mentioning this concurrency hazard shows excellent production-level awareness.
*   **Design for Reentrancy**: Mention why passing the state parameter by reference is important for **reentrant** functions. If the library gets used in an event loop or a multi-threaded service, global variables would create race conditions.
