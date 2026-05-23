"""
P438: Find All Anagrams in a String (Medium)
https://leetcode.com/problems/find-all-anagrams-in-a-string/
Topics: Hash Table, String, Sliding Window

Given two strings s and p, return an array of all the start indices of p's anagrams in s. You may return the answer in any order.

Example 1:
    Input: s = "cbaebabacd", p = "abc"
    Output: [0,6]
    Explanation:
    The substring with start index = 0 is "cba", which is an anagram of "abc".
    The substring with start index = 6 is "bac", which is an anagram of "abc".

Example 2:
    Input: s = "abab", p = "ab"
    Output: [0,1,2]
    Explanation:
    The substring with start index = 0 is "ab", which is an anagram of "ab".
    The substring with start index = 1 is "ba", which is an anagram of "ab".
    The substring with start index = 2 is "ab", which is an anagram of "ab".

Constraints:
    - 1 <= s.length, p.length <= 3 * 104
    - s and p consist of lowercase English letters.

Template (python3):
    class Solution:
        def findAnagrams(self, s: str, p: str) -> List[int]:

Hint: Use a sliding window with frequency counters to compare against pattern.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "438. Find All Anagrams in a String"
    test_cases = [
        TestCase(input=("cbaebabacd", "abc"), expected=[0, 6], label="example 1"),
        TestCase(input=("abab", "ab"), expected=[0, 1, 2], label="example 2"),
        TestCase(input=("af", "bf"), expected=[], label="no anagrams"),
        TestCase(input=("abc", "abc"), expected=[0], label="exact match single"),
        TestCase(input=("aaaaaaaaaa", "aa"), expected=[0, 1, 2, 3, 4, 5, 6, 7, 8], label="all same chars"),
        TestCase(input=("abacbabc", "abc"), expected=[1, 2, 3, 5], label="overlapping anagrams"),
        TestCase(input=("a", "aa"), expected=[], label="pattern longer than string"),
    ]

    def solve(self, s: str, p: str) -> list[int]:
        from collections import Counter

        if len(p) > len(s):
            return []
        p_count = Counter(p)
        s_count = Counter(s[: len(p)])
        result = []
        if s_count == p_count:
            result.append(0)
        for i in range(len(p), len(s)):
            s_count[s[i]] += 1
            s_count[s[i - len(p)]] -= 1
            if s_count[s[i - len(p)]] == 0:
                del s_count[s[i - len(p)]]
            if s_count == p_count:
                result.append(i - len(p) + 1)
        return result


if __name__ == "__main__":
    Solution().run()
