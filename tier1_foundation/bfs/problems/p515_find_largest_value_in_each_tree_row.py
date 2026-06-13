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

def solve(root: Optional[TreeNode]) -> List[int]:
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
        write_ints(result)
