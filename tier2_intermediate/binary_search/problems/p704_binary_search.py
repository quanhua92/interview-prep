"""P704: Binary Search (Easy)

TODO: Implement solve() below.
Hint: Use the classic binary search pattern with left and right pointers.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "704. Binary Search"
    test_cases = [
        TestCase(input=([-1,0,3,5,9,12], 9), expected=4, label="example 1"),
        TestCase(input=([-1,0,3,5,9,12], 2), expected=-1, label="example 2"),
        TestCase(input=([5], 5), expected=0, label="single element"),
    ]

    def solve(self, nums: list[int], target: int) -> int:
        raise NotImplementedError("TODO: Implement solve(self, nums: list[int], target: int) -> int")

if __name__ == "__main__":
    Solution().run()
