"""
P212: Word Search II (Hard)
https://leetcode.com/problems/word-search-ii/
Topics: Array, String, Backtracking, Trie, Matrix

Given an m x n board of characters and a list of strings words, return all words on the board.
Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

Example 1:
    Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
    Output: ["eat","oath"]

Example 2:
    Input: board = [["a","b"],["c","d"]], words = ["abcb"]
    Output: []

Constraints:
    - m == board.length
    - n == board[i].length
    - 1 <= m, n <= 12
    - board[i][j] is a lowercase English letter.
    - 1 <= words.length <= 3 * 104
    - 1 <= words[i].length <= 10
    - words[i] consists of lowercase English letters.
    - All the strings of words are unique.

Hints:
    - You would need to optimize your backtracking to pass the larger test. Could you stop backtracking earlier?
    - If the current candidate does not exist in all words&#39; prefix, you could stop backtracking immediately. What kind of data structure could answer such query efficiently? Does a hash table work? Why or why not? How about a Trie? If you would like to learn how to implement a basic trie, please work on this problem: <a href="https://leetcode.com/problems/implement-trie-prefix-tree/">Implement Trie (Prefix Tree)</a> first.

Template (python3):
    class Solution:
        def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:

Hint: Build a Trie from the word list, then use DFS on the board to find matching words.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class TrieNode:
    def __init__(self):
        self.children: dict[str, TrieNode] = {}
        self.word: str | None = None


class Solution(Problem):
    name = "212. Word Search II"
    test_cases = [
        TestCase(
            input=(
                [
                    ["o", "a", "a", "n"],
                    ["e", "t", "a", "e"],
                    ["i", "h", "k", "r"],
                    ["i", "f", "l", "v"],
                ],
                ["oath", "pea", "eat", "rain"],
            ),
            expected=["eat", "oath"],
            label="example 1",
        ),
        TestCase(
            input=([["a", "b"], ["c", "d"]], ["abcb"]), expected=[], label="example 2"
        ),
        TestCase(
            input=([["a"]], ["a"]),
            expected=["a"],
            label="1x1 board single char",
        ),
        TestCase(
            input=([["a", "b"], ["c", "d"]], ["xyz"]),
            expected=[],
            label="word not on board",
        ),
        TestCase(
            input=([["a", "a"], ["a", "a"]], ["aaaa"]),
            expected=["aaaa"],
            label="same letter grid",
        ),
        TestCase(
            input=(
                [
                    ["o", "a", "a", "n"],
                    ["e", "t", "a", "e"],
                    ["i", "h", "k", "r"],
                    ["i", "f", "l", "v"],
                ],
                ["oath", "oat"],
            ),
            expected=["oat", "oath"],
            label="prefix is also a word",
        ),
    ]

    def solve(self, board: list[list[str]], words: list[str]) -> list[str]:
        raise NotImplementedError(
            "TODO: Implement solve(self, board: list[list[str]], words: list[str]) -> list[str]"
        )


if __name__ == "__main__":
    Solution().run()
