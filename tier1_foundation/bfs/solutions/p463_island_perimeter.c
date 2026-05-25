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

#include "ctest.h"

static int islandPerimeter(int **grid, int gridSize, int *gridColSize) {
    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};
    int visited[100][100];
    int perimeter = 0;
    int qr[10000], qc[10000];
    int front = 0, back = 0;

    memset(visited, 0, sizeof(visited));

    for (int r = 0; r < gridSize; r++) {
        for (int c = 0; c < gridColSize[r]; c++) {
            if (grid[r][c] == 1) {
                qr[back] = r;
                qc[back] = c;
                back++;
                visited[r][c] = 1;

                while (front < back) {
                    int cr = qr[front];
                    int cc = qc[front];
                    front++;
                    for (int d = 0; d < 4; d++) {
                        int nr = cr + dr[d];
                        int nc = cc + dc[d];
                        if (nr < 0 || nr >= gridSize || nc < 0 || nc >= gridColSize[0]
                            || grid[nr][nc] == 0) {
                            perimeter++;
                        } else if (!visited[nr][nc]) {
                            visited[nr][nc] = 1;
                            qr[back] = nr;
                            qc[back] = nc;
                            back++;
                        }
                    }
                }
                return perimeter;
            }
        }
    }
    return 0;
}

typedef struct {
    const char *label;
    int *flat;
    int rows, cols;
    int expected;
} TC;

int main(void) {
    (void)th_print_arr;
    (void)th_arr_eq;

    int g1[] = {0,1,0,0, 1,1,1,0, 0,1,0,0, 1,1,0,0};
    int g2[] = {1};
    int g3[] = {1,0};
    int g4[] = {1,1,1};
    int g5[] = {1,1,1};
    int g6[] = {1,1,1,1};
    int g7[] = {1,1,1,1,1,1};

    TC tests[] = {
        {"example 1", g1, 4, 4, 16},
        {"example 2", g2, 1, 1, 4},
        {"example 3", g3, 1, 2, 4},
        {"horizontal line of 3", g4, 1, 3, 8},
        {"vertical line of 3", g5, 3, 1, 8},
        {"2x2 block", g6, 2, 2, 8},
        {"3x2 block", g7, 2, 3, 10},
    };

    int nt = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < nt; i++) {
        int *grid[100];
        int cs[100];
        for (int j = 0; j < tests[i].rows; j++) {
            grid[j] = tests[i].flat + j * tests[i].cols;
            cs[j] = tests[i].cols;
        }
        int got = islandPerimeter(grid, tests[i].rows, cs);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d\n    Got:      %d\n", tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, nt);
    return passed == nt ? 0 : 1;
}
