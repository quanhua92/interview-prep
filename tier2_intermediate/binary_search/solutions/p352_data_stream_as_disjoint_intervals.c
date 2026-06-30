/*
 * P352: Data Stream as Disjoint Intervals [PREMIUM] (Hard)
 * https://leetcode.com/problems/data-stream-as-disjoint-intervals/
 * Topics: Binary Search, Design, Ordered Set
 *
 * Given a data stream input of non-negative integers a1, a2, ..., an, summarize the numbers seen so far as a list of disjoint intervals.
 *
 * Implement the SummaryRanges class:
 *
 * SummaryRanges() Initializes the object with an empty stream.
 * void addNum(int value) Adds the integer value to the stream.
 * int[][] getIntervals() Returns a summary of the integers in the stream currently as a list of disjoint intervals [starti, endi]. The answer should be sorted by starti.
 *
 *
 * Example 1:
 *
 * Input
 * ["SummaryRanges", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals"]
 * [[], [1], [], [3], [], [7], [], [2], [], [6], []]
 * Output
 * [null, null, [[1, 1]], null, [[1, 1], [3, 3]], null, [[1, 1], [3, 3], [7, 7]], null, [[1, 3], [7, 7]], null, [[1, 3], [6, 7]]]
 *
 * Explanation
 * SummaryRanges summaryRanges = new SummaryRanges();
 * summaryRanges.addNum(1);      // arr = [1]
 * summaryRanges.getIntervals(); // return [[1, 1]]
 * summaryRanges.addNum(3);      // arr = [1, 3]
 * summaryRanges.getIntervals(); // return [[1, 1], [3, 3]]
 * summaryRanges.addNum(7);      // arr = [1, 3, 7]
 * summaryRanges.getIntervals(); // return [[1, 1], [3, 3], [7, 7]]
 * summaryRanges.addNum(2);      // arr = [1, 2, 3, 7]
 * summaryRanges.getIntervals(); // return [[1, 3], [7, 7]]
 * summaryRanges.addNum(6);      // arr = [1, 2, 3, 6, 7]
 * summaryRanges.getIntervals(); // return [[1, 3], [6, 7]]
 *
 *
 *
 * Constraints:
 *
 * 0 <= value <= 10^4
 * At most 3 * 10^4 calls will be made to addNum and getIntervals.
 * At most 10^2 calls will be made to getIntervals.
 *
 *
 * Follow up: What if there are lots of merges and the number of disjoint intervals is small compared to the size of the data stream?
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
    s->cap = 16;
    s->n = 0;
    s->lo = (int *)malloc(s->cap * sizeof(int));
    s->hi = (int *)malloc(s->cap * sizeof(int));
}

static void solution_addNum(SummaryRanges *s, int value) {
    int lo = value, hi = value;
    int pos = 0;
    while (pos < s->n && s->lo[pos] < lo) pos++;
    if (pos > 0 && s->hi[pos - 1] >= lo - 1) {
        pos--;
        lo = s->lo[pos];
    }
    while (pos < s->n && s->lo[pos] <= hi + 1) {
        if (s->hi[pos] > hi) hi = s->hi[pos];
        memmove(&s->lo[pos], &s->lo[pos + 1], (s->n - pos - 1) * sizeof(int));
        memmove(&s->hi[pos], &s->hi[pos + 1], (s->n - pos - 1) * sizeof(int));
        s->n--;
    }
    if (s->n >= s->cap) {
        s->cap *= 2;
        s->lo = (int *)realloc(s->lo, s->cap * sizeof(int));
        s->hi = (int *)realloc(s->hi, s->cap * sizeof(int));
    }
    memmove(&s->lo[pos + 1], &s->lo[pos], (s->n - pos) * sizeof(int));
    memmove(&s->hi[pos + 1], &s->hi[pos], (s->n - pos) * sizeof(int));
    s->lo[pos] = lo;
    s->hi[pos] = hi;
    s->n++;
}

static void solution_getIntervals(SummaryRanges *s) {
    write_int(s->n);
    for (int k = 0; k < s->n; k++) {
        int row[2] = {s->lo[k], s->hi[k]};
        write_ints(row, 2);
    }
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
