/*
 * P973: K Closest Points to Origin (Medium)
 * https://leetcode.com/problems/k-closest-points-to-origin/
 * Topics: Array, Math, Divide and Conquer, Geometry, Sorting, Heap (Priority Queue), Quickselect
 * 
 * Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane and an integer k, return the k closest points to the origin (0, 0).
 * The distance between two points on the X-Y plane is the Euclidean distance (i.e., √(x1 - x2)2 + (y1 - y2)2).
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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "cpptest.h"
#pragma GCC diagnostic pop
#include <algorithm>
#include <vector>

std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>> points, int k)
{
    /* TODO: Implement */
    return 0;
}

int main(void)
{
    struct TC {
        const char *label;
        std::vector<std::vector<int>> input;
        int k;
        std::vector<std::vector<int>> expected;
    };
    TC tests[] = {
        {"example 1",          {{1, 3}, {-2, 2}},                  1, {{-2, 2}}},
        {"example 2 (sorted)", {{3, 3}, {5, -1}, {-2, 4}},         2, {{-2, 4}, {3, 3}}},
        {"origin itself",      {{0, 0}},                           1, {{0, 0}}},
        {"tie on distance",    {{1, 0}, {0, 1}, {2, 0}},            2, {{0, 1}, {1, 0}}},
        {"negative coords",    {{-1, -1}, {2, 2}, {3, 3}},         1, {{-1, -1}}},
        {"two tied closest",   {{1, 0}, {0, 1}, {2, 0}},            2, {{0, 1}, {1, 0}}},
        {"all same point",     {{1, 1}, {1, 1}, {1, 1}},           2, {{1, 1}, {1, 1}}},
        {"origin is closest",  {{3, 4}, {0, 0}, {1, 1}},           1, {{0, 0}}},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  973. K Closest Points to Origin\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        auto got = kClosest(tests[i].input, tests[i].k);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected %zu points, got %zu\n", tests[i].expected.size(), got.size());
        }
    }

    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
