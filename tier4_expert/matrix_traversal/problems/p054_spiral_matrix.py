"""
P54: Spiral Matrix (Medium)
https://leetcode.com/problems/spiral-matrix/
Topics: Array, Matrix, Simulation

Given an m x n matrix, return all elements of the matrix in spiral order.

Example 1:
    Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
    Output: [1,2,3,6,9,8,7,4,5]

Example 2:
    Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
    Output: [1,2,3,4,8,12,11,10,9,5,6,7]

Constraints:
    - m == matrix.length
    - n == matrix[i].length
    - 1 <= m, n <= 10
    - -100 <= matrix[i][j] <= 100

Hints:
    - Well for some problems, the best way really is to come up with some algorithms for simulation. Basically, you need to simulate what the problem asks us to do.
    - We go boundary by boundary and move inwards. That is the essential operation. First row, last column, last row, first column, and then we move inwards by 1 and repeat. That's all. That is all the simulation that we need.
    - Think about when you want to switch the progress on one of the indexes. If you progress on i out of [i, j], you'll shift in the same column. Similarly, by changing values for j, you'd be shifting in the same row.
Also, keep track of the end of a boundary so that you can move inwards and then keep repeating. It's always best to simulate edge cases like a single column or a single row to see if anything breaks or not.

Template (python3):
    class Solution:
        def spiralOrder(self, matrix: List[List[int]]) -> List[int]:

Hint: Use four boundary pointers (top, bottom, left, right) and shrink them as you traverse.
"""

from src.wasm_libs.py.io import *


def solve(matrix: list[list[int]]) -> list[int]:
    raise NotImplementedError


def read_int_matrix():
    import sys

    read_int()
    remaining = sys.stdin.read().strip().split("\n")
    if not remaining or not remaining[0].strip():
        return []
    return [list(map(int, line.split())) for line in remaining]


if __name__ == "__main__":
    matrix = read_int_matrix()
    result = solve(matrix)
    write_ints(result)
