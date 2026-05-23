"""
P392: Is Subsequence [PREMIUM] (Easy)
https://leetcode.com/problems/is-subsequence/
Topics: Two Pointers, String, Dynamic Programming

Given two strings s and t, return true if s is a subsequence of t, or false otherwise.
A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).
Example 1:
    Input: s = "abc", t = "ahbgdc"
    Output: true

Example 2:
    Input: s = "axc", t = "ahbgdc"
    Output: false

Constraints:
    - 0 <= s.length <= 100
    - 0 <= t.length <= 104
    - s and t consist only of lowercase English letters.

Template (python3):
    class Solution:
        def isSubsequence(self, s: str, t: str) -> bool:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "392. Is Subsequence"
    test_cases = [
        TestCase(input=("abc", "ahbgdc"), expected=True, label="example 1"),
        TestCase(input=("axc", "ahbgdc"), expected=False, label="example 2"),
        TestCase(input=("", "ahbgdc"), expected=True, label="empty s is subsequence"),
        TestCase(input=("abc", "abc"), expected=True, label="s equals t"),
        TestCase(input=("abcd", "abc"), expected=False, label="s longer than t"),
        TestCase(input=("z", "aaaaa"), expected=False, label="single char not found"),
    ]

    def solve(self, s: str, t: str) -> bool:
        i = 0
        for ch in t:
            if i < len(s) and s[i] == ch:
                i += 1
        return i == len(s)


if __name__ == "__main__":
    Solution().run()
