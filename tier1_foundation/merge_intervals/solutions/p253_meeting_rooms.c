/*
 * P253: Meeting Rooms II (Medium)
 * https://leetcode.com/problems/meeting-rooms-ii/
 * Topics: Array, Two Pointers, Sorting, Heap (Priority Queue), Prefix Sum
 *
 * Given an array of meeting time intervals intervals where intervals[i] = [starti, endi], return the minimum number of conference rooms required.
 *
 * Example 1:
 *     Input: intervals = [[0,30],[5,10],[15,20]]
 *     Output: 2
 *
 * Example 2:
 *     Input: intervals = [[7,10],[2,4]]
 *     Output: 1
 *
 * Constraints:
 *     - 1 <= intervals.length <= 10^4
 *     - 0 <= starti < endi <= 10^6
 *
 * Hints:
 *     - Think about how we would approach this problem if we were given the intervals sorted by start time.
 *     - What if we use a min-heap to track the ending times of meetings?
 *
 * Template (python3):
 *     class Solution:
 *         def minMeetingRooms(self, intervals: List[List[int]]) -> int:
 *
 * Hint: Sort start and end times separately, then use two pointers to count concurrent meetings.
 */


#include "ctest.h"
#include <stdlib.h>

static int cmp_int(const void *a, const void *b)
{
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

int minMeetingRooms(int *intervals, int n)
{
    if (n == 0) return 0;
    int *starts = malloc(n * sizeof(int));
    int *ends = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        starts[i] = intervals[2 * i];
        ends[i] = intervals[2 * i + 1];
    }
    qsort(starts, n, sizeof(int), cmp_int);
    qsort(ends, n, sizeof(int), cmp_int);
    int rooms = 0, ep = 0;
    for (int i = 0; i < n; i++) {
        if (starts[i] >= ends[ep])
            ep++;
        else
            rooms++;
    }
    free(starts);
    free(ends);
    return rooms;
}

void __attribute__((unused)) _use_harness_fns(void)
{
    (void)th_print_arr;
    (void)th_arr_eq;
}

int main(void)
{
    TestCase tests[] = {
        {.label = "example 1",
         .input_arr = {0, 30, 5, 10, 15, 20},
         .input_arr_n = 6,
         .target = 0,
         .expected = {2},
         .expected_n = 1},
        {.label = "example 2",
         .input_arr = {7, 10, 2, 4},
         .input_arr_n = 4,
         .target = 0,
         .expected = {1},
         .expected_n = 1},
        {.label = "no meetings",
         .input_arr = {0},
         .input_arr_n = 0,
         .target = 0,
         .expected = {0},
         .expected_n = 1},
        {.label = "single meeting",
         .input_arr = {0, 1},
         .input_arr_n = 2,
         .target = 0,
         .expected = {1},
         .expected_n = 1},
        {.label = "all meetings overlap",
         .input_arr = {0, 10, 1, 9, 2, 8, 3, 7},
         .input_arr_n = 8,
         .target = 0,
         .expected = {4},
         .expected_n = 1},
        {.label = "meetings end and start at same time",
         .input_arr = {0, 5, 5, 10, 5, 10},
         .input_arr_n = 6,
         .target = 0,
         .expected = {2},
         .expected_n = 1},
        {.label = "all same start time",
         .input_arr = {0, 30, 0, 30, 0, 30},
         .input_arr_n = 6,
         .target = 0,
         .expected = {3},
         .expected_n = 1},
        {.label = "no overlap sequential",
         .input_arr = {0, 1, 1, 2, 2, 3},
         .input_arr_n = 6,
         .target = 0,
         .expected = {1},
         .expected_n = 1},
    };
    int n = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;
    for (int i = 0; i < n; i++) {
        int got = minMeetingRooms(tests[i].input_arr, tests[i].input_arr_n / 2);
        if (got == tests[i].expected[0]) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d\n    Got:      %d\n",
                   tests[i].expected[0], got);
        }
    }
    printf("\n  %d/%d passed\n", passed, n);
    return passed == n ? 0 : 1;
}
