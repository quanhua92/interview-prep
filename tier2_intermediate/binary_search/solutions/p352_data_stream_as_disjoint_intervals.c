/*
 * P352: Data Stream as Disjoint Intervals [PREMIUM] (Hard)
 * https://leetcode.com/problems/data-stream-as-disjoint-intervals/
 * Topics: Binary Search, Design, Ordered Set
 *
 * Given a data stream input of non-negative integers a1, a2, ..., an, summarize the numbers seen so far as a list of disjoint intervals.
 * Implement the SummaryRanges class:
 * Example 1:
 * Follow up: What if there are lots of merges and the number of disjoint intervals is small compared to the size of the data stream?
 *     Input
 * Example 1:
 *     ["SummaryRanges", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals"]
 *     [[], [1], [], [3], [], [7], [], [2], [], [6], []]
 *     Output
 *     [null, null, [[1, 1]], null, [[1, 1], [3, 3]], null, [[1, 1], [3, 3], [7, 7]], null, [[1, 3], [7, 7]], null, [[1, 3], [6, 7]]]
 *
 *     Explanation
 *     SummaryRanges summaryRanges = new SummaryRanges();
 *     summaryRanges.addNum(1);      // arr = [1]
 *     summaryRanges.getIntervals(); // return [[1, 1]]
 *     summaryRanges.addNum(3);      // arr = [1, 3]
 *     summaryRanges.getIntervals(); // return [[1, 1], [3, 3]]
 *     summaryRanges.addNum(7);      // arr = [1, 3, 7]
 *     summaryRanges.getIntervals(); // return [[1, 1], [3, 3], [7, 7]]
 *     summaryRanges.addNum(2);      // arr = [1, 2, 3, 7]
 *     summaryRanges.getIntervals(); // return [[1, 3], [7, 7]]
 *     summaryRanges.addNum(6);      // arr = [1, 2, 3, 6, 7]
 *     summaryRanges.getIntervals(); // return [[1, 3], [6, 7]]
 *
 * Constraints:
 *     - 0 <= value <= 104
 *     - At most 3 * 104 calls will be made to addNum and getIntervals.
 *     - At most 102 calls will be made to getIntervals.
 *
 * Template (python3):
 *     class SummaryRanges:
 *
 *         def __init__(self):
 *
 *
 *         def addNum(self, value: int) -> None:
 *
 *
 *         def getIntervals(self) -> List[List[int]]:
 *
 *
 *
 *     # Your SummaryRanges object will be instantiated and called as such:
 *     # obj = SummaryRanges()
 *     # obj.addNum(value)
 *     # param_2 = obj.getIntervals()
 */

#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { int lo, hi; } Interval;

static Interval *solve_intervals(const int *values, int n, int *ret_size)
{
    Interval *intervals = NULL;
    int cap = 0, len = 0;

    for (int vi = 0; vi < n; vi++) {
        int v = values[vi];
        int lo = v, hi = v;

        int pos = 0;
        while (pos < len && intervals[pos].lo < lo) pos++;

        if (pos > 0 && intervals[pos - 1].hi >= lo - 1) {
            pos--;
            lo = intervals[pos].lo;
        }

        int j = pos;
        while (j < len && intervals[j].lo <= hi + 1) {
            if (intervals[j].hi > hi) hi = intervals[j].hi;
            j++;
        }

        int new_len = pos + 1 + (len - j);
        if (new_len > cap) {
            cap = new_len * 2;
            intervals = (Interval *)realloc(intervals, cap * sizeof(Interval));
        }

        if (len - j > 0)
            memmove(&intervals[pos + 1], &intervals[j], (len - j) * sizeof(Interval));

        intervals[pos].lo = lo;
        intervals[pos].hi = hi;
        len = new_len;
    }

    *ret_size = len;
    return intervals;
}

int main(void)
{
    int n;
    int *values = read_ints(&n);
    int ret_size = 0;
    Interval *result = solve_intervals(values, n, &ret_size);
    write_matrix2d_int((int *)result, ret_size, 2);
    free(values);
    free(result);
    return 0;
}
