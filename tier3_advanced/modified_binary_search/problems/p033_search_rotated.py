"""
P33: Search in Rotated Sorted Array (Medium)
https://leetcode.com/problems/search-in-rotated-sorted-array/
Topics: Array, Binary Search

There is an integer array nums sorted in ascending order (with distinct values).
Prior to being passed to your function, nums is possibly rotated at an unknown pivot index k (1 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].
Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.
You must write an algorithm with O(log n) runtime complexity.

Example 1:
    Input: nums = [4,5,6,7,0,1,2], target = 0
    Output: 4

Example 2:
    Input: nums = [4,5,6,7,0,1,2], target = 3
    Output: -1

Example 3:
    Input: nums = [1], target = 0
    Output: -1

Constraints:
    - 1 <= nums.length <= 5000
    - -104 <= nums[i] <= 104
    - All values of nums are unique.
    - nums is an ascending array that is possibly rotated.
    - -104 <= target <= 104

Template (python3):
    class Solution:
        def search(self, nums: List[int], target: int) -> int:

Hint: Determine which half is sorted, then check if target lies in that half.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "33. Search in Rotated Sorted Array"
    test_cases = [
        TestCase(input=([4, 5, 6, 7, 0, 1, 2], 0), expected=4, label="example 1"),
        TestCase(input=([4, 5, 6, 7, 0, 1, 2], 3), expected=-1, label="example 2"),
        TestCase(input=([1], 0), expected=-1, label="single element"),
    ]

    def solve(self, nums: list[int], target: int) -> int:
        raise NotImplementedError(
            "TODO: Implement solve(self, nums: list[int], target: int) -> int"
        )


if __name__ == "__main__":
    Solution().run()
