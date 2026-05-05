"""P424: Longest Repeating Character Replacement (Medium)

TODO: Implement solve() below.
Hint: Freq map + max_freq tracker, window valid when len - max_freq <= k. Left only moves right.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "424. Longest Repeating Character Replacement"
    test_cases = [
        TestCase(input=("ABAB", 2), expected=4, label="example 1"),
        TestCase(input=("AABABBA", 1), expected=4, label="example 2"),
        TestCase(input=("AAAA", 0), expected=4, label="no changes needed"),
        TestCase(input=("ABCDE", 1), expected=2, label="all unique"),
    ]

    def solve(self, s: str, k: int) -> int:
        freq: dict[str, int] = {}
        max_freq = 0
        left = 0
        max_len = 0
        for right, ch in enumerate(s):
            freq[ch] = freq.get(ch, 0) + 1
            max_freq = max(max_freq, freq[ch])
            # Shrink window if it needs more than k replacements
            while (right - left + 1) - max_freq > k:
                freq[s[left]] -= 1
                left += 1
            max_len = max(max_len, right - left + 1)
        return max_len


if __name__ == "__main__":
    Solution().run()
