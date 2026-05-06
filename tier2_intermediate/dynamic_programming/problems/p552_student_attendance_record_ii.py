"""
P552: Student Attendance Record II [PREMIUM] (Hard)
https://leetcode.com/problems/student-attendance-record-ii/
Topics: Dynamic Programming

An attendance record for a student can be represented as a string where each character signifies whether the student was absent, late, or present on that day. The record only contains the following three characters:
Any student is eligible for an attendance award if they meet both of the following criteria:
Given an integer n, return the number of possible attendance records of length n that make a student eligible for an attendance award. The answer may be very large, so return it modulo 109 + 7.
Example 1:
    Input: n = 2
    Output: 8
    Explanation: There are 8 records with length 2 that are eligible for an award:
    "PP", "AP", "PA", "LP", "PL", "AL", "LA", "LL"
    Only "AA" is not eligible because there are 2 absences (there need to be fewer than 2).

Example 2:
    Input: n = 1
    Output: 3

Example 3:
    Input: n = 10101
    Output: 183236316

Constraints:
    - 1 <= n <= 105

Template (python3):
    class Solution:
        def checkRecord(self, n: int) -> int:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "552. Student Attendance Record II"
    test_cases = [
        TestCase(input=2, expected=8, label="example 1"),
        TestCase(input=1, expected=3, label="example 2"),
        TestCase(input=10101, expected=183236316, label="example 3"),
    ]

    def solve(self, n: int) -> int:
        raise NotImplementedError("TODO: Implement solve(self, n) -> int")


if __name__ == "__main__":
    Solution().run()
