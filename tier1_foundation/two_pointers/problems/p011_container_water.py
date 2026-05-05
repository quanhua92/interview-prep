"""P011: Container With Most Water (Medium)

TODO: Implement solve() below.
Hint: Start with pointers at both ends and move the shorter one inward.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "11. Container With Most Water"
    test_cases = [
        TestCase(input=[1, 8, 6, 2, 5, 4, 8, 3, 7], expected=49, label="example 1"),
        TestCase(input=[1, 1], expected=1, label="example 2"),
        TestCase(input=[4, 3, 2, 1, 4], expected=16, label="symmetric"),
    ]

    def solve(self, height: list[int]) -> int:
        raise NotImplementedError("TODO: Implement solve(self, height: list[int]) -> int")


if __name__ == "__main__":
    Solution().run()
