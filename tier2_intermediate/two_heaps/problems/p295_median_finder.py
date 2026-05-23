"""
P295: Find Median from Data Stream (Hard)
https://leetcode.com/problems/find-median-from-data-stream/
Topics: Two Pointers, Design, Sorting, Heap (Priority Queue), Data Stream

The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.
Implement the MedianFinder class:

Example 1:
    Input
    ["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
    [[], [1], [2], [], [3], []]
    Output
    [null, null, null, 1.5, null, 2.0]

    Explanation
    MedianFinder medianFinder = new MedianFinder();
    medianFinder.addNum(1);    // arr = [1]
    medianFinder.addNum(2);    // arr = [1, 2]
    medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
    medianFinder.addNum(3);    // arr[1, 2, 3]
    medianFinder.findMedian(); // return 2.0

Constraints:
    - -105 <= num <= 105
    - There will be at least one element in the data structure before calling findMedian.
    - At most 5 * 104 calls will be made to addNum and findMedian.

Template (python3):
    class MedianFinder:

        def __init__(self):


        def addNum(self, num: int) -> None:


        def findMedian(self) -> float:



    # Your MedianFinder object will be instantiated and called as such:
    # obj = MedianFinder()
    # obj.addNum(num)
    # param_2 = obj.findMedian()

Hint: Use a max-heap for the lower half and a min-heap for the upper half.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "295. Find Median from Data Stream"
    test_cases = [
        TestCase(
            input=([5, 15, 1, 3], "median"),
            expected=[5.0, 10.0, 5.0, 4.0],
            label="stream median",
        ),
        TestCase(input=([1, 2], "median"), expected=[1.0, 1.5], label="two elements"),
        TestCase(input=([42], "median"), expected=[42.0], label="single element"),
        TestCase(input=([3, 3, 3, 3], "median"), expected=[3.0, 3.0, 3.0, 3.0], label="all same"),
        TestCase(input=([-5, -3, -1, 0], "median"), expected=[-5.0, -4.0, -3.0, -2.0], label="negative numbers"),
        TestCase(input=([100, 0, 100, 0, 100, 0], "median"), expected=[100.0, 50.0, 100.0, 50.0, 100.0, 50.0], label="alternating high low"),
        TestCase(input=([10, 9, 8, 7, 6, 5], "median"), expected=[10.0, 9.5, 9.0, 8.5, 8.0, 7.5], label="descending order"),
        TestCase(input=([-100000, 100000], "median"), expected=[-100000.0, 0.0], label="extreme values"),
    ]

    def solve(self, stream: list[int], _unused: str) -> list[float]:
        raise NotImplementedError(
            "TODO: Implement solve(self, stream: list[int], _unused: str) -> list[float]"
        )


if __name__ == "__main__":
    Solution().run()
