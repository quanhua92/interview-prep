"""
P498: Diagonal Traverse (Medium)
https://leetcode.com/problems/diagonal-traverse/
Topics: Array, Matrix, Simulation

Given an m x n matrix mat, return an array of all the elements of the array in a diagonal order.

Example 1:
    Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
    Output: [1,2,4,7,5,3,6,8,9]

Example 2:
    Input: mat = [[1,2],[3,4]]
    Output: [1,2,3,4]

Constraints:
    - m == mat.length
    - n == mat[i].length
    - 1 <= m, n <= 104
    - 1 <= m * n <= 104
    - -105 <= mat[i][j] <= 105

Template (python3):
    class Solution:
        def findDiagonalOrder(self, mat: List[List[int]]) -> List[int]:

Hint: Group by i+j diagonal index. If d is even, reverse to simulate up-right direction.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "498. Diagonal Traverse"
    test_cases = [
        TestCase(
            input=[[1, 2, 3], [4, 5, 6], [7, 8, 9]],
            expected=[1, 2, 4, 7, 5, 3, 6, 8, 9],
            label="example 1",
        ),
        TestCase(
            input=[[1, 2], [3, 4], [5, 6]],
            expected=[1, 2, 3, 5, 4, 6],
            label="example 2",
        ),
        TestCase(input=[[1]], expected=[1], label="single element"),
        TestCase(
            input=[[1, 2, 3, 4]],
            expected=[1, 2, 3, 4],
            label="single row",
        ),
        TestCase(
            input=[[1], [2], [3], [4]],
            expected=[1, 2, 3, 4],
            label="single column",
        ),
        TestCase(
            input=[[1, 2, 3, 4], [5, 6, 7, 8]],
            expected=[1, 2, 5, 6, 3, 4, 7, 8],
            label="2x4 rectangular",
        ),
        TestCase(
            input=[[-1, -2], [3, 4]],
            expected=[-1, -2, 3, 4],
            label="negative values 2x2",
        ),
    ]

    def solve(self, mat: list[list[int]]) -> list[int]:
        raise NotImplementedError(
            "TODO: Implement solve(self, mat: list[list[int]]) -> list[int]"
        )


if __name__ == "__main__":
    Solution().run()
