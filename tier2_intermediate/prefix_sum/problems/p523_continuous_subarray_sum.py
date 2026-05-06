"""
P523: Continuous Subarray Sum [PREMIUM] (Medium)
https://leetcode.com/problems/continuous-subarray-sum/
Topics: Array, Hash Table, Math, Prefix Sum

Given an integer array nums and an integer k, return true if nums has a good subarray or false otherwise.
A good subarray is a subarray where:
Note that:
Example 1:
    Input: nums = [23,2,4,6,7], k = 6
    Output: true
    Explanation: [2, 4] is a continuous subarray of size 2 whose elements sum up to 6.

Example 2:
    Input: nums = [23,2,6,4,7], k = 6
    Output: true
    Explanation: [23, 2, 6, 4, 7] is an continuous subarray of size 5 whose elements sum up to 42.
    42 is a multiple of 6 because 42 = 7 * 6 and 7 is an integer.

Example 3:
    Input: nums = [23,2,6,4,7], k = 13
    Output: false

Constraints:
    - 1 <= nums.length <= 105
    - 0 <= nums[i] <= 109
    - 0 <= sum(nums[i]) <= 231 - 1
    - 1 <= k <= 231 - 1

Template (python3):
    class Solution:
        def checkSubarraySum(self, nums: List[int], k: int) -> bool:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "523. Continuous Subarray Sum"
    test_cases = [
        TestCase(input=([23, 2, 4, 6, 7], 6), expected=True, label="example 1"),
        TestCase(input=([23, 2, 6, 4, 7], 6), expected=True, label="example 2"),
        TestCase(input=([23, 2, 6, 4, 7], 13), expected=False, label="example 3"),
    ]

    def solve(self, nums: list[int], k: int) -> bool:
        raise NotImplementedError("TODO: Implement solve(self, nums, k) -> bool")


if __name__ == "__main__":
    Solution().run()
