"""P136: Single Number (Easy)

TODO: Implement solve() below.
Hint: XOR all numbers — pairs cancel out, leaving the single number.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "136. Single Number"
    test_cases = [
        TestCase(input=[2,2,1], expected=1, label="example 1"),
        TestCase(input=[4,1,2,1,2], expected=4, label="example 2"),
        TestCase(input=[1], expected=1, label="single element"),
    ]

    def solve(self, nums: list[int]) -> int:
        result = 0
        for num in nums:
            result ^= num
        return result

if __name__ == "__main__":
    Solution().run()
