"""P153: Find Minimum in Rotated Sorted Array (Medium)

TODO: Implement solve() below.
Hint: Compare mid element with the rightmost to decide which half contains the minimum.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "153. Find Minimum in Rotated Sorted Array"
    test_cases = [
        TestCase(input=[3,4,5,1,2], expected=1, label="example 1"),
        TestCase(input=[4,5,6,7,0,1,2], expected=0, label="example 2"),
        TestCase(input=[1], expected=1, label="single element"),
    ]

    def solve(self, nums: list[int]) -> int:
        raise NotImplementedError("TODO: Implement solve(self, nums: list[int]) -> int")

if __name__ == "__main__":
    Solution().run()
