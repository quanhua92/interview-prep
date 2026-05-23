"""
P3: Longest Substring Without Repeating Characters (Medium)
https://leetcode.com/problems/longest-substring-without-repeating-characters/
Topics: Hash Table, String, Sliding Window

Given a string s, find the length of the longest substring without duplicate characters.

Example 1:
    Input: s = "abcabcbb"
    Output: 3
    Explanation: The answer is "abc", with the length of 3.

Example 2:
    Input: s = "bbbbb"
    Output: 1
    Explanation: The answer is "b", with the length of 1.

Example 3:
    Input: s = "pwwkew"
    Output: 3
    Explanation: The answer is "wke", with the length of 3.
    Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.

Constraints:
    - 0 <= s.length <= 5 * 104
    - s consists of English letters, digits, symbols and spaces.

Hints:
    - Generate all possible substrings & check for each substring if it's valid and keep updating maxLen accordingly.

Template (python3):
    class Solution:
        def lengthOfLongestSubstring(self, s: str) -> int:

Hint: Use a hash map to track the last index of each character.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "3. Longest Substring Without Repeating Characters"
    test_cases = [
        TestCase(input="abcabcbb", expected=3, label="example 1"),
        TestCase(input="bbbbb", expected=1, label="example 2"),
        TestCase(input="pwwkew", expected=3, label="example 3"),
        TestCase(input="", expected=0, label="empty string"),
        TestCase(input="a", expected=1, label="single character"),
        TestCase(input=" ", expected=1, label="single space"),
        TestCase(input="au", expected=2, label="two unique chars"),
        TestCase(input="dvdf", expected=3, label="reset from duplicate after unique prefix"),
        TestCase(input="tmmzuxt", expected=5, label="char seen before current window"),
    ]

    def solve(self, s: str) -> int:
        char_index: dict[str, int] = {}
        left = 0
        max_len = 0
        for right, ch in enumerate(s):
            if ch in char_index and char_index[ch] >= left:
                left = char_index[ch] + 1
            char_index[ch] = right
            max_len = max(max_len, right - left + 1)
        return max_len


if __name__ == "__main__":
    Solution().run()
