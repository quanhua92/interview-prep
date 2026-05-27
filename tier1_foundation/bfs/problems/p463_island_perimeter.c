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
    abort();
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
