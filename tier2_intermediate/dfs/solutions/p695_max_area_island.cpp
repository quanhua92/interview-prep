/*
 * P695: Max Area of Island (Medium)
 * https://leetcode.com/problems/max-area-of-island/
 * Topics: Array, Depth-First Search, Breadth-First Search, Union Find, Matrix
 *
 * You are given an m x n binary matrix grid. An island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.
 * The area of an island is the number of cells with a value 1 in the island.
 * Return the maximum area of an island in grid. If there is no island, return 0.
 *
 * Example 1:
 *     Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
 *     Output: 6
 *     Explanation: The answer is not 11, because the island must be connected 4-directionally.
 *
 * Example 2:
 *     Input: grid = [[0,0,0,0,0,0,0,0]]
 *     Output: 0
 *
 * Constraints:
 *     - m == grid.length
 *     - n == grid[i].length
 *     - 1 <= m, n <= 50
 *     - grid[i][j] is either 0 or 1.
 *
 * Template (python3):
 *     class Solution:
 *         def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
 *
 * Hint: Use DFS to explore each island and track the maximum area found.
 */

#include "io.h"
#include <vector>
#include <algorithm>

static int dfs(std::vector<std::vector<int>>& grid, int r, int c, int rows, int cols) {
    if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] != 1) return 0;
    grid[r][c] = 0;
    return 1 + dfs(grid, r+1, c, rows, cols) + dfs(grid, r-1, c, rows, cols)
             + dfs(grid, r, c+1, rows, cols) + dfs(grid, r, c-1, rows, cols);
}

int main() {
    auto meta = read_ints();
    int rows = meta[0], cols = meta[1];
    if (rows == 0 || cols == 0) { write_int(0); return 0; }
    std::vector<std::vector<int>> grid(rows);
    for (int r = 0; r < rows; r++) {
        grid[r] = read_ints();
    }
    int max_area = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 1) {
                max_area = std::max(max_area, dfs(grid, r, c, rows, cols));
            }
        }
    }
    write_int(max_area);
    return 0;
}
