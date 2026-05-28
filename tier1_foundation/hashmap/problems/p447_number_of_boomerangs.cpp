/*
 * P447: Number of Boomerangs [PREMIUM] (Medium)
 * https://leetcode.com/problems/number-of-boomerangs/
 * Topics: Array, Hash Table, Math
 *
 * You are given n points in the plane that are all distinct, where points[i] = [xi, yi]. A boomerang is a tuple of points (i, j, k) such that the distance between i and j equals the distance between i and k (the order of the tuple matters).
 * Return the number of boomerangs.
 * Example 1:
 *     Input: points = [[0,0],[1,0],[2,0]]
 *     Output: 2
 *     Explanation: The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]].
 *
 * Example 2:
 *     Input: points = [[1,1],[2,2],[3,3]]
 *     Output: 2
 *
 * Example 3:
 *     Input: points = [[1,1]]
 *     Output: 0
 *
 * Constraints:
 *     - n == points.length
 *     - 1 <= n <= 500
 *     - points[i].length == 2
 *     - -104 <= xi, yi <= 104
 *     - All the points are unique.
 *
 * Template (python3):
 *     class Solution:
 *         def numberOfBoomerangs(self, points: List[List[int]]) -> int:
 */


#include "io.h"
#include <unordered_map>
#include <utility>
#include <vector>

int numberOfBoomerangs(const std::vector<std::pair<int,int>> &points)
{
    abort();
}

int main(void)
{
    std::vector<int> header = read_ints();
    int n = header[0];

    std::vector<std::pair<int,int>> points;
    for (int i = 0; i < n; i++) {
        std::vector<int> row = read_ints();
        points.push_back({row[0], row[1]});
    }
    write_int(numberOfBoomerangs(points));
    return 0;
}
