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

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase, TreeNode
from collections import deque


class Solution(Problem):
    name = "102. Binary Tree Level Order Traversal"
    test_cases = [
        TestCase(
            input=TreeNode.from_list([3, 9, 20, None, None, 15, 7]),
            expected=[[3], [9, 20], [15, 7]],
            label="example 1",
        ),
        TestCase(input=TreeNode.from_list([1]), expected=[[1]], label="example 2"),
        TestCase(input=TreeNode.from_list([]), expected=[], label="empty"),
    ]

    def solve(self, root: TreeNode | None) -> list[list[int]]:
        if not root:
            return []
        result = []
        queue = deque([root])
        while queue:
            level_size = len(queue)
            level = []
            for _ in range(level_size):
                node = queue.popleft()
                level.append(node.val)
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
            result.append(level)
        return result


if __name__ == "__main__":
    Solution().run()
