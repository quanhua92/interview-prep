"""P084: Largest Rectangle in Histogram (Hard)

TODO: Implement solve() below.
Hint: Use a monotonic increasing stack with a sentinel to compute max rectangle area.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "84. Largest Rectangle in Histogram"
    test_cases = [
        TestCase(input=[2,1,5,6,2,3], expected=10, label="example 1"),
        TestCase(input=[2,4], expected=4, label="example 2"),
    ]

    def solve(self, heights: list[int]) -> int:
        raise NotImplementedError("TODO: Implement solve(self, heights: list[int]) -> int")

if __name__ == "__main__":
    Solution().run()
