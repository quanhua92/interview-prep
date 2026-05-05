"""P212: Word Search II (Hard)

TODO: Implement solve() below.
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
                [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]],
                ["oath","pea","eat","rain"]
            ),
            expected=["eat","oath"],
            label="example 1"
        ),
        TestCase(
            input=([["a","b"],["c","d"]], ["abcb"]),
            expected=[],
            label="example 2"
        ),
    ]

    def solve(self, board: list[list[str]], words: list[str]) -> list[str]:
        raise NotImplementedError("TODO: Implement solve(self, board: list[list[str]], words: list[str]) -> list[str]")

if __name__ == "__main__":
    Solution().run()
