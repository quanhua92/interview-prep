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
    - At most 3 * 10^4 calls in total will be made to insert, search, and startsWith.

Template (python3):
    class Trie:

        def __init__(self):
            raise NotImplementedError
        def insert(self, word: str) -> None:
            raise NotImplementedError
        def search(self, word: str) -> bool:
            raise NotImplementedError
        def startsWith(self, prefix: str) -> bool:
            raise NotImplementedError
Hint: Build a Trie class with insert, search, and starts_with methods.
"""

from src.wasm_libs.py.io import *


class TrieNode:
    def __init__(self):
        raise NotImplementedError
class Trie:
    def __init__(self):
        raise NotImplementedError
    def insert(self, word: str) -> None:
        raise NotImplementedError
    def search(self, word: str) -> bool:
        raise NotImplementedError
    def starts_with(self, prefix: str) -> bool:
        raise NotImplementedError
    def _find(self, prefix: str) -> TrieNode | None:
        raise NotImplementedError
def solve(operations: list[tuple[str, str]]) -> list:
    raise NotImplementedError
if __name__ == "__main__":
    n = read_int()
    operations = []
    for _ in range(n):
        op = read_line()
        val = read_line()
        operations.append((op, val))
    results = solve(operations)
    for r in results:
        if r is None:
            write_string("null")
        else:
            write_bool(r)
