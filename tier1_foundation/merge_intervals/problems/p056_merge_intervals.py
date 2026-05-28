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

from src.wasm_libs.py.io import *


def solve(intervals: list[list[int]]) -> list[list[int]]:
    raise NotImplementedError

if __name__ == "__main__":
    n = read_int()
    intervals = []
    for _ in range(n):
        intervals.append(read_ints())
    result = solve(intervals)
    for row in result:
        write_ints(row)
