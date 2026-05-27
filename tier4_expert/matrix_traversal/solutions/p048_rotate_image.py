"""
P48: Rotate Image (Medium)
https://leetcode.com/problems/rotate-image/
Topics: Array, Math, Matrix

You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).
You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.

Example 1:
    Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
    Output: [[7,4,1],[8,5,2],[9,6,3]]

Example 2:
    Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
    Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]

Constraints:
    - n == matrix.length == matrix[i].length
    - 1 <= n <= 20
    - -1000 <= matrix[i][j] <= 1000

Template (python3):
    class Solution:
        def rotate(self, matrix: List[List[int]]) -> None:
            \'\'\'
            Do not return anything, modify matrix in-place instead.
            \'\'\'

Hint: Transpose the matrix first, then reverse each row.
"""

from src.wasm_libs.py.io import *


def solve(matrix: list[list[int]]) -> list[list[int]]:
    n = len(matrix)
    for i in range(n):
        for j in range(i + 1, n):
            matrix[i][j], matrix[j][i] = matrix[j][i], matrix[i][j]
    for row in matrix:
        row.reverse()
    return matrix


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
    matrix = read_int_matrix()
    result = solve(matrix)
    write_matrix(result)
