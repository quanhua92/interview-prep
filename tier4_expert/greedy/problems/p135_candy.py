"""P135: Candy (Hard)

TODO: Implement solve() below.
Hint: Two-pass greedy: left-to-right then right-to-left, taking the max of both passes.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "135. Candy"
    test_cases = [
        TestCase(input=[1,0,2], expected=5, label="example 1"),
        TestCase(input=[1,2,2], expected=4, label="example 2"),
        TestCase(input=[1,3,2,2,1], expected=7, label="decreasing then flat"),
        TestCase(input=[1], expected=1, label="single child"),
    ]

    def solve(self, ratings: list[int]) -> int:
        raise NotImplementedError("TODO: Implement solve(self, ratings: list[int]) -> int")

if __name__ == "__main__":
    Solution().run()
