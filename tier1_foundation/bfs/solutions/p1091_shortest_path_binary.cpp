/*
 * P1091: Shortest Path in Binary Matrix (Medium)
 * https://leetcode.com/problems/shortest-path-in-binary-matrix/
 * Topics: Array, Breadth-First Search, Matrix
 *
 * Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. If there is no clear path, return -1.
 * A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:
 * The length of a clear path is the number of visited cells of this path.
 *
 * Example 1:
 *     Input: grid = [[0,1],[1,0]]
 *     Output: 2
 *
 * Example 2:
 *     Input: grid = [[0,0,0],[1,1,0],[1,1,0]]
 *     Output: 4
 *
 * Example 3:
 *     Input: grid = [[1,0,0],[1,1,0],[1,1,0]]
 *     Output: -1
 *
 * Constraints:
 *     - n == grid.length
 *     - n == grid[i].length
 *     - 1 <= n <= 100
 *     - grid[i][j] is 0 or 1
 *
 * Hints:
 *     - Do a breadth first search to find the shortest path.
 *
 * Template (python3):
 *     class Solution:
 *         def shortestPathBinaryMatrix(self, grid: List[List[int]]) -> int:
 *
 * Hint: BFS from (0,0) with 8 directions, return distance to (n-1,n-1) or -1.
 */


#include "cpptest.h"
#include <queue>
#include <tuple>

using namespace std;

static int shortestPathBinaryMatrix(vector<vector<int>> &grid) {
    int n = (int)grid.size();
    if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) return -1;
    if (n == 1) return 1;
    queue<tuple<int,int,int>> q;
    q.push({0, 0, 1});
    grid[0][0] = 1;
    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    while (!q.empty()) {
        auto [r, c, dist] = q.front();
        q.pop();
        for (int d = 0; d < 8; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 0) {
                if (nr == n - 1 && nc == n - 1) return dist + 1;
                grid[nr][nc] = 1;
                q.push({nr, nc, dist + 1});
            }
        }
    }
    return -1;
}

int main() {
    (void)print_arr;
    struct TC {
        string label;
        vector<vector<int>> grid;
        int expected;
    };
    TC tests[] = {
        {"example 1", {{0,1},{1,0}}, 2},
        {"example 2", {{0,0,0},{1,1,0},{1,1,0}}, 4},
        {"blocked", {{1,0},{0,1}}, -1},
        {"single cell", {{0}}, 1},
        {"3x3 all open (diagonal)", {{0,0,0},{0,0,0},{0,0,0}}, 3},
        {"2x2 all open (diagonal)", {{0,0},{0,0}}, 2},
        {"3x3 only corners open", {{0,1,1},{1,1,1},{1,1,0}}, -1},
    };
    int nt = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < nt; i++) {
        vector<vector<int>> g = tests[i].grid;
        int got = shortestPathBinaryMatrix(g);
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
