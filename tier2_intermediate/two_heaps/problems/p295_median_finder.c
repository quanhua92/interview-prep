/*
 * P295: Find Median from Data Stream (Hard)
 * https://leetcode.com/problems/find-median-from-data-stream/
 * Topics: Two Heaps, Design, Sorting, Heap (Priority Queue), Data Stream
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
 *     Explanation
 *     MedianFinder medianFinder = new MedianFinder();
 *     medianFinder.addNum(1);    // arr = [1]
 *     medianFinder.addNum(2);    // arr = [1, 2]
 *     medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
 *     medianFinder.addNum(3);    // arr[1, 2, 3]
 *     medianFinder.findMedian(); // return 2.0
 *
 * Constraints:
 *     - -10^5 <= num <= 10^5
 *     - There will be at least one element in the data structure before calling findMedian.
 *     - At most 5 * 10^4 calls will be made to addNum and findMedian.
 *
 * Template (python3):
 *     class MedianFinder:
 *
 *         def __init__(self):
 *
 *
 *         def addNum(self, num: int) -> None:
 *
 *
 *         def findMedian(self) -> float:
 *
 *
 *
 *     # Your MedianFinder object will be instantiated and called as such:
 *     # obj = MedianFinder()
 *     # obj.addNum(num)
 *     # param_2 = obj.findMedian()
 *
 * Hint: Use a max-heap for the lower half and a min-heap for the upper half.
 */


#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 100005

static int small[MAX_N], large[MAX_N];
static int sn, ln;

static void sift_up_small(int i)
{
    abort();
}

static void sift_down_small(int i)
{
    abort();
}

static void sift_up_large(int i)
{
    abort();
}

static void sift_down_large(int i)
{
    abort();
}

static void add_num(int num)
{
    abort();
}

static double find_median(void)
{
    abort();
}

int main(void)
{
    int n;
    int *stream = read_ints(&n);
    sn = ln = 0;
    for (int i = 0; i < n; i++) {
        add_num(stream[i]);
        printf("%.6f\n", find_median());
    }
    free(stream);
    return 0;
}
