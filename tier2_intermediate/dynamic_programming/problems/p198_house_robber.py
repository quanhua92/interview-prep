"""P198: House Robber (Medium)

TODO: Implement solve() below.
Hint: Use two variables (prev, curr) -- for each house decide to rob or skip.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "198. House Robber"
    test_cases = [
        TestCase(input=[1,2,3,1], expected=4, label="example 1"),
        TestCase(input=[2,7,9,3,1], expected=12, label="example 2"),
        TestCase(input=[1], expected=1, label="single house"),
        TestCase(input=[], expected=0, label="no houses"),
    ]

    def solve(self, nums: list[int]) -> int:
        raise NotImplementedError("TODO: Implement solve(self, nums: list[int]) -> int")


if __name__ == "__main__":
    Solution().run()
