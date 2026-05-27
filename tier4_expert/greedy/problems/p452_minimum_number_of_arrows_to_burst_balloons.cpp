/*
 * P452: Minimum Number of Arrows to Burst Balloons [PREMIUM] (Medium)
 * https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/
 * Topics: Array, Greedy, Sorting
 *
 * Given the array points, return the minimum number of arrows that must be shot to burst all balloons.
 */


#include "cpptest.h"
#include <vector>

using ll = long long;

int findMinArrowShots(std::vector<std::pair<ll, ll>> &points) {
    abort();
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
