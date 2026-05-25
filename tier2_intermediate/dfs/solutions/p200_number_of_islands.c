/*
 * P200: Number of Islands (Medium)
 * https://leetcode.com/problems/number-of-islands/
 * Topics: Array, Depth-First Search, Breadth-First Search, Union Find, Matrix
 *
 * Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.
 * An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.
 *
 * Example 1:
 *     Input: grid = [
 *       ["1","1","1","1","0"],
 *       ["1","1","0","1","0"],
 *       ["1","1","0","0","0"],
 *       ["0","0","0","0","0"]
 *     ]
 *     Output: 1
 *
 * Example 2:
 *     Input: grid = [
 *       ["1","1","0","0","0"],
 *       ["1","1","0","0","0"],
 *       ["0","0","1","0","0"],
 *       ["0","0","0","1","1"]
 *     ]
 *     Output: 3
 *
 * Constraints:
 *     - m == grid.length
 *     - n == grid[i].length
 *     - 1 <= m, n <= 300
 *     - grid[i][j] is '0' or '1'.
 *
 * Template (python3):
 *     class Solution:
 *         def numIslands(self, grid: List[List[str]]) -> int:
 *
 * Hint: Use DFS to mark visited land cells, counting each new island.
 */


#include "ctest.h"

static int numIslands(const char **grid, int gridSize, const int *gridColSize) {
    if (gridSize == 0) return 0;
    int max_cells = 0;
    for (int i = 0; i < gridSize; i++) max_cells += gridColSize[i];
    char *visited = calloc(max_cells, 1);
    int *stk = malloc(max_cells * sizeof(int));
    int count = 0;
    for (int r = 0; r < gridSize; r++) {
        for (int c = 0; c < gridColSize[r]; c++) {
            int idx = r * gridColSize[0] + c;
            if (grid[r][c] == '1' && !visited[idx]) {
                count++;
                int sp = 0;
                visited[idx] = 1;
                stk[sp++] = r; stk[sp++] = c;
                while (sp > 0) {
                    int cc = stk[--sp], rr = stk[--sp];
                    int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
                    for (int d = 0; d < 4; d++) {
                        int nr = rr + dr[d], nc = cc + dc[d];
                        if (nr >= 0 && nr < gridSize && nc >= 0 && nc < gridColSize[nr]) {
                            int ni = nr * gridColSize[0] + nc;
                            if (grid[nr][nc] == '1' && !visited[ni]) {
                                visited[ni] = 1;
                                stk[sp++] = nr; stk[sp++] = nc;
                            }
                        }
                    }
                }
            }
        }
    }
    free(visited);
    free(stk);
    return count;
}

int main(void) {
    (void)th_print_arr;
    (void)th_arr_eq;

    printf("\n============================================================\n");
    printf("  200. Number of Islands\n");
    printf("============================================================\n");

    int passed = 0;

    {
        const char *g1[] = {"11110","11010","11000","00000"};
        int cs[] = {5,5,5,5};
        int got = numIslands(g1, 4, cs);
        if (got == 1) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n    Expected: 1\n    Got:      %d\n", got); }
    }
    {
        const char *g2[] = {"11000","11000","00100","00011"};
        int cs[] = {5,5,5,5};
        int got = numIslands(g2, 4, cs);
        if (got == 3) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n    Expected: 3\n    Got:      %d\n", got); }
    }
    {
        int got = numIslands(NULL, 0, NULL);
        if (got == 0) { passed++; printf("  Test 3 (empty grid): PASS\n"); }
        else { printf("  Test 3 (empty grid): FAIL\n    Expected: 0\n    Got:      %d\n", got); }
    }
    {
        const char *g4[] = {"0"};
        int cs[] = {1};
        int got = numIslands(g4, 1, cs);
        if (got == 0) { passed++; printf("  Test 4 (single cell water): PASS\n"); }
        else { printf("  Test 4 (single cell water): FAIL\n    Expected: 0\n    Got:      %d\n", got); }
    }
    {
        const char *g5[] = {"1"};
        int cs[] = {1};
        int got = numIslands(g5, 1, cs);
        if (got == 1) { passed++; printf("  Test 5 (single cell land): PASS\n"); }
        else { printf("  Test 5 (single cell land): FAIL\n    Expected: 1\n    Got:      %d\n", got); }
    }
    {
        const char *g6[] = {"10101"};
        int cs[] = {5};
        int got = numIslands(g6, 1, cs);
        if (got == 3) { passed++; printf("  Test 6 (single row): PASS\n"); }
        else { printf("  Test 6 (single row): FAIL\n    Expected: 3\n    Got:      %d\n", got); }
    }
    {
        const char *g7[] = {"1","0","1","0","1"};
        int cs[] = {1,1,1,1,1};
        int got = numIslands(g7, 5, cs);
        if (got == 3) { passed++; printf("  Test 7 (single column): PASS\n"); }
        else { printf("  Test 7 (single column): FAIL\n    Expected: 3\n    Got:      %d\n", got); }
    }
    {
        const char *g8[] = {"111","111","111"};
        int cs[] = {3,3,3};
        int got = numIslands(g8, 3, cs);
        if (got == 1) { passed++; printf("  Test 8 (all land 3x3): PASS\n"); }
        else { printf("  Test 8 (all land 3x3): FAIL\n    Expected: 1\n    Got:      %d\n", got); }
    }

    printf("\n  %d/8 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 8 ? 0 : 1;
}
