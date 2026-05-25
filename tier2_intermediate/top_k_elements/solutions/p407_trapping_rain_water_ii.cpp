/*
 * P407: Trapping Rain Water II [PREMIUM] (Hard)
 * https://leetcode.com/problems/trapping-rain-water-ii/
 * Topics: Array, Breadth-First Search, Heap (Priority Queue), Matrix
 *
 * Given an m x n integer matrix heightMap representing the height of each unit cell in a 2D elevation map, return the volume of water it can trap after raining.
 * Example 1:
 *     Input: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
 *     Output: 4
 *     Explanation: After the rain, water is trapped between the blocks.
 *     We have two small ponds 1 and 3 units trapped.
 *     The total volume of water trapped is 4.
 *
 * Example 2:
 *     Input: heightMap = [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]
 *     Output: 10
 *
 * Constraints:
 *     - m == heightMap.length
 *     - n == heightMap[i].length
 *     - 1 <= m, n <= 200
 *     - 0 <= heightMap[i][j] <= 2 * 104
 *
 * Template (python3):
 *     class Solution:
 *         def trapRainWater(self, heightMap: List[List[int]]) -> int:
 */


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "cpptest.h"
#pragma GCC diagnostic pop
#include <queue>
#include <tuple>
#include <vector>

int trapRainWater(const std::vector<std::vector<int>> &heightMap)
{
    int m = heightMap.size();
    if (m == 0) return 0;
    int n = heightMap[0].size();
    if (n == 0 || m < 3 || n < 3) return 0;

    std::priority_queue<std::tuple<int, int, int>,
                        std::vector<std::tuple<int, int, int>>,
                        std::greater<>>
        pq;
    std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));

    for (int r = 0; r < m; r++) {
        pq.push({heightMap[r][0], r, 0});
        visited[r][0] = true;
        pq.push({heightMap[r][n - 1], r, n - 1});
        visited[r][n - 1] = true;
    }
    for (int c = 1; c < n - 1; c++) {
        pq.push({heightMap[0][c], 0, c});
        visited[0][c] = true;
        pq.push({heightMap[m - 1][c], m - 1, c});
        visited[m - 1][c] = true;
    }

    static const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int water = 0;

    while (!pq.empty()) {
        auto [h, r, c] = pq.top();
        pq.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dirs[d][0], nc = c + dirs[d][1];
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && !visited[nr][nc]) {
                visited[nr][nc] = true;
                if (h > heightMap[nr][nc]) water += h - heightMap[nr][nc];
                pq.push({std::max(h, heightMap[nr][nc]), nr, nc});
            }
        }
    }

    return water;
}

int main(void)
{
    struct TC {
        const char *label;
        std::vector<std::vector<int>> input;
        int expected;
    };
    TC tests[] = {
        {"example 1", {{1, 4, 3, 1, 3, 2}, {3, 2, 1, 3, 2, 4}, {2, 3, 3, 2, 3, 1}}, 4},
        {"example 2", {{3, 3, 3, 3, 3}, {3, 2, 2, 2, 3}, {3, 2, 1, 2, 3}, {3, 2, 2, 2, 3}, {3, 3, 3, 3, 3}}, 10},
        {"1x1 no trap", {{1}}, 0},
        {"3x3 basin", {{5, 5, 5}, {5, 1, 5}, {5, 5, 5}}, 4},
        {"2x4 no interior", {{5, 5, 5, 5}, {5, 5, 5, 5}}, 0},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  407. Trapping Rain Water II\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        int got = trapRainWater(tests[i].input);
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
