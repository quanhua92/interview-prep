# Subtree of Another Tree

- **Category**: Coding
- **Difficulty**: Easy
- **Target Role**: Software Engineer / QA & Test Engineer
- **Source**: LeetCode 572, Glassdoor
- **Flashcards**: [DFS deck](../../flash_cards/coding/dfs.md)

---

## Question Description

Given the roots of two binary trees `root` and `subRoot`, return `true` if there is a subtree of `root` with the same structure and node values of `subRoot` and `false` otherwise.

A subtree of a binary tree `tree` is a tree that consists of a node in `tree` and all of this node's descendants. The tree `tree` could also be considered as a subtree of itself.

### Examples
*   **Input**: `root = [3,4,5,1,2]`, `subRoot = [4,1,2]`
    *   **Output**: `true`
    *   **Explanation**: 
        The subtree rooted at node `4` in `root` is identical to `subRoot` in both structure and values.
*   **Input**: `root = [3,4,5,1,2,null,null,null,null,0]`, `subRoot = [4,1,2]`
    *   **Output**: `false`
    *   **Explanation**: 
        The subtree rooted at node `4` in `root` contains a node `0` as a child of `2`, which does not exist in `subRoot`. Hence, they are not identical.

---

## Detailed Solution (C++)

The standard solution uses double recursion:
1. `isSubtree(root, subRoot)`: Checks if the current subtree starting at `root` is matching `subRoot`, or recursively checks if `subRoot` is a subtree of `root->left` or `root->right`.
2. `isSame(a, b)`: Helper function to determine if two binary trees are identical by checking if their values are equal and recursively matching their left and right subtrees.

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
    bool isSame(TreeNode* a, TreeNode* b) noexcept {
        if (!a && !b) {
            return true;
        }
        if (!a || !b) {
            return false;
        }
        return (a->val == b->val) && 
               isSame(a->left, b->left) && 
               isSame(a->right, b->right);
    }

public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) noexcept {
        if (!subRoot) {
            return true; // An empty tree is always a subtree
        }
        if (!root) {
            return false; // A non-empty subRoot cannot be a subtree of an empty root
        }
        
        // Check if the current tree matches or recurse into child nodes
        if (isSame(root, subRoot)) {
            return true;
        }
        
        return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the recursive Python implementation using helper functions.

```python
from typing import Optional

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def isSubtree(self, root: Optional[TreeNode], subRoot: Optional[TreeNode]) -> bool:
        """
        Determines if subRoot is a subtree of root.
        
        Time Complexity: O(N * M) in the worst case, where N is the size of root and M of subRoot.
        Space Complexity: O(H) recursion stack space where H is the height of root.
        """
        if not subRoot:
            return True
        if not root:
            return False
            
        if self.isSame(root, subRoot):
            return True
            
        return self.isSubtree(root.left, subRoot) or self.isSubtree(root.right, subRoot)

    def isSame(self, a: Optional[TreeNode], b: Optional[TreeNode]) -> bool:
        if not a and not b:
            return True
        if not a or not b:
            return False
        return (a.val == b.val) and self.isSame(a.left, b.left) and self.isSame(a.right, b.right)
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Object Identity vs Value Equivalence
*   In Python, comparing references (`a is b`) is $\mathcal{O}(1)$ and checks if both variables point to the exact same memory address. 
*   However, tree nodes might have identical values and structure but different memory addresses. Always compare values (`a.val == b.val`) and structures recursively instead of relying on identity operators.

### 2. Tail Recursion Limitation
*   Python does not perform tail-call optimization (TCO). A deeply skewed binary tree of depth $2000$ will crash Python due to `RecursionError` (limit $1000$).
*   If working with extremely large skewed trees, rewrite the outer tree traversal iteratively (using BFS or iterative DFS with a queue/stack) while keeping `isSame` recursive.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n \times m)$ | In the worst case, we run `isSame` (which takes $\mathcal{O}(m)$) for every node in the primary tree. |
| **Space Complexity** | $\mathcal{O}(h)$ | Where $h$ is the height of the primary tree. In the worst case (skewed tree), $h = n$. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How can we solve this problem in $\mathcal{O}(n + m)$ time complexity?
*   **Answer**: We can serialize both trees into string representations (using a pre-order traversal) and run the **Knuth-Morris-Pratt (KMP)** algorithm to check if the serialized string of `subRoot` is a substring of the serialized string of `root`.
*   **Serialization Rules**:
    1.  Serialize empty children as a special character (e.g. `"#"` or `"null"`).
    2.  Use clear separators (like `","` or `"^"`) before and after each node's value. This prevents false positive matches like value `"2"` matching inside `"12"`.
*   **Serialized Preorder Representation**:
    *   `root`: `",3,4,1,#,#,2,#,#,5,#,#"`
    *   `subRoot`: `",4,1,#,#,2,#,#"`

### Q2: What is the Tree Hashing / Merkle Tree approach?
*   **Answer**: We can compute a unique hash for each node's subtree in a bottom-up traversal:
    $$\text{hash}(node) = \text{hash\_function}(node.val, \text{hash}(node.left), \text{hash}(node.right))$$
    *   Store the hash values of all subtrees in a hash set.
    *   Compute the hash of `subRoot`.
    *   Check if `subRoot`'s hash exists in our set in $\mathcal{O}(1)$ time.
    *   This yields $\mathcal{O}(n + m)$ average time complexity.

---

## Pro-Tip: How to Impress the Interviewer

*   **Avoid Substring Matching Bugs**: If you mention the serialization approach, proactively bring up the **value boundary bug** (e.g. a subtree serializing to `"2"` should not match a tree serializing to `"12"`). Explain that adding distinct boundary characters (e.g. `",2,"` and `",12,"`) ensures true syntactic uniqueness.
*   **Hash Collision Mitigation**: When describing the Merkle Tree hashing optimization, explain that hashing is prone to collisions (especially in large trees). Detail that if two hashes match, we should run `isSame` as a fallback validation to ensure correctness. This is how actual secure storage engines like Git and IPFS function.
