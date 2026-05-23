"""
P46: Permutations (Medium)
https://leetcode.com/problems/permutations/
Topics: Array, Backtracking

Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.

Example 1:
    Input: nums = [1,2,3]
    Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

Example 2:
    Input: nums = [0,1]
    Output: [[0,1],[1,0]]

Example 3:
    Input: nums = [1]
    Output: [[1]]

Constraints:
    - 1 <= nums.length <= 6
    - -10 <= nums[i] <= 10
    - All the integers of nums are unique.

Template (python3):
    class Solution:
        def permute(self, nums: List[int]) -> List[List[int]]:

Hint: Use backtracking with swapping to generate all permutations in-place.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "46. Permutations"
    test_cases = [
        TestCase(
            input=[1, 2, 3],
            expected=[[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]],
            label="example 1",
        ),
        TestCase(input=[0, 1], expected=[[0, 1], [1, 0]], label="example 2"),
        TestCase(input=[1], expected=[[1]], label="single element"),
        TestCase(
            input=[-1, 0, 1],
            expected=[[-1, 0, 1], [-1, 1, 0], [0, -1, 1], [0, 1, -1], [1, -1, 0], [1, 0, -1]],
            label="negative and zero mix",
        ),
        TestCase(
            input=[-3, -1],
            expected=[[-3, -1], [-1, -3]],
            label="two negative elements",
        ),
        TestCase(
            input=[1, 2, 3, 4],
            expected=[
                [1, 2, 3, 4], [1, 2, 4, 3], [1, 3, 2, 4], [1, 3, 4, 2], [1, 4, 2, 3], [1, 4, 3, 2],
                [2, 1, 3, 4], [2, 1, 4, 3], [2, 3, 1, 4], [2, 3, 4, 1], [2, 4, 1, 3], [2, 4, 3, 1],
                [3, 1, 2, 4], [3, 1, 4, 2], [3, 2, 1, 4], [3, 2, 4, 1], [3, 4, 1, 2], [3, 4, 2, 1],
                [4, 1, 2, 3], [4, 1, 3, 2], [4, 2, 1, 3], [4, 2, 3, 1], [4, 3, 1, 2], [4, 3, 2, 1],
            ],
            label="four elements",
        ),
        TestCase(input=[-5], expected=[[-5]], label="single negative element"),
    ]

    def solve(self, nums: list[int]) -> list[list[int]]:
        perms = [[]]
        for num in nums:
            new_perms = []
            for p in perms:
                for i in range(len(p) + 1):
                    new_perms.append(p[:i] + [num] + p[i:])
            perms = new_perms
        return sorted(perms)

    def solve_alternative(self, nums: list[int]) -> list[list[int]]:
        result: list[list[int]] = []

        def backtrack(first: int = 0):
            if first == len(nums):
                result.append(nums[:])
                return
            for i in range(first, len(nums)):
                nums[first], nums[i] = nums[i], nums[first]
                backtrack(first + 1)
                nums[first], nums[i] = nums[i], nums[first]

        backtrack()
        return sorted(result)


if __name__ == "__main__":
    Solution().run()
