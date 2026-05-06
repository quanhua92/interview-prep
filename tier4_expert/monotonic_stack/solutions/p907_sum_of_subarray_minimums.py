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
    ]

    def solve(self, arr: list[int]) -> int:
        MOD = 10**9 + 7
        n = len(arr)
        left: list[int] = [-1] * n  # previous smaller element index
        right: list[int] = [n] * n  # next smaller or equal element index

        stack: list[int] = []
        for i in range(n):
            while stack and arr[stack[-1]] >= arr[i]:
                stack.pop()
            left[i] = stack[-1] if stack else -1
            stack.append(i)

        stack.clear()
        for i in range(n - 1, -1, -1):
            while stack and arr[stack[-1]] > arr[i]:
                stack.pop()
            right[i] = stack[-1] if stack else n
            stack.append(i)

        total = 0
        for i in range(n):
            count_left = i - left[i]
            count_right = right[i] - i
            total = (total + arr[i] * count_left * count_right) % MOD

        return total


if __name__ == "__main__":
    Solution().run()
