"""P912: Sort an Array (Medium)

TODO: Implement solve() below.
Hint: Implement merge sort — divide array in half, sort recursively, merge.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "912. Sort an Array"
    test_cases = [
        TestCase(input=[5,2,3,1], expected=[1,2,3,5], label="example 1"),
        TestCase(input=[5,1,1,2,0,0], expected=[0,0,1,1,2,5], label="duplicates"),
        TestCase(input=[1], expected=[1], label="single element"),
        TestCase(input=[], expected=[], label="empty array"),
    ]

    def solve(self, nums: list[int]) -> list[int]:
        raise NotImplementedError("TODO: Implement solve(self, nums: list[int]) -> list[int]")

if __name__ == "__main__":
    Solution().run()
