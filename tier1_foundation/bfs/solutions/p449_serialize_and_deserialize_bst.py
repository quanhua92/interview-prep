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
    - The number of nodes in the tree is in the range [0, 104].
    - 0 <= Node.val <= 104
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

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "449. Serialize and Deserialize BST"
    test_cases = [
        TestCase(input={"vals": [2, 1, 3]}, expected=[2, 1, 3], label="example 1"),
        TestCase(input={"vals": []}, expected=[], label="empty tree"),
        TestCase(input={"vals": [1]}, expected=[1], label="single node"),
        TestCase(
            input={"vals": [3, 1, 4, None, 2]},
            expected=[3, 1, 4, None, 2],
            label="bst with left subtree",
        ),
        TestCase(
            input={"vals": [5, 3, 8, 1, 4, 7, 9]},
            expected=[5, 3, 8, 1, 4, 7, 9],
            label="balanced bst 3 levels",
        ),
        TestCase(
            input={"vals": [4, 2, 5, 1, 3]},
            expected=[4, 2, 5, 1, 3],
            label="complete bst",
        ),
    ]

    def solve(self, vals: list[int]) -> list[int | None]:
        from collections import deque
        from src.utils import TreeNode

        if not vals:
            return []
        root = TreeNode(vals[0])
        queue: deque = deque([root])
        i = 1
        while queue and i < len(vals):
            node = queue.popleft()
            if i < len(vals) and vals[i] is not None:
                node.left = TreeNode(vals[i])
                queue.append(node.left)
            i += 1
            if i < len(vals) and vals[i] is not None:
                node.right = TreeNode(vals[i])
                queue.append(node.right)
            i += 1

        serialized: list[int | None] = []
        queue = deque([root])
        while queue:
            node = queue.popleft()
            if node:
                serialized.append(node.val)
                if node.left or node.right:
                    queue.append(node.left)
                    queue.append(node.right)
            else:
                serialized.append(None)
        while serialized and serialized[-1] is None:
            serialized.pop()
        return serialized

    def _serialize(self, root) -> str:
        from collections import deque

        if not root:
            return ""
        result = []
        queue = deque([root])
        while queue:
            node = queue.popleft()
            if node:
                result.append(str(node.val))
                queue.append(node.left)
                queue.append(node.right)
            else:
                result.append("#")
        return ",".join(result)

    def _deserialize(self, data: str):
        from collections import deque
        from src.utils import TreeNode

        if not data:
            return None
        vals = data.split(",")
        root = TreeNode(int(vals[0]))
        queue = deque([root])
        i = 1
        while queue and i < len(vals):
            node = queue.popleft()
            if vals[i] != "#":
                node.left = TreeNode(int(vals[i]))
                queue.append(node.left)
            i += 1
            if i < len(vals) and vals[i] != "#":
                node.right = TreeNode(int(vals[i]))
                queue.append(node.right)
            i += 1
        return root


if __name__ == "__main__":
    Solution().run()
