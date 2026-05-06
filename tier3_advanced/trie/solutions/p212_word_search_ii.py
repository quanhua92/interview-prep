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
    ]

    def solve(self, board: list[list[str]], words: list[str]) -> list[str]:
        rows, cols = len(board), len(board[0])
        result: list[str] = []

        def _build_trie(words: list[str]) -> TrieNode:
            root = TrieNode()
            for w in words:
                node = root
                for ch in w:
                    if ch not in node.children:
                        node.children[ch] = TrieNode()
                    node = node.children[ch]
                node.word = w
            return root

        def dfs(r: int, c: int, parent: TrieNode):
            ch = board[r][c]
            curr = parent.children.get(ch)
            if not curr:
                return
            if curr.word:
                result.append(curr.word)
                curr.word = None  # avoid duplicates
            board[r][c] = "#"
            for dr, dc in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                nr, nc = r + dr, c + dc
                if 0 <= nr < rows and 0 <= nc < cols and board[nr][nc] != "#":
                    dfs(nr, nc, curr)
            board[r][c] = ch
            if not curr.children:
                parent.children.pop(ch)

        root = _build_trie(words)
        for r in range(rows):
            for c in range(cols):
                dfs(r, c, root)
        return sorted(result)


if __name__ == "__main__":
    Solution().run()
