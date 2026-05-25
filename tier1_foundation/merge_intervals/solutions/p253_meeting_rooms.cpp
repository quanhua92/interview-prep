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


#include "cpptest.h"
#include <algorithm>

int minMeetingRooms(const std::vector<int> &flat)
{
    int n = flat.size() / 2;
    if (n == 0) return 0;
    std::vector<int> starts(n), ends(n);
    for (int i = 0; i < n; i++) {
        starts[i] = flat[2 * i];
        ends[i] = flat[2 * i + 1];
    }
    std::sort(starts.begin(), starts.end());
    std::sort(ends.begin(), ends.end());
    int rooms = 0, ep = 0;
    for (int s : starts) {
        if (s >= ends[ep])
            ep++;
        else
            rooms++;
    }
    return rooms;
}

void __attribute__((unused)) _use_harness_fns(void)
{
    (void)print_arr;
}

int main()
{
    TestCase tests[] = {
        {"example 1", {0, 30, 5, 10, 15, 20}, 0, {2}},
        {"example 2", {7, 10, 2, 4}, 0, {1}},
        {"no meetings", {}, 0, {0}},
        {"single meeting", {0, 1}, 0, {1}},
        {"all meetings overlap", {0, 10, 1, 9, 2, 8, 3, 7}, 0, {4}},
        {"meetings end and start at same time", {0, 5, 5, 10, 5, 10}, 0, {2}},
        {"all same start time", {0, 30, 0, 30, 0, 30}, 0, {3}},
        {"no overlap sequential", {0, 1, 1, 2, 2, 3}, 0, {1}},
    };
    int n = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;
    for (int i = 0; i < n; i++) {
        int got = minMeetingRooms(tests[i].input_arr);
        if (got == tests[i].expected[0]) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label.c_str());
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label.c_str());
            printf("    Expected: %d\n    Got:      %d\n",
                   tests[i].expected[0], got);
        }
    }
    printf("\n  %d/%d passed\n", passed, n);
    return passed == n ? 0 : 1;
}
