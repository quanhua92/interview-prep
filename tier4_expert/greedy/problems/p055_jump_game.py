"""
P55: Jump Game (Medium)
https://leetcode.com/problems/jump-game/
Topics: Array, Dynamic Programming, Greedy

You are given an integer array nums. You are initially positioned at the array's first index, and each element in the array represents your maximum jump length at that position.
Return true if you can reach the last index, or false otherwise.

Example 1:
    Input: nums = [2,3,1,1,4]
    Output: true
    Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.

Example 2:
    Input: nums = [3,2,1,0,4]
    Output: false
    Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.

Constraints:
    - 1 <= nums.length <= 104
    - 0 <= nums[i] <= 105

Template (python3):
    class Solution:
        def canJump(self, nums: List[int]) -> bool:

Hint: Track the farthest reachable index; if you pass it, the end is unreachable.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "55. Jump Game"
    test_cases = [
        TestCase(input=[2, 3, 1, 1, 4], expected=True, label="example 1"),
        TestCase(input=[3, 2, 1, 0, 4], expected=False, label="example 2"),
        TestCase(input=[0], expected=True, label="single element"),
        TestCase(input=[1, 1, 1, 1, 1], expected=True, label="all ones"),
        TestCase(input=[5, 0, 0, 0, 0], expected=True, label="big jump from start"),
        TestCase(input=[0, 1], expected=False, label="stuck at start"),
        TestCase(input=[2, 0], expected=True, label="two elements reachable"),
    ]

    def solve(self, nums: list[int]) -> bool:
        raise NotImplementedError(
            "TODO: Implement solve(self, nums: list[int]) -> bool"
        )


if __name__ == "__main__":
    Solution().run()
