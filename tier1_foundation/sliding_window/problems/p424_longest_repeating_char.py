"""
P424: Longest Repeating Character Replacement (Medium)
https://leetcode.com/problems/longest-repeating-character-replacement/
Topics: Hash Table, String, Sliding Window

You are given a string s and an integer k. You can choose any character of the string and change it to any other uppercase English character. You can perform this operation at most k times.
Return the length of the longest substring containing the same letter you can get after performing the above operations.

Example 1:
    Input: s = "ABAB", k = 2
    Output: 4
    Explanation: Replace the two 'A's with two 'B's or vice versa.

Example 2:
    Input: s = "AABABBA", k = 1
    Output: 4
    Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
    The substring "BBBB" has the longest repeating letters, which is 4.
    There may exists other ways to achieve this answer too.

Constraints:
    - 1 <= s.length <= 105
    - s consists of only uppercase English letters.
    - 0 <= k <= s.length

Template (python3):
    class Solution:
        def characterReplacement(self, s: str, k: int) -> int:

Hint: Freq map + max_freq tracker, window valid when len - max_freq <= k. Left only moves right.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "424. Longest Repeating Character Replacement"
    test_cases = [
        TestCase(input=("ABAB", 2), expected=4, label="example 1"),
        TestCase(input=("AABABBA", 1), expected=4, label="example 2"),
        TestCase(input=("AAAA", 0), expected=4, label="no changes needed"),
        TestCase(input=("ABCDE", 1), expected=2, label="all unique"),
    ]

    def solve(self, s: str, k: int) -> int:
        raise NotImplementedError("TODO: Implement solve(self, s: str, k: int) -> int")


if __name__ == "__main__":
    Solution().run()
