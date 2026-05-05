"""P003: Longest Substring Without Repeating Characters (Medium)

TODO: Implement solve() below.
Hint: Use a hash map to track the last index of each character.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "3. Longest Substring Without Repeating Characters"
    test_cases = [
        TestCase(input="abcabcbb", expected=3, label="example 1"),
        TestCase(input="bbbbb", expected=1, label="example 2"),
        TestCase(input="pwwkew", expected=3, label="example 3"),
        TestCase(input="", expected=0, label="empty string"),
    ]

    def solve(self, s: str) -> int:
        raise NotImplementedError("TODO: Implement solve(self, s: str) -> int")


if __name__ == "__main__":
    Solution().run()
