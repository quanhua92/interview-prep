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

from src.wasm_libs.py.io import *


def solve(nums: list[int]) -> list[list[int]]:
    result: list[list[int]] = []

    def backtrack(start: int, path: list[int]):
        if len(path) >= 2:
            result.append(path[:])
        used: set[int] = set()
        for i in range(start, len(nums)):
            if nums[i] in used:
                continue
            if not path or nums[i] >= path[-1]:
                used.add(nums[i])
                path.append(nums[i])
                backtrack(i + 1, path)
                path.pop()

    backtrack(0, [])
    return sorted(result)


if __name__ == "__main__":
    nums = read_ints()
    subs = solve(nums)
    for s in subs:
        write_ints(s)
