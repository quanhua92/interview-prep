"""P1091: Shortest Path in Binary Matrix (Medium)

TODO: Implement solve() below.
Hint: BFS from (0,0) with 8 directions, return distance to (n-1,n-1) or -1.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "1091. Shortest Path in Binary Matrix"
    test_cases = [
        TestCase(input=[[0, 1], [1, 0]], expected=2, label="example 1"),
        TestCase(input=[[0, 0, 0], [1, 1, 0], [1, 1, 0]], expected=4, label="example 2"),
        TestCase(input=[[1, 0], [0, 1]], expected=-1, label="blocked"),
        TestCase(input=[[0]], expected=1, label="single cell"),
    ]

    def solve(self, grid: list[list[int]]) -> int:
        raise NotImplementedError("TODO: Implement solve(self, grid: list[list[int]]) -> int")


if __name__ == "__main__":
    Solution().run()
