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

from src.wasm_libs.py.io import read_ints, write_int


def main():
    meta = read_ints()
    rows, cols = meta[0], meta[1]
    if rows == 0 or cols == 0:
        write_int(0)
        return
    grid = [read_ints() for _ in range(rows)]
    max_area = 0

    def dfs(r, c):
        if r < 0 or r >= rows or c < 0 or c >= cols or grid[r][c] != 1:
            return 0
        grid[r][c] = 0
        return 1 + dfs(r + 1, c) + dfs(r - 1, c) + dfs(r, c + 1) + dfs(r, c - 1)

    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == 1:
                max_area = max(max_area, dfs(r, c))
    write_int(max_area)


if __name__ == "__main__":
    main()
