/*
 * P295: Find Median from Data Stream (Hard)
 * https://leetcode.com/problems/find-median-from-data-stream/
 * Topics: Two Pointers, Design, Sorting, Heap (Priority Queue), Data Stream
 *
 * The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.
 * Implement the MedianFinder class:
 *
 * Example 1:
 *     Input
 *     ["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
 *     [[], [1], [2], [], [3], []]
 *     Output
 *     [null, null, null, 1.5, null, 2.0]
 *
 * Constraints:
 *     - -105 <= num <= 105
 *     - There will be at least one element in the data structure before calling findMedian.
 *     - At most 5 * 104 calls will be made to addNum and findMedian.
 *
 * Template (python3):
 *     class MedianFinder:
 *         def __init__(self):
 *         def addNum(self, num: int) -> None:
 *         def findMedian(self) -> float:
 *
 * Hint: Use a max-heap for the lower half and a min-heap for the upper half.
 */

#include "io.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;
    int *stream = read_ints(&n);
    abort();
}
