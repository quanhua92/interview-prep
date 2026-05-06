"""
P479: Largest Palindrome Product [PREMIUM] (Hard)
https://leetcode.com/problems/largest-palindrome-product/
Topics: Math, Enumeration

Given an integer n, return the largest palindromic integer that can be represented as the product of two n-digits integers. Since the answer can be very large, return it modulo 1337.
Example 1:
    Input: n = 2
    Output: 987
    Explanation: 99 x 91 = 9009, 9009 % 1337 = 987

Example 2:
    Input: n = 1
    Output: 9

Constraints:
    - 1 <= n <= 8

Template (python3):
    class Solution:
        def largestPalindrome(self, n: int) -> int:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "479. Largest Palindrome Product"
    test_cases = [
        TestCase(input=2, expected=987, label="example 1"),
        TestCase(input=1, expected=9, label="example 2"),
    ]

    def solve(self, n: int) -> int:
        raise NotImplementedError("TODO: Implement solve(self, n) -> int")


if __name__ == "__main__":
    Solution().run()
