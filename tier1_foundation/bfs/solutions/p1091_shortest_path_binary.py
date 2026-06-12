"""
P1091: Shortest Path in Binary Matrix (Medium)
https://leetcode.com/problems/shortest-path-in-binary-matrix/
Topics: Array, Breadth-First Search, Matrix

Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. If there is no clear path, return -1.
A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:
- All the cells in the binary matrix are either 0 (walkable) or 1 (blocked).
- All the visited cells of the path are 0.
- All the adjacent cells of the path are 8-directionally connected (i.e., they are different and they share an edge or a corner).
The length of a clear path is the number of visited cells of this path.

Example 1:
    Input: grid = [[0,1],[1,0]]
    Output: 2

Example 2:
    Input: grid = [[0,0,0],[1,1,0],[1,1,0]]
    Output: 4

Example 3:
    Input: grid = [[1,0,0],[1,1,0],[1,1,0]]
    Output: -1

Constraints:
    - n == grid.length
    - n == grid[i].length
    - 1 <= n <= 100
    - grid[i][j] is 0 or 1

Hints:
    - Do a breadth first search to find the shortest path.

Template (python3):
    class Solution:
        def shortestPathBinaryMatrix(self, grid: List[List[int]]) -> int:

Hint: BFS from (0,0) with 8 directions, return distance to (n-1,n-1) or -1.
"""

from src.wasm_libs.py.io import *
from collections import deque


def solve(grid: list[list[int]]) -> int:
    n = len(grid)
    if grid[0][0] == 1 or grid[n - 1][n - 1] == 1:
        return -1
    if n == 1:
        return 1
    directions = [
        (-1, -1), (-1, 0), (-1, 1),
        (0, -1), (0, 1),
        (1, -1), (1, 0), (1, 1),
    ]
    queue = deque([(0, 0, 1)])
    grid[0][0] = 1
    while queue:
        row, col, dist = queue.popleft()
        for dr, dc in directions:
            nr, nc = row + dr, col + dc
            if 0 <= nr < n and 0 <= nc < n and grid[nr][nc] == 0:
                if nr == n - 1 and nc == n - 1:
                    return dist + 1
                grid[nr][nc] = 1
                queue.append((nr, nc, dist + 1))
    return -1


if __name__ == "__main__":
    _n = read_int()
    grid = []
    while True:
        row = read_ints()
        if not row:
            break
        grid.append(row)
    result = solve(grid)
    write_int(result)
