"""
P456: 132 Pattern [PREMIUM] (Medium)
https://leetcode.com/problems/132-pattern/
Topics: Array, Binary Search, Stack, Monotonic Stack, Ordered Set

Given an array of n integers nums, a 132 pattern is a subsequence of three integers nums[i], nums[j] and nums[k] such that i < j < k and nums[i] < nums[k] < nums[j].
Return true if there is a 132 pattern in nums, otherwise, return false.
Example 1:
    Input: nums = [1,2,3,4]
    Output: false
    Explanation: There is no 132 pattern in the sequence.

Example 2:
    Input: nums = [3,1,4,2]
    Output: true
    Explanation: There is a 132 pattern in the sequence: [1, 4, 2].

Example 3:
    Input: nums = [-1,3,2,0]
    Output: true
    Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1, 3, 0] and [-1, 2, 0].

Constraints:
    - n == nums.length
    - 1 <= n <= 2 * 105
    - -109 <= nums[i] <= 109

Template (python3):
    class Solution:
        def find132pattern(self, nums: List[int]) -> bool:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "456. 132 Pattern"
    test_cases = [
        TestCase(input=[1, 2, 3, 4], expected=False, label="example 1"),
        TestCase(input=[3, 1, 4, 2], expected=True, label="example 2"),
        TestCase(input=[-1, 3, 2, 0], expected=True, label="example 3"),
    ]

    def solve(self, nums: list[int]) -> bool:
        third = float("-inf")
        stack: list[int] = []
        for num in reversed(nums):
            if num < third:
                return True
            while stack and stack[-1] < num:
                third = stack.pop()
            stack.append(num)
        return False


if __name__ == "__main__":
    Solution().run()
