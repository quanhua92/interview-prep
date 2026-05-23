"""
P208: Implement Trie (Prefix Tree) (Medium)
https://leetcode.com/problems/implement-trie-prefix-tree/
Topics: Hash Table, String, Design, Trie

A trie (pronounced as "try") or prefix tree is a tree data structure used to efficiently store and retrieve keys in a dataset of strings. There are various applications of this data structure, such as autocomplete and spellchecker.
Implement the Trie class:

Example 1:
    Input
    ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
    [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
    Output
    [null, null, true, false, true, null, true]

    Explanation
    Trie trie = new Trie();
    trie.insert("apple");
    trie.search("apple");   // return True
    trie.search("app");     // return False
    trie.startsWith("app"); // return True
    trie.insert("app");
    trie.search("app");     // return True

Constraints:
    - 1 <= word.length, prefix.length <= 2000
    - word and prefix consist only of lowercase English letters.
    - At most 3 * 104 calls in total will be made to insert, search, and startsWith.

Template (python3):
    class Trie:

        def __init__(self):


        def insert(self, word: str) -> None:


        def search(self, word: str) -> bool:


        def startsWith(self, prefix: str) -> bool:



    # Your Trie object will be instantiated and called as such:
    # obj = Trie()
    # obj.insert(word)
    # param_2 = obj.search(word)
    # param_3 = obj.startsWith(prefix)

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
            label="full sequence",
        ),
        TestCase(
            input=[
                ("insert", "a"),
                ("search", "a"),
                ("search", "b"),
                ("starts_with", "a"),
                ("starts_with", "b"),
            ],
            expected=[None, True, False, True, False],
            label="single character",
        ),
        TestCase(
            input=[
                ("insert", "hello"),
                ("search", "world"),
                ("starts_with", "world"),
                ("search", "hel"),
                ("starts_with", "hel"),
            ],
            expected=[None, False, False, False, True],
            label="search non-existent word/prefix",
        ),
        TestCase(
            input=[
                ("insert", "a"),
                ("insert", "ab"),
                ("insert", "abc"),
                ("search", "a"),
                ("search", "ab"),
                ("search", "abc"),
                ("search", "abcd"),
                ("starts_with", "ab"),
                ("starts_with", "abcd"),
            ],
            expected=[None, None, None, True, True, True, False, True, False],
            label="overlapping prefixes",
        ),
        TestCase(
            input=[
                ("insert", "test"),
                ("insert", "test"),
                ("search", "test"),
                ("starts_with", "te"),
            ],
            expected=[None, None, True, True],
            label="duplicate insert",
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
