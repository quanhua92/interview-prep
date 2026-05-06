"""
P565: Array Nesting [PREMIUM] (Medium)
https://leetcode.com/problems/array-nesting/
Topics: Array, Depth-First Search

You are given an integer array nums of length n where nums is a permutation of the numbers in the range [0, n - 1].
You should build a set s[k] = {nums[k], nums[nums[k]], nums[nums[nums[k]]], ... } subjected to the following rule:
Return the longest length of a set s[k].
Example 1:
    Input: nums = [5,4,0,3,1,6,2]
    Output: 4
    Explanation:
    nums[0] = 5, nums[1] = 4, nums[2] = 0, nums[3] = 3, nums[4] = 1, nums[5] = 6, nums[6] = 2.
    One of the longest sets s[k]:
    s[0] = {nums[0], nums[5], nums[6], nums[2]} = {5, 6, 2, 0}

Example 2:
    Input: nums = [0,1,2]
    Output: 1

Constraints:
    - 1 <= nums.length <= 105
    - 0 <= nums[i] < nums.length
    - All the values of nums are unique.

Template (python3):
    class Solution:
        def arrayNesting(self, nums: List[int]) -> int:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "565. Array Nesting"
    test_cases = [
        TestCase(input=[5, 4, 0, 3, 1, 6, 2], expected=4, label="example 1"),
        TestCase(input=[0, 1, 2], expected=1, label="example 2"),
    ]

    def solve(self, nums: list[int]) -> int:
        raise NotImplementedError("TODO: Implement solve(self, nums) -> int")


if __name__ == "__main__":
    Solution().run()
