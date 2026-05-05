"""P438: Find All Anagrams in a String (Medium)

TODO: Implement solve() below.
Hint: Use a sliding window with frequency counters to compare against pattern.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "438. Find All Anagrams in a String"
    test_cases = [
        TestCase(input=("cbaebabacd", "abc"), expected=[0, 6], label="example 1"),
        TestCase(input=("abab", "ab"), expected=[0, 1, 2], label="example 2"),
        TestCase(input=("af", "bf"), expected=[], label="no anagrams"),
    ]

    def solve(self, s: str, p: str) -> list[int]:
        raise NotImplementedError("TODO: Implement solve(self, s: str, p: str) -> list[int]")


if __name__ == "__main__":
    Solution().run()
