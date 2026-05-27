/*
 * P200: Number of Islands (Medium)
 * https://leetcode.com/problems/number-of-islands/
 * Topics: Array, Depth-First Search, Breadth-First Search, Union Find, Matrix
 */

#include "io.h"
#include <stdlib.h>
#include <string.h>

static int numIslands(char **grid, int rows, int cols) {
    if (rows == 0) return 0;
    int count = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == '1') {
                count++;
                int sp = 0;
                int *stk = malloc(rows * cols * 2 * sizeof(int));
                stk[sp++] = r; stk[sp++] = c;
                grid[r][c] = '0';
                while (sp > 0) {
                    int cc = stk[--sp], rr = stk[--sp];
                    int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
                    for (int d = 0; d < 4; d++) {
                        int nr = rr + dr[d], nc = cc + dc[d];
                        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == '1') {
                            grid[nr][nc] = '0';
                            stk[sp++] = nr; stk[sp++] = nc;
                        }
                    }
                }
                free(stk);
            }
        }
    }
    return count;
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
