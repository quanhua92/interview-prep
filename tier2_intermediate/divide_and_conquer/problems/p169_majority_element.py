"""
P169: Majority Element (Easy)
https://leetcode.com/problems/majority-element/
Topics: Array, Hash Table, Divide and Conquer, Sorting, Counting

Given an array nums of size n, return the majority element.
The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.

Example 1:
    Input: nums = [3,2,3]
    Output: 3

Example 2:
    Input: nums = [2,2,1,1,1,2,2]
    Output: 2

Constraints:
    - n == nums.length
    - 1 <= n <= 5 * 104
    - -109 <= nums[i] <= 109

Template (python3):
    class Solution:
        def majorityElement(self, nums: List[int]) -> int:

Hint: Use Boyer-Moore voting algorithm — maintain a candidate and count.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "169. Majority Element"
    test_cases = [
        TestCase(input=[3, 2, 3], expected=3, label="example 1"),
        TestCase(input=[2, 2, 1, 1, 1, 2, 2], expected=2, label="example 2"),
        TestCase(input=[1], expected=1, label="single element"),
    ]

    def solve(self, nums: list[int]) -> int:
        raise NotImplementedError("TODO: Implement solve(self, nums: list[int]) -> int")


if __name__ == "__main__":
    Solution().run()
