"""P498: Diagonal Traverse (Medium)

TODO: Implement solve() below.
Hint: Group by i+j diagonal index. If d is even, reverse to simulate up-right direction.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "498. Diagonal Traverse"
    test_cases = [
        TestCase(input=[[1,2,3],[4,5,6],[7,8,9]], expected=[1,2,4,7,5,3,6,8,9], label="example 1"),
        TestCase(input=[[1,2],[3,4],[5,6]], expected=[1,2,3,5,4,6], label="example 2"),
        TestCase(input=[[1]], expected=[1], label="single element"),
    ]

    def solve(self, mat: list[list[int]]) -> list[int]:
        raise NotImplementedError("TODO: Implement solve(self, mat: list[list[int]]) -> list[int]")


if __name__ == "__main__":
    Solution().run()
