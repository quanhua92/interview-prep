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
#include <stdlib.h>

int solve(int **grid, int gridSize, int *gridColSize) {
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
                qr[back] = r; qc[back] = c; back++;
                visited[r][c] = 1;
                while (front < back) {
                    int cr = qr[front]; int cc = qc[front]; front++;
                    for (int d = 0; d < 4; d++) {
                        int nr = cr + dr[d]; int nc = cc + dc[d];
                        if (nr < 0 || nr >= gridSize || nc < 0 || nc >= gridColSize[0] || grid[nr][nc] == 0) {
                            perimeter++;
                        } else if (!visited[nr][nc]) {
                            visited[nr][nc] = 1;
                            qr[back] = nr; qc[back] = nc; back++;
                        }
                    }
                }
                return perimeter;
            }
        }
    }
    return 0;
}

int main(void)
{
    int n;
    int *size_line = read_ints(&n);
    int rows = size_line[0];
    free(size_line);
    int **grid = (int **)malloc(sizeof(int *) * rows);
    int cs[100];
    for (int i = 0; i < rows; i++) {
        int row_n;
        grid[i] = read_ints(&row_n);
        cs[i] = row_n;
    }
    int result = solve(grid, rows, cs);
    write_int(result);
    for (int i = 0; i < rows; i++) free(grid[i]);
    free(grid);
    return 0;
}
