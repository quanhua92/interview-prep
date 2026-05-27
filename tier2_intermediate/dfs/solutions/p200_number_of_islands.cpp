/*
 * P200: Number of Islands (Medium)
 * https://leetcode.com/problems/number-of-islands/
 * Topics: Array, Depth-First Search, Breadth-First Search, Union Find, Matrix
 */

#include "io.h"
#include <vector>
#include <string>

static void dfs(std::vector<std::vector<char>>& grid, int r, int c, int rows, int cols) {
    if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] != '1') return;
    grid[r][c] = '0';
    dfs(grid, r + 1, c, rows, cols);
    dfs(grid, r - 1, c, rows, cols);
    dfs(grid, r, c + 1, rows, cols);
    dfs(grid, r, c - 1, rows, cols);
}

int main() {
    auto meta = read_ints();
    int rows = meta[0], cols = meta[1];
    if (rows == 0) { write_int(0); return 0; }
    std::vector<std::vector<char>> grid(rows);
    for (int r = 0; r < rows; r++) {
        std::string line = read_line();
        grid[r] = std::vector<char>(line.begin(), line.end());
    }
    int count = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == '1') {
                count++;
                dfs(grid, r, c, rows, cols);
            }
        }
    }
    write_int(count);
    return 0;
}
