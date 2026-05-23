"""
P491: Non-decreasing Subsequences [PREMIUM] (Medium)
https://leetcode.com/problems/non-decreasing-subsequences/
Topics: Array, Hash Table, Backtracking, Bit Manipulation

Given an integer array nums, return all the different possible non-decreasing subsequences of the given array with at least two elements. You may return the answer in any order.
Example 1:
    Input: nums = [4,6,7,7]
    Output: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]

Example 2:
    Input: nums = [4,4,3,2,1]
    Output: [[4,4]]

Constraints:
    - 1 <= nums.length <= 15
    - -100 <= nums[i] <= 100

Template (python3):
    class Solution:
        def findSubsequences(self, nums: List[int]) -> List[List[int]]:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "491. Non-decreasing Subsequences"
    test_cases = [
        TestCase(
            input=[4, 6, 7, 7],
            expected=[
                [4, 6],
                [4, 6, 7],
                [4, 6, 7, 7],
                [4, 7],
                [4, 7, 7],
                [6, 7],
                [6, 7, 7],
                [7, 7],
            ],
            label="example 1",
        ),
        TestCase(input=[4, 4, 3, 2, 1], expected=[[4, 4]], label="example 2"),
        TestCase(input=[2, 2, 2], expected=[[2, 2], [2, 2, 2]], label="all same elements"),
        TestCase(input=[5, 4, 3, 2, 1], expected=[], label="strictly decreasing"),
        TestCase(
            input=[1, 2, 3],
            expected=[[1, 2], [1, 2, 3], [1, 3], [2, 3]],
            label="strictly increasing",
        ),
        TestCase(input=[1], expected=[], label="single element"),
    ]

    def solve(self, nums: list[int]) -> list[list[int]]:
        raise NotImplementedError(
            "TODO: Implement solve(self, nums) -> list[list[int]]"
        )


if __name__ == "__main__":
    Solution().run()
