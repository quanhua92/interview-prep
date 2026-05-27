"""
P211: Design Add and Search Words Data Structure (Medium)
https://leetcode.com/problems/design-add-and-search-words-data-structure/
Topics: String, Depth-First Search, Design, Trie

Design a data structure that supports adding new words and finding if a string matches any previously added string.
Implement the WordDictionary class:
Example:

Example 1:
    Input
    ["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
    [[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
    Output
    [null,null,null,null,false,true,true,true]

    Explanation
    WordDictionary wordDictionary = new WordDictionary();
    wordDictionary.addWord("bad");
    wordDictionary.addWord("dad");
    wordDictionary.addWord("mad");
    wordDictionary.search("pad"); // return False
    wordDictionary.search("bad"); // return True
    wordDictionary.search(".ad"); // return True
    wordDictionary.search("b.."); // return True

Constraints:
    - 1 <= word.length <= 25
    - word in addWord consists of lowercase English letters.
    - word in search consist of '.' or lowercase English letters.
    - There will be at most 2 dots in word for search queries.
    - At most 104 calls will be made to addWord and search.

Hints:
    - You should be familiar with how a Trie works. If not, please work on this problem: <a href="https://leetcode.com/problems/implement-trie-prefix-tree/">Implement Trie (Prefix Tree)</a> first.

Template (python3):
    class WordDictionary:

        def __init__(self):


        def addWord(self, word: str) -> None:


        def search(self, word: str) -> bool:



    # Your WordDictionary object will be instantiated and called as such:
    # obj = WordDictionary()
    # obj.addWord(word)
    # param_2 = obj.search(word)

Hint: Build a Trie from the word list, then search with DFS handling '.' wildcards by trying all children.
"""

from src.wasm_libs.py.io import *


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


def solve(words: list[str], search_words: list[str]) -> list[bool]:
    wd = WordDictionary()
    for w in words:
        wd.add_word(w)
    return [wd.search(sw) for sw in search_words]


if __name__ == "__main__":
    n_words = read_int()
    words = [read_line() for _ in range(n_words)]
    n_searches = read_int()
    search_words = [read_line() for _ in range(n_searches)]
    results = solve(words, search_words)
    for r in results:
        write_bool(r)
