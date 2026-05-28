/*
 * P452: Minimum Number of Arrows to Burst Balloons [PREMIUM] (Medium)
 * https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/
 * Topics: Array, Greedy, Sorting
 *
 * There are some spherical balloons taped onto a flat wall that represents the XY-plane. The balloons are represented as a 2D integer array points where points[i] = [xstart, xend] denotes a balloon whose horizontal diameter stretches between xstart and xend.
 * Given the array points, return the minimum number of arrows that must be shot to burst all balloons.
 *
 * Example 1:
 *     Input: points = [[10,16],[2,8],[1,6],[7,12]]
 *     Output: 2
 *
 * Example 2:
 *     Input: points = [[1,2],[3,4],[5,6],[7,8]]
 *     Output: 4
 *
 * Example 3:
 *     Input: points = [[1,2],[2,3],[3,4],[4,5]]
 *     Output: 2
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


#include "io.h"
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
    std::vector<int> header = read_ints();
    (void)header;
    std::vector<std::pair<ll, ll>> points;
    while (true) {
        std::vector<int> row = read_ints();
        if (row.size() < 2) break;
        points.push_back({(ll)row[0], (ll)row[1]});
    }
    int result = findMinArrowShots(points);
    write_int(result);
    return 0;
}
