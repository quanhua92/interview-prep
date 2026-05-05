"""P424: Longest Repeating Character Replacement (Medium)

TODO: Implement solve() below.
Hint: Freq map + max_freq tracker, window valid when len - max_freq <= k. Left only moves right.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "424. Longest Repeating Character Replacement"
    test_cases = [
        TestCase(input=("ABAB", 2), expected=4, label="example 1"),
        TestCase(input=("AABABBA", 1), expected=4, label="example 2"),
        TestCase(input=("AAAA", 0), expected=4, label="no changes needed"),
        TestCase(input=("ABCDE", 1), expected=2, label="all unique"),
    ]

    def solve(self, s: str, k: int) -> int:
        raise NotImplementedError("TODO: Implement solve(self, s: str, k: int) -> int")


if __name__ == "__main__":
    Solution().run()
