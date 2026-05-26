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

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "520. Detect Capital"
    test_cases = [
        TestCase(input="USA", expected=True, label="example 1"),
        TestCase(input="FlaG", expected=False, label="example 2"),
        TestCase(input="a", expected=True, label="single lowercase"),
        TestCase(input="Z", expected=True, label="single uppercase"),
        TestCase(input="leetcode", expected=True, label="all lowercase"),
        TestCase(input="Google", expected=True, label="title case"),
        TestCase(input="mL", expected=False, label="lowercase then uppercase"),
    ]

    def solve(self, word: str) -> bool:
        raise NotImplementedError("TODO: Implement solve(self, word: str)")
if __name__ == "__main__":
    Solution().run()
