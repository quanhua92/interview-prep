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
    - 1 <= s.length <= 10^4
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

from src.wasm_libs.py.io import *


def solve(s: str) -> bool:
    mapping = {")": "(", "]": "[", "}": "{"}
    stack: list[str] = []
    for ch in s:
        if ch in mapping:
            if not stack or stack[-1] != mapping[ch]:
                return False
            stack.pop()
        else:
            stack.append(ch)
    return len(stack) == 0


if __name__ == "__main__":
    s = read_line()
    result = solve(s)
    write_bool(result)
