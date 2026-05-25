/*
 * P452: Minimum Number of Arrows to Burst Balloons [PREMIUM] (Medium)
 * https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/
 * Topics: Array, Greedy, Sorting
 *
 * There are some spherical balloons taped onto a flat wall that represents the XY-plane. The balloons are represented as a 2D integer array points where points[i] = [xstart, xend] denotes a balloon whose horizontal diameter stretches between xstart and xend. You do not know the exact y-coordinates of the balloons.
 * Arrows can be shot up directly vertically (in the positive y-direction) from different points along the x-axis. A balloon with xstart and xend is burst by an arrow shot at x if xstart <= x <= xend. There is no limit to the number of arrows that can be shot. A shot arrow keeps traveling up infinitely, bursting any balloons in its path.
 * Given the array points, return the minimum number of arrows that must be shot to burst all balloons.
 * Example 1:
 *     Input: points = [[10,16],[2,8],[1,6],[7,12]]
 *     Output: 2
 *     Explanation: The balloons can be burst by 2 arrows:
 *     - Shoot an arrow at x = 6, bursting the balloons [2,8] and [1,6].
 *     - Shoot an arrow at x = 11, bursting the balloons [10,16] and [7,12].
 *
 * Example 2:
 *     Input: points = [[1,2],[3,4],[5,6],[7,8]]
 *     Output: 4
 *     Explanation: One arrow needs to be shot for each balloon for a total of 4 arrows.
 *
 * Example 3:
 *     Input: points = [[1,2],[2,3],[3,4],[4,5]]
 *     Output: 2
 *     Explanation: The balloons can be burst by 2 arrows:
 *     - Shoot an arrow at x = 2, bursting the balloons [1,2] and [2,3].
 *     - Shoot an arrow at x = 4, bursting the balloons [3,4] and [4,5].
 *
 * Constraints:
 *     - 1 <= points.length <= 105
 *     - points[i].length == 2
 *     - -231 <= xstart < xend <= 231 - 1
 *
 * Template (python3):
 *     class Solution:
 *         def findMinArrowShots(self, points: List[List[int]]) -> int:
 */


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "cpptest.h"
#pragma GCC diagnostic pop
#include <algorithm>
#include <vector>

using ll = long long;

int findMinArrowShots(std::vector<std::pair<ll, ll>> &points) {
    if (points.empty()) return 0;
    std::sort(points.begin(), points.end(),
              [](const auto &a, const auto &b) { return a.second < b.second; });
    int arrows = 1;
    ll end = points[0].second;
    for (int i = 1; i < (int)points.size(); i++) {
        if (points[i].first > end) { arrows++; end = points[i].second; }
    }
    return arrows;
}

int main() {
    printf("\n============================================================\n");
    printf("  452. Minimum Number of Arrows to Burst Balloons\n");
    printf("============================================================\n");
    struct T { const char *label; std::vector<std::pair<ll, ll>> pts; int expected; };
    std::vector<T> tests = {
        {"example 1", {{10,16},{2,8},{1,6},{7,12}}, 2},
        {"example 2", {{1,2},{3,4},{5,6},{7,8}}, 4},
        {"example 3", {{1,2},{2,3},{3,4},{4,5}}, 2},
        {"single balloon", {{1,2}}, 1},
        {"all overlapping", {{1,10},{2,9},{3,8}}, 1},
        {"nested intervals", {{1,5},{2,3}}, 1},
        {"far apart balloons", {{-2147483646LL,-2147483645LL},{2147483646LL,2147483647LL}}, 2},
    };
    int passed = 0;
    for (int i = 0; i < (int)tests.size(); i++) {
        auto pts = tests[i].pts;
        int got = findMinArrowShots(pts);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d, Got: %d\n", tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, (int)tests.size());
    printf("============================================================\n\n");
    return passed == (int)tests.size() ? 0 : 1;
}
