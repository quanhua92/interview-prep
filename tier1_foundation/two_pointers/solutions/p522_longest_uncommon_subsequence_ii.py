"""
P522: Longest Uncommon Subsequence II [PREMIUM] (Medium)
https://leetcode.com/problems/longest-uncommon-subsequence-ii/
Topics: Array, Hash Table, Two Pointers, String, Sorting

Given an array of strings strs, return the length of the longest uncommon subsequence between them. If the longest uncommon subsequence does not exist, return -1.
An uncommon subsequence between an array of strings is a string that is a subsequence of one string but not the others.
A subsequence of a string s is a string that can be obtained after deleting any number of characters from s.
Example 1:
    Input: strs = ["aba","cdc","eae"]
    Output: 3

Example 2:
    Input: strs = ["aaa","aaa","aa"]
    Output: -1

Constraints:
    - 2 <= strs.length <= 50
    - 1 <= strs[i].length <= 10
    - strs[i] consists of lowercase English letters.

Template (python3):
    class Solution:
        def findLUSlength(self, strs: List[str]) -> int:
"""

from src.wasm_libs.py.io import *


def solve(strs: list[str]) -> int:
    def is_subseq(a: str, b: str) -> bool:
        i = 0
        for ch in b:
            if i < len(a) and a[i] == ch:
                i += 1
        return i == len(a)

    strs.sort(key=len, reverse=True)
    for i, candidate in enumerate(strs):
        is_uncommon = True
        for j, other in enumerate(strs):
            if i != j and is_subseq(candidate, other):
                is_uncommon = False
                break
        if is_uncommon:
            return len(candidate)
    return -1


if __name__ == "__main__":
    n = read_int()
    strs = [read_line() for _ in range(n)]
    result = solve(strs)
    write_int(result)
