# TODO: Implement
"""
P538: Convert BST to Greater Tree [PREMIUM] (Medium)
https://leetcode.com/problems/convert-bst-to-greater-tree/
Topics: Tree, Depth-First Search, Binary Search Tree, Binary Tree

Given the root of a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST is changed to the original key plus the sum of all keys greater than the original key in BST.
As a reminder, a binary search tree is a tree that satisfies these constraints:
Example 2:
Note: This question is the same as 1038: https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/
Example 1:
    Input: root = [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
    Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]

Example 2:
    Input: root = [0,null,1]
    Output: [1,null,1]

Constraints:
    - The number of nodes in the tree is in the range [0, 104].
    - -104 <= Node.val <= 104
    - All the values in the tree are unique.
    - root is guaranteed to be a valid binary search tree.

Template (python3):
    # Definition for a binary tree node.
    # class TreeNode:
    #     def __init__(self, val=0, left=None, right=None):
    #         self.val = val
    #         self.left = left
    #         self.right = right
    class Solution:
        def convertBST(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase, TreeNode


class Solution(Problem):
    name = "538. Convert BST to Greater Tree"
    test_cases = [
        TestCase(
            input=TreeNode.from_list(
                [4, 1, 6, 0, 2, 5, 7, None, None, None, 3, None, None, None, 8]
            ),
            expected=TreeNode.from_list(
                [30, 36, 21, 36, 35, 26, 15, None, None, None, 33, None, None, None, 8]
            ),
            label="example 1",
        ),
        TestCase(
            input=TreeNode.from_list([0, None, 1]),
            expected=TreeNode.from_list([1, None, 1]),
            label="example 2",
        ),
        TestCase(
            input=TreeNode.from_list([2, 1, 3]),
            expected=TreeNode.from_list([5, 6, 3]),
            label="small balanced BST",
        ),
        TestCase(
            input=TreeNode.from_list([1]),
            expected=TreeNode.from_list([1]),
            label="single node",
        ),
        TestCase(
            input=TreeNode.from_list([1, None, 2, None, 3]),
            expected=TreeNode.from_list([6, None, 5, None, 3]),
            label="right-skewed BST",
        ),
        TestCase(input=None, expected=None, label="empty tree"),
    ]

    def solve(self, root: TreeNode | None) -> TreeNode | None:
        raise NotImplementedError("TODO: Implement solve(...)")


if __name__ == "__main__":
    Solution().run()

