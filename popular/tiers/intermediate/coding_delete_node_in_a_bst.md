# Delete Node in a BST

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / QA & Test Engineer
- **Source**: LeetCode 450, Glassdoor
- **Flashcards**: [DFS deck](../../flash_cards/coding/dfs.md)

---

## Question Description

Given the root of a Binary Search Tree (BST) and a `key`, delete the node with the given `key` in the BST. Return the root node reference (possibly updated) of the BST.

Basically, the deletion can be divided into two stages:
1. Search for a node to remove.
2. If the node is found, delete the node.

### Examples
*   **Input**: `root = [5,3,6,2,4,null,7]`, `key = 3`
    *   **Output**: `[5,4,6,2,null,null,7]` (or `[5,2,6,null,4,null,7]`)
    *   **Explanation**: 
        The node to be deleted is `3`. Valid BSTs after deletion are:
        ```text
              5                      5
             / \                    / \
            4   6        or        2   6
           /     \                  \   \
          2       7                  4   7
        ```
*   **Input**: `root = [5,3,6,2,4,null,7]`, `key = 0`
    *   **Output**: `[5,3,6,2,4,null,7]`
    *   **Explanation**: The key `0` is not present in the BST, so the tree is returned unchanged.
*   **Input**: `root = []`, `key = 0`
    *   **Output**: `[]`

---

## Detailed Solution (C++)

To delete a node from a Binary Search Tree, we recursively locate the node:
*   If `key < root->val`, search in the left subtree.
*   If `key > root->val`, search in the right subtree.
*   If `key == root->val`, we handle three cases:
    1.  **No children**: Return `nullptr` and delete the node.
    2.  **One child**: Return the non-null child and delete the current node to free heap memory.
    3.  **Two children**: Find the **inorder successor** (the minimum node in the right subtree), copy its value to the current node, and recursively delete the successor from the right subtree.

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
public:
    TreeNode* deleteNode(TreeNode* root, int key) noexcept {
        if (!root) {
            return nullptr;
        }

        // Locate the target node
        if (key < root->val) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->val) {
            root->right = deleteNode(root->right, key);
        } else {
            // Target node found
            
            // Case 1 & 2: Node has 0 or 1 child
            if (!root->left) {
                TreeNode* temp = root->right;
                delete root; // Avoid memory leaks on the heap
                return temp;
            }
            if (!root->right) {
                TreeNode* temp = root->left;
                delete root; // Avoid memory leaks on the heap
                return temp;
            }

            // Case 3: Node has 2 children
            // Find the inorder successor (leftmost leaf in the right subtree)
            TreeNode* min_node = root->right;
            while (min_node->left) {
                min_node = min_node->left;
            }

            // Copy the successor's value to current node
            root->val = min_node->val;

            // Delete the successor recursively
            root->right = deleteNode(root->right, min_node->val);
        }
        return root;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the standard recursive Python implementation. Python does not require manual memory deallocation since its garbage collector uses reference counting.

```python
from typing import Optional

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def deleteNode(self, root: Optional[TreeNode], key: int) -> Optional[TreeNode]:
        """
        Deletes a node with the given key from a BST and returns the updated root.
        
        Time Complexity: O(H) where H is the height of the tree.
        Space Complexity: O(H) call stack space.
        """
        if not root:
            return None

        # 1. Search for the node
        if key < root.val:
            root.left = self.deleteNode(root.left, key)
        elif key > root.val:
            root.right = self.deleteNode(root.right, key)
        else:
            # 2. Node found: handle deletions
            
            # Case 1: Left child is missing (handles 0 or 1 child)
            if not root.left:
                return root.right
            
            # Case 2: Right child is missing (handles 1 child)
            if not root.right:
                return root.left

            # Case 3: Two children
            # Find the inorder successor (leftmost node of right subtree)
            min_node = root.right
            while min_node.left:
                min_node = min_node.left
            
            # Swap values
            root.val = min_node.val
            
            # Delete successor node
            root.right = self.deleteNode(root.right, min_node.val)

        return root
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Recursion Stack Limit
*   For an unbalanced, skewed BST (essentially a linked list), the height $H$ can equal $N$. The call stack can grow up to $10^4$ frames (which exceeds Python's default stack limit of $1000$).
*   **Workaround**: An iterative deletion can be written to perform searching and pointer updating in $\mathcal{O}(1)$ space.

### 2. TreeNode Identity vs Value Swaps
*   In Python, swapping values (`root.val = min_node.val`) is simple. However, if other objects hold references to the specific `TreeNode` instances, swapping values can cause stale references or data consistency issues.
*   In production, structural modifications (rewiring the parent pointers to the successor node object) are preferred.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(h)$ | Where $h$ is the height of the tree. For balanced trees, $h = \log n$. For skewed trees, $h = n$. |
| **Space Complexity** | $\mathcal{O}(h)$ | Call stack depth is proportional to the tree height. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Can we delete a node without copying/swapping values? (Structural Deletion)
*   **Answer**: Yes, we can delete the node by altering parent and child pointers. If the node has two children, we can hook the left subtree of the deleted node to the leftmost leaf of its right subtree, and then return the right subtree.
*   **C++ Structural Example**:
    ```cpp
    TreeNode* deleteNodeStructural(TreeNode* root, int key) {
        if (!root) return nullptr;
        if (key < root->val) {
            root->left = deleteNodeStructural(root->left, key);
        } else if (key > root->val) {
            root->right = deleteNodeStructural(root->right, key);
        } else {
            if (!root->left) { TreeNode* r = root->right; delete root; return r; }
            if (!root->right) { TreeNode* l = root->left; delete root; return l; }
            
            TreeNode* successor = root->right;
            while (successor->left) {
                successor = successor->left;
            }
            successor->left = root->left; // hook left child
            TreeNode* new_root = root->right;
            delete root;
            return new_root;
        }
        return root;
    }
    ```

### Q2: How can we implement this iteratively in $\mathcal{O}(1)$ space?
*   **Answer**: We can keep track of the `parent` and `curr` node. Once the node is found, we swap it with the successor and delete the successor by updating parent's pointers, all within a single loop without recursion.

---

## Pro-Tip: How to Impress the Interviewer

*   **Highlight C++ Memory Leaks**: Always point out that in languages without garbage collection (C++), simply returning a child pointer like `return root->right;` without calling `delete root;` creates a memory leak. Pointing this out and cleaning up memory dynamically demonstrates low-level systems discipline.
*   **Discuss Succesor vs Predecessor**: Mention that we can use either the inorder successor (minimum of the right subtree) or the inorder predecessor (maximum of the left subtree). Explain that choosing randomly between successor and predecessor can help keep the BST more balanced in systems with heavy write/delete workloads.
