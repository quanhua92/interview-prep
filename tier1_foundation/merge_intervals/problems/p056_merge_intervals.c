/*
 * P56: Merge Intervals (Medium)
 * https://leetcode.com/problems/merge-intervals/
 * Topics: Array, Sorting
 * 
 * Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.
 * 
 * Example 1:
 *     Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
 *     Output: [[1,6],[8,10],[15,18]]
 *     Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].
 * 
 * Example 2:
 *     Input: intervals = [[1,4],[4,5]]
 *     Output: [[1,5]]
 *     Explanation: Intervals [1,4] and [4,5] are considered overlapping.
 * 
 * Constraints:
 *     - 1 <= intervals.length <= 104
 *     - intervals[i].length == 2
 *     - 0 <= starti <= endi <= 104
 * 
 * Template (python3):
 *     class Solution:
 *         def merge(self, intervals: List[List[int]]) -> List[List[int]]:
 * 
 * Hint: Sort intervals by start time, then merge overlapping ones.
 */
#include "ctest.h"
#include <stdlib.h>

static int pair_cmp(const void *a, const void *b)
{
    abort();
}

int *solve(int *flat, int flat_n, int target, int *ret_size)
{
    abort();
}

int main(void)
{
    TestCase cases[] = {
        {"example 1",                   {1,3,2,6,8,10,15,18}, 8, 0, {1,6,8,10,15,18}, 6},
        {"example 2",                   {1,4,4,5},             4, 0, {1,5},             2},
        {"overlapping start",           {1,4,0,4},             4, 0, {0,4},             2},
        {"single interval",             {1,1},                 2, 0, {1,1},             2},
        {"all overlap into one",        {1,4,2,3,3,5},         6, 0, {1,5},             2},
        {"no overlaps",                 {1,2,3,4,5,6},         6, 0, {1,2,3,4,5,6},    6},
        {"interval contains others",    {1,10,2,3,4,5},        6, 0, {1,10},            2},
        {"adjacent intervals touching", {1,2,2,3,3,4},         6, 0, {1,4},             2},
    };

    RUN_TESTS("P56: Merge Intervals", solve, cases, 8);
}
