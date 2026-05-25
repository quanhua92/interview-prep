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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "cpptest.h"
#pragma GCC diagnostic pop
#include <algorithm>
#include <unordered_map>
#include <vector>

int numberOfBoomerangs(const std::vector<std::pair<int,int>> &points)
{
    /* TODO: Implement */
    return 0;
}

int main(void)
{
    struct TC {
        const char *label;
        std::vector<std::pair<int,int>> points;
        int expected;
    };
    TC tests[] = {
        {"example 1", {{0,0},{1,0},{2,0}}, 2},
        {"example 2", {{1,1},{2,2},{3,3}}, 2},
        {"example 3", {{1,1}}, 0},
        {"only 2 points", {{0,0},{1,0}}, 0},
        {"square 4 points", {{0,0},{0,1},{1,0},{1,1}}, 8},
        {"isoceles triangle", {{0,0},{1,1},{1,-1}}, 2},
        {"isoceles different heights", {{0,0},{3,4},{3,-4}}, 2},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  447. Number of Boomerangs\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        int got = numberOfBoomerangs(tests[i].points);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d\n    Got:      %d\n", tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
