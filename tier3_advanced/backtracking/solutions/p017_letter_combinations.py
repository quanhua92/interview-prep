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
        if not digits:
            return []

        phone_map = {
            "2": "abc", "3": "def", "4": "ghi", "5": "jkl",
            "6": "mno", "7": "pqrs", "8": "tuv", "9": "wxyz",
        }
        result: list[str] = []

        def backtrack(index: int, path: list[str]):
            if index == len(digits):
                result.append("".join(path))
                return
            for letter in phone_map[digits[index]]:
                path.append(letter)
                backtrack(index + 1, path)
                path.pop()

        backtrack(0, [])
        return sorted(result)


if __name__ == "__main__":
    Solution().run()
