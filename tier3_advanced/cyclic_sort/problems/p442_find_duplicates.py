"""
P442: Find All Duplicates in an Array (Medium)
https://leetcode.com/problems/find-all-duplicates-in-an-array/
Topics: Array, Hash Table

Given an integer array nums of length n where all the integers of nums are in the range [1, n] and each integer appears at most twice, return an array of all the integers that appears twice.
You must write an algorithm that runs in O(n) time and uses only constant auxiliary space, excluding the space needed to store the output

Example 1:
    Input: nums = [4,3,2,7,8,2,3,1]
    Output: [2,3]

Example 2:
    Input: nums = [1,1,2]
    Output: [1]

Example 3:
    Input: nums = [1]
    Output: []

Constraints:
    - n == nums.length
    - 1 <= n <= 105
    - 1 <= nums[i] <= n
    - Each element in nums appears once or twice.

Template (python3):
    class Solution:
        def findDuplicates(self, nums: List[int]) -> List[int]:

Hint: Negate the value at index abs(num)-1 to mark seen numbers in-place.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "442. Find All Duplicates in an Array"
    test_cases = [
        TestCase(input=[4, 3, 2, 7, 8, 2, 3, 1], expected=[2, 3], label="example 1"),
        TestCase(input=[1, 1, 2], expected=[1], label="example 2"),
        TestCase(input=[1], expected=[], label="single"),
    ]

    def solve(self, nums: list[int]) -> list[int]:
        raise NotImplementedError(
            "TODO: Implement solve(self, nums: list[int]) -> list[int]"
        )


if __name__ == "__main__":
    Solution().run()
