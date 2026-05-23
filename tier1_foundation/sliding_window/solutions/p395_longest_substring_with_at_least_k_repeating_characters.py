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
    - 1 <= s.length <= 104
    - s consists of only lowercase English letters.
    - 1 <= k <= 105

Template (python3):
    class Solution:
        def longestSubstring(self, s: str, k: int) -> int:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "395. Longest Substring with At Least K Repeating Characters"
    test_cases = [
        TestCase(input=("aaabb", 3), expected=3, label="example 1"),
        TestCase(input=("ababbc", 2), expected=5, label="example 2"),
        TestCase(input=("ababacb", 3), expected=0, label="no valid substring"),
        TestCase(input=("a", 1), expected=1, label="single char k=1"),
        TestCase(input=("a", 2), expected=0, label="single char k>1"),
        TestCase(input=("bbaaacbd", 3), expected=3, label="multiple runs"),
    ]

    def solve(self, s: str, k: int) -> int:
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

    def solve_alternative(self, s: str, k: int) -> int:
        def helper(sub: str, k: int) -> int:
            if len(sub) < k:
                return 0
            freq = {}
            for ch in sub:
                freq[ch] = freq.get(ch, 0) + 1
            bad_chars = [ch for ch, cnt in freq.items() if cnt < k]
            if not bad_chars:
                return len(sub)
            max_len = 0
            start = 0
            for i, ch in enumerate(sub):
                if ch in bad_chars:
                    if i - start >= k:
                        max_len = max(max_len, helper(sub[start:i], k))
                    start = i + 1
            if len(sub) - start >= k:
                max_len = max(max_len, helper(sub[start:], k))
            return max_len

        return helper(s, k)


if __name__ == "__main__":
    Solution().run()
