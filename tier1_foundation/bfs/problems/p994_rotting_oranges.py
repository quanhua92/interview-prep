"""P994: Rotting Oranges (Medium)

TODO: Implement solve() below.
Hint: Use BFS starting from all rotten oranges simultaneously.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase
from collections import deque


class Solution(Problem):
    name = "994. Rotting Oranges"
    test_cases = [
        TestCase(input=[[2,1,1],[1,1,0],[0,1,1]], expected=4, label="example 1"),
        TestCase(input=[[2,1,1],[0,1,1],[1,0,1]], expected=-1, label="example 2"),
        TestCase(input=[[0,2]], expected=0, label="no fresh"),
    ]

    def solve(self, grid: list[list[int]]) -> int:
        raise NotImplementedError("TODO: Implement solve(self, grid: list[list[int]]) -> int")


if __name__ == "__main__":
    Solution().run()
