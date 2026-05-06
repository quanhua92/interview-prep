"""
P463: Island Perimeter [PREMIUM] (Easy)
https://leetcode.com/problems/island-perimeter/
Topics: Array, Depth-First Search, Breadth-First Search, Matrix

You are given row x col grid representing a map where grid[i][j] = 1 represents land and grid[i][j] = 0 represents water.
Grid cells are connected horizontally/vertically (not diagonally). The grid is completely surrounded by water, and there is exactly one island (i.e., one or more connected land cells).
The island doesn't have "lakes", meaning the water inside isn't connected to the water around the island. One cell is a square with side length 1. The grid is rectangular, width and height don't exceed 100. Determine the perimeter of the island.
Example 1:
    Input: grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
    Output: 16
    Explanation: The perimeter is the 16 yellow stripes in the image above.

Example 2:
    Input: grid = [[1]]
    Output: 4

Example 3:
    Input: grid = [[1,0]]
    Output: 4

Constraints:
    - row == grid.length
    - col == grid[i].length
    - 1 <= row, col <= 100
    - grid[i][j] is 0 or 1.
    - There is exactly one island in grid.

Template (python3):
    class Solution:
        def islandPerimeter(self, grid: List[List[int]]) -> int:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "463. Island Perimeter"
    test_cases = [
        TestCase(
            input=[[0, 1, 0, 0], [1, 1, 1, 0], [0, 1, 0, 0], [1, 1, 0, 0]],
            expected=16,
            label="example 1",
        ),
        TestCase(input=[[1]], expected=4, label="example 2"),
        TestCase(input=[[1, 0]], expected=4, label="example 3"),
    ]

    def solve(self, grid: list[list[int]]) -> int:
        raise NotImplementedError("TODO: Implement solve(self, grid) -> int")


if __name__ == "__main__":
    Solution().run()
