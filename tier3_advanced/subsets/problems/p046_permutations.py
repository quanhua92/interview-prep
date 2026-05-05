"""P046: Permutations (Medium)

TODO: Implement solve() below.
Hint: Use backtracking with swapping to generate all permutations in-place.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "46. Permutations"
    test_cases = [
        TestCase(input=[1,2,3], expected=[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]], label="example 1"),
        TestCase(input=[0,1], expected=[[0,1],[1,0]], label="example 2"),
        TestCase(input=[1], expected=[[1]], label="single element"),
    ]

    def solve(self, nums: list[int]) -> list[list[int]]:
        raise NotImplementedError("TODO: Implement solve(self, nums: list[int]) -> list[list[int]]")

if __name__ == "__main__":
    Solution().run()
