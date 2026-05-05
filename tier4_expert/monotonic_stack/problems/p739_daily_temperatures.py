"""P739: Daily Temperatures (Medium)

TODO: Implement solve() below.
Hint: Use a monotonic decreasing stack to track indices of warmer days.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "739. Daily Temperatures"
    test_cases = [
        TestCase(input=[73,74,75,71,69,72,76,73], expected=[1,1,4,2,1,1,0,0], label="example 1"),
        TestCase(input=[30,40,50,60], expected=[1,1,1,0], label="example 2"),
        TestCase(input=[30,60,90], expected=[1,1,0], label="example 3"),
    ]

    def solve(self, temperatures: list[int]) -> list[int]:
        raise NotImplementedError("TODO: Implement solve(self, temperatures: list[int]) -> list[int]")

if __name__ == "__main__":
    Solution().run()
