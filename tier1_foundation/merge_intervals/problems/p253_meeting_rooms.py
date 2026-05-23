"""
P253: Meeting Rooms II (Medium)
https://leetcode.com/problems/meeting-rooms-ii/
Topics: Array, Two Pointers, Sorting, Heap (Priority Queue), Prefix Sum

Given an array of meeting time intervals intervals where intervals[i] = [starti, endi], return the minimum number of conference rooms required.

Example 1:
    Input: intervals = [[0,30],[5,10],[15,20]]
    Output: 2

Example 2:
    Input: intervals = [[7,10],[2,4]]
    Output: 1

Constraints:
    - 1 <= intervals.length <= 10^4
    - 0 <= starti < endi <= 10^6

Hints:
    - Think about how we would approach this problem if we were given the intervals sorted by start time.
    - What if we use a min-heap to track the ending times of meetings?

Template (python3):
    class Solution:
        def minMeetingRooms(self, intervals: List[List[int]]) -> int:

Hint: Sort start and end times separately, then use two pointers to count concurrent meetings.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "253. Meeting Rooms II"
    test_cases = [
        TestCase(input=[[0, 30], [5, 10], [15, 20]], expected=2, label="example 1"),
        TestCase(input=[[7, 10], [2, 4]], expected=1, label="example 2"),
        TestCase(input=[], expected=0, label="no meetings"),
        TestCase(input=[[0, 1]], expected=1, label="single meeting"),
        TestCase(
            input=[[0, 10], [1, 9], [2, 8], [3, 7]],
            expected=4,
            label="all meetings overlap",
        ),
        TestCase(
            input=[[0, 5], [5, 10], [5, 10]],
            expected=2,
            label="meetings end and start at same time",
        ),
        TestCase(
            input=[[0, 30], [0, 30], [0, 30]],
            expected=3,
            label="all same start time",
        ),
        TestCase(
            input=[[0, 1], [1, 2], [2, 3]],
            expected=1,
            label="no overlap sequential",
        ),
    ]

    def solve(self, intervals: list[list[int]]) -> int:
        raise NotImplementedError(
            "TODO: Implement solve(self, intervals: list[list[int]]) -> int"
        )


if __name__ == "__main__":
    Solution().run()
