"""
P17: Letter Combinations of a Phone Number (Medium)
https://leetcode.com/problems/letter-combinations-of-a-phone-number/
Topics: Hash Table, String, Backtracking

Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.
A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.

Example 1:
    Input: digits = "23"
    Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

Example 2:
    Input: digits = ""
    Output: []

Example 3:
    Input: digits = "2"
    Output: ["a","b","c"]

Constraints:
    - 0 <= digits.length <= 4
    - digits[i] is a digit in the range ['2', '9'].

Template (python3):
    class Solution:
        def letterCombinations(self, digits: str) -> List[str]:

Hint: Map each digit to its letters and use backtracking to build all combinations.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "17. Letter Combinations of a Phone Number"
    test_cases = [
        TestCase(
            input="23",
            expected=["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"],
            label="example 1",
        ),
        TestCase(input="", expected=[], label="empty input"),
        TestCase(input="2", expected=["a", "b", "c"], label="single digit"),
        TestCase(input="7", expected=["p", "q", "r", "s"], label="digit with 4 letters"),
        TestCase(input="9", expected=["w", "x", "y", "z"], label="digit 9"),
        TestCase(
            input="79",
            expected=[
                "pw", "px", "py", "pz", "qw", "qx", "qy", "qz",
                "rw", "rx", "ry", "rz", "sw", "sx", "sy", "sz",
            ],
            label="two 4-letter digits",
        ),
    ]

    def solve(self, digits: str) -> list[str]:
        if not digits:
            return []

        phone_map = {
            "2": "abc",
            "3": "def",
            "4": "ghi",
            "5": "jkl",
            "6": "mno",
            "7": "pqrs",
            "8": "tuv",
            "9": "wxyz",
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
