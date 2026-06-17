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
 *     - 0 <= value <= 10^4
 *     - At most 3 * 10^4 calls will be made to addNum and getIntervals.
 *     - At most 10^2 calls will be made to getIntervals.
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
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *lo;
    int *hi;
    int n;
    int cap;
} SummaryRanges;

static void solution_init(SummaryRanges *s) {
    (void)s;
    abort();
}

static void solution_addNum(SummaryRanges *s, int value) {
    (void)s; (void)value;
    abort();
}

static void solution_getIntervals(SummaryRanges *s) {
    (void)s;
    abort();
}

int main(void)
{
    int num_ops = read_int();
    SummaryRanges sr;
    solution_init(&sr);
    for (int i = 0; i < num_ops; i++) {
        char *op = read_line();
        int argc = read_int();
        int *args = NULL;
        if (argc > 0) {
            int rc;
            args = read_ints(&rc);
        }
        if (strcmp(op, "getIntervals") == 0) {
            solution_getIntervals(&sr);
        } else if (strcmp(op, "addNum") == 0) {
            solution_addNum(&sr, args[0]);
        }
        free(op);
        free(args);
    }
    free(sr.lo);
    free(sr.hi);
    return 0;
}
