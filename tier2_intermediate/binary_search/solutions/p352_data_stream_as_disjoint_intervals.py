"""
P352: Data Stream as Disjoint Intervals [PREMIUM] (Hard)
https://leetcode.com/problems/data-stream-as-disjoint-intervals/
Topics: Binary Search, Design, Ordered Set

Given a data stream input of non-negative integers a1, a2, ..., an, summarize the numbers seen so far as a list of disjoint intervals.

Implement the SummaryRanges class:

SummaryRanges() Initializes the object with an empty stream.
void addNum(int value) Adds the integer value to the stream.
int[][] getIntervals() Returns a summary of the integers in the stream currently as a list of disjoint intervals [starti, endi]. The answer should be sorted by starti.


Example 1:

Input
["SummaryRanges", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals"]
[[], [1], [], [3], [], [7], [], [2], [], [6], []]
Output
[null, null, [[1, 1]], null, [[1, 1], [3, 3]], null, [[1, 1], [3, 3], [7, 7]], null, [[1, 3], [7, 7]], null, [[1, 3], [6, 7]]]

Explanation
SummaryRanges summaryRanges = new SummaryRanges();
summaryRanges.addNum(1);      // arr = [1]
summaryRanges.getIntervals(); // return [[1, 1]]
summaryRanges.addNum(3);      // arr = [1, 3]
summaryRanges.getIntervals(); // return [[1, 1], [3, 3]]
summaryRanges.addNum(7);      // arr = [1, 3, 7]
summaryRanges.getIntervals(); // return [[1, 1], [3, 3], [7, 7]]
summaryRanges.addNum(2);      // arr = [1, 2, 3, 7]
summaryRanges.getIntervals(); // return [[1, 3], [7, 7]]
summaryRanges.addNum(6);      // arr = [1, 2, 3, 6, 7]
summaryRanges.getIntervals(); // return [[1, 3], [6, 7]]



Constraints:

0 <= value <= 10^4
At most 3 * 10^4 calls will be made to addNum and getIntervals.
At most 10^2 calls will be made to getIntervals.


Follow up: What if there are lots of merges and the number of disjoint intervals is small compared to the size of the data stream?
"""

import bisect

from src.wasm_libs.py.io import *


class SummaryRanges:
    def __init__(self):
        self.intervals: list[list[int]] = []

    def addNum(self, value: int) -> None:
        lo, hi = value, value
        pos = bisect.bisect_left(self.intervals, [lo, hi])
        if pos > 0 and self.intervals[pos - 1][1] >= lo - 1:
            pos -= 1
            lo = self.intervals[pos][0]
        while pos < len(self.intervals) and self.intervals[pos][0] <= hi + 1:
            hi = max(hi, self.intervals[pos][1])
            del self.intervals[pos]
        self.intervals.insert(pos, [lo, hi])

    def getIntervals(self) -> list[list[int]]:
        return self.intervals


def solve(num_ops: int) -> None:
    sr = SummaryRanges()
    for _ in range(num_ops):
        op = read_line()
        argc = read_int()
        args = read_ints() if argc else []
        if op == "getIntervals":
            intervals = sr.getIntervals()
            write_int(len(intervals))
            for a, b in intervals:
                write_ints([a, b])
        elif op == "addNum":
            sr.addNum(args[0])


if __name__ == "__main__":
    solve(read_int())
