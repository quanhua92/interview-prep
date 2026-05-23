"""
P57: Insert Interval (Medium)
https://leetcode.com/problems/insert-interval/
Topics: Array

You are given an array of non-overlapping intervals intervals where intervals[i] = [starti, endi] represent the start and the end of the ith interval and intervals is sorted in ascending order by starti. You are also given an interval newInterval = [start, end] that represents the start and end of another interval.
Insert newInterval into intervals such that intervals is still sorted in ascending order by starti and intervals still does not have any overlapping intervals (merge overlapping intervals if necessary).
Return intervals after the insertion.
Note that you don't need to modify intervals in-place. You can make a new array and return it.

Example 1:
    Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
    Output: [[1,5],[6,9]]

Example 2:
    Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
    Output: [[1,2],[3,10],[12,16]]
    Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].

Constraints:
    - 0 <= intervals.length <= 104
    - intervals[i].length == 2
    - 0 <= starti <= endi <= 105
    - intervals is sorted by starti in ascending order.
    - newInterval.length == 2
    - 0 <= start <= end <= 105

Hints:
    - Intervals Array is sorted. Can you use Binary Search to find the correct position to insert the new Interval.?
    - Can you try merging the overlapping intervals while inserting the new interval?
    - This can be done by comparing the end of the last interval with the start of the new interval and vice versa.

Template (python3):
    class Solution:
        def insert(self, intervals: List[List[int]], newInterval: List[int]) -> List[List[int]]:

Hint: Add non-overlapping before, merge overlapping, add non-overlapping after.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "57. Insert Interval"
    test_cases = [
        TestCase(
            input=([[1, 3], [6, 9]], [2, 5]),
            expected=[[1, 5], [6, 9]],
            label="example 1",
        ),
        TestCase(
            input=([[1, 2], [3, 5], [6, 7], [8, 10], [12, 16]], [4, 8]),
            expected=[[1, 2], [3, 10], [12, 16]],
            label="example 2",
        ),
        TestCase(input=([], [5, 7]), expected=[[5, 7]], label="empty intervals"),
        TestCase(input=([[1, 5]], [2, 3]), expected=[[1, 5]], label="contained"),
        TestCase(
            input=([[3, 5], [6, 9]], [1, 2]),
            expected=[[1, 2], [3, 5], [6, 9]],
            label="insert before all",
        ),
        TestCase(
            input=([[1, 2], [3, 5]], [6, 9]),
            expected=[[1, 2], [3, 5], [6, 9]],
            label="insert after all",
        ),
        TestCase(
            input=([[1, 3], [6, 9]], [0, 2]),
            expected=[[0, 3], [6, 9]],
            label="merge with first interval",
        ),
        TestCase(
            input=([[1, 3], [6, 9]], [8, 10]),
            expected=[[1, 3], [6, 10]],
            label="merge with last interval",
        ),
        TestCase(
            input=([[1, 2], [4, 5]], [2, 4]),
            expected=[[1, 5]],
            label="bridge gap between intervals",
        ),
    ]

    def solve(
        self, intervals: list[list[int]], new_interval: list[int]
    ) -> list[list[int]]:
        raise NotImplementedError(
            "TODO: Implement solve(self, intervals: list[list[int]], new_interval: list[int]) -> list[list[int]]"
        )


if __name__ == "__main__":
    Solution().run()
