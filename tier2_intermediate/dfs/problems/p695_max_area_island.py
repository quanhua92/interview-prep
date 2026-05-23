"""
P695: Max Area of Island (Medium)
https://leetcode.com/problems/max-area-of-island/
Topics: Array, Depth-First Search, Breadth-First Search, Union Find, Matrix

You are given an m x n binary matrix grid. An island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.
The area of an island is the number of cells with a value 1 in the island.
Return the maximum area of an island in grid. If there is no island, return 0.

Example 1:
    Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
    Output: 6
    Explanation: The answer is not 11, because the island must be connected 4-directionally.

Example 2:
    Input: grid = [[0,0,0,0,0,0,0,0]]
    Output: 0

Constraints:
    - m == grid.length
    - n == grid[i].length
    - 1 <= m, n <= 50
    - grid[i][j] is either 0 or 1.

Template (python3):
    class Solution:
        def maxAreaOfIsland(self, grid: List[List[int]]) -> int:

Hint: Use DFS to explore each island and track the maximum area found.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "695. Max Area of Island"
    test_cases = [
        TestCase(
            input=[
                [0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0],
                [0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0],
                [0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0],
                [0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0],
            ],
            expected=6,
            label="example 1",
        ),
        TestCase(input=[[0, 0, 0, 0, 0, 0, 0, 0]], expected=0, label="example 2"),
        TestCase(input=[[1]], expected=1, label="single cell land"),
        TestCase(input=[[0]], expected=0, label="single cell water"),
        TestCase(
            input=[[1, 1, 1], [1, 1, 1], [1, 1, 1]],
            expected=9,
            label="all land 3x3",
        ),
        TestCase(
            input=[[1, 0, 1, 0, 1]],
            expected=1,
            label="single row alternating",
        ),
        TestCase(
            input=[[1], [0], [1], [0], [1]],
            expected=1,
            label="single column alternating",
        ),
    ]

    def solve(self, grid: list[list[int]]) -> int:
        raise NotImplementedError(
            "TODO: Implement solve(self, grid: list[list[int]]) -> int"
        )


if __name__ == "__main__":
    Solution().run()
