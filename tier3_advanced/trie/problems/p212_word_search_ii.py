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
    - 1 <= words.length <= 3 * 10^4
    - 1 <= words[i].length <= 10
    - words[i] consists of lowercase English letters.
    - All the strings of words are unique.

Hints:
    - You would need to optimize your backtracking to pass the larger test. Could you stop backtracking earlier?
    - If the current candidate does not exist in all words&#39; prefix, you could stop backtracking immediately. What kind of data structure could answer such query efficiently? Does a hash table work? Why or why not? How about a Trie? If you would like to learn how to implement a basic trie, please work on this problem: <a href="https://leetcode.com/problems/implement-trie-prefix-tree/">Implement Trie (Prefix Tree)</a> first.

Template (python3):
    class Solution:
        def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
            raise NotImplementedError
Hint: Build a Trie from the word list, then use DFS on the board to find matching words.
"""

from src.wasm_libs.py.io import *


class TrieNode:
    def __init__(self):
        raise NotImplementedError
def solve(board: list[list[str]], words: list[str]) -> list[str]:
    raise NotImplementedError
if __name__ == "__main__":
    rows = read_int()
    cols = read_int()
    board = []
    for _ in range(rows):
        line = read_line()
        board.append(list(line))
    n_words = read_int()
    words = [read_line() for _ in range(n_words)]
    result = solve(board, words)
    write_int(len(result))
    for w in result:
        write_string(w)
