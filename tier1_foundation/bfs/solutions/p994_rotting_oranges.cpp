/*
 * P994: Rotting Oranges (Medium)
 * https://leetcode.com/problems/rotting-oranges/
 * Topics: Array, Breadth-First Search, Matrix
 *
 * You are given an m x n grid where each cell can have one of three values:
 * Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.
 * Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.
 *
 * Example 1:
 *     Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
 *     Output: 4
 *
 * Example 2:
 *     Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
 *     Output: -1
 *     Explanation: The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.
 *
 * Example 3:
 *     Input: grid = [[0,2]]
 *     Output: 0
 *     Explanation: Since there are already no fresh oranges at minute 0, the answer is just 0.
 *
 * Constraints:
 *     - m == grid.length
 *     - n == grid[i].length
 *     - 1 <= m, n <= 10
 *     - grid[i][j] is 0, 1, or 2.
 *
 * Template (python3):
 *     class Solution:
 *         def orangesRotting(self, grid: List[List[int]]) -> int:
 *
 * Hint: Use BFS starting from all rotten oranges simultaneously.
 */


#include "cpptest.h"
#include <queue>
#include <utility>

using namespace std;

static int orangesRotting(vector<vector<int>> &grid) {
    int rows = (int)grid.size();
    int cols = (int)grid[0].size();
    queue<pair<int,int>> q;
    int fresh = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 2) {
                q.push({r, c});
            } else if (grid[r][c] == 1) {
                fresh++;
            }
        }
    }
    if (fresh == 0) return 0;
    int minutes = 0;
    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};
    while (!q.empty()) {
        int sz = (int)q.size();
        for (int i = 0; i < sz; i++) {
            auto [r, c] = q.front();
            q.pop();
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == 1) {
                    grid[nr][nc] = 2;
                    fresh--;
                    q.push({nr, nc});
                }
            }
        }
        if (!q.empty()) minutes++;
    }
    return fresh == 0 ? minutes : -1;
}

int main() {
    (void)print_arr;
    struct TC {
        string label;
        vector<vector<int>> grid;
        int expected;
    };
    TC tests[] = {
        {"example 1", {{2,1,1},{1,1,0},{0,1,1}}, 4},
        {"example 2", {{2,1,1},{0,1,1},{1,0,1}}, -1},
        {"no fresh", {{0,2}}, 0},
        {"single fresh no rotten", {{1}}, -1},
        {"single rotten", {{2}}, 0},
        {"all fresh no rotten", {{1,1,1},{1,1,1},{1,1,1}}, -1},
        {"multiple rotten sources", {{2,2},{1,1},{0,1}}, 2},
    };
    int nt = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < nt; i++) {
        vector<vector<int>> grid = tests[i].grid;
        int got = orangesRotting(grid);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label.c_str());
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label.c_str());
            printf("    Expected: %d\n    Got:      %d\n", tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, nt);
    return passed == nt ? 0 : 1;
}
