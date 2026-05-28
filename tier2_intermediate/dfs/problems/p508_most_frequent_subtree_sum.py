"""
P508: Most Frequent Subtree Sum [PREMIUM] (Medium)
https://leetcode.com/problems/most-frequent-subtree-sum/
Topics: Hash Table, Tree, Depth-First Search, Binary Tree

Given the root of a binary tree, return the most frequent subtree sum. If there is a tie, return all the values with the highest frequency in any order.

Example 1:
    Input: root = [5,2,-3]
    Output: [2,-3,4]

Example 2:
    Input: root = [5,2,-5]
    Output: [2]

Constraints:
    - The number of nodes in the tree is in the range [1, 10^4].
    - -10^5 <= Node.val <= 10^5

Template (python3):
    class Solution:
        def findFrequentTreeSum(self, root: Optional[TreeNode]) -> List[int]:
"""

from src.wasm_libs.py.io import *


def solve(tree_vals: list) -> list[int]:
    raise NotImplementedError


if __name__ == "__main__":
    line = read_line()
    tree_vals = [None if x == "null" else int(x) for x in line.split()]
    result = solve(tree_vals)
    write_ints(result)
