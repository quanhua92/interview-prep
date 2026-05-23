"""
P352: Data Stream as Disjoint Intervals [PREMIUM] (Hard)
https://leetcode.com/problems/data-stream-as-disjoint-intervals/
Topics: Binary Search, Design, Ordered Set

Given a data stream input of non-negative integers a1, a2, ..., an, summarize the numbers seen so far as a list of disjoint intervals.
Implement the SummaryRanges class:
Example 1:
Follow up: What if there are lots of merges and the number of disjoint intervals is small compared to the size of the data stream?
    Input
Example 1:
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
    - 0 <= value <= 104
    - At most 3 * 104 calls will be made to addNum and getIntervals.
    - At most 102 calls will be made to getIntervals.

Template (python3):
    class SummaryRanges:

        def __init__(self):


        def addNum(self, value: int) -> None:


        def getIntervals(self) -> List[List[int]]:



    # Your SummaryRanges object will be instantiated and called as such:
    # obj = SummaryRanges()
    # obj.addNum(value)
    # param_2 = obj.getIntervals()
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "352. Data Stream as Disjoint Intervals"
    test_cases = [
        TestCase(input=[1, 3, 7, 2, 6], expected=[[1, 3], [6, 7]], label="example from problem"),
        TestCase(input=[1, 0], expected=[[0, 1]], label="adjacent values merge"),
        TestCase(input=[0], expected=[[0, 0]], label="single zero"),
        TestCase(input=[100, 1, 50], expected=[[1, 1], [50, 50], [100, 100]], label="no merges sorted output"),
        TestCase(input=[], expected=[], label="empty stream"),
    ]

    def solve(self) -> None:
        raise NotImplementedError("TODO: Implement solve(self) -> None")


if __name__ == "__main__":
    Solution().run()
