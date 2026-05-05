"""P211: Design Add and Search Words Data Structure (Medium)

TODO: Implement solve() below.
Hint: Build a Trie from the word list, then search with DFS handling '.' wildcards by trying all children.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class TrieNode:
    def __init__(self):
        self.children: dict[str, TrieNode] = {}
        self.is_end = False


class WordDictionary:
    def __init__(self):
        self.root = TrieNode()

    def add_word(self, word: str) -> None:
        node = self.root
        for ch in word:
            if ch not in node.children:
                node.children[ch] = TrieNode()
            node = node.children[ch]
        node.is_end = True

    def search(self, word: str) -> bool:
        return self._dfs(self.root, word, 0)

    def _dfs(self, node: TrieNode, word: str, index: int) -> bool:
        if index == len(word):
            return node.is_end
        ch = word[index]
        if ch == ".":
            for child in node.children.values():
                if self._dfs(child, word, index + 1):
                    return True
            return False
        if ch not in node.children:
            return False
        return self._dfs(node.children[ch], word, index + 1)


class Solution(Problem):
    name = "211. Design Add and Search Words Data Structure"
    test_cases = [
        TestCase(
            input=(["bad","dad","mad"], ["pad","bad",".ad","b.."]),
            expected=[False, True, True, True],
            label="example 1",
        ),
        TestCase(
            input=(["a","ab"], ["a",".a","ab"]),
            expected=[True, False, True],
            label="example 2",
        ),
    ]

    def solve(self, words: list[str], search_words: list[str]) -> list[bool]:
        wd = WordDictionary()
        for w in words:
            wd.add_word(w)
        return [wd.search(sw) for sw in search_words]


if __name__ == "__main__":
    Solution().run()
