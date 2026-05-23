"""
P450: Delete Node in a BST [PREMIUM] (Medium)
https://leetcode.com/problems/delete-node-in-a-bst/
Topics: Tree, Binary Search Tree, Binary Tree

Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.
Basically, the deletion can be divided into two stages:
Example 3:
Follow up: Could you solve it with time complexity O(height of tree)?
Example 1:
    Input: root = [5,3,6,2,4,null,7], key = 3
    Output: [5,4,6,2,null,null,7]
    Explanation: Given key to delete is 3. So we find the node with value 3 and delete it.
    One valid answer is [5,4,6,2,null,null,7], shown in the above BST.
    Please notice that another valid answer is [5,2,6,null,4,null,7] and it's also accepted.

Example 2:
    Input: root = [5,3,6,2,4,null,7], key = 0
    Output: [5,3,6,2,4,null,7]
    Explanation: The tree does not contain a node with value = 0.

Example 3:
    Input: root = [], key = 0
    Output: []

Constraints:
    - The number of nodes in the tree is in the range [0, 104].
    - -105 <= Node.val <= 105
    - Each node has a unique value.
    - root is a valid binary search tree.
    - -105 <= key <= 105

Template (python3):
    # Definition for a binary tree node.
    # class TreeNode:
    #     def __init__(self, val=0, left=None, right=None):
    #         self.val = val
    #         self.left = left
    #         self.right = right
    class Solution:
        def deleteNode(self, root: Optional[TreeNode], key: int) -> Optional[TreeNode]:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase, TreeNode


class Solution(Problem):
    name = "450. Delete Node in a BST"
    test_cases = [
        TestCase(
            input=(TreeNode.from_list([5, 3, 6, 2, 4, None, 7]), 3),
            expected=TreeNode.from_list([5, 4, 6, 2, None, None, 7]),
            label="example 1",
        ),
        TestCase(
            input=(TreeNode.from_list([5, 3, 6, 2, 4, None, 7]), 0),
            expected=TreeNode.from_list([5, 3, 6, 2, 4, None, 7]),
            label="example 2",
        ),
        TestCase(
            input=(TreeNode.from_list([]), 0),
            expected=TreeNode.from_list([]),
            label="example 3",
        ),
        TestCase(
            input=(TreeNode.from_list([5]), 5),
            expected=TreeNode.from_list([]),
            label="delete single node root",
        ),
        TestCase(
            input=(TreeNode.from_list([3, 1, 4]), 3),
            expected=TreeNode.from_list([4, 1]),
            label="delete root with two children",
        ),
        TestCase(
            input=(TreeNode.from_list([2, 1, 3]), 1),
            expected=TreeNode.from_list([2, None, 3]),
            label="delete left leaf",
        ),
        TestCase(
            input=(TreeNode.from_list([5, 3, None, 2, None, 1]), 3),
            expected=TreeNode.from_list([5, 2, None, 1]),
            label="delete node with only left child",
        ),
    ]

    def solve(self, root: TreeNode | None, key: int) -> TreeNode | None:
        if not root:
            return None
        if key < root.val:
            root.left = self.solve(root.left, key)
        elif key > root.val:
            root.right = self.solve(root.right, key)
        else:
            if not root.left:
                return root.right
            if not root.right:
                return root.left
            min_node = root.right
            while min_node.left:
                min_node = min_node.left
            root.val = min_node.val
            root.right = self.solve(root.right, min_node.val)
        return root


if __name__ == "__main__":
    Solution().run()
