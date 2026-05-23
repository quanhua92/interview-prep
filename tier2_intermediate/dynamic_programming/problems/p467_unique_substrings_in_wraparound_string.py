"""
P467: Unique Substrings in Wraparound String [PREMIUM] (Medium)
https://leetcode.com/problems/unique-substrings-in-wraparound-string/
Topics: String, Dynamic Programming

We define the string base to be the infinite wraparound string of "abcdefghijklmnopqrstuvwxyz", so base will look like this:
Given a string s, return the number of unique non-empty substrings of s are present in base.
Example 1:
    Input: s = "a"
    Output: 1
    Explanation: Only the substring "a" of s is in base.

Example 2:
    Input: s = "cac"
    Output: 2
    Explanation: There are two substrings ("a", "c") of s in base.

Example 3:
    Input: s = "zab"
    Output: 6
    Explanation: There are six substrings ("z", "a", "b", "za", "ab", and "zab") of s in base.

Constraints:
    - 1 <= s.length <= 105
    - s consists of lowercase English letters.

Hint: One possible solution might be to consider allocating an array size of 26 for each character in the alphabet. (Credits to @r2ysxu)

Template (python3):
    class Solution:
        def findSubstringInWraproundString(self, s: str) -> int:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "467. Unique Substrings in Wraparound String"
    test_cases = [
        TestCase(input="a", expected=1, label="example 1"),
        TestCase(input="cac", expected=2, label="example 2"),
        TestCase(input="zab", expected=6, label="example 3"),
        TestCase(input="aaaaa", expected=1, label="all same chars only a in wraparound"),
        TestCase(input="zabcdefg", expected=36, label="wraparound chain length 8"),
        TestCase(input="abcdefghijklmnopqrstuvwxyz", expected=351, label="full alphabet"),
    ]

    def solve(self, s: str) -> int:
        raise NotImplementedError("TODO: Implement solve(self, s) -> int")


if __name__ == "__main__":
    Solution().run()
