"""
P102: Binary Tree Level Order Traversal (Medium)
https://leetcode.com/problems/binary-tree-level-order-traversal/
Topics: Tree, Breadth-First Search, Binary Tree

Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).

Example 1:
    Input: root = [3,9,20,null,null,15,7]
    Output: [[3],[9,20],[15,7]]

Example 2:
    Input: root = [1]
    Output: [[1]]

Example 3:
    Input: root = []
    Output: []

Constraints:
    - The number of nodes in the tree is in the range [0, 2000].
    - -1000 <= Node.val <= 1000

Hints:
    - Use a queue to perform BFS.

Template (python3):
    # Definition for a binary tree node.
    # class TreeNode:
    #     def __init__(self, val=0, left=None, right=None):
    #         self.val = val
    #         self.left = left
    #         self.right = right
    class Solution:
        def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:

Hint: Use a queue to process nodes level by level.
"""

from src.wasm_libs.py.io import *
import sys
from collections import deque
from typing import Optional, List


# =====================================================================
# 1. CORE DATA STRUCTURE
# =====================================================================
class TreeNode:
    def __init__(self, val: int = 0):
        self.val = val
        self.left: Optional[TreeNode] = None
        self.right: Optional[TreeNode] = None


# =====================================================================
# 2. LEETCODE SOLUTION
# =====================================================================

def solve(root: Optional[TreeNode]) -> List[List[int]]:
    raise NotImplementedError


# =====================================================================
# 3. ENVIRONMENT UTILITIES (Level-Order parsing used by LeetCode platform)
# =====================================================================

def build_tree_from_list(vals: List[Optional[int]]) -> Optional[TreeNode]:
    """Reconstructs a real TreeNode binary tree from a level-order array."""
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


# =====================================================================
# 4. RUNTIME SYSTEM EXECUTION BLOCK
# =====================================================================

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

        initial_tree = build_tree_from_list(vals)
        result = solve(initial_tree)
        for row in result:
            write_ints(row)
