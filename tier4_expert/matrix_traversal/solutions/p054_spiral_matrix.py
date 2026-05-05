"""P054: Spiral Matrix (Medium)

TODO: Implement solve() below.
Hint: Use four boundary pointers (top, bottom, left, right) and shrink them as you traverse.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "54. Spiral Matrix"
    test_cases = [
        TestCase(input=[[1,2,3],[4,5,6],[7,8,9]], expected=[1,2,3,6,9,8,7,4,5], label="example 1"),
        TestCase(input=[[1,2,3,4],[5,6,7,8],[9,10,11,12]], expected=[1,2,3,4,8,12,11,10,9,5,6,7], label="example 2"),
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
