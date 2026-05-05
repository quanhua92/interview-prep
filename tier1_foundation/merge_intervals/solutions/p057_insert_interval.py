"""P057: Insert Interval (Medium)

TODO: Implement solve() below.
Hint: Add non-overlapping before, merge overlapping, add non-overlapping after.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "57. Insert Interval"
    test_cases = [
        TestCase(input=([[1, 3], [6, 9]], [2, 5]), expected=[[1, 5], [6, 9]], label="example 1"),
        TestCase(input=([[1, 2], [3, 5], [6, 7], [8, 10], [12, 16]], [4, 8]), expected=[[1, 2], [3, 10], [12, 16]], label="example 2"),
        TestCase(input=([], [5, 7]), expected=[[5, 7]], label="empty intervals"),
        TestCase(input=([[1, 5]], [2, 3]), expected=[[1, 5]], label="contained"),
    ]

    def solve(self, intervals: list[list[int]], new_interval: list[int]) -> list[list[int]]:
        result: list[list[int]] = []
        i = 0
        n = len(intervals)
        # Add all intervals that end before new_interval starts
        while i < n and intervals[i][1] < new_interval[0]:
            result.append(intervals[i])
            i += 1
        # Merge all overlapping intervals
        while i < n and intervals[i][0] <= new_interval[1]:
            new_interval[0] = min(new_interval[0], intervals[i][0])
            new_interval[1] = max(new_interval[1], intervals[i][1])
            i += 1
        result.append(new_interval)
        # Add remaining intervals
        while i < n:
            result.append(intervals[i])
            i += 1
        return result


if __name__ == "__main__":
    Solution().run()
