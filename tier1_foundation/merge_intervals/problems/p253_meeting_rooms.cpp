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
 * Hint: Sort start and end times separately, then use two pointers to count concurrent meetings.
 */


#include "io.h"
#include <vector>

int solve(std::vector<std::vector<int>> &intervals)
{
    abort();
}

int main()
{
    int n = read_int();
    std::vector<std::vector<int>> intervals(n);
    for (int i = 0; i < n; i++) {
        intervals[i] = read_ints();
    }
    write_int(solve(intervals));
    return 0;
}
