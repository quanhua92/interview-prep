"""
P463: Island Perimeter [PREMIUM] (Easy)
https://leetcode.com/problems/island-perimeter/
Topics: Array, Depth-First Search, Breadth-First Search, Matrix

You are given row x col grid representing a map where grid[i][j] = 1 represents land and grid[i][j] = 0 represents water.
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

from src.wasm_libs.py.io import *
from collections import deque


def solve(grid: list[list[int]]) -> int:
    rows, cols = len(grid), len(grid[0])
    visited = set()
    perimeter = 0
    directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == 1:
                queue = deque([(r, c)])
                visited.add((r, c))
                while queue:
                    cr, cc = queue.popleft()
                    for dr, dc in directions:
                        nr, nc = cr + dr, cc + dc
                        if nr < 0 or nr >= rows or nc < 0 or nc >= cols or grid[nr][nc] == 0:
                            perimeter += 1
                        elif (nr, nc) not in visited:
                            visited.add((nr, nc))
                            queue.append((nr, nc))
                return perimeter
    return 0


# Alternative Solution: O(1) Space
# Instead of BFS with a visited set, count contributions per land cell.
# Each land cell contributes 4 to the perimeter, minus 2 for each shared edge
# with the cell to its right or below (avoids double-counting).
def solve_o1(grid: list[list[int]]) -> int:
    perimeter = 0
    rows, cols = len(grid), len(grid[0])
    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == 0:
                continue
            base_perimeter = 4
            if c + 1 < cols and grid[r][c + 1] == 1:
                base_perimeter -= 2
            if r + 1 < rows and grid[r + 1][c] == 1:
                base_perimeter -= 2
            perimeter += base_perimeter
    return perimeter


if __name__ == "__main__":
    _cols = read_int()
    grid = []
    while True:
        row = read_ints()
        if not row:
            break
        grid.append(row)
    result = solve(grid)
    write_int(result)
