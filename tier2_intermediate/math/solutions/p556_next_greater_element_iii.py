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
    - 1 <= n <= 2^31 - 1

Template (python3):
    class Solution:
        def nextGreaterElement(self, n: int) -> int:
"""

from src.wasm_libs.py.io import *


def solve(n: int) -> int:
    digits = list(str(n))
    i = len(digits) - 2
    while i >= 0 and digits[i] >= digits[i + 1]:
        i -= 1
    if i < 0:
        return -1
    j = len(digits) - 1
    while digits[j] <= digits[i]:
        j -= 1
    digits[i], digits[j] = digits[j], digits[i]
    digits[i + 1 :] = reversed(digits[i + 1 :])
    result = int("".join(digits))
    return result if result <= 2**31 - 1 else -1


if __name__ == "__main__":
    n = read_int()
    result = solve(n)
    write_int(result)
