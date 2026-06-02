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


def solve(vals: list[int | None]) -> list[int | None]:
    if not vals or vals[0] is None:
        return []
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

    serialized = []
    queue = deque([root])
    while queue:
        node = queue.popleft()
        if node:
            serialized.append(node["val"])
            if node["left"] or node["right"]:
                queue.append(node["left"])
                queue.append(node["right"])
        else:
            serialized.append(None)
    while serialized and serialized[-1] is None:
        serialized.pop()
    return serialized


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
        parts = []
        for v in result:
            if v is None:
                parts.append("null")
            else:
                parts.append(str(v))
        write_string(" ".join(parts))
