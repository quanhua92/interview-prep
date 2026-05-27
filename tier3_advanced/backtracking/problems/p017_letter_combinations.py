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

from src.wasm_libs.py.io import *


def solve(digits: str) -> list[str]:
    raise NotImplementedError


if __name__ == "__main__":
    digits = read_line()
    combos = solve(digits)
    for c in combos:
        write_string(c)
