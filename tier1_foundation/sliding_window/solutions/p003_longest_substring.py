"""P003: Longest Substring Without Repeating Characters (Medium)

TODO: Implement solve() below.
Hint: Use a hash map to track the last index of each character.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "3. Longest Substring Without Repeating Characters"
    test_cases = [
        TestCase(input="abcabcbb", expected=3, label="example 1"),
        TestCase(input="bbbbb", expected=1, label="example 2"),
        TestCase(input="pwwkew", expected=3, label="example 3"),
        TestCase(input="", expected=0, label="empty string"),
    ]

    def solve(self, s: str) -> int:
        char_index: dict[str, int] = {}
        left = 0
        max_len = 0
        for right, ch in enumerate(s):
            if ch in char_index and char_index[ch] >= left:
                left = char_index[ch] + 1
            char_index[ch] = right
            max_len = max(max_len, right - left + 1)
        return max_len


if __name__ == "__main__":
    Solution().run()
