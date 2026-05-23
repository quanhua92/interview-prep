"""
P200: Number of Islands (Medium)
https://leetcode.com/problems/number-of-islands/
Topics: Array, Depth-First Search, Breadth-First Search, Union Find, Matrix

Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example 1:
    Input: grid = [
      ["1","1","1","1","0"],
      ["1","1","0","1","0"],
      ["1","1","0","0","0"],
      ["0","0","0","0","0"]
    ]
    Output: 1

Example 2:
    Input: grid = [
      ["1","1","0","0","0"],
      ["1","1","0","0","0"],
      ["0","0","1","0","0"],
      ["0","0","0","1","1"]
    ]
    Output: 3

Constraints:
    - m == grid.length
    - n == grid[i].length
    - 1 <= m, n <= 300
    - grid[i][j] is '0' or '1'.

Template (python3):
    class Solution:
        def numIslands(self, grid: List[List[str]]) -> int:

Hint: Use DFS to mark visited land cells, counting each new island.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "200. Number of Islands"
    test_cases = [
        TestCase(
            input=[
                ["1", "1", "1", "1", "0"],
                ["1", "1", "0", "1", "0"],
                ["1", "1", "0", "0", "0"],
                ["0", "0", "0", "0", "0"],
            ],
            expected=1,
            label="example 1",
        ),
        TestCase(
            input=[
                ["1", "1", "0", "0", "0"],
                ["1", "1", "0", "0", "0"],
                ["0", "0", "1", "0", "0"],
                ["0", "0", "0", "1", "1"],
            ],
            expected=3,
            label="example 2",
        ),
        TestCase(
            input=[
                [],
            ],
            expected=0,
            label="empty grid",
        ),
        TestCase(
            input=[
                ["0"],
            ],
            expected=0,
            label="single cell water",
        ),
        TestCase(
            input=[
                ["1"],
            ],
            expected=1,
            label="single cell land",
        ),
        TestCase(
            input=[
                ["1", "0", "1", "0", "1"],
            ],
            expected=3,
            label="single row",
        ),
        TestCase(
            input=[
                ["1"],
                ["0"],
                ["1"],
                ["0"],
                ["1"],
            ],
            expected=3,
            label="single column",
        ),
        TestCase(
            input=[
                ["1", "1", "1"],
                ["1", "1", "1"],
                ["1", "1", "1"],
            ],
            expected=1,
            label="all land 3x3",
        ),
    ]

    def solve(self, grid: list[list[str]]) -> int:
        if not grid or not grid[0]:
            return 0
        rows, cols = len(grid), len(grid[0])
        count = 0

        def dfs(r: int, c: int):
            if r < 0 or r >= rows or c < 0 or c >= cols or grid[r][c] != "1":
                return
            grid[r][c] = "0"
            dfs(r + 1, c)
            dfs(r - 1, c)
            dfs(r, c + 1)
            dfs(r, c - 1)

        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == "1":
                    count += 1
                    dfs(r, c)
        return count


if __name__ == "__main__":
    Solution().run()
