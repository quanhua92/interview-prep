"""
P450: Delete Node in a BST [PREMIUM] (Medium)
https://leetcode.com/problems/delete-node-in-a-bst/
Topics: Tree, Binary Search Tree, Binary Tree

Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.

Example 1:
    Input: root = [5,3,6,2,4,null,7], key = 3
    Output: [5,4,6,2,null,null,7]

Example 2:
    Input: root = [5,3,6,2,4,null,7], key = 0
    Output: [5,3,6,2,4,null,7]

Example 3:
    Input: root = [], key = 0
    Output: []

Constraints:
    - The number of nodes in the tree is in the range [0, 10^4].
    - -10^5 <= Node.val <= 10^5

Template (python3):
    class Solution:
        def deleteNode(self, root: Optional[TreeNode], key: int) -> Optional[TreeNode]:
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
    raise NotImplementedError


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
