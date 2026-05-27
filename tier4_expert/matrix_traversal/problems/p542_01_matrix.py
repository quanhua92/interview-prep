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
    - 1 <= m, n <= 104
    - 1 <= m * n <= 104
    - mat[i][j] is either 0 or 1.
    - There is at least one 0 in mat.

Template (python3):
    class Solution:
        def updateMatrix(self, mat: List[List[int]]) -> List[List[int]]:
"""

from src.wasm_libs.py.io import *


def solve(mat: list[list[int]]) -> list[list[int]]:
    raise NotImplementedError


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
