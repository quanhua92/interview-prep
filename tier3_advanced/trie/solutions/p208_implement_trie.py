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
        node = self.root
        for ch in word:
            if ch not in node.children:
                node.children[ch] = TrieNode()
            node = node.children[ch]
        node.is_end = True

    def search(self, word: str) -> bool:
        node = self._find(word)
        return node is not None and node.is_end

    def starts_with(self, prefix: str) -> bool:
        return self._find(prefix) is not None

    def _find(self, prefix: str) -> TrieNode | None:
        node = self.root
        for ch in prefix:
            if ch not in node.children:
                return None
            node = node.children[ch]
        return node

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
        trie = Trie()
        results = []
        for op, val in operations:
            if op == "insert":
                trie.insert(val)
                results.append(None)
            elif op == "search":
                results.append(trie.search(val))
            elif op == "starts_with":
                results.append(trie.starts_with(val))
        return results

if __name__ == "__main__":
    Solution().run()
