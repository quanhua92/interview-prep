"""
P538: Convert BST to Greater Tree [PREMIUM] (Medium)
https://leetcode.com/problems/convert-bst-to-greater-tree/
Topics: Tree, Depth-First Search, Binary Search Tree, Binary Tree

Given the root of a BST, convert it to a Greater Tree such that every key is changed to the original key plus the sum of all keys greater than the original key.

Example 1:
    Input: root = [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
    Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]

Example 2:
    Input: root = [0,null,1]
    Output: [1,null,1]

Constraints:
    - The number of nodes in the tree is in the range [0, 10^4].
    - -10^4 <= Node.val <= 10^4

Template (python3):
    class Solution:
        def convertBST(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
"""

from src.wasm_libs.py.io import *


def solve(tree_vals: list) -> str:
    raise NotImplementedError


if __name__ == "__main__":
    line = read_line()
    tree_vals = [None if x == "null" else int(x) for x in line.split()] if line.strip() else []
    result = solve(tree_vals)
    print(result)
