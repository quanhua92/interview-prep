"""
P395: Longest Substring with At Least K Repeating Characters [PREMIUM] (Medium)
https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/
Topics: Hash Table, String, Divide and Conquer, Sliding Window

Given a string s and an integer k, return the length of the longest substring of s such that the frequency of each character in this substring is greater than or equal to k.
if no such substring exists, return 0.
Example 1:
    Input: s = "aaabb", k = 3
    Output: 3
    Explanation: The longest substring is "aaa", as 'a' is repeated 3 times.

Example 2:
    Input: s = "ababbc", k = 2
    Output: 5
    Explanation: The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.

Constraints:
    - 1 <= s.length <= 10^4
    - s consists of only lowercase English letters.
    - 1 <= k <= 10^5

Template (python3):
    class Solution:
        def longestSubstring(self, s: str, k: int) -> int:
"""

from src.wasm_libs.py.io import *
from collections import Counter


def solve(s: str, k: int) -> int:
    max_len = 0
    for t in range(1, 27):
        freq: dict[str, int] = {}
        left = 0
        unique = 0
        at_least_k = 0
        for right in range(len(s)):
            ch = s[right]
            freq[ch] = freq.get(ch, 0) + 1
            if freq[ch] == 1:
                unique += 1
            if freq[ch] == k:
                at_least_k += 1
            while unique > t:
                lc = s[left]
                if freq[lc] == k:
                    at_least_k -= 1
                freq[lc] -= 1
                if freq[lc] == 0:
                    unique -= 1
                left += 1
            if unique == t and at_least_k == t:
                max_len = max(max_len, right - left + 1)
    return max_len


# Divide and Conquer approach (added for reference — not used by judge)
def longest_substring_dc(s: str, k: int) -> int:
    if len(s) < k:
        return 0
    freq = Counter(s)
    for char, count in freq.items():
        if count < k:
            return max(longest_substring_dc(sub, k) for sub in s.split(char))
    return len(s)


if __name__ == "__main__":
    s = read_line()
    k = read_int()
    result = solve(s, k)
    write_int(result)
