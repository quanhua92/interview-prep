"""
P513: Find Bottom Left Tree Value [PREMIUM] (Medium)
https://leetcode.com/problems/find-bottom-left-tree-value/
Topics: Tree, Depth-First Search, Breadth-First Search, Binary Tree

Given the root of a binary tree, return the leftmost value in the last row of the tree.
Example 1:
    Input: root = [2,1,3]
    Output: 1

Example 2:
    Input: root = [1,2,3,4,null,5,6,null,null,7]
    Output: 7

Constraints:
    - The number of nodes in the tree is in the range [1, 104].
    - -231 <= Node.val <= 231 - 1

Template (python3):
    # Definition for a binary tree node.
    # class TreeNode:
    #     def __init__(self, val=0, left=None, right=None):
    #         self.val = val
    #         self.left = left
    #         self.right = right
    class Solution:
        def findBottomLeftValue(self, root: Optional[TreeNode]) -> int:
"""

from src.wasm_libs.py.io import *
from collections import deque


def build_tree(vals: list[int]) -> list | None:
    if not vals or vals[0] is None:
        return None
    root = {"val": vals[0], "left": None, "right": None}
    queue = deque([root])
    i = 1
    while queue and i < len(vals):
        node = queue.popleft()
        if i < len(vals) and vals[i] is not None:
            node["left"] = {"val": vals[i], "left": None, "right": None}
            queue.append(node["left"])
        i += 1
        if i < len(vals) and vals[i] is not None:
            node["right"] = {"val": vals[i], "left": None, "right": None}
            queue.append(node["right"])
        i += 1
    return root


def solve(vals: list[int]) -> int:
    root = build_tree(vals)
    queue = deque([root])
    result = 0
    while queue:
        level_size = len(queue)
        result = queue[0]["val"]
        for _ in range(level_size):
            node = queue.popleft()
            if node["left"]:
                queue.append(node["left"])
            if node["right"]:
                queue.append(node["right"])
    return result


if __name__ == "__main__":
    n = read_int()
    tokens = read_line().split()
    vals = []
    for t in tokens:
        if t == "null":
            vals.append(None)
        else:
            vals.append(int(t))
    result = solve(vals)
    write_int(result)
