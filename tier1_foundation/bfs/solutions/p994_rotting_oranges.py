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

from src.wasm_libs.py.io import *
from collections import deque


def solve(grid: list[list[int]]) -> int:
    rows, cols = len(grid), len(grid[0])
    queue: deque[tuple[int, int]] = deque()
    fresh = 0
    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == 2:
                queue.append((r, c))
            elif grid[r][c] == 1:
                fresh += 1
    if fresh == 0:
        return 0
    minutes = 0
    directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
    while queue:
        for _ in range(len(queue)):
            r, c = queue.popleft()
            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] == 1:
                    grid[nr][nc] = 2
                    fresh -= 1
                    queue.append((nr, nc))
        if queue:
            minutes += 1
    return minutes if fresh == 0 else -1


if __name__ == "__main__":
    _cols = read_int()
    grid = []
    while True:
        try:
            row = read_ints()
            if not row:
                break
            grid.append(row)
        except EOFError:
            break
    result = solve(grid)
    write_int(result)
