"""
P520: Detect Capital [PREMIUM] (Easy)
https://leetcode.com/problems/detect-capital/
Topics: String

We define the usage of capitals in a word to be right when one of the following cases holds:
Given a string word, return true if the usage of capitals in it is right.
Example 1:
    Input: word = "USA"
    Output: true

Example 2:
    Input: word = "FlaG"
    Output: false

Constraints:
    - 1 <= word.length <= 100
    - word consists of lowercase and uppercase English letters.

Template (python3):
    class Solution:
        def detectCapitalUse(self, word: str) -> bool:
"""

from src.wasm_libs.py.io import *


def solve(word: str) -> bool:
    raise NotImplementedError


if __name__ == "__main__":
    word = read_line()
    result = solve(word)
    write_bool(result)
