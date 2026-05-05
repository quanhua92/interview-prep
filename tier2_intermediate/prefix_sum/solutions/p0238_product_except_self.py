"""P0238: Product of Array Except Self (Medium)

TODO: Implement solve() below.
Hint: Build left and right product arrays, then combine.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "238. Product of Array Except Self"
    test_cases = [
        TestCase(input=[1,2,3,4], expected=[24,12,8,6], label="example 1"),
        TestCase(input=[-1,1,0,-3,3], expected=[0,0,9,0,0], label="example 2"),
        TestCase(input=[1,2], expected=[2,1], label="two elements"),
    ]

    def solve(self, nums: list[int]) -> list[int]:
        n = len(nums)
        output = [1] * n

        # Left pass: output[i] = product of nums[0:i]
        left_product = 1
        for i in range(n):
            output[i] = left_product
            left_product *= nums[i]

        # Right pass: multiply by product of nums[i+1:n]
        right_product = 1
        for i in range(n - 1, -1, -1):
            output[i] *= right_product
            right_product *= nums[i]

        return output

if __name__ == "__main__":
    Solution().run()
