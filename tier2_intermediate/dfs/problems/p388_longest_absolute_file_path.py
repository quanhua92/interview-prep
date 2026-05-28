"""
P388: Longest Absolute File Path [PREMIUM] (Medium)
https://leetcode.com/problems/longest-absolute-file-path/
Topics: String, Stack, Depth-First Search

Given a string input representing the file system, return the length of the longest absolute path to a file.

Example 1:
    Input: input = "dir\\n\\tsubdir1\\n\\tsubdir2\\n\\t\\tfile.ext"
    Output: 20

Example 2:
    Input: input = "dir\\n\\tsubdir1\\n\\t\\tfile1.ext\\n\\t\\tsubsubdir1\\n\\tsubdir2\\n\\t\\tsubsubdir2\\n\\t\\t\\tfile2.ext"
    Output: 32

Example 3:
    Input: input = "a"
    Output: 0

Constraints:
    - 1 <= input.length <= 10^4

Template (python3):
    class Solution:
        def lengthLongestPath(self, input: str) -> int:
"""

from src.wasm_libs.py.io import read_line, write_int


def solve(input_str: str) -> int:
    raise NotImplementedError


if __name__ == "__main__":
    lines = []
    while True:
        line = read_line()
        if not line:
            break
        lines.append(line)
    input_str = "\n".join(lines)
    result = solve(input_str)
    write_int(result)
