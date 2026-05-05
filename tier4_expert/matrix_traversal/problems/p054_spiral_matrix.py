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
        raise NotImplementedError("TODO: Implement solve(self, matrix: list[list[int]]) -> list[int]")

if __name__ == "__main__":
    Solution().run()
