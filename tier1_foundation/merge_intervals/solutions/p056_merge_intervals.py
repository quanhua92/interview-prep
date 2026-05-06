"""
P56: Merge Intervals (Medium)
https://leetcode.com/problems/merge-intervals/
Topics: Array, Sorting

Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.

Example 1:
    Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
    Output: [[1,6],[8,10],[15,18]]
    Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].

Example 2:
    Input: intervals = [[1,4],[4,5]]
    Output: [[1,5]]
    Explanation: Intervals [1,4] and [4,5] are considered overlapping.

Constraints:
    - 1 <= intervals.length <= 104
    - intervals[i].length == 2
    - 0 <= starti <= endi <= 104

Template (python3):
    class Solution:
        def merge(self, intervals: List[List[int]]) -> List[List[int]]:

Hint: Sort intervals by start time, then merge overlapping ones.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "56. Merge Intervals"
    test_cases = [
        TestCase(
            input=[[1, 3], [2, 6], [8, 10], [15, 18]],
            expected=[[1, 6], [8, 10], [15, 18]],
            label="example 1",
        ),
        TestCase(input=[[1, 4], [4, 5]], expected=[[1, 5]], label="example 2"),
        TestCase(input=[[1, 4], [0, 4]], expected=[[0, 4]], label="overlapping start"),
    ]

    def solve(self, intervals: list[list[int]]) -> list[list[int]]:
        if not intervals:
            return []
        intervals.sort(key=lambda x: x[0])
        merged = [intervals[0]]
        for start, end in intervals[1:]:
            last = merged[-1]
            if start <= last[1]:
                last[1] = max(last[1], end)
            else:
                merged.append([start, end])
        return merged


if __name__ == "__main__":
    Solution().run()
