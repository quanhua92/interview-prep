"""
P191: Number of 1 Bits (Easy)
https://leetcode.com/problems/number-of-1-bits/
Topics: Divide and Conquer, Bit Manipulation

Given a positive integer n, write a function that returns the number of set bits in its binary representation (also known as the Hamming weight).

Example 1:
    Input: n = 11
    Output: 3
    Explanation:
    The input binary string 1011 has a total of three set bits.

Example 2:
    Input: n = 128
    Output: 1
    Explanation:
    The input binary string 10000000 has a total of one set bit.

Example 3:
    Input: n = 2147483645
    Output: 30
    Explanation:
    The input binary string 1111111111111111111111111111101 has a total of thirty set bits.

Constraints:
    - 1 <= n <= 231 - 1

Template (python3):
    class Solution:
        def hammingWeight(self, n: int) -> int:

Hint: Use Brian Kernighan's algorithm: n &= (n - 1) clears the lowest set bit.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "191. Number of 1 Bits"
    test_cases = [
        TestCase(
            input=0b00000000000000000000000000001011, expected=3, label="example 1"
        ),
        TestCase(
            input=0b00000000000000000000000010000000, expected=1, label="power of two"
        ),
        TestCase(
            input=2147483645, expected=30, label="leetcode example 3"
        ),
        TestCase(input=0, expected=0, label="zero"),
        TestCase(input=1, expected=1, label="single bit"),
        TestCase(input=0x55555555, expected=16, label="alternating bits"),
        TestCase(input=(1 << 31) - 1, expected=31, label="max value all bits set"),
    ]

    def solve(self, n: int) -> int:
        raise NotImplementedError("TODO: Implement solve(self, n: int) -> int")


if __name__ == "__main__":
    Solution().run()
