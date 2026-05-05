"""P253: Meeting Rooms II (Medium)

TODO: Implement solve() below.
Hint: Sort start and end times separately, then use two pointers to count concurrent meetings.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "253. Meeting Rooms II"
    test_cases = [
        TestCase(input=[[0,30],[5,10],[15,20]], expected=2, label="example 1"),
        TestCase(input=[[7,10],[2,4]], expected=1, label="example 2"),
        TestCase(input=[], expected=0, label="no meetings"),
    ]

    def solve(self, intervals: list[list[int]]) -> int:
        raise NotImplementedError("TODO: Implement solve(self, intervals: list[list[int]]) -> int")


if __name__ == "__main__":
    Solution().run()
