"""
P450: Delete Node in a BST [PREMIUM] (Medium)
https://leetcode.com/problems/delete-node-in-a-bst/
Topics: Tree, Binary Search Tree, Binary Tree

Given the root of a Binary Search Tree (BST) and a key, delete the node with the given key in the BST.
Return the root node reference (possibly updated) of the BST.

The deletion process involves finding the node and handling three cases:
- Node has no children: simply remove it.
- Node has one child: replace the node with its child.
- Node has two children: find the inorder successor (smallest in the right subtree),
  attach the deleted node's left subtree to the successor, and replace with the right subtree.

Example 1:
    Input: root = [5,3,6,2,4,null,7], key = 3
    Output: [5,4,6,2,null,null,7]
    Explanation: The node with value 3 is deleted. One valid answer is [5,4,6,2,null,null,7],
    another is [5,2,6,null,4,null,7].

Example 2:
    Input: root = [5,3,6,2,4,null,7], key = 0
    Output: [5,3,6,2,4,null,7]
    Explanation: The key 0 is not found, so the tree is unchanged.

Example 3:
    Input: root = [], key = 0
    Output: []

Constraints:
    - The number of nodes in the tree is in the range [0, 10^4].
    - -10^5 <= Node.val <= 10^5
    - Each node has a unique value.
    - root is a valid binary search tree.

Template (python3):
    # Definition for a binary tree node.
    # class TreeNode:
    #     def __init__(self, val=0, left=None, right=None):
    #         self.val = val
    #         self.left = left
    #         self.right = right
    class Solution:
        def deleteNode(self, root: Optional[TreeNode], key: int) -> Optional[TreeNode]:

Hint: Recurse down the BST to find the target. When found with two children,
find the leftmost node in the right subtree (inorder successor), attach the left
subtree to it, and return the right subtree as the new root.
"""

from src.wasm_libs.py.io import read_line, write_string
from collections import deque
from typing import Optional, List


class TreeNode:
    def __init__(self, val: int = 0):
        self.val = val
        self.left: Optional[TreeNode] = None
        self.right: Optional[TreeNode] = None


def tree_to_list(root: Optional[TreeNode]) -> List[Optional[int]]:
    if not root:
        return []
    result = []
    queue = deque([root])
    while queue:
        node = queue.popleft()
        if node:
            result.append(node.val)
            queue.append(node.left)
            queue.append(node.right)
        else:
            result.append(None)
    while len(result) > 1 and result[-1] is None:
        result.pop()
    return result


def build_tree_from_list(vals: List[Optional[int]]) -> Optional[TreeNode]:
    if not vals or vals[0] is None:
        return None
    root = TreeNode(vals[0])
    queue = deque([root])
    i = 1
    while queue and i < len(vals):
        node = queue.popleft()
        if i < len(vals):
            if vals[i] is not None:
                node.left = TreeNode(vals[i])
                queue.append(node.left)
            i += 1
        if i < len(vals):
            if vals[i] is not None:
                node.right = TreeNode(vals[i])
                queue.append(node.right)
            i += 1
    return root


def solve(root: Optional[TreeNode], key: int) -> Optional[TreeNode]:
    if not root:
        return None
    if key < root.val:
        root.left = solve(root.left, key)
    elif key > root.val:
        root.right = solve(root.right, key)
    else:
        if not root.left:
            return root.right
        if not root.right:
            return root.left
        min_node = root.right
        while min_node.left:
            min_node = min_node.left
        root.val = min_node.val
        root.right = solve(root.right, min_node.val)
    return root


if __name__ == "__main__":
    tree_line = read_line()
    key = int(read_line())
    parts = tree_line.split()
    vals = [None if x == "null" else int(x) for x in parts]
    root = build_tree_from_list(vals)
    root = solve(root, key)
    result = tree_to_list(root)
    if not result:
        write_string("null")
    else:
        output = " ".join("null" if v is None else str(v) for v in result)
        write_string(output)
