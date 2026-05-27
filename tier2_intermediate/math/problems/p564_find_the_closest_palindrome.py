"""
P564: Find the Closest Palindrome [PREMIUM] (Hard)
https://leetcode.com/problems/find-the-closest-palindrome/
Topics: Math, String

Given a string n representing an integer, return the closest integer (not including itself), which is a palindrome. If there is a tie, return the smaller one.
The closest is defined as the absolute difference minimized between two integers.
Example 1:
    Input: n = "123"
    Output: "121"

Example 2:
    Input: n = "1"
    Output: "0"
    Explanation: 0 and 2 are the closest palindromes but we return the smallest which is 0.

Constraints:
    - 1 <= n.length <= 18
    - n consists of only digits.
    - n does not have leading zeros.
    - n is representing an integer in the range [1, 1018 - 1].

Hint: Will brute force work for this problem? Think of something else.
Hint: Take some examples like 1234, 999,1000, etc and check their closest palindromes. How many different cases are possible?
Hint: Do we have to consider only left half or right half of the string or both?
Hint: Try to find the closest palindrome of these numbers- 12932, 99800, 12120. Did you observe something?

Template (python3):
    class Solution:
        def nearestPalindromic(self, n: str) -> str:
"""

from src.wasm_libs.py.io import *


def solve(n: str) -> str:
    raise NotImplementedError


if __name__ == "__main__":
    n = read_line()
    result = solve(n)
    write_string(result)
