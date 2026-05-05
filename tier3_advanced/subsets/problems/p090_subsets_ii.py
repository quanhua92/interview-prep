"""P090: Subsets II (Medium)

TODO: Implement solve() below.
Hint: Sort first, then skip duplicates at the same recursion level during backtracking.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "90. Subsets II"
    test_cases = [
        TestCase(input=[1,2,2], expected=[[],[1],[1,2],[1,2,2],[2],[2,2]], label="example 1"),
        TestCase(input=[0], expected=[[],[0]], label="example 2"),
    ]

    def solve(self, nums: list[int]) -> list[list[int]]:
        raise NotImplementedError("TODO: Implement solve(self, nums: list[int]) -> list[list[int]]")

if __name__ == "__main__":
    Solution().run()
