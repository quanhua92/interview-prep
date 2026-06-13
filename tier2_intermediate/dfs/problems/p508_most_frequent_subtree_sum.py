"""
P508: Most Frequent Subtree Sum [PREMIUM] (Medium)
https://leetcode.com/problems/most-frequent-subtree-sum/
Topics: Hash Table, Tree, Depth-First Search, Binary Tree

Given the root of a binary tree, return the most frequent subtree sum. If there is a tie, return all the values with the highest frequency in any order.

Example 1:
    Input: root = [5,2,-3]
    Output: [2,-3,4]

Example 2:
    Input: root = [5,2,-5]
    Output: [2]

Constraints:
    - The number of nodes in the tree is in the range [1, 10^4].
    - -10^5 <= Node.val <= 10^5

Template (python3):
    class Solution:
        def findFrequentTreeSum(self, root: Optional[TreeNode]) -> List[int]:
"""

from src.wasm_libs.py.io import *
from collections import deque
from typing import Optional, List


class TreeNode:
    def __init__(self, val: int = 0):
        self.val = val
        self.left: Optional[TreeNode] = None
        self.right: Optional[TreeNode] = None


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


def solve(root: TreeNode) -> List[int]:
    raise NotImplementedError


if __name__ == "__main__":
    line = read_line()
    parts = line.split()
    vals = [None if x == "null" else int(x) for x in parts]
    root = build_tree_from_list(vals)
    result = solve(root)
    write_ints(result)
