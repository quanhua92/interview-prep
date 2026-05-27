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

from src.wasm_libs.py.io import *
import heapq


def solve(stream: list[int]) -> list[float]:
    small: list[int] = []
    large: list[int] = []
    medians: list[float] = []

    for num in stream:
        heapq.heappush(small, -num)
        heapq.heappush(large, -heapq.heappop(small))
        if len(large) > len(small):
            heapq.heappush(small, -heapq.heappop(large))

        if len(small) > len(large):
            medians.append(float(-small[0]))
        elif len(large) > len(small):
            medians.append(float(large[0]))
        else:
            medians.append((-small[0] + large[0]) / 2.0)
    return medians


if __name__ == "__main__":
    stream = read_ints()
    result = solve(stream)
    for m in result:
        print(m)
