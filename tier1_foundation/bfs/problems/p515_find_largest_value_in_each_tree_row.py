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
    - The number of nodes in the tree will be in the range [0, 104].
    - -231 <= Node.val <= 231 - 1

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

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase, TreeNode
from typing import Any


class Solution(Problem):
    name = "515. Find Largest Value in Each Tree Row"
    test_cases = [
        TestCase(input="[1,3,2,5,3,null,9]", expected=[1, 3, 9], label="example 1"),
        TestCase(input=[1, 2, 3], expected=[1, 3], label="example 2"),
    ]

    def solve(self, root: TreeNode | None) -> Any:
        raise NotImplementedError("TODO: Implement solve(self, root) -> Any")


if __name__ == "__main__":
    Solution().run()
