"""
P483: Smallest Good Base [PREMIUM] (Hard)
https://leetcode.com/problems/smallest-good-base/
Topics: Math, Binary Search

Given an integer n represented as a string, return the smallest good base of n.
We call k >= 2 a good base of n, if all digits of n base k are 1's.
Example 1:
    Input: n = "13"
    Output: "3"
    Explanation: 13 base 3 is 111.

Example 2:
    Input: n = "4681"
    Output: "8"
    Explanation: 4681 base 8 is 11111.

Example 3:
    Input: n = "1000000000000000000"
    Output: "999999999999999999"
    Explanation: 1000000000000000000 base 999999999999999999 is 11.

Constraints:
    - n is an integer in the range [3, 1018].
    - n does not contain any leading zeros.

Template (python3):
    class Solution:
        def smallestGoodBase(self, n: str) -> str:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "483. Smallest Good Base"
    test_cases = [
        TestCase(input="13", expected="3", label="example 1"),
        TestCase(input="4681", expected="8", label="example 2"),
        TestCase(
            input="1000000000000000000",
            expected="999999999999999999",
            label="example 3",
        ),
    ]

    def solve(self, n: str) -> str:
        raise NotImplementedError("TODO: Implement solve(self, n) -> str")


if __name__ == "__main__":
    Solution().run()
