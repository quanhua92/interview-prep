"""P907: Sum of Subarray Minimums (Medium)

TODO: Implement solve() below.
Hint: Use a monotonic stack to find the number of subarrays where each element is the minimum.
For each element, find the previous smaller and next smaller element boundaries.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "907. Sum of Subarray Minimums"
    test_cases = [
        TestCase(input=[3,1,2,4], expected=17, label="example 1"),
        TestCase(input=[11,81,94,43,3], expected=444, label="example 2"),
        TestCase(input=[1], expected=1, label="single element"),
    ]

    def solve(self, arr: list[int]) -> int:
        raise NotImplementedError("TODO: Implement solve(self, arr: list[int]) -> int")

if __name__ == "__main__":
    Solution().run()
