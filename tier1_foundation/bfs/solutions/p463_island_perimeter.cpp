/*
 * P463: Island Perimeter [PREMIUM] (Easy)
 * https://leetcode.com/problems/island-perimeter/
 * Topics: Array, Depth-First Search, Breadth-First Search, Matrix
 *
 * You are given row x col grid representing a map where grid[i][j] = 1 represents land and grid[i][j] = 0 represents water.
 * Grid cells are connected horizontally/vertically (not diagonally). The grid is completely surrounded by water, and there is exactly one island (i.e., one or more connected land cells).
 * The island doesn't have "lakes", meaning the water inside isn't connected to the water around the island. One cell is a square with side length 1. The grid is rectangular, width and height don't exceed 100. Determine the perimeter of the island.
 * Example 1:
 *     Input: grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
 *     Output: 16
 *     Explanation: The perimeter is the 16 yellow stripes in the image above.
 *
 * Example 2:
 *     Input: grid = [[1]]
 *     Output: 4
 *
 * Example 3:
 *     Input: grid = [[1,0]]
 *     Output: 4
 *
 * Constraints:
 *     - row == grid.length
 *     - col == grid[i].length
 *     - 1 <= row, col <= 100
 *     - grid[i][j] is 0 or 1.
 *     - There is exactly one island in grid.
 *
 * Template (python3):
 *     class Solution:
 *         def islandPerimeter(self, grid: List[List[int]]) -> int:
 */

#include "cpptest.h"
#include <queue>
#include <utility>

using namespace std;

static int islandPerimeter(vector<vector<int>> &grid) {
    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};
    int rows = (int)grid.size();
    int cols = (int)grid[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    int perimeter = 0;
    queue<pair<int, int>> q;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 1) {
                q.push({r, c});
                visited[r][c] = true;
                while (!q.empty()) {
                    auto [cr, cc] = q.front();
                    q.pop();
                    for (int d = 0; d < 4; d++) {
                        int nr = cr + dr[d];
                        int nc = cc + dc[d];
                        if (nr < 0 || nr >= rows || nc < 0 || nc >= cols
                            || grid[nr][nc] == 0) {
                            perimeter++;
                        } else if (!visited[nr][nc]) {
                            visited[nr][nc] = true;
                            q.push({nr, nc});
                        }
                    }
                }
                return perimeter;
            }
        }
    }
    return 0;
}

int main() {
    (void)print_arr;

    struct TC {
        string label;
        vector<vector<int>> grid;
        int expected;
    };

    TC tests[] = {
        {"example 1", {{0,1,0,0},{1,1,1,0},{0,1,0,0},{1,1,0,0}}, 16},
        {"example 2", {{1}}, 4},
        {"example 3", {{1,0}}, 4},
        {"horizontal line of 3", {{1,1,1}}, 8},
        {"vertical line of 3", {{1},{1},{1}}, 8},
        {"2x2 block", {{1,1},{1,1}}, 8},
        {"3x2 block", {{1,1,1},{1,1,1}}, 10},
    };

    int nt = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < nt; i++) {
        int got = islandPerimeter(tests[i].grid);
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
