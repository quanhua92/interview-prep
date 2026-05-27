/*
 * P391: Perfect Rectangle [PREMIUM] (Hard)
 * https://leetcode.com/problems/perfect-rectangle/
 * Topics: Array, Hash Table, Math, Geometry, Line Sweep
 *
 * Given an array rectangles where rectangles[i] = [xi, yi, ai, bi] represents an axis-aligned rectangle. The bottom-left point of the rectangle is (xi, yi) and the top-right point of it is (ai, bi).
 * Return true if all the rectangles together form an exact cover of a rectangular region.
 * Example 1:
 *     Input: rectangles = [[1,1,3,3],[3,1,4,2],[3,2,4,4],[1,3,2,4],[2,3,3,4]]
 *     Output: true
 *     Explanation: All 5 rectangles together form an exact cover of a rectangular region.
 *
 * Example 2:
 *     Input: rectangles = [[1,1,2,3],[1,3,2,4],[3,1,4,2],[3,2,4,4]]
 *     Output: false
 *     Explanation: Because there is a gap between the two rectangular regions.
 *
 * Example 3:
 *     Input: rectangles = [[1,1,3,3],[3,1,4,2],[1,3,2,4],[2,2,4,4]]
 *     Output: false
 *     Explanation: Because two of the rectangles overlap with each other.
 *
 * Constraints:
 *     - 1 <= rectangles.length <= 2 * 104
 *     - rectangles[i].length == 4
 *     - -105 <= xi < ai <= 105
 *     - -105 <= yi < bi <= 105
 *
 * Template (python3):
 *     class Solution:
 *         def isRectangleCover(self, rectangles: List[List[int]]) -> bool:
 */


#include "io.h"
#include <set>

static bool isRectangleCover(const std::vector<std::vector<int>> &rectangles)
{
    std::set<std::pair<long long,long long>> corners;
    long long total_area = 0;
    long long min_x = 200000LL, min_y = 200000LL;
    long long max_x = -200000LL, max_y = -200000LL;

    for (const auto &r : rectangles) {
        long long x1 = r[0], y1 = r[1], x2 = r[2], y2 = r[3];
        min_x = std::min(min_x, x1);
        min_y = std::min(min_y, y1);
        max_x = std::max(max_x, x2);
        max_y = std::max(max_y, y2);
        total_area += (x2 - x1) * (y2 - y1);

        std::pair<long long,long long> pts[] = {{x1,y1},{x1,y2},{x2,y1},{x2,y2}};
        for (const auto &p : pts) {
            auto it = corners.find(p);
            if (it != corners.end())
                corners.erase(it);
            else
                corners.insert(p);
        }
    }

    if (corners.size() != 4) return false;
    std::set<std::pair<long long,long long>> expected = {
        {min_x, min_y}, {min_x, max_y}, {max_x, min_y}, {max_x, max_y}
    };
    if (corners != expected) return false;

    return total_area == (max_x - min_x) * (max_y - min_y);
}

int main(void)
{
    std::vector<int> header = read_ints();
    int n = header[0];

    std::vector<std::vector<int>> rectangles;
    for (int i = 0; i < n; i++) {
        rectangles.push_back(read_ints());
    }

    write_bool(isRectangleCover(rectangles));
    return 0;
}
