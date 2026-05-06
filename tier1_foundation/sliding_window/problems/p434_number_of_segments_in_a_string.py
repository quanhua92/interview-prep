"""
P434: Number of Segments in a String [PREMIUM] (Easy)
https://leetcode.com/problems/number-of-segments-in-a-string/
Topics: String

Given a string s, return the number of segments in the string.
A segment is defined to be a contiguous sequence of non-space characters.
Example 1:
    Input: s = "Hello, my name is John"
    Output: 5
    Explanation: The five segments are ["Hello,", "my", "name", "is", "John"]

Example 2:
    Input: s = "Hello"
    Output: 1

Constraints:
    - 0 <= s.length <= 300
    - s consists of lowercase and uppercase English letters, digits, or one of the following characters "!@#$%^&*()_+-=',.:".
    - The only space character in s is ' '.

Template (python3):
    class Solution:
        def countSegments(self, s: str) -> int:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "434. Number of Segments in a String"
    test_cases = [
        TestCase(input="Hello, my name is John", expected=5, label="example 1"),
        TestCase(input="Hello", expected=1, label="example 2"),
    ]

    def solve(self, s: str) -> int:
        raise NotImplementedError("TODO: Implement solve(self, s) -> int")


if __name__ == "__main__":
    Solution().run()
