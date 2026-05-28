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

from src.wasm_libs.py.io import read_line


def solve(tree_vals: list, key: int) -> str:
    raise NotImplementedError


if __name__ == "__main__":
    tree_line = read_line()
    key = int(read_line())
    parts = tree_line.split()
    tree_vals = [None if x == "null" else int(x) for x in parts]
    result = solve(tree_vals, key)
    print(result)
