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


#include "cpptest.h"
#include <algorithm>
#include <utility>
#include <vector>

static std::vector<int> solve(const std::vector<int> &flat, int target)
{
    (void)target;
    int n = (int)(flat.size() / 2);
    if (n == 0)
        return {};

    std::vector<std::pair<int, int>> iv(n);
    for (int i = 0; i < n; i++)
        iv[i] = {flat[i * 2], flat[i * 2 + 1]};
    std::sort(iv.begin(), iv.end());

    std::vector<int> res;
    res.push_back(iv[0].first);
    res.push_back(iv[0].second);

    for (int i = 1; i < n; i++) {
        if (iv[i].first <= res.back()) {
            res.back() = std::max(res.back(), iv[i].second);
        } else {
            res.push_back(iv[i].first);
            res.push_back(iv[i].second);
        }
    }

    return res;
}

int main()
{
    TestCase cases[] = {
        {"example 1",                   {1,3,2,6,8,10,15,18}, 0, {1,6,8,10,15,18}},
        {"example 2",                   {1,4,4,5},             0, {1,5}},
        {"overlapping start",           {1,4,0,4},             0, {0,4}},
        {"single interval",             {1,1},                 0, {1,1}},
        {"all overlap into one",        {1,4,2,3,3,5},         0, {1,5}},
        {"no overlaps",                 {1,2,3,4,5,6},         0, {1,2,3,4,5,6}},
        {"interval contains others",    {1,10,2,3,4,5},        0, {1,10}},
        {"adjacent intervals touching", {1,2,2,3,3,4},         0, {1,4}},
    };

    RUN_TESTS("P56: Merge Intervals", solve, cases, 8);
}
