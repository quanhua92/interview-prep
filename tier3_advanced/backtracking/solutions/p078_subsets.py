"""
P78: Subsets (Medium)
https://leetcode.com/problems/subsets/
Topics: Array, Backtracking, Bit Manipulation

Given an integer array nums of unique elements, return all possible subsets (the power set).
The solution set must not contain duplicate subsets. Return the solution in any order.

Example 1:
    Input: nums = [1,2,3]
    Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

Example 2:
    Input: nums = [0]
    Output: [[],[0]]

Constraints:
    - 1 <= nums.length <= 10
    - -10 <= nums[i] <= 10
    - All the numbers of nums are unique.

Template (python3):
    class Solution:
        def subsets(self, nums: List[int]) -> List[List[int]]:

Hint: Use backtracking to generate all possible subsets by including/excluding each element.
"""

from src.wasm_libs.py.io import *


def solve(nums: list[int]) -> list[list[int]]:
    result: list[list[int]] = []

    def backtrack(start: int, current: list[int]):
        result.append(current[:])
        for i in range(start, len(nums)):
            current.append(nums[i])
            backtrack(i + 1, current)
            current.pop()

    backtrack(0, [])
    return result


if __name__ == "__main__":
    nums = read_ints()
    subsets = solve(nums)
    for s in subsets:
        if s:
            write_ints(s)
        else:
            print()
