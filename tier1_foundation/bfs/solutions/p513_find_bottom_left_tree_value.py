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

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase, TreeNode


class Solution(Problem):
    name = "513. Find Bottom Left Tree Value"
    test_cases = [
        TestCase(input=TreeNode.from_list([2, 1, 3]), expected=1, label="example 1"),
        TestCase(
            input=TreeNode.from_list([1, 2, 3, 4, None, 5, 6, None, None, 7]),
            expected=7,
            label="example 2",
        ),
    ]

    def solve(self, root: TreeNode) -> int:
        from collections import deque

        queue = deque([root])
        result = 0
        while queue:
            level_size = len(queue)
            result = queue[0].val
            for _ in range(level_size):
                node = queue.popleft()
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
        return result


if __name__ == "__main__":
    Solution().run()
