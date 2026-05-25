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
 *     - At most 102 calls will be made to getIntervals.
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { int lo, hi; } Interval;

static Interval *solve_intervals(const int *values, int n, int *ret_size)
{
    abort();
}

static int check(const Interval *got, int gn, const int *expected, int en)
{
    abort();
}

int main(void)
{
    struct {
        const char *label;
        int values[10];
        int n;
        int expected[20];
        int expected_n;
        int pass;
    } tests[] = {
        { "example from problem", {1,3,7,2,6}, 5, {1,3,6,7}, 4, 0 },
        { "adjacent values merge", {1,0}, 2, {0,1}, 2, 0 },
        { "single zero", {0}, 1, {0,0}, 2, 0 },
        { "no merges sorted output", {100,1,50}, 3, {1,1,50,50,100,100}, 6, 0 },
        { "empty stream", {0}, 0, {0}, 0, 0 },
    };
    int tn = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;

    for (int i = 0; i < tn; i++) {
        int ret_size = 0;
        Interval *got = solve_intervals(tests[i].values, tests[i].n, &ret_size);
        tests[i].pass = check(got, ret_size, tests[i].expected, tests[i].expected_n);
        if (tests[i].pass) passed++;
        free(got);
    }

    printf("\n============================================================\n");
    printf("  352. Data Stream as Disjoint Intervals\n");
    printf("============================================================\n");
    for (int i = 0; i < tn; i++)
        printf("  Test %d (%s): %s\n", i + 1, tests[i].label, tests[i].pass ? "PASS" : "FAIL");
    printf("\n  %d/%d passed\n", passed, tn);
    printf("============================================================\n");
    return passed == tn ? 0 : 1;
}
