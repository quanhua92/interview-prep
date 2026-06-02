"""
P515: Find Largest Value in Each Tree Row [PREMIUM] (Medium)
https://leetcode.com/problems/find-largest-value-in-each-tree-row/
Topics: Tree, Depth-First Search, Breadth-First Search, Binary Tree

Given the root of a binary tree, return an array of the largest value in each row of the tree (0-indexed).
Example 1:
    Input: root = [1,3,2,5,3,null,9]
    Output: [1,3,9]

Example 2:
    Input: root = [1,2,3]
    Output: [1,3]

Constraints:
    - The number of nodes in the tree will be in the range [0, 10^4].
    - -2^31 <= Node.val <= 2^31 - 1

Template (python3):
    # Definition for a binary tree node.
    # class TreeNode:
    #     def __init__(self, val=0, left=None, right=None):
    #         self.val = val
    #         self.left = left
    #         self.right = right
    class Solution:
        def largestValues(self, root: Optional[TreeNode]) -> List[int]:
"""

from src.wasm_libs.py.io import *
import sys
from collections import deque


def build_tree(vals: list[int]) -> list | None:
    raise NotImplementedError

def solve(vals: list[int]) -> list[int]:
    raise NotImplementedError

if __name__ == "__main__":
    n = read_int()
    if n == 0:
        sys.exit(0)
    else:
        tokens = read_line().split()
        vals = []
        for t in tokens:
            if t == "null":
                vals.append(None)
            else:
                vals.append(int(t))
        result = solve(vals)
        write_ints(result)
