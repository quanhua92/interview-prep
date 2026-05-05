"""P438: Find All Anagrams in a String (Medium)

TODO: Implement solve() below.
Hint: Use a sliding window with frequency counters to compare against pattern.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "438. Find All Anagrams in a String"
    test_cases = [
        TestCase(input=("cbaebabacd", "abc"), expected=[0, 6], label="example 1"),
        TestCase(input=("abab", "ab"), expected=[0, 1, 2], label="example 2"),
        TestCase(input=("af", "bf"), expected=[], label="no anagrams"),
    ]

    def solve(self, s: str, p: str) -> list[int]:
        from collections import Counter
        if len(p) > len(s):
            return []
        p_count = Counter(p)
        s_count = Counter(s[:len(p)])
        result = []
        if s_count == p_count:
            result.append(0)
        for i in range(len(p), len(s)):
            s_count[s[i]] += 1
            s_count[s[i - len(p)]] -= 1
            if s_count[s[i - len(p)]] == 0:
                del s_count[s[i - len(p)]]
            if s_count == p_count:
                result.append(i - len(p) + 1)
        return result


if __name__ == "__main__":
    Solution().run()
