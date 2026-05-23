"""
P410: Split Array Largest Sum (Hard)
https://leetcode.com/problems/split-array-largest-sum/
Topics: Array, Binary Search, Dynamic Programming, Greedy, Prefix Sum

Given an integer array nums and an integer k, split nums into k non-empty subarrays such that the largest sum of any subarray is minimized.
Return the minimized largest sum of the split.
A subarray is a contiguous part of the array.

Example 1:
    Input: nums = [7,2,5,10,8], k = 2
    Output: 18
    Explanation: There are four ways to split nums into two subarrays.
    The best way is to split it into [7,2,5] and [10,8], where the largest sum among the two subarrays is only 18.

Example 2:
    Input: nums = [1,2,3,4,5], k = 2
    Output: 9
    Explanation: There are four ways to split nums into two subarrays.
    The best way is to split it into [1,2,3] and [4,5], where the largest sum among the two subarrays is only 9.

Constraints:
    - 1 <= nums.length <= 1000
    - 0 <= nums[i] <= 106
    - 1 <= k <= min(50, nums.length)

Template (python3):
    class Solution:
        def splitArray(self, nums: List[int], k: int) -> int:

Hint: Binary search the answer in [max(nums), sum(nums)] and check feasibility greedily.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "410. Split Array Largest Sum"
    test_cases = [
        TestCase(input=([7, 2, 5, 10, 8], 2), expected=18, label="example 1"),
        TestCase(input=([1, 2, 3, 4, 5], 2), expected=9, label="example 2"),
        TestCase(input=([1, 4, 4], 3), expected=4, label="example 3"),
        TestCase(input=([1, 2, 3, 4, 5], 5), expected=5, label="k equals length"),
        TestCase(input=([5], 1), expected=5, label="single element"),
        TestCase(input=([0, 0, 0, 0], 2), expected=0, label="all zeros"),
        TestCase(input=([1, 1, 1, 1, 1, 1, 1, 1], 4), expected=2, label="uniform values"),
        TestCase(input=([1000000, 1000000, 1000000], 2), expected=2000000, label="large values"),
    ]

    def solve(self, nums: list[int], k: int) -> int:
        raise NotImplementedError(
            "TODO: Implement solve(self, nums: list[int], k: int) -> int"
        )


if __name__ == "__main__":
    Solution().run()
