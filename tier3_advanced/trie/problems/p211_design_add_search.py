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

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "211. Design Add and Search Words Data Structure"
    test_cases = [
        TestCase(
            input=(["bad", "dad", "mad"], ["pad", "bad", ".ad", "b.."]),
            expected=[False, True, True, True],
            label="example 1",
        ),
        TestCase(
            input=(["a", "ab"], ["a", ".a", "ab"]),
            expected=[True, False, True],
            label="example 2",
        ),
        TestCase(
            input=(["abc"], ["...", ".."]),
            expected=[True, False],
            label="all dots pattern",
        ),
        TestCase(
            input=(["a", "b"], ["."]),
            expected=[True],
            label="single char dot matches multiple",
        ),
        TestCase(
            input=(["abc", "xbc"], [".bc"]),
            expected=[True],
            label="dot at beginning",
        ),
        TestCase(
            input=(["abc"], ["a.c", "a.."]),
            expected=[True, True],
            label="dot in middle and at end",
        ),
    ]

    def solve(self, words: list[str], search_words: list[str]) -> list[bool]:
        raise NotImplementedError(
            "TODO: Implement solve(self, words: list[str], search_words: list[str]) -> list[bool]"
        )


if __name__ == "__main__":
    Solution().run()
