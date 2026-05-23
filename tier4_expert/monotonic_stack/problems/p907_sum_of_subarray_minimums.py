"""
P907: Sum of Subarray Minimums (Medium)
https://leetcode.com/problems/sum-of-subarray-minimums/
Topics: Array, Dynamic Programming, Stack, Monotonic Stack

Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous) subarray of arr. Since the answer may be large, return the answer modulo 109 + 7.

Example 1:
    Input: arr = [3,1,2,4]
    Output: 17
    Explanation:
    Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4].
    Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.
    Sum is 17.

Example 2:
    Input: arr = [11,81,94,43,3]
    Output: 444

Constraints:
    - 1 <= arr.length <= 3 * 104
    - 1 <= arr[i] <= 3 * 104

Template (python3):
    class Solution:
        def sumSubarrayMins(self, arr: List[int]) -> int:

Hint: Use a monotonic stack to find the number of subarrays where each element is the minimum.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "907. Sum of Subarray Minimums"
    test_cases = [
        TestCase(input=[3, 1, 2, 4], expected=17, label="example 1"),
        TestCase(input=[11, 81, 94, 43, 3], expected=444, label="example 2"),
        TestCase(input=[1], expected=1, label="single element"),
        TestCase(input=[2, 1], expected=4, label="two elements"),
        TestCase(input=[3, 3, 3], expected=18, label="all same"),
        TestCase(input=[1, 2, 3], expected=10, label="strictly increasing"),
        TestCase(input=[3, 2, 1], expected=10, label="strictly decreasing"),
    ]

    def solve(self, arr: list[int]) -> int:
        raise NotImplementedError("TODO: Implement solve(self, arr: list[int]) -> int")


if __name__ == "__main__":
    Solution().run()
