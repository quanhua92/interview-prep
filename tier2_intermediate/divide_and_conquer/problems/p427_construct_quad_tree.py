"""
P427: Construct Quad Tree [PREMIUM] (Medium)
https://leetcode.com/problems/construct-quad-tree/
Topics: Array, Divide and Conquer, Tree, Matrix

Given a n * n matrix grid of 0's and 1's only. We want to represent grid with a Quad-Tree.
Return the root of the Quad-Tree representing grid.

Example 1:
    Input: grid = [[0,1],[1,0]]
    Output: [[0,1],[1,0],[1,1],[1,1],[1,0]]

Constraints:
    - n == grid.length == grid[i].length
    - n == 2x where 0 <= x <= 6

Hint: Recursively divide grid into 4 quadrants, make leaf if all same value.
"""

from src.wasm_libs.py.io import *


def solve(grid: list[list[int]]):
    raise NotImplementedError


if __name__ == "__main__":
    cols = read_int()
    grid = []
    for _ in range(cols):
        grid.append(read_ints())
    solve(grid)
