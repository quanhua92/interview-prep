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

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "54. Spiral Matrix"
    test_cases = [
        TestCase(
            input=[[1, 2, 3], [4, 5, 6], [7, 8, 9]],
            expected=[1, 2, 3, 6, 9, 8, 7, 4, 5],
            label="example 1",
        ),
        TestCase(
            input=[[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]],
            expected=[1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7],
            label="example 2",
        ),
        TestCase(input=[[7]], expected=[7], label="single element"),
    ]

    def solve(self, matrix: list[list[int]]) -> list[int]:
        if not matrix or not matrix[0]:
            return []
        result: list[int] = []
        top, bottom = 0, len(matrix) - 1
        left, right = 0, len(matrix[0]) - 1
        while top <= bottom and left <= right:
            for c in range(left, right + 1):
                result.append(matrix[top][c])
            top += 1
            for r in range(top, bottom + 1):
                result.append(matrix[r][right])
            right -= 1
            if top <= bottom:
                for c in range(right, left - 1, -1):
                    result.append(matrix[bottom][c])
                bottom -= 1
            if left <= right:
                for r in range(bottom, top - 1, -1):
                    result.append(matrix[r][left])
                left += 1
        return result


if __name__ == "__main__":
    Solution().run()
