"""P208: Implement Trie (Prefix Tree) (Medium)

TODO: Implement solve() below.
Hint: Build a Trie class with insert, search, and starts_with methods.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class TrieNode:
    def __init__(self):
        self.children: dict[str, TrieNode] = {}
        self.is_end = False

class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word: str) -> None:
        ...

    def search(self, word: str) -> bool:
        ...

    def starts_with(self, prefix: str) -> bool:
        ...

    def _find(self, prefix: str) -> TrieNode | None:
        ...

class Solution(Problem):
    name = "208. Implement Trie (Prefix Tree)"
    test_cases = [
        TestCase(
            input=[
                ("insert", "apple"),
                ("search", "apple"),
                ("search", "app"),
                ("starts_with", "app"),
                ("insert", "app"),
                ("search", "app"),
            ],
            expected=[None, True, False, True, None, True],
            label="full sequence"
        ),
    ]

    def solve(self, operations: list[tuple[str, str]], expected: list = None) -> list:
        raise NotImplementedError("TODO: Implement solve(self, operations: list[tuple[str, str]], expected: list = None) -> list")

if __name__ == "__main__":
    Solution().run()
