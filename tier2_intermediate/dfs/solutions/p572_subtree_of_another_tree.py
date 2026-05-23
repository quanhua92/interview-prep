"""
P572: Subtree of Another Tree [PREMIUM] (Easy)
https://leetcode.com/problems/subtree-of-another-tree/
Topics: Tree, Depth-First Search, String Matching, Binary Tree, Hash Function

Given the roots of two binary trees root and subRoot, return true if there is a subtree of root with the same structure and node values of subRoot and false otherwise.
A subtree of a binary tree tree is a tree that consists of a node in tree and all of this node's descendants. The tree tree could also be considered as a subtree of itself.
Example 1:
    Input: root = [3,4,5,1,2], subRoot = [4,1,2]
    Output: true

Example 2:
    Input: root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
    Output: false

Constraints:
    - The number of nodes in the root tree is in the range [1, 2000].
    - The number of nodes in the subRoot tree is in the range [1, 1000].
    - -104 <= root.val <= 104
    - -104 <= subRoot.val <= 104

Hint: Which approach is better here- recursive or iterative?
Hint: If recursive approach is better, can you write recursive function with its parameters?
Hint: Two trees <b>s</b> and <b>t</b> are said to be identical if their root values are same and their left and right subtrees are identical. Can you write this in form of recursive formulae?
Hint: Recursive formulae can be:
isIdentical(s,t)= s.val==t.val AND isIdentical(s.left,t.left) AND isIdentical(s.right,t.right)

Template (python3):
    # Definition for a binary tree node.
    # class TreeNode:
    #     def __init__(self, val=0, left=None, right=None):
    #         self.val = val
    #         self.left = left
    #         self.right = right
    class Solution:
        def isSubtree(self, root: Optional[TreeNode], subRoot: Optional[TreeNode]) -> bool:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase, TreeNode


class Solution(Problem):
    name = "572. Subtree of Another Tree"
    test_cases = [
        TestCase(
            input=(TreeNode.from_list([3, 4, 5, 1, 2]), TreeNode.from_list([4, 1, 2])),
            expected=True,
            label="example 1",
        ),
        TestCase(
            input=(
                TreeNode.from_list([3, 4, 5, 1, 2, None, None, None, None, 0]),
                TreeNode.from_list([4, 1, 2]),
            ),
            expected=False,
            label="example 2",
        ),
        TestCase(
            input=(TreeNode.from_list([1, 2, 3]), TreeNode.from_list([1, 2, 3])),
            expected=True,
            label="identical trees",
        ),
        TestCase(
            input=(TreeNode.from_list([1]), TreeNode.from_list([1])),
            expected=True,
            label="single node match",
        ),
        TestCase(
            input=(
                TreeNode.from_list([1, None, 2, None, 3]),
                TreeNode.from_list([2, None, 3]),
            ),
            expected=True,
            label="right-skewed subtree",
        ),
        TestCase(
            input=(TreeNode.from_list([1, 2]), TreeNode.from_list([3])),
            expected=False,
            label="no matching value",
        ),
    ]

    def solve(self, root: TreeNode, subRoot: TreeNode) -> bool:
        def is_same(a: TreeNode | None, b: TreeNode | None) -> bool:
            if not a and not b:
                return True
            if not a or not b:
                return False
            return (
                a.val == b.val and is_same(a.left, b.left) and is_same(a.right, b.right)
            )

        if not subRoot:
            return True
        if not root:
            return False
        if is_same(root, subRoot):
            return True
        return self.solve(root.left, subRoot) or self.solve(root.right, subRoot)


if __name__ == "__main__":
    Solution().run()
