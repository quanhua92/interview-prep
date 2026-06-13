"""
P538: Convert BST to Greater Tree [PREMIUM] (Medium)
https://leetcode.com/problems/convert-bst-to-greater-tree/
Topics: Tree, Depth-First Search, Binary Search Tree, Binary Tree

Given the root of a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST is changed to the original key plus the sum of all keys greater than the original key in BST.
As a reminder, a binary search tree is a tree that satisfies these constraints:
Note: This question is the same as 1038: https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/
Example 1:
    Input: root = [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
    Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]

Example 2:
    Input: root = [0,null,1]
    Output: [1,null,1]

Constraints:
    - The number of nodes in the tree is in the range [0, 10^4].
    - -10^4 <= Node.val <= 10^4
    - All the values in the tree are unique.
    - root is guaranteed to be a valid binary search tree.

Template (python3):
    # Definition for a binary tree node.
    # class TreeNode:
    #     def __init__(self, val=0, left=None, right=None):
    #         self.val = val
    #         self.left = left
    #         self.right = right
    class Solution:
        def convertBST(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
"""

from src.wasm_libs.py.io import *
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


def solve(root: Optional[TreeNode]) -> Optional[TreeNode]:
    total = 0

    def reverse_inorder(node):
        nonlocal total
        if not node:
            return
        reverse_inorder(node.right)
        total += node.val
        node.val = total
        reverse_inorder(node.left)

    reverse_inorder(root)
    return root


if __name__ == "__main__":
    line = read_line()
    if not line.strip():
        write_string("")
    else:
        parts = line.split()
        vals = [None if x == "null" else int(x) for x in parts]
        root = build_tree_from_list(vals)
        root = solve(root)
        result = tree_to_list(root)
        output = " ".join("null" if v is None else str(v) for v in result)
        write_string(output)
