"""
P15: 3Sum (Medium)
https://leetcode.com/problems/3sum/
Topics: Array, Two Pointers, Sorting

Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.
Notice that the solution set must not contain duplicate triplets.

Example 1:
    Input: nums = [-1,0,1,2,-1,-4]
    Output: [[-1,-1,2],[-1,0,1]]
    Explanation:
    nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
    nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
    nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
    The distinct triplets are [-1,0,1] and [-1,-1,2].
    Notice that the order of the output and the order of the triplets does not matter.

Example 2:
    Input: nums = [0,1,1]
    Output: []
    Explanation: The only possible triplet does not sum up to 0.

Example 3:
    Input: nums = [0,0,0]
    Output: [[0,0,0]]
    Explanation: The only possible triplet sums up to 0.

Constraints:
    - 3 <= nums.length <= 3000
    - -105 <= nums[i] <= 105

Hints:
    - So, we essentially need to find three numbers x, y, and z such that they add up to the given value. If we fix one of the numbers say x, we are left with the two-sum problem at hand!
    - For the two-sum problem, if we fix one of the numbers, say x, we have to scan the entire array to find the next number y, which is value - x where value is the input parameter. Can we change our array somehow so that this search becomes faster?
    - The second train of thought for two-sum is, without changing the array, can we use additional space somehow? Like maybe a hash map to speed up the search?

Template (python3):
    class Solution:
        def threeSum(self, nums: List[int]) -> List[List[int]]:

Hint: Sort, iterate i, nested two pointers for remaining pair, skip duplicates.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "15. 3Sum"
    test_cases = [
        TestCase(
            input=[-1, 0, 1, 2, -1, -4],
            expected=sorted([sorted(t) for t in [[-1, -1, 2], [-1, 0, 1]]]),
            label="example 1",
        ),
        TestCase(input=[0, 1, 1], expected=[], label="no triplets"),
        TestCase(input=[0, 0, 0], expected=[[0, 0, 0]], label="all zeros"),
        TestCase(input=[], expected=[], label="empty"),
        TestCase(input=[-2, 0, 0, 2, 2], expected=[[-2, 0, 2]], label="adjacent duplicate pairs"),
        TestCase(input=[0, 0, 0, 0, 0], expected=[[0, 0, 0]], label="all identical values"),
        TestCase(input=[-3, -3, 0, 1, 1, 2, 2], expected=[[-3, 1, 2]], label="skip-i with left/right dup"),
        TestCase(input=[-2, 0, 0, 0, 2, 2, 2], expected=[[-2, 0, 2], [0, 0, 0]], label="triple duplicate"),
    ]

    def solve(self, nums: list[int]) -> list[list[int]]:
        raise NotImplementedError(
            "TODO: Implement solve(self, nums: list[int]) -> list[list[int]]"
        )


if __name__ == "__main__":
    Solution().run()
