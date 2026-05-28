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

#include "io.h"
#include <stdlib.h>

static int cmp_int(const void *a, const void *b)
{
    abort();
}

int solve(int n, int intervals[][2])
{
    abort();
}

int main(void)
{
    int n = read_int();
    int (*intervals)[2] = malloc(n * sizeof(*intervals));
    for (int i = 0; i < n; i++) {
        int *row = read_ints(NULL);
        intervals[i][0] = row[0];
        intervals[i][1] = row[1];
        free(row);
    }
    write_int(solve(n, intervals));
    free(intervals);
    return 0;
}
