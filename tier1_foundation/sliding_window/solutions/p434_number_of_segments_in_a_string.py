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
        TestCase(input="", expected=0, label="empty string"),
        TestCase(input="   ", expected=0, label="only spaces"),
        TestCase(input="    foo    bar   ", expected=2, label="leading/trailing/multiple spaces"),
        TestCase(input="a b c d e", expected=5, label="single char segments"),
    ]

    def solve(self, s: str) -> int:
        count = 0
        in_segment = False
        for ch in s:
            if ch != " " and not in_segment:
                count += 1
                in_segment = True
            elif ch == " ":
                in_segment = False
        return count


if __name__ == "__main__":
    Solution().run()
