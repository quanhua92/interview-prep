"""
P567: Permutation in String [PREMIUM] (Medium)
https://leetcode.com/problems/permutation-in-string/
Topics: Hash Table, Two Pointers, String, Sliding Window

Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.
In other words, return true if one of s1's permutations is the substring of s2.
Example 1:
    Input: s1 = "ab", s2 = "eidbaooo"
    Output: true
    Explanation: s2 contains one permutation of s1 ("ba").

Example 2:
    Input: s1 = "ab", s2 = "eidboaoo"
    Output: false

Constraints:
    - 1 <= s1.length, s2.length <= 10^4
    - s1 and s2 consist of lowercase English letters.

Hint: Obviously, brute force will result in TLE. Think of something else.
Hint: How will you check whether one string is a permutation of another string?
Hint: One way is to sort the string and then compare. But, Is there a better way?
Hint: If one string is a permutation of another string then they must have one common metric. What is that?
Hint: Both strings must have same character frequencies, if  one is permutation of another. Which data structure should be used to store frequencies?
Hint: What about hash table?  An array of size 26?

Template (python3):
    class Solution:
        def checkInclusion(self, s1: str, s2: str) -> bool:
"""

from collections import Counter
from src.wasm_libs.py.io import *


def solve(s1: str, s2: str) -> bool:
    n1, n2 = len(s1), len(s2)
    if n1 > n2:
        return False
    target = Counter(s1)
    window = Counter(s2[:n1])
    if window == target:
        return True
    for i in range(n1, n2):
        left_ch = s2[i - n1]
        if window[left_ch] == 1:
            del window[left_ch]
        else:
            window[left_ch] -= 1
        window[s2[i]] = window.get(s2[i], 0) + 1
        if window == target:
            return True
    return False


if __name__ == "__main__":
    s1 = read_line()
    s2 = read_line()
    result = solve(s1, s2)
    write_bool(result)
