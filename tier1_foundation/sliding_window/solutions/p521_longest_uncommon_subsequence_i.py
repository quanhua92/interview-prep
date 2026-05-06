"""
P521: Longest Uncommon Subsequence I [PREMIUM] (Easy)
https://leetcode.com/problems/longest-uncommon-subsequence-i/
Topics: String

Given two strings a and b, return the length of the longest uncommon subsequence between a and b. If no such uncommon subsequence exists, return -1.
An uncommon subsequence between two strings is a string that is a subsequence of exactly one of them.
Example 1:
    Input: a = "aba", b = "cdc"
    Output: 3
    Explanation: One longest uncommon subsequence is "aba" because "aba" is a subsequence of "aba" but not "cdc".
    Note that "cdc" is also a longest uncommon subsequence.

Example 2:
    Input: a = "aaa", b = "bbb"
    Output: 3
    Explanation: The longest uncommon subsequences are "aaa" and "bbb".

Example 3:
    Input: a = "aaa", b = "aaa"
    Output: -1
    Explanation: Every subsequence of string a is also a subsequence of string b. Similarly, every subsequence of string b is also a subsequence of string a. So the answer would be -1.

Constraints:
    - 1 <= a.length, b.length <= 100
    - a and b consist of lower-case English letters.

Hint: Think very simple.
Hint: If <code>a == b</code>, the answer is -1.
Hint: Otherwise, the answer is the string <code>a</code> or the string <code>b</code>.

Template (python3):
    class Solution:
        def findLUSlength(self, a: str, b: str) -> int:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "521. Longest Uncommon Subsequence I"
    test_cases = [
        TestCase(input=("aba", "cdc"), expected=3, label="example 1"),
        TestCase(input=("aaa", "bbb"), expected=3, label="example 2"),
        TestCase(input=("aaa", "aaa"), expected=-1, label="example 3"),
    ]

    def solve(self, a: str, b: str) -> int:
        return -1 if a == b else max(len(a), len(b))


if __name__ == "__main__":
    Solution().run()
