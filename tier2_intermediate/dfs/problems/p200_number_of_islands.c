/*
 * P200: Number of Islands (Medium)
 * https://leetcode.com/problems/number-of-islands/
 * Topics: Array, Depth-First Search, Breadth-First Search, Union Find, Matrix
 */

#include "io.h"
#include <stdlib.h>
#include <string.h>

static int numIslands(char **grid, int rows, int cols) {
    abort();
}

int main(void) {
    int *meta = read_ints(&(int){0});
    int rows = meta[0], cols = meta[1];
    free(meta);
    if (rows == 0) { write_int(0); return 0; }
    char **grid = malloc(rows * sizeof(char*));
    for (int r = 0; r < rows; r++) {
        char *line = read_line();
        grid[r] = line;
    }
    write_int(numIslands(grid, rows, cols));
    for (int r = 0; r < rows; r++) free(grid[r]);
    free(grid);
    return 0;
}
