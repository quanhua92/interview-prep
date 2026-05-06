"""
P522: Longest Uncommon Subsequence II [PREMIUM] (Medium)
https://leetcode.com/problems/longest-uncommon-subsequence-ii/
Topics: Array, Hash Table, Two Pointers, String, Sorting

Given an array of strings strs, return the length of the longest uncommon subsequence between them. If the longest uncommon subsequence does not exist, return -1.
An uncommon subsequence between an array of strings is a string that is a subsequence of one string but not the others.
A subsequence of a string s is a string that can be obtained after deleting any number of characters from s.
Example 1:
    Input: strs = ["aba","cdc","eae"]
    Output: 3

Example 2:
    Input: strs = ["aaa","aaa","aa"]
    Output: -1

Constraints:
    - 2 <= strs.length <= 50
    - 1 <= strs[i].length <= 10
    - strs[i] consists of lowercase English letters.

Template (python3):
    class Solution:
        def findLUSlength(self, strs: List[str]) -> int:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "522. Longest Uncommon Subsequence II"
    test_cases = [
        TestCase(input=["aba", "cdc", "eae"], expected=3, label="example 1"),
        TestCase(input=["aaa", "aaa", "aa"], expected=-1, label="example 2"),
    ]

    def solve(self, strs: list[str]) -> int:
        raise NotImplementedError("TODO: Implement solve(self, strs) -> int")


if __name__ == "__main__":
    Solution().run()
