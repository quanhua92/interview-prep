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
    - 1 <= n <= 2^31 - 1

Template (python3):
    class Solution:
        def hammingWeight(self, n: int) -> int:

Hint: Use Brian Kernighan's algorithm: n &= (n - 1) clears the lowest set bit.
"""

from src.wasm_libs.py.io import *


def solve(n: int) -> int:
    count = 0
    while n:
        n &= n - 1
        count += 1
    return count


if __name__ == "__main__":
    n = read_int()
    result = solve(n)
    write_int(result)
