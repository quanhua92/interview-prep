"""
P449: Serialize and Deserialize BST [PREMIUM] (Medium)
https://leetcode.com/problems/serialize-and-deserialize-bst/
Topics: String, Tree, Depth-First Search, Breadth-First Search, Design, Binary Search Tree, Binary Tree

Serialization is converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.
Design an algorithm to serialize and deserialize a binary search tree. There is no restriction on how your serialization/deserialization algorithm should work. You need to ensure that a binary search tree can be serialized to a string, and this string can be deserialized to the original tree structure.
The encoded string should be as compact as possible.
Example 1:
    Input: root = [2,1,3]
    Output: [2,1,3]

Example 2:
    Input: root = []
    Output: []

Constraints:
    - The number of nodes in the tree is in the range [0, 10^4].
    - 0 <= Node.val <= 10^4
    - The input tree is guaranteed to be a binary search tree.

Template (python3):
    # Definition for a binary tree node.
    # class TreeNode:
    #     def __init__(self, x):
    #         self.val = x
    #         self.left = None
    #         self.right = None

    class Codec:

        def serialize(self, root: Optional[TreeNode]) -> str:
            '''Encodes a tree to a single string.
            '''


        def deserialize(self, data: str) -> Optional[TreeNode]:
            '''Decodes your encoded data to tree.
            '''

    # Your Codec object will be instantiated and called as such:
    # Your Codec object will be instantiated and called as such:
    # ser = Codec()
    # deser = Codec()
    # tree = ser.serialize(root)
    # ans = deser.deserialize(tree)
    # return ans
"""

from src.wasm_libs.py.io import *
import sys
from collections import deque
from typing import Optional, List


# =====================================================================
# 1. CORE DATA STRUCTURE
# =====================================================================
class TreeNode:
    def __init__(self, x: int):
        self.val = x
        self.left: Optional[TreeNode] = None
        self.right: Optional[TreeNode] = None


# =====================================================================
# 2. LEETCODE SOLUTION: CODEC CLASS (Using Compact BST Boundaries)
# =====================================================================
class Codec:
    def serialize(self, root: Optional[TreeNode]) -> str:
        raise NotImplementedError

    def deserialize(self, data: str) -> Optional[TreeNode]:
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


def convert_tree_to_list(root: Optional[TreeNode]) -> List[Optional[int]]:
    """Flattens a real TreeNode tree back into a level-order array with nulls."""
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
            
    while result and result[-1] is None:
        result.pop()
        
    return result


# =====================================================================
# 4. RUNTIME SYSTEM EXECUTION BLOCK
# =====================================================================
def solve(root: Optional[TreeNode]) -> Optional[TreeNode]:
    """Simulates how the LeetCode platform calls and validates your Codec."""
    ser = Codec()
    deser = Codec()
    
    tree_str = ser.serialize(root)
    ans_tree = deser.deserialize(tree_str)
    
    return ans_tree


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
        result_tree = solve(initial_tree)
        result_list = convert_tree_to_list(result_tree)
        
        parts = []
        for v in result_list:
            if v is None:
                parts.append("null")
            else:
                parts.append(str(v))
        write_string(" ".join(parts))
