"""P015: 3Sum (Medium)

TODO: Implement solve() below.
Hint: Sort, iterate i, nested two pointers for remaining pair, skip duplicates.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "15. 3Sum"
    test_cases = [
        TestCase(input=[-1, 0, 1, 2, -1, -4], expected=sorted([sorted(t) for t in [[-1, -1, 2], [-1, 0, 1]]]), label="example 1"),
        TestCase(input=[0, 1, 1], expected=[], label="no triplets"),
        TestCase(input=[0, 0, 0], expected=[[0, 0, 0]], label="all zeros"),
        TestCase(input=[], expected=[], label="empty"),
    ]

    def solve(self, nums: list[int]) -> list[list[int]]:
        raise NotImplementedError("TODO: Implement solve(self, nums: list[int]) -> list[list[int]]")


if __name__ == "__main__":
    Solution().run()
