"""
P136: Single Number (Easy)
https://leetcode.com/problems/single-number/
Topics: Array, Bit Manipulation

Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.
You must implement a solution with a linear runtime complexity and use only constant extra space.

Example 1:
    Input: nums = [2,2,1]
    Output: 1

Example 2:
    Input: nums = [4,1,2,1,2]
    Output: 4

Example 3:
    Input: nums = [1]
    Output: 1

Constraints:
    - 1 <= nums.length <= 3 * 104
    - -3 * 104 <= nums[i] <= 3 * 104
    - Each element in the array appears twice except for one element which appears only once.

Hints:
    - Think about the XOR (^) operator's property.

Template (python3):
    class Solution:
        def singleNumber(self, nums: List[int]) -> int:

Hint: XOR all numbers — pairs cancel out, leaving the single number.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "136. Single Number"
    test_cases = [
        TestCase(input=[2, 2, 1], expected=1, label="example 1"),
        TestCase(input=[4, 1, 2, 1, 2], expected=4, label="example 2"),
        TestCase(input=[1], expected=1, label="single element"),
        TestCase(input=[-1, -1, -2], expected=-2, label="negative numbers"),
        TestCase(input=[0, 0, 1], expected=1, label="zero pairs"),
        TestCase(input=[-1], expected=-1, label="single negative"),
        TestCase(input=[7, 7, 7, 7, 99, 3, 3, 4, 4], expected=99, label="many pairs"),
    ]

    def solve(self, nums: list[int]) -> int:
        result = 0
        for num in nums:
            result ^= num
        return result


if __name__ == "__main__":
    Solution().run()
