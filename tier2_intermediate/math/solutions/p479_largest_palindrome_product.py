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

from src.wasm_libs.py.io import *


def solve(n: int) -> int:
    if n == 1:
        return 9
    upper = 10**n - 1
    lower = 10 ** (n - 1)
    left = upper
    while left >= lower:
        palindrome = left
        tmp = left
        while tmp > 0:
            palindrome = palindrome * 10 + tmp % 10
            tmp //= 10
        right = upper
        while right >= lower:
            if right * right < palindrome:
                break
            if palindrome % right == 0:
                return palindrome % 1337
            right -= 1
        left -= 1
    return 0


if __name__ == "__main__":
    n = read_int()
    result = solve(n)
    write_int(result)
