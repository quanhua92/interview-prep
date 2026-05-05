"""P695: Max Area of Island (Medium)

TODO: Implement solve() below.
Hint: Use DFS to explore each island and track the maximum area found.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "695. Max Area of Island"
    test_cases = [
        TestCase(input=[[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]], expected=6, label="example 1"),
        TestCase(input=[[0,0,0,0,0,0,0,0]], expected=0, label="example 2"),
    ]

    def solve(self, grid: list[list[int]]) -> int:
        raise NotImplementedError("TODO: Implement solve(self, grid: list[list[int]]) -> int")

if __name__ == "__main__":
    Solution().run()
