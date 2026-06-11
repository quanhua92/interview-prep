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

#include "io.h"
#include <cstdlib>
#include <queue>
#include <utility>

using namespace std;

static int solve(vector<vector<int>> &grid) {
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
                        if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || grid[nr][nc] == 0) {
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

// Alternative Solution: O(1) Space
// Instead of BFS with a visited matrix, count contributions per land cell.
// Each land cell contributes 4 to the perimeter, minus 2 for each shared edge
// with the cell to its right or below (avoids double-counting).
static int solve_o1(vector<vector<int>> &grid) {
    int rows = (int)grid.size();
    int cols = (int)grid[0].size();
    int perimeter = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 0) continue;
            int base_perimeter = 4;
            if (c + 1 < cols && grid[r][c + 1] == 1)
                base_perimeter -= 2;
            if (r + 1 < rows && grid[r + 1][c] == 1)
                base_perimeter -= 2;
            perimeter += base_perimeter;
        }
    }
    return perimeter;
}

int main(void)
{
    (void)read_int();
    vector<vector<int>> grid;
    while (true) {
        vector<int> row = read_ints();
        if (row.empty()) break;
        grid.push_back(row);
    }
    write_int(solve(grid));
    return 0;
}
