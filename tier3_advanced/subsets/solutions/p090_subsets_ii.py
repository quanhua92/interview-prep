"""
P90: Subsets II (Medium)
https://leetcode.com/problems/subsets-ii/
Topics: Array, Backtracking, Bit Manipulation

Given an integer array nums that may contain duplicates, return all possible subsets (the power set).
The solution set must not contain duplicate subsets. Return the solution in any order.

Example 1:
    Input: nums = [1,2,2]
    Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]

Example 2:
    Input: nums = [0]
    Output: [[],[0]]

Constraints:
    - 1 <= nums.length <= 10
    - -10 <= nums[i] <= 10

Template (python3):
    class Solution:
        def subsetsWithDup(self, nums: List[int]) -> List[List[int]]:

Hint: Sort first, then skip duplicates at the same recursion level during backtracking.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "90. Subsets II"
    test_cases = [
        TestCase(
            input=[1, 2, 2],
            expected=[[], [1], [1, 2], [1, 2, 2], [2], [2, 2]],
            label="example 1",
        ),
        TestCase(input=[0], expected=[[], [0]], label="example 2"),
        TestCase(
            input=[2, 2, 2],
            expected=[[], [2], [2, 2], [2, 2, 2]],
            label="all duplicates",
        ),
        TestCase(
            input=[1, 1, 2, 2],
            expected=[[], [1], [1, 1], [1, 1, 2], [1, 1, 2, 2], [1, 2], [1, 2, 2], [2], [2, 2]],
            label="multiple duplicates",
        ),
        TestCase(
            input=[-1, -1, 0],
            expected=[[], [-1], [-1, -1], [-1, -1, 0], [-1, 0], [0]],
            label="negative duplicates",
        ),
        TestCase(
            input=[1, 1, 1, 1],
            expected=[[], [1], [1, 1], [1, 1, 1], [1, 1, 1, 1]],
            label="all same element",
        ),
    ]

    def solve(self, nums: list[int]) -> list[list[int]]:
        result: list[list[int]] = []
        nums.sort()

        def backtrack(start: int, current: list[int]):
            result.append(current[:])
            for i in range(start, len(nums)):
                if i > start and nums[i] == nums[i - 1]:
                    continue
                current.append(nums[i])
                backtrack(i + 1, current)
                current.pop()

        backtrack(0, [])
        return result


if __name__ == "__main__":
    Solution().run()
