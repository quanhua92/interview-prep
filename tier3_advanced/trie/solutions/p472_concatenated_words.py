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
    ]

    def solve(self, words: list[str]) -> list[str]:
        class TrieNode:
            def __init__(self):
                self.children: dict[str, "TrieNode"] = {}
                self.is_end = False

        root = TrieNode()

        def insert(word: str):
            node = root
            for ch in word:
                if ch not in node.children:
                    node.children[ch] = TrieNode()
                node = node.children[ch]
            node.is_end = True

        def can_concatenate(word: str, start: int, count: int) -> bool:
            node = root
            for i in range(start, len(word)):
                ch = word[i]
                if ch not in node.children:
                    return False
                node = node.children[ch]
                if node.is_end:
                    if i == len(word) - 1:
                        return count >= 1
                    if can_concatenate(word, i + 1, count + 1):
                        return True
            return False

        words_sorted = sorted(words, key=len)
        result = []
        for word in words_sorted:
            if can_concatenate(word, 0, 0):
                result.append(word)
            insert(word)
        return sorted(result)

    def solve_alternative(self, words: list[str]) -> list[str]:
        word_set = set(words)

        def can_form(word: str) -> bool:
            if not word:
                return False
            dp = [False] * (len(word) + 1)
            dp[0] = True
            for i in range(1, len(word) + 1):
                for j in range(i):
                    if dp[j] and word[j:i] in word_set:
                        if j != 0 or i != len(word):
                            dp[i] = True
                            break
            return dp[len(word)]

        result = []
        for word in sorted(words, key=len):
            if can_form(word):
                result.append(word)
        return sorted(result)


if __name__ == "__main__":
    Solution().run()
