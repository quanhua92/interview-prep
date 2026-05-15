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
    ]

    def solve(self, intervals: list[list[int]]) -> int:
        if not intervals:
            return 0
        events = []
        for start, end in intervals:
            events.append((start, 1))
            events.append((end, -1))
        events.sort(key=lambda x: (x[0], x[1]))
        concurrent = 0
        max_rooms = 0
        for _, delta in events:
            concurrent += delta
            max_rooms = max(max_rooms, concurrent)
        return max_rooms

    def solve_alternative(self, intervals: list[list[int]]) -> int:
        if not intervals:
            return 0
        starts = sorted(i[0] for i in intervals)
        ends = sorted(i[1] for i in intervals)
        rooms = 0
        end_ptr = 0
        for start in starts:
            if start >= ends[end_ptr]:
                end_ptr += 1
            else:
                rooms += 1
        return rooms


if __name__ == "__main__":
    Solution().run()
