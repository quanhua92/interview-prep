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
    - At most 10^4 calls will be made to addWord and search.

Hints:
    - You should be familiar with how a Trie works. If not, please work on this problem: <a href="https://leetcode.com/problems/implement-trie-prefix-tree/">Implement Trie (Prefix Tree)</a> first.

Template (python3):
    class WordDictionary:

        def __init__(self):
            raise NotImplementedError
        def addWord(self, word: str) -> None:
            raise NotImplementedError
        def search(self, word: str) -> bool:
            raise NotImplementedError
Hint: Build a Trie from the word list, then search with DFS handling '.' wildcards by trying all children.
"""

from src.wasm_libs.py.io import *


class TrieNode:
    def __init__(self):
        raise NotImplementedError
class WordDictionary:
    def __init__(self):
        raise NotImplementedError
    def add_word(self, word: str) -> None:
        raise NotImplementedError
    def search(self, word: str) -> bool:
        raise NotImplementedError
    def _dfs(self, node: TrieNode, word: str, index: int) -> bool:
        raise NotImplementedError
def solve(words: list[str], search_words: list[str]) -> list[bool]:
    raise NotImplementedError
if __name__ == "__main__":
    n_words = read_int()
    words = [read_line() for _ in range(n_words)]
    n_searches = read_int()
    search_words = [read_line() for _ in range(n_searches)]
    results = solve(words, search_words)
    for r in results:
        write_bool(r)
