"""
P500: Keyboard Row [PREMIUM] (Easy)
https://leetcode.com/problems/keyboard-row/
Topics: Array, Hash Table, String

Given an array of strings words, return the words that can be typed using letters of the alphabet on only one row of American keyboard like the image below.
Note that the strings are case-insensitive, both lowercased and uppercased of the same letter are treated as if they are at the same row.
In the American keyboard:
Example 1:
    Input: words = ["Hello","Alaska","Dad","Peace"]
    Output: ["Alaska","Dad"]
    Explanation:
    Both "a" and "A" are in the 2nd row of the American keyboard due to case insensitivity.

Example 2:
    Input: words = ["omk"]
    Output: []

Example 3:
    Input: words = ["adsdf","sfd"]
    Output: ["adsdf","sfd"]

Constraints:
    - 1 <= words.length <= 20
    - 1 <= words[i].length <= 100
    - words[i] consists of English letters (both lowercase and uppercase).

Template (python3):
    class Solution:
        def findWords(self, words: List[str]) -> List[str]:
"""

from src.wasm_libs.py.io import *


def solve(words: list[str]) -> list[str]:
    raise NotImplementedError

if __name__ == "__main__":
    n = read_int()
    words = []
    for _ in range(n):
        words.append(read_line())
    result = solve(words)
    if result:
        write_string(result[0])
        for w in result[1:]:
            write_string(w)
