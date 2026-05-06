"""
P525: Contiguous Array [PREMIUM] (Medium)
https://leetcode.com/problems/contiguous-array/
Topics: Array, Hash Table, Prefix Sum

Given a binary array nums, return the maximum length of a contiguous subarray with an equal number of 0 and 1.
Example 1:
    Input: nums = [0,1]
    Output: 2
    Explanation: [0, 1] is the longest contiguous subarray with an equal number of 0 and 1.

Example 2:
    Input: nums = [0,1,0]
    Output: 2
    Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.

Example 3:
    Input: nums = [0,1,1,1,1,1,0,0,0]
    Output: 6
    Explanation: [1,1,1,0,0,0] is the longest contiguous subarray with equal number of 0 and 1.

Constraints:
    - 1 <= nums.length <= 105
    - nums[i] is either 0 or 1.

Template (python3):
    class Solution:
        def findMaxLength(self, nums: List[int]) -> int:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "525. Contiguous Array"
    test_cases = [
        TestCase(input=[0, 1], expected=2, label="example 1"),
        TestCase(input=[0, 1, 0], expected=2, label="example 2"),
        TestCase(input=[0, 1, 1, 1, 1, 1, 0, 0, 0], expected=6, label="example 3"),
    ]

    def solve(self, nums: list[int]) -> int:
        raise NotImplementedError("TODO: Implement solve(self, nums) -> int")


if __name__ == "__main__":
    Solution().run()
