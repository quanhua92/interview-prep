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
 *     - -105 <= num <= 105
 *     - There will be at least one element in the data structure before calling findMedian.
 *     - At most 5 * 104 calls will be made to addNum and findMedian.
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
    while (i > 0) {
        int p = (i - 1) / 2;
        if (small[p] < small[i]) { int t = small[p]; small[p] = small[i]; small[i] = t; i = p; }
        else break;
    }
}

static void sift_down_small(int i)
{
    while (1) {
        int s = i, l = 2*i+1, r = 2*i+2;
        if (l < sn && small[l] > small[s]) s = l;
        if (r < sn && small[r] > small[s]) s = r;
        if (s != i) { int t = small[s]; small[s] = small[i]; small[i] = t; i = s; }
        else break;
    }
}

static void sift_up_large(int i)
{
    while (i > 0) {
        int p = (i - 1) / 2;
        if (large[p] > large[i]) { int t = large[p]; large[p] = large[i]; large[i] = t; i = p; }
        else break;
    }
}

static void sift_down_large(int i)
{
    while (1) {
        int s = i, l = 2*i+1, r = 2*i+2;
        if (l < ln && large[l] < large[s]) s = l;
        if (r < ln && large[r] < large[s]) s = r;
        if (s != i) { int t = large[s]; large[s] = large[i]; large[i] = t; i = s; }
        else break;
    }
}

static void add_num(int num)
{
    small[sn] = num; sn++; sift_up_small(sn - 1);
    large[ln] = small[0]; ln++; sift_up_large(ln - 1);
    small[0] = small[--sn]; if (sn > 0) sift_down_small(0);
    if (ln > sn) {
        small[sn] = large[0]; sn++; sift_up_small(sn - 1);
        large[0] = large[--ln]; if (ln > 0) sift_down_large(0);
    }
}

static double find_median(void)
{
    if (sn > ln) return (double)small[0];
    if (ln > sn) return (double)large[0];
    return (small[0] + large[0]) / 2.0;
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
