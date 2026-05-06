"""
P556: Next Greater Element III [PREMIUM] (Medium)
https://leetcode.com/problems/next-greater-element-iii/
Topics: Math, Two Pointers, String

Given a positive integer n, find the smallest integer which has exactly the same digits existing in the integer n and is greater in value than n. If no such positive integer exists, return -1.
Note that the returned integer should fit in 32-bit integer, if there is a valid answer but it does not fit in 32-bit integer, return -1.
Example 1:
    Input: n = 12
    Output: 21

Example 2:
    Input: n = 21
    Output: -1

Constraints:
    - 1 <= n <= 231 - 1

Template (python3):
    class Solution:
        def nextGreaterElement(self, n: int) -> int:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "556. Next Greater Element III"
    test_cases = [
        TestCase(input=12, expected=21, label="example 1"),
        TestCase(input=21, expected=-1, label="example 2"),
    ]

    def solve(self, n: int) -> int:
        raise NotImplementedError("TODO: Implement solve(self, n) -> int")


if __name__ == "__main__":
    Solution().run()
