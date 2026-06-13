/*
 * P200: Number of Islands (Medium)
 * https://leetcode.com/problems/number-of-islands/
 * Topics: Array, Depth-First Search, Breadth-First Search, Union Find, Matrix
 */

#include "io.h"
#include <vector>
#include <string>

static void dfs(std::vector<std::vector<char>>& grid, int r, int c, int rows, int cols) {
    abort();
}

static int solve(std::vector<std::vector<char>>& grid, int rows, int cols) {
    abort();
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
    write_int(solve(grid, rows, cols));
    return 0;
}
