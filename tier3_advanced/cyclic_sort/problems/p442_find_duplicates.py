"""P442: Find All Duplicates in an Array (Medium)

TODO: Implement solve() below.
Hint: Negate the value at index abs(num)-1 to mark seen numbers in-place.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "442. Find All Duplicates in an Array"
    test_cases = [
        TestCase(input=[4,3,2,7,8,2,3,1], expected=[2,3], label="example 1"),
        TestCase(input=[1,1,2], expected=[1], label="example 2"),
        TestCase(input=[1], expected=[], label="single"),
    ]

    def solve(self, nums: list[int]) -> list[int]:
        raise NotImplementedError("TODO: Implement solve(self, nums: list[int]) -> list[int]")

if __name__ == "__main__":
    Solution().run()
