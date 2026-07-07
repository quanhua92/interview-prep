# Serialize and Deserialize BST

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 449, Glassdoor
- **Flashcards**: [BFS deck](../../flash_cards/coding/bfs.md)

---

## Question Description

Serialization is converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a **binary search tree (BST)**. There is no restriction on how your serialization/deserialization algorithm should work. You need to ensure that a binary search tree can be serialized to a string, and this string can be deserialized to the original tree structure.

The encoded string should be **as compact as possible**.

### Examples
*   **Input**: `root = [2,1,3]`
    *   **Output**: `[2,1,3]`
*   **Input**: `root = []`
    *   **Output**: `[]`

---

## Detailed Solution (C++)

A key property of a **Binary Search Tree (BST)** is that its preorder traversal carries enough structural information to uniquely reconstruct the tree *without* storing `null` pointers. This is because we can deduce where children belong using mathematical BST boundaries ($\text{lower}$ and $\text{upper}$ bounds).

This results in the most compact representation possible: a simple, space-separated string of numbers.

### Standard C++ Production Code

```cpp
#include <string>
#include <sstream>
#include <vector>
#include <climits>

// Definition for a binary tree node.
#ifdef LOCAL_TESTING
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
#endif

class Codec {
public:
    // Encodes a tree to a single string.
    std::string serialize(TreeNode* root) {
        std::string result;
        serializeHelper(root, result);
        if (!result.empty()) {
            result.pop_back(); // Remove trailing space
        }
        return result;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(std::string data) {
        if (data.empty()) {
            return nullptr;
        }

        std::vector<int> vals;
        std::stringstream ss(data);
        std::string token;
        while (ss >> token) {
            vals.push_back(std::stoi(token));
        }

        int index = 0;
        // Use LLONG_MIN/LLONG_MAX to prevent overflow boundaries
        return deserializeHelper(vals, index, LLONG_MIN, LLONG_MAX);
    }

private:
    // Helper to perform pre-order traversal
    void serializeHelper(TreeNode* root, std::string& result) {
        if (!root) {
            return;
        }
        result += std::to_string(root->val) + " ";
        serializeHelper(root->left, result);
        serializeHelper(root->right, result);
    }

    // Helper to reconstruct BST using range boundaries
    TreeNode* deserializeHelper(const std::vector<int>& vals, int& index, long long lower, long long upper) {
        if (index >= static_cast<int>(vals.size())) {
            return nullptr;
        }

        long long val = vals[index];
        // If the current value violates the BST boundaries for this subtree,
        // it belongs to a different subtree. Return nullptr.
        if (val < lower || val > upper) {
            return nullptr;
        }

        TreeNode* root = new TreeNode(static_cast<int>(val));
        index++; // Increment pointer to consume the value
        
        root->left = deserializeHelper(vals, index, lower, val);
        root->right = deserializeHelper(vals, index, val, upper);

        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// std::string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the recursive pre-order Python implementation, using a deque to efficiently consume deserialized values.

```python
from typing import Optional
from collections import deque

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Codec:
    def serialize(self, root: Optional[TreeNode]) -> str:
        """
        Encodes a BST to a single string using Pre-order traversal.
        Completely omits 'null' markers to ensure it is as compact as possible.
        
        Time Complexity: O(N)
        Space Complexity: O(N)
        """
        vals = []

        def pre_order(node: Optional[TreeNode]):
            if not node:
                return
            vals.append(str(node.val))
            pre_order(node.left)
            pre_order(node.right)

        pre_order(root)
        return " ".join(vals)

    def deserialize(self, data: str) -> Optional[TreeNode]:
        """
        Decodes your encoded data to tree.
        Implicitly discovers where 'null' pointers go using mathematical BST bounds.
        
        Time Complexity: O(N)
        Space Complexity: O(N)
        """
        if not data:
            return None

        # Convert split strings directly into a queue of integers
        queue = deque(int(x) for x in data.split())

        def build(lower: float, upper: float) -> Optional[TreeNode]:
            if not queue:
                return None

            next_val = queue[0]
            # If the next value does not fit within the BST boundaries,
            # it belongs to another sub-tree (representing a None pointer here).
            if next_val < lower or next_val > upper:
                return None

            queue.popleft() # Consume the value
            root = TreeNode(next_val)

            root.left = build(lower, next_val)
            root.right = build(next_val, upper)

            return root

        return build(float('-inf'), float('inf'))

# Your Codec object will be instantiated and called as such:
# ser = Codec()
# deser = Codec()
# tree = ser.serialize(root)
# ans = deser.deserialize(tree)
# return ans
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Handling Tree Nulls via Queue vs. Stack Indexing
*   In Python, popping elements from the left of a list takes $\mathcal{O}(n)$ time. By wrapping our list in `collections.deque`, we ensure that `popleft()` takes $\mathcal{O}(1)$ time. 
*   An alternative approach to avoid queue overhead is to pass an index integer wrapped in a list (e.g., `idx = [0]`) to maintain mutable state across recursion levels:
    ```python
    def build(lower, upper):
        if idx[0] >= len(vals): return None
        # ... logic ...
        idx[0] += 1
    ```
    Both solutions achieve $\mathcal{O}(n)$ time complexity, but the deque approach is cleaner and more idiomatic.

### 2. String Concatenation vs. List Join
*   Using `+` to concatenate strings inside recursive loops (e.g., `data += str(node.val) + " "`) creates new string instances every time, leading to an $\mathcal{O}(n^2)$ time penalty due to immutable string copying.
*   Always collect values in a `list` and use `" ".join(list)` at the end to assemble the string in $\mathcal{O}(n)$ time.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | Both serialization and deserialization visit each tree node exactly once. |
| **Space Complexity** | $\mathcal{O}(n)$ | Preorder serialization list and recursion call stack for both operations. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Can we use this exact algorithm for general binary trees?
*   **No**. A general binary tree does not satisfy the BST range property ($left < root < right$). 
*   To serialize a general binary tree, we must store structural metadata:
    1.  Include `null` markers (e.g. `1 2 null null 3`).
    2.  Provide two traversal lists (e.g., preorder + inorder, or postorder + inorder), provided all node values are guaranteed to be unique.

### Q2: How can we serialize the tree into a binary format instead of a string to save more space?
*   **The Idea**: String representation takes a variable amount of bytes per number (e.g., `12345` takes 5 bytes for ASCII + 1 byte for space). 
*   **Solution**: Write the integers as raw binary data. In C++, write the bytes of the integers directly to a char buffer:
    ```cpp
    void serializeBinary(TreeNode* root, std::string& buffer) {
        if (!root) return;
        buffer.append(reinterpret_cast<const char*>(&root->val), sizeof(root->val));
        serializeBinary(root->left, buffer);
        serializeBinary(root->right, buffer);
    }
    ```
    This guarantees exactly 4 bytes per node, eliminating string conversion overhead and space separators.

### Q3: How do we deserialize a BST using post-order serialization?
*   **The Approach**: Post-order visits nodes in the order: `left`, `right`, `root`. The root node is at the very end of the list.
*   **Solution**: We can deserialize post-order by reading the list **backward**. We parse the right child first, then the left child:
    ```python
    def deserialize(self, data: str) -> Optional[TreeNode]:
        vals = [int(x) for x in data.split()]
        def build(lower, upper):
            if not vals:
                return None
            val = vals[-1]
            if val < lower or val > upper:
                return None
            vals.pop()
            root = TreeNode(val)
            root.right = build(val, upper)
            root.left = build(lower, val)
            return root
        return build(float('-inf'), float('inf'))
    ```

---

## Pro-Tip: How to Impress the Interviewer

*   **Highlight Null Marker Optimization**: Start by noting that standard binary tree serialization requires storing `null` nodes (which makes up roughly half of the data in a full binary tree). Mention that because this is a BST, we can omit `null` entries entirely. This demonstrates immediate optimization intuition.
*   **Discuss Varint Encoding**: Mention that if the values in the BST are usually small (e.g., within $[0, 127]$), we can use **Varint** (Variable-length Quantity) encoding (like Protocol Buffers). This allows representing small numbers with a single byte, while larger ones take up to 4 or 5 bytes.
