/*
 * P542: 01 Matrix [PREMIUM] (Medium)
 * https://leetcode.com/problems/01-matrix/
 * Topics: Array, Dynamic Programming, Breadth-First Search, Matrix
 *
 * Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.
 * The distance between two cells sharing a common edge is 1.
 * Example 2:
 * Note: This question is the same as 1765: https://leetcode.com/problems/map-of-highest-peak/
 * Example 1:
 *     Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
 *     Output: [[0,0,0],[0,1,0],[0,0,0]]
 *
 * Example 2:
 *     Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
 *     Output: [[0,0,0],[0,1,0],[1,2,1]]
 *
 * Constraints:
 *     - m == mat.length
 *     - n == mat[i].length
 *     - 1 <= m, n <= 104
 *     - 1 <= m * n <= 104
 *     - mat[i][j] is either 0 or 1.
 *     - There is at least one 0 in mat.
 *
 * Template (python3):
 *     class Solution:
 *         def updateMatrix(self, mat: List[List[int]]) -> List[List[int]]:
 */


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "cpptest.h"
#pragma GCC diagnostic pop
#include <queue>
#include <climits>

static std::vector<std::vector<int>> updateMatrix(const std::vector<std::vector<int>> &mat)
{
    if (mat.empty()) return {};
    int m = mat.size(), n = mat[0].size();
    std::vector<std::vector<int>> dist(m, std::vector<int>(n, -1));
    std::queue<std::pair<int,int>> q;

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (mat[i][j] == 0) {
                dist[i][j] = 0;
                q.push({i, j});
            }

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
    return dist;
}

typedef struct {
    const char *label;
    std::vector<std::vector<int>> input;
    std::vector<std::vector<int>> expected;
} MatDistTC;

int main(void)
{
    MatDistTC tests[] = {
        {"example 1", {{0,0,0},{0,1,0},{0,0,0}}, {{0,0,0},{0,1,0},{0,0,0}}},
        {"example 2", {{0,0,0},{0,1,0},{1,1,1}}, {{0,0,0},{0,1,0},{1,2,1}}},
        {"single zero", {{0}}, {{0}}},
        {"single column", {{1},{0},{1}}, {{1},{0},{1}}},
        {"single row", {{0,1,1,1}}, {{0,1,2,3}}},
        {"cross of ones around center zero", {{1,1,1},{1,0,1},{1,1,1}}, {{2,1,2},{1,0,1},{2,1,2}}},
        {"corner zeros", {{1,1,0},{1,1,1},{0,1,1}}, {{2,1,0},{1,2,1},{0,1,2}}},
    };

    int n_tests = (int)(sizeof(tests) / sizeof(tests[0]));
    printf("\n============================================================\n");
    printf("  542. 01 Matrix\n");
    printf("============================================================\n");
    int passed = 0;
    for (int t = 0; t < n_tests; t++) {
        MatDistTC &tc = tests[t];
        std::vector<std::vector<int>> got = updateMatrix(tc.input);
        if (got == tc.expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", t + 1, tc.label);
        } else {
            printf("  Test %d (%s): FAIL\n", t + 1, tc.label);
        }
    }
    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
