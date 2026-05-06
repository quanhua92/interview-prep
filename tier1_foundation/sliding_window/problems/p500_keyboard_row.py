"""
P500: Keyboard Row [PREMIUM] (Easy)
https://leetcode.com/problems/keyboard-row/
Topics: Array, Hash Table, String

Given an array of strings words, return the words that can be typed using letters of the alphabet on only one row of American keyboard like the image below.
Note that the strings are case-insensitive, both lowercased and uppercased of the same letter are treated as if they are at the same row.
In the American keyboard:
Example 1:
    Input: words = ["Hello","Alaska","Dad","Peace"]
    Output: ["Alaska","Dad"]
    Explanation:
    Both "a" and "A" are in the 2nd row of the American keyboard due to case insensitivity.

Example 2:
    Input: words = ["omk"]
    Output: []

Example 3:
    Input: words = ["adsdf","sfd"]
    Output: ["adsdf","sfd"]

Constraints:
    - 1 <= words.length <= 20
    - 1 <= words[i].length <= 100
    - words[i] consists of English letters (both lowercase and uppercase).

Template (python3):
    class Solution:
        def findWords(self, words: List[str]) -> List[str]:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "500. Keyboard Row"
    test_cases = [
        TestCase(
            input=["Hello", "Alaska", "Dad", "Peace"],
            expected=["Alaska", "Dad"],
            label="example 1",
        ),
        TestCase(input=["omk"], expected=[], label="example 2"),
        TestCase(input=["adsdf", "sfd"], expected=["adsdf", "sfd"], label="example 3"),
    ]

    def solve(self, words: list[str]) -> list[str]:
        raise NotImplementedError("TODO: Implement solve(self, words) -> list[str]")


if __name__ == "__main__":
    Solution().run()
