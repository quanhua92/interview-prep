"""
P695: Max Area of Island (Medium)
https://leetcode.com/problems/max-area-of-island/
Topics: Array, Depth-First Search, Breadth-First Search, Union Find, Matrix

You are given an m x n binary matrix grid. Return the maximum area of an island.

Example 1:
    Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
    Output: 6

Example 2:
    Input: grid = [[0,0,0,0,0,0,0,0]]
    Output: 0

Constraints:
    - m == grid.length
    - n == grid[i].length
    - 1 <= m, n <= 50

Template (python3):
    class Solution:
        def maxAreaOfIsland(self, grid: List[List[int]]) -> int:

Hint: Use DFS to explore each island and track the maximum area found.
"""

from src.wasm_libs.py.io import *


def solve(grid: list[list[int]]) -> int:
    raise NotImplementedError


if __name__ == "__main__":
    meta = read_ints()
    rows, cols = meta[0], meta[1]
    grid = [read_ints() for _ in range(rows)]
    result = solve(grid)
    write_int(result)
