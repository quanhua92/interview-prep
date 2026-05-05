"""P057: Insert Interval (Medium)

TODO: Implement solve() below.
Hint: Add non-overlapping before, merge overlapping, add non-overlapping after.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "57. Insert Interval"
    test_cases = [
        TestCase(input=([[1, 3], [6, 9]], [2, 5]), expected=[[1, 5], [6, 9]], label="example 1"),
        TestCase(input=([[1, 2], [3, 5], [6, 7], [8, 10], [12, 16]], [4, 8]), expected=[[1, 2], [3, 10], [12, 16]], label="example 2"),
        TestCase(input=([], [5, 7]), expected=[[5, 7]], label="empty intervals"),
        TestCase(input=([[1, 5]], [2, 3]), expected=[[1, 5]], label="contained"),
    ]

    def solve(self, intervals: list[list[int]], new_interval: list[int]) -> list[list[int]]:
        raise NotImplementedError("TODO: Implement solve(self, intervals: list[list[int]], new_interval: list[int]) -> list[list[int]]")


if __name__ == "__main__":
    Solution().run()
