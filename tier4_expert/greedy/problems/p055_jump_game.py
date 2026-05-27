"""
P55: Jump Game (Medium)
https://leetcode.com/problems/jump-game/
Topics: Array, Dynamic Programming, Greedy

You are given an integer array nums. You are initially positioned at the array's first index, and each element in the array represents your maximum jump length at that position.
Return true if you can reach the last index, or false otherwise.

Constraints:
    - 1 <= nums.length <= 104
    - 0 <= nums[i] <= 105

Template (python3):
    class Solution:
        def canJump(self, nums: List[int]) -> bool:

Hint: Track the farthest reachable index; if you pass it, the end is unreachable.
"""

from src.wasm_libs.py.io import *


def solve(nums: list[int]) -> bool:
    raise NotImplementedError


if __name__ == "__main__":
    nums = read_ints()
    result = solve(nums)
    write_bool(result)
