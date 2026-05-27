/*
 * P973: K Closest Points to Origin (Medium)
 * https://leetcode.com/problems/k-closest-points-to-origin/
 * Topics: Array, Math, Divide and Conquer, Geometry, Sorting, Heap (Priority Queue), Quickselect
 *
 * Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane and an integer k, return the k closest points to the origin (0, 0).
 * The distance between two points on the X-Y plane is the Euclidean distance (i.e., sqrt((x1 - x2)^2 + (y1 - y2)^2)).
 * You may return the answer in any order. The answer is guaranteed to be unique (except for the order that it is in).
 *
 * Example 1:
 *     Input: points = [[1,3],[-2,2]], k = 1
 *     Output: [[-2,2]]
 *     Explanation:
 *     The distance between (1, 3) and the origin is sqrt(10).
 *     The distance between (-2, 2) and the origin is sqrt(8).
 *     Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
 *     We only want the closest k = 1 points from the origin, so the answer is just [[-2,2]].
 *
 * Example 2:
 *     Input: points = [[3,3],[5,-1],[-2,4]], k = 2
 *     Output: [[3,3],[-2,4]]
 *     Explanation: The answer [[-2,4],[3,3]] would also be accepted.
 *
 * Constraints:
 *     - 1 <= k <= points.length <= 104
 *     - -104 <= xi, yi <= 104
 *
 * Template (python3):
 *     class Solution:
 *         def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
 *
 * Hint: Use a max-heap of size k keyed by negative distance squared.
 */

#include "io.h"
#include <algorithm>
#include <vector>

std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>> points, int k)
{
    std::sort(points.begin(), points.end(), [](const auto &a, const auto &b) {
        int da = a[0] * a[0] + a[1] * a[1];
        int db = b[0] * b[0] + b[1] * b[1];
        return da < db || (da == db && (a[0] < b[0] || (a[0] == b[0] && a[1] < b[1])));
    });
    points.resize(k);
    std::sort(points.begin(), points.end());
    return points;
}

int main(void)
{
    std::vector<int> flat = read_ints();
    std::vector<int> k_arr = read_ints();
    int k = k_arr[0];
    std::vector<std::vector<int>> points;
    for (size_t i = 0; i < flat.size(); i += 2)
        points.push_back({flat[i], flat[i + 1]});
    auto result = kClosest(points, k);
    for (const auto &p : result)
        write_ints(p);
    return 0;
}
