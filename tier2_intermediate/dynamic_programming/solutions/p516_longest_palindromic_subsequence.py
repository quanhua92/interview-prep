"""
P516: Longest Palindromic Subsequence [PREMIUM] (Medium)
https://leetcode.com/problems/longest-palindromic-subsequence/
Topics: String, Dynamic Programming

Given a string s, find the longest palindromic subsequence's length in s.
A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.
Example 1:
    Input: s = "bbbab"
    Output: 4
    Explanation: One possible longest palindromic subsequence is "bbbb".

Example 2:
    Input: s = "cbbd"
    Output: 2
    Explanation: One possible longest palindromic subsequence is "bb".

Constraints:
    - 1 <= s.length <= 1000
    - s consists only of lowercase English letters.

Template (python3):
    class Solution:
        def longestPalindromeSubseq(self, s: str) -> int:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "516. Longest Palindromic Subsequence"
    test_cases = [
        TestCase(input="bbbab", expected=4, label="example 1"),
        TestCase(input="cbbd", expected=2, label="example 2"),
        TestCase(input="a", expected=1, label="single char"),
        TestCase(input="aa", expected=2, label="two same chars"),
        TestCase(input="abcdef", expected=1, label="all distinct"),
        TestCase(input="aabbaa", expected=6, label="full palindrome"),
    ]

    def solve(self, s: str) -> int:
        n = len(s)
        dp = [[0] * n for _ in range(n)]
        for i in range(n):
            dp[i][i] = 1
        for length in range(2, n + 1):
            for i in range(n - length + 1):
                j = i + length - 1
                if s[i] == s[j]:
                    dp[i][j] = dp[i + 1][j - 1] + 2
                else:
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1])
        return dp[0][n - 1]


if __name__ == "__main__":
    Solution().run()
