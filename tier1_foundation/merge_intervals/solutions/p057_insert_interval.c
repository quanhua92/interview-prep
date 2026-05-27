/*
 * P57: Insert Interval (Medium)
 * https://leetcode.com/problems/insert-interval/
 * Topics: Array
 *
 * You are given an array of non-overlapping intervals intervals where intervals[i] = [starti, endi] represent the start and the end of the ith interval and intervals is sorted in ascending order by starti. You are also given an interval newInterval = [start, end] that represents the start and end of another interval.
 * Insert newInterval into intervals such that intervals is still sorted in ascending order by starti and intervals still does not have any overlapping intervals (merge overlapping intervals if necessary).
 * Return intervals after the insertion.
 * Note that you don't need to modify intervals in-place. You can make a new array and return it.
 *
 * Example 1:
 *     Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
 *     Output: [[1,5],[6,9]]
 *
 * Example 2:
 *     Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
 *     Output: [[1,2],[3,10],[12,16]]
 *     Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
 *
 * Constraints:
 *     - 0 <= intervals.length <= 104
 *     - intervals[i].length == 2
 *     - 0 <= starti <= endi <= 105
 *     - intervals is sorted by starti in ascending order.
 *     - newInterval.length == 2
 *     - 0 <= start <= end <= 105
 *
 * Hints:
 *     - Intervals Array is sorted. Can you use Binary Search to find the correct position to insert the new Interval.?
 *     - Can you try merging the overlapping intervals while inserting the new interval?
 *     - This can be done by comparing the end of the last interval with the start of the new interval and vice versa.
 *
 * Template (python3):
 *     class Solution:
 *         def insert(self, intervals: List[List[int]], newInterval: List[int]) -> List[List[int]]:
 *
 * Hint: Add non-overlapping before, merge overlapping, add non-overlapping after.
 */

#include "io.h"
#include <stdlib.h>

void solve(int num_intervals, int intervals[][2], int new_interval[2])
{
    int new_start = new_interval[0];
    int new_end = new_interval[1];
    int cap = (num_intervals + 1) * 2;
    int *result = malloc(cap * sizeof(int));
    int ri = 0;
    int i = 0;

    while (i < num_intervals && intervals[i][1] < new_start) {
        result[ri++] = intervals[i][0];
        result[ri++] = intervals[i][1];
        i++;
    }

    while (i < num_intervals && intervals[i][0] <= new_end) {
        if (intervals[i][0] < new_start) new_start = intervals[i][0];
        if (intervals[i][1] > new_end) new_end = intervals[i][1];
        i++;
    }

    result[ri++] = new_start;
    result[ri++] = new_end;

    while (i < num_intervals) {
        result[ri++] = intervals[i][0];
        result[ri++] = intervals[i][1];
        i++;
    }

    for (int j = 0; j < ri; j += 2) {
        int row[2] = {result[j], result[j + 1]};
        write_ints(row, 2);
    }
    free(result);
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
    int *ni = read_ints(NULL);
    int new_interval[2] = {ni[0], ni[1]};
    free(ni);
    solve(n, intervals, new_interval);
    free(intervals);
    return 0;
}
