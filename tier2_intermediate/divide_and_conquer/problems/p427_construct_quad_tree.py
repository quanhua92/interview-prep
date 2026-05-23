"""
P427: Construct Quad Tree [PREMIUM] (Medium)
https://leetcode.com/problems/construct-quad-tree/
Topics: Array, Divide and Conquer, Tree, Matrix

Given a n * n matrix grid of 0's and 1's only. We want to represent grid with a Quad-Tree.
Return the root of the Quad-Tree representing grid.
A Quad-Tree is a tree data structure in which each internal node has exactly four children. Besides, each node has two attributes:
We can construct a Quad-Tree from a two-dimensional area using the following steps:
If you want to know more about the Quad-Tree, you can refer to the wiki.
Quad-Tree format:
You don't need to read this section for solving the problem. This is only if you want to understand the output format here. The output represents the serialized format of a Quad-Tree using level order traversal, where null signifies a path terminator where no node exists below.
It is very similar to the serialization of the binary tree. The only difference is that the node is represented as a list [isLeaf, val].
If the value of isLeaf or val is True we represent it as 1 in the list [isLeaf, val] and if the value of isLeaf or val is False we represent it as 0.
    class Node {
    public boolean val;
    public boolean isLeaf;
    public Node topLeft;
    public Node topRight;
    public Node bottomLeft;
    public Node bottomRight;
    }

Example 1:
    Input: grid = [[0,1],[1,0]]
    Output: [[0,1],[1,0],[1,1],[1,1],[1,0]]
    Explanation: The explanation of this example is shown below:
    Notice that 0 represents False and 1 represents True in the photo representing the Quad-Tree.

Example 2:
    Input: grid = [[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0]]
    Output: [[0,1],[1,1],[0,1],[1,1],[1,0],null,null,null,null,[1,0],[1,0],[1,1],[1,1]]
    Explanation: All values in the grid are not the same. We divide the grid into four sub-grids.
    The topLeft, bottomLeft and bottomRight each has the same value.
    The topRight have different values so we divide it into 4 sub-grids where each has the same value.
    Explanation is shown in the photo below:

Constraints:
    - n == grid.length == grid[i].length
    - n == 2x where 0 <= x <= 6

Template (python3):
    '''
    # Definition for a QuadTree node.
    class Node:
        def __init__(self, val, isLeaf, topLeft, topRight, bottomLeft, bottomRight):
            self.val = val
            self.isLeaf = isLeaf
            self.topLeft = topLeft
            self.topRight = topRight
            self.bottomLeft = bottomLeft
            self.bottomRight = bottomRight
    '''

    class Solution:
        def construct(self, grid: List[List[int]]) -> 'Node':
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase
from typing import Any


class Solution(Problem):
    name = "427. Construct Quad Tree"
    test_cases = [
        TestCase(
            input=[[0, 1], [1, 0]],
            expected=[[0, 1], [1, 0], [1, 1], [1, 1], [1, 0]],
            label="example 2",
        ),
        TestCase(
            input=[
                [1, 1, 1, 1, 0, 0, 0, 0],
                [1, 1, 1, 1, 0, 0, 0, 0],
                [1, 1, 1, 1, 1, 1, 1, 1],
                [1, 1, 1, 1, 1, 1, 1, 1],
                [1, 1, 1, 1, 0, 0, 0, 0],
                [1, 1, 1, 1, 0, 0, 0, 0],
                [1, 1, 1, 1, 0, 0, 0, 0],
                [1, 1, 1, 1, 0, 0, 0, 0],
            ],
            expected=[
                [0, 1],
                [1, 1],
                [0, 1],
                [1, 1],
                [1, 0],
                [1, 0],
                [1, 0],
                [1, 1],
                [1, 1],
            ],
            label="example 3",
        ),
        TestCase(input=[[0]], expected=[[1, 0]], label="1x1 all zeros"),
        TestCase(input=[[1]], expected=[[1, 1]], label="1x1 all ones"),
        TestCase(
            input=[[1, 1], [1, 1]],
            expected=[[1, 1]],
            label="2x2 all same (ones)",
        ),
        TestCase(
            input=[[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]],
            expected=[[1, 0]],
            label="4x4 all zeros",
        ),
    ]

    def solve(self, grid: list[list[int]]) -> Any:
        raise NotImplementedError("TODO: Implement solve(self, grid) -> Any")


if __name__ == "__main__":
    Solution().run()
