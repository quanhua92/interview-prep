/*
 * P695: Max Area of Island (Medium)
 * https://leetcode.com/problems/max-area-of-island/
 * Topics: Array, Depth-First Search, Breadth-First Search, Union Find, Matrix
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
