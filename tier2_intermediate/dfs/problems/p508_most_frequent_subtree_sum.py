# TODO: Implement
"""
P508: Most Frequent Subtree Sum [PREMIUM] (Medium)
https://leetcode.com/problems/most-frequent-subtree-sum/
Topics: Hash Table, Tree, Depth-First Search, Binary Tree

Given the root of a binary tree, return the most frequent subtree sum. If there is a tie, return all the values with the highest frequency in any order.
The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself).
Example 1:
    Input: root = [5,2,-3]
    Output: [2,-3,4]

Example 2:
    Input: root = [5,2,-5]
    Output: [2]

Constraints:
    - The number of nodes in the tree is in the range [1, 104].
    - -105 <= Node.val <= 105

Template (python3):
    # Definition for a binary tree node.
    # class TreeNode:
    #     def __init__(self, val=0, left=None, right=None):
    #         self.val = val
    #         self.left = left
    #         self.right = right
    class Solution:
        def findFrequentTreeSum(self, root: Optional[TreeNode]) -> List[int]:
"""

import sys

sys.path.insert(0, ".")
from collections import Counter

from src.utils import Problem, TestCase, TreeNode


class Solution(Problem):
    name = "508. Most Frequent Subtree Sum"
    test_cases = [
        TestCase(
            input=TreeNode.from_list([5, 2, -3]),
            expected=[-3, 2, 4],
            label="example 1",
        ),
        TestCase(
            input=TreeNode.from_list([5, 2, -5]),
            expected=[2],
            label="example 2",
        ),
        TestCase(
            input=TreeNode.from_list([1]),
            expected=[1],
            label="single node",
        ),
        TestCase(
            input=TreeNode.from_list([1, 2, 3]),
            expected=[2, 3, 6],
            label="balanced tree",
        ),
        TestCase(
            input=TreeNode.from_list([-1, -2, -3]),
            expected=[-6, -3, -2],
            label="all negative values",
        ),
    ]

    def solve(self, root: TreeNode) -> list[int]:
        raise NotImplementedError("TODO: Implement solve(self, root: TreeNode)")
        def subtree_sum(node: TreeNode) -> int:
            s = (
                node.val
                + (subtree_sum(node.left) if node.left else 0)
                + (subtree_sum(node.right) if node.right else 0)
            )
            freq[s] += 1
            return s

        subtree_sum(root)
        max_count = max(freq.values())
        return sorted([s for s, c in freq.items() if c == max_count])


if __name__ == "__main__":
    Solution().run()
