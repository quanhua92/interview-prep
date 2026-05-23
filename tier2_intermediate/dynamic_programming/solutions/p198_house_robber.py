"""
P198: House Robber (Medium)
https://leetcode.com/problems/house-robber/
Topics: Array, Dynamic Programming

You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and it will automatically contact the police if two adjacent houses were broken into on the same night.
Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.

Example 1:
    Input: nums = [1,2,3,1]
    Output: 4
    Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
    Total amount you can rob = 1 + 3 = 4.

Example 2:
    Input: nums = [2,7,9,3,1]
    Output: 12
    Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
    Total amount you can rob = 2 + 9 + 1 = 12.

Constraints:
    - 1 <= nums.length <= 100
    - 0 <= nums[i] <= 400

Template (python3):
    class Solution:
        def rob(self, nums: List[int]) -> int:

Hint: Use two variables (prev, curr) -- for each house decide to rob or skip.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "198. House Robber"
    test_cases = [
        TestCase(input=[1, 2, 3, 1], expected=4, label="example 1"),
        TestCase(input=[2, 7, 9, 3, 1], expected=12, label="example 2"),
        TestCase(input=[1], expected=1, label="single house"),
        TestCase(input=[], expected=0, label="no houses"),
        TestCase(input=[2, 1, 1, 2], expected=4, label="alternate houses equal"),
        TestCase(input=[0, 0, 0], expected=0, label="all zeros"),
        TestCase(input=[1, 2], expected=2, label="two houses"),
        TestCase(input=[10, 1, 10, 1, 10], expected=30, label="alternating high low"),
        TestCase(input=[100, 1, 1, 100, 1, 1, 100], expected=300, label="three peaks"),
        TestCase(input=[400] * 100, expected=20000, label="max values large array"),
    ]

    def solve(self, nums: list[int]) -> int:
        prev, curr = 0, 0
        for num in nums:
            prev, curr = curr, max(curr, prev + num)
        return curr


if __name__ == "__main__":
    Solution().run()
