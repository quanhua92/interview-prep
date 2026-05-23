"""
P503: Next Greater Element II [PREMIUM] (Medium)
https://leetcode.com/problems/next-greater-element-ii/
Topics: Array, Stack, Monotonic Stack

Given a circular integer array nums (i.e., the next element of nums[nums.length - 1] is nums[0]), return the next greater number for every element in nums.
The next greater number of a number x is the first greater number to its traversing-order next in the array, which means you could search circularly to find its next greater number. If it doesn't exist, return -1 for this number.
Example 1:
    Input: nums = [1,2,1]
    Output: [2,-1,2]
    Explanation: The first 1's next greater number is 2;
    The number 2 can't find next greater number.
    The second 1's next greater number needs to search circularly, which is also 2.

Example 2:
    Input: nums = [1,2,3,4,3]
    Output: [2,3,4,-1,4]

Constraints:
    - 1 <= nums.length <= 104
    - -109 <= nums[i] <= 109

Template (python3):
    class Solution:
        def nextGreaterElements(self, nums: List[int]) -> List[int]:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "503. Next Greater Element II"
    test_cases = [
        TestCase(input=[1, 2, 1], expected=[2, -1, 2], label="example 1"),
        TestCase(input=[1, 2, 3, 4, 3], expected=[2, 3, 4, -1, 4], label="example 2"),
        TestCase(input=[5], expected=[-1], label="single element"),
        TestCase(input=[2, 2, 2], expected=[-1, -1, -1], label="all same"),
        TestCase(input=[5, 4, 3, 2], expected=[-1, 5, 5, 5], label="strictly decreasing wraps"),
        TestCase(input=[-3, -2, -1], expected=[-2, -1, -1], label="with negatives"),
    ]

    def solve(self, nums: list[int]) -> list[int]:
        n = len(nums)
        result = [-1] * n
        stack: list[int] = []
        for i in range(2 * n):
            idx = i % n
            while stack and nums[stack[-1]] < nums[idx]:
                result[stack.pop()] = nums[idx]
            if i < n:
                stack.append(idx)
        return result


if __name__ == "__main__":
    Solution().run()
