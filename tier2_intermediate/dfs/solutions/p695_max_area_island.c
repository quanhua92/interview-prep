/*
 * P695: Max Area of Island (Medium)
 * https://leetcode.com/problems/max-area-of-island/
 * Topics: Array, Depth-First Search, Breadth-First Search, Union Find, Matrix
 */

#include "io.h"
#include <stdlib.h>

static int dfs(int **grid, int r, int c, int rows, int cols) {
    if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] != 1) return 0;
    grid[r][c] = 0;
    return 1 + dfs(grid, r+1, c, rows, cols) + dfs(grid, r-1, c, rows, cols)
             + dfs(grid, r, c+1, rows, cols) + dfs(grid, r, c-1, rows, cols);
}

int main(void) {
    int *meta = read_ints(&(int){0});
    int rows = meta[0], cols = meta[1];
    free(meta);
    if (rows == 0 || cols == 0) { write_int(0); return 0; }
    int **grid = malloc(rows * sizeof(int*));
    for (int r = 0; r < rows; r++) {
        int n;
        grid[r] = read_ints(&n);
    }
    int max_area = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 1) {
                int area = dfs(grid, r, c, rows, cols);
                if (area > max_area) max_area = area;
            }
        }
    }
    write_int(max_area);
    for (int r = 0; r < rows; r++) free(grid[r]);
    free(grid);
    return 0;
}
