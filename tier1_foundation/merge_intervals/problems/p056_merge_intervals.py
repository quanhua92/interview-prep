"""P056: Merge Intervals (Medium)

TODO: Implement solve() below.
Hint: Sort intervals by start time, then merge overlapping ones.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "56. Merge Intervals"
    test_cases = [
        TestCase(input=[[1,3],[2,6],[8,10],[15,18]], expected=[[1,6],[8,10],[15,18]], label="example 1"),
        TestCase(input=[[1,4],[4,5]], expected=[[1,5]], label="example 2"),
        TestCase(input=[[1,4],[0,4]], expected=[[0,4]], label="overlapping start"),
    ]

    def solve(self, intervals: list[list[int]]) -> list[list[int]]:
        raise NotImplementedError("TODO: Implement solve(self, intervals: list[list[int]]) -> list[list[int]]")


if __name__ == "__main__":
    Solution().run()
