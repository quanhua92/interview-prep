"""P017: Letter Combinations of a Phone Number (Medium)

TODO: Implement solve() below.
Hint: Map each digit to its letters and use backtracking to build all combinations.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "17. Letter Combinations of a Phone Number"
    test_cases = [
        TestCase(input="23", expected=["ad","ae","af","bd","be","bf","cd","ce","cf"], label="example 1"),
        TestCase(input="", expected=[], label="empty input"),
        TestCase(input="2", expected=["a","b","c"], label="single digit"),
    ]

    def solve(self, digits: str) -> list[str]:
        raise NotImplementedError("TODO: Implement solve(self, digits: str) -> list[str]")


if __name__ == "__main__":
    Solution().run()
