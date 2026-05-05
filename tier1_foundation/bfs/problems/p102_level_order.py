"""P102: Binary Tree Level Order Traversal (Medium)

TODO: Implement solve() below.
Hint: Use a queue to process nodes level by level.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase, TreeNode
from collections import deque


class Solution(Problem):
    name = "102. Binary Tree Level Order Traversal"
    test_cases = [
        TestCase(input=TreeNode.from_list([3,9,20,None,None,15,7]), expected=[[3],[9,20],[15,7]], label="example 1"),
        TestCase(input=TreeNode.from_list([1]), expected=[[1]], label="example 2"),
        TestCase(input=TreeNode.from_list([]), expected=[], label="empty"),
    ]

    def solve(self, root: TreeNode | None) -> list[list[int]]:
        raise NotImplementedError("TODO: Implement solve(self, root: TreeNode | None) -> list[list[int]]")


if __name__ == "__main__":
    Solution().run()
