"""
P524: Longest Word in Dictionary through Deleting [PREMIUM] (Medium)
https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/
Topics: Array, Two Pointers, String, Sorting

Given a string s and a string array dictionary, return the longest string in the dictionary that can be formed by deleting some of the given string characters. If there is more than one possible result, return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.
Example 1:
    Input: s = "abpcplea", dictionary = ["ale","apple","monkey","plea"]
    Output: "apple"

Example 2:
    Input: s = "abpcplea", dictionary = ["a","b","c"]
    Output: "a"

Constraints:
    - 1 <= s.length <= 1000
    - 1 <= dictionary.length <= 1000
    - 1 <= dictionary[i].length <= 1000
    - s and dictionary[i] consist of lowercase English letters.

Template (python3):
    class Solution:
        def findLongestWord(self, s: str, dictionary: List[str]) -> str:
"""

from src.wasm_libs.py.io import *


def solve(s: str, dictionary: list[str]) -> str:
    def is_subseq(word: str, target: str) -> bool:
        i = 0
        for ch in target:
            if i < len(word) and word[i] == ch:
                i += 1
        return i == len(word)

    best = ""
    for word in dictionary:
        if is_subseq(word, s):
            if len(word) > len(best) or (len(word) == len(best) and word < best):
                best = word
    return best


if __name__ == "__main__":
    s = read_line()
    dict_size = read_int()
    dictionary = [read_line() for _ in range(dict_size)]
    result = solve(s, dictionary)
    write_string(result)
