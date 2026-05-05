"""P200: Number of Islands (Medium)

TODO: Implement solve() below.
Hint: Use DFS to mark visited land cells, counting each new island.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "200. Number of Islands"
    test_cases = [
        TestCase(input=[["1","1","1","1","0"],["1","1","0","1","0"],["1","1","0","0","0"],["0","0","0","0","0"]], expected=1, label="example 1"),
        TestCase(input=[["1","1","0","0","0"],["1","1","0","0","0"],["0","0","1","0","0"],["0","0","0","1","1"]], expected=3, label="example 2"),
        TestCase(input=[[],], expected=0, label="empty grid"),
    ]

    def solve(self, grid: list[list[str]]) -> int:
        raise NotImplementedError("TODO: Implement solve(self, grid: list[list[str]]) -> int")

if __name__ == "__main__":
    Solution().run()
