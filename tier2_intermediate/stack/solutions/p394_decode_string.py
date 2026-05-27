"""
P394: Decode String (Medium)
https://leetcode.com/problems/decode-string/
Topics: String, Stack, Recursion

Given an encoded string, return its decoded string.
The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.
You may assume that the input string is always valid; there are no extra white spaces, square brackets are well-formed, etc. Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there will not be input like 3a or 2[4].
The test cases are generated so that the length of the output will never exceed 105.

Example 1:
    Input: s = "3[a]2[bc]"
    Output: "aaabcbc"

Example 2:
    Input: s = "3[a2[c]]"
    Output: "accaccacc"

Example 3:
    Input: s = "2[abc]3[cd]ef"
    Output: "abcabccdcdcdef"

Constraints:
    - 1 <= s.length <= 30
    - s consists of lowercase English letters, digits, and square brackets '[]'.
    - s is guaranteed to be a valid input.
    - All the integers in s are in the range [1, 300].

Template (python3):
    class Solution:
        def decodeString(self, s: str) -> str:

Hint: Use a stack to handle nested k[encoded] patterns.
"""

from src.wasm_libs.py.io import *


def solve(s: str) -> str:
    stack: list[tuple[int, str]] = []
    curr_num = 0
    curr_str = ""

    for ch in s:
        if ch.isdigit():
            curr_num = curr_num * 10 + int(ch)
        elif ch == "[":
            stack.append((curr_num, curr_str))
            curr_num = 0
            curr_str = ""
        elif ch == "]":
            repeat, prefix = stack.pop()
            curr_str = prefix + curr_str * repeat
        else:
            curr_str += ch

    return curr_str


if __name__ == "__main__":
    s = read_line()
    result = solve(s)
    write_string(result)
