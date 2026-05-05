"""P055: Jump Game (Medium)

TODO: Implement solve() below.
Hint: Track the farthest reachable index; if you pass it, the end is unreachable.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "55. Jump Game"
    test_cases = [
        TestCase(input=[2,3,1,1,4], expected=True, label="example 1"),
        TestCase(input=[3,2,1,0,4], expected=False, label="example 2"),
        TestCase(input=[0], expected=True, label="single element"),
    ]

    def solve(self, nums: list[int]) -> bool:
        raise NotImplementedError("TODO: Implement solve(self, nums: list[int]) -> bool")

if __name__ == "__main__":
    Solution().run()
