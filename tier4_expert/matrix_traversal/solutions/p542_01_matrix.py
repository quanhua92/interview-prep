"""
P542: 01 Matrix [PREMIUM] (Medium)
https://leetcode.com/problems/01-matrix/
Topics: Array, Dynamic Programming, Breadth-First Search, Matrix

Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.
The distance between two cells sharing a common edge is 1.
Example 2:
Note: This question is the same as 1765: https://leetcode.com/problems/map-of-highest-peak/
Example 1:
    Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
    Output: [[0,0,0],[0,1,0],[0,0,0]]

Example 2:
    Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
    Output: [[0,0,0],[0,1,0],[1,2,1]]

Constraints:
    - m == mat.length
    - n == mat[i].length
    - 1 <= m, n <= 10^4
    - 1 <= m * n <= 10^4
    - mat[i][j] is either 0 or 1.
    - There is at least one 0 in mat.

Template (python3):
    class Solution:
        def updateMatrix(self, mat: List[List[int]]) -> List[List[int]]:
"""

from collections import deque

from src.wasm_libs.py.io import *


def solve(mat: list[list[int]]) -> list[list[int]]:
    m, n = len(mat), len(mat[0])
    dist = [[0] * n for _ in range(m)]
    queue: deque[tuple[int, int]] = deque()
    for r in range(m):
        for c in range(n):
            if mat[r][c] == 0:
                queue.append((r, c))
            else:
                dist[r][c] = -1
    dirs = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    while queue:
        r, c = queue.popleft()
        for dr, dc in dirs:
            nr, nc = r + dr, c + dc
            if 0 <= nr < m and 0 <= nc < n and dist[nr][nc] == -1:
                dist[nr][nc] = dist[r][c] + 1
                queue.append((nr, nc))
    return dist


def read_int_matrix():
    import sys

    read_int()
    remaining = sys.stdin.read().strip().split("\n")
    if not remaining or not remaining[0].strip():
        return []
    return [list(map(int, line.split())) for line in remaining]


def write_matrix(mat: list[list[int]]):
    for row in mat:
        write_ints(row)


if __name__ == "__main__":
    mat = read_int_matrix()
    result = solve(mat)
    write_matrix(result)
