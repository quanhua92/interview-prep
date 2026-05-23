"""
P994: Rotting Oranges (Medium)
https://leetcode.com/problems/rotting-oranges/
Topics: Array, Breadth-First Search, Matrix

You are given an m x n grid where each cell can have one of three values:
Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.
Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.

Example 1:
    Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
    Output: 4

Example 2:
    Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
    Output: -1
    Explanation: The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.

Example 3:
    Input: grid = [[0,2]]
    Output: 0
    Explanation: Since there are already no fresh oranges at minute 0, the answer is just 0.

Constraints:
    - m == grid.length
    - n == grid[i].length
    - 1 <= m, n <= 10
    - grid[i][j] is 0, 1, or 2.

Template (python3):
    class Solution:
        def orangesRotting(self, grid: List[List[int]]) -> int:

Hint: Use BFS starting from all rotten oranges simultaneously.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "994. Rotting Oranges"
    test_cases = [
        TestCase(
            input=[[2, 1, 1], [1, 1, 0], [0, 1, 1]], expected=4, label="example 1"
        ),
        TestCase(
            input=[[2, 1, 1], [0, 1, 1], [1, 0, 1]], expected=-1, label="example 2"
        ),
        TestCase(input=[[0, 2]], expected=0, label="no fresh"),
        TestCase(input=[[1]], expected=-1, label="single fresh no rotten"),
        TestCase(input=[[2]], expected=0, label="single rotten"),
        TestCase(
            input=[[1, 1, 1], [1, 1, 1], [1, 1, 1]],
            expected=-1,
            label="all fresh no rotten",
        ),
        TestCase(
            input=[[2, 2], [1, 1], [0, 1]],
            expected=2,
            label="multiple rotten sources",
        ),
    ]

    def solve(self, grid: list[list[int]]) -> int:
        raise NotImplementedError(
            "TODO: Implement solve(self, grid: list[list[int]]) -> int"
        )


if __name__ == "__main__":
    Solution().run()
