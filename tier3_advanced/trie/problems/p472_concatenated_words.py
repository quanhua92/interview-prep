"""
P472: Concatenated Words [PREMIUM] (Hard)
https://leetcode.com/problems/concatenated-words/
Topics: Array, String, Dynamic Programming, Depth-First Search, Trie, Sorting

Given an array of strings words (without duplicates), return all the concatenated words in the given list of words.
A concatenated word is defined as a string that is comprised entirely of at least two shorter words (not necessarily distinct) in the given array.
Example 1:
    Input: words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
    Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]
    Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats";
    "dogcatsdog" can be concatenated by "dog", "cats" and "dog";
    "ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".

Example 2:
    Input: words = ["cat","dog","catdog"]
    Output: ["catdog"]

Constraints:
    - 1 <= words.length <= 104
    - 1 <= words[i].length <= 30
    - words[i] consists of only lowercase English letters.
    - All the strings of words are unique.
    - 1 <= sum(words[i].length) <= 105

Template (python3):
    class Solution:
        def findAllConcatenatedWordsInADict(self, words: List[str]) -> List[str]:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "472. Concatenated Words"
    test_cases = [
        TestCase(
            input=[
                "cat",
                "cats",
                "catsdogcats",
                "dog",
                "dogcatsdog",
                "hippopotamuses",
                "rat",
                "ratcatdogcat",
            ],
            expected=["catsdogcats", "dogcatsdog", "ratcatdogcat"],
            label="example 1",
        ),
        TestCase(
            input=["cat", "dog", "catdog"], expected=["catdog"], label="example 2"
        ),
        TestCase(
            input=["cat", "catcat"],
            expected=["catcat"],
            label="word from duplicate parts",
        ),
        TestCase(
            input=["a", "b", "c"],
            expected=[],
            label="no concatenated words",
        ),
        TestCase(
            input=["a", "aa", "aaaa"],
            expected=["aa", "aaaa"],
            label="deep concatenation chain",
        ),
        TestCase(
            input=["ab", "abab"],
            expected=["abab"],
            label="self-similar concatenation",
        ),
    ]

    def solve(self, words: list[str]) -> list[str]:
        raise NotImplementedError("TODO: Implement solve(self, words) -> list[str]")


if __name__ == "__main__":
    Solution().run()
