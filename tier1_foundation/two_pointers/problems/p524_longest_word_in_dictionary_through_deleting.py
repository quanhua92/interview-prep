"""
P524: Longest Word in Dictionary through Deleting [PREMIUM] (Medium)
https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/
Topics: Array, Two Pointers, String, Sorting

Given a string s and a string array dictionary, return the longest string in the dictionary that can be formed by deleting some of the given string characters. If there is more than one possible result, return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.
Example 1:
    Input: s = "abpcplea", dictionary = ["ale","apple","monkey","plea"]
    Output: "apple"

Example 2:
    Input: s = "abpcplea", dictionary = ["a","b","c"]
    Output: "a"

Constraints:
    - 1 <= s.length <= 1000
    - 1 <= dictionary.length <= 1000
    - 1 <= dictionary[i].length <= 1000
    - s and dictionary[i] consist of lowercase English letters.

Template (python3):
    class Solution:
        def findLongestWord(self, s: str, dictionary: List[str]) -> str:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "524. Longest Word in Dictionary through Deleting"
    test_cases = [
        TestCase(
            input=("abpcplea", ["ale", "apple", "monkey", "plea"]),
            expected="apple",
            label="example 1",
        ),
        TestCase(input=("abpcplea", ["a", "b", "c"]), expected="a", label="example 2"),
        TestCase(input=("abpcplea", []), expected="", label="empty dictionary"),
        TestCase(input=("abc", ["xyz", "def"]), expected="", label="no match"),
        TestCase(input=("abpcplea", ["apple", "ale", "abpple"]), expected="abpple", label="same length lexicographical tie"),
        TestCase(input=("a", ["a", "aa", "aaa"]), expected="a", label="longer dict words than s"),
    ]

    def solve(self, s: str, dictionary: list[str]) -> str:
        raise NotImplementedError("TODO: Implement solve(self, s, dictionary) -> str")


if __name__ == "__main__":
    Solution().run()
