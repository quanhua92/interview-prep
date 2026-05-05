"""P211: Design Add and Search Words Data Structure (Medium)

TODO: Implement solve() below.
Hint: Build a Trie from the word list, then search with DFS handling '.' wildcards by trying all children.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


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
        raise NotImplementedError("TODO: Implement solve(self, words: list[str], search_words: list[str]) -> list[bool]")


if __name__ == "__main__":
    Solution().run()
