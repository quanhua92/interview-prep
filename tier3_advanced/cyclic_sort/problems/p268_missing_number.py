"""P268: Missing Number (Easy)

TODO: Implement solve() below.
Hint: Use the sum formula n*(n+1)//2 minus the actual sum to find the missing number.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "268. Missing Number"
    test_cases = [
        TestCase(input=[3,0,1], expected=2, label="example 1"),
        TestCase(input=[0,1], expected=2, label="example 2"),
        TestCase(input=[9,6,4,2,3,5,7,0,1], expected=8, label="example 3"),
    ]

    def solve(self, nums: list[int]) -> int:
        raise NotImplementedError("TODO: Implement solve(self, nums: list[int]) -> int")

if __name__ == "__main__":
    Solution().run()
