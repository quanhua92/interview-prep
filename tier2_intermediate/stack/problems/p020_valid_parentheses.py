"""
P20: Valid Parentheses (Easy)
https://leetcode.com/problems/valid-parentheses/
Topics: String, Stack

Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
An input string is valid if:

Example 1:
    Input: s = "()"
    Output: true

Example 2:
    Input: s = "()[]{}"
    Output: true

Example 3:
    Input: s = "(]"
    Output: false

Example 4:
    Input: s = "([])"
    Output: true

Example 5:
    Input: s = "([)]"
    Output: false

Constraints:
    - 1 <= s.length <= 104
    - s consists of parentheses only '()[]{}'.

Hints:
    - Use a stack of characters.
    - When you encounter an opening bracket, push it to the top of the stack.
    - When you encounter a closing bracket, check if the top of the stack was the opening for it. If yes, pop it from the stack. Otherwise, return false.

Template (python3):
    class Solution:
        def isValid(self, s: str) -> bool:

Hint: Use a stack to match opening and closing brackets.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "20. Valid Parentheses"
    test_cases = [
        TestCase(input="()", expected=True, label="simple pair"),
        TestCase(input="()[]{}", expected=True, label="mixed brackets"),
        TestCase(input="(]", expected=False, label="mismatched"),
        TestCase(input="([)]", expected=False, label="interleaved"),
        TestCase(input="{[]}", expected=True, label="nested"),
    ]

    def solve(self, s: str) -> bool:
        raise NotImplementedError("TODO: Implement solve(self, s: str) -> bool")


if __name__ == "__main__":
    Solution().run()
