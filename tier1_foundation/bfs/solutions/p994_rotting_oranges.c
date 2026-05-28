/*
 * P994: Rotting Oranges (Medium)
 * https://leetcode.com/problems/rotting-oranges/
 * Topics: Array, Breadth-First Search, Matrix
 *
 * You are given an m x n grid where each cell can have one of three values:
 * Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.
 * Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.
 *
 * Example 1:
 *     Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
 *     Output: 4
 *
 * Example 2:
 *     Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
 *     Output: -1
 *     Explanation: The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.
 *
 * Example 3:
 *     Input: grid = [[0,2]]
 *     Output: 0
 *     Explanation: Since there are already no fresh oranges at minute 0, the answer is just 0.
 *
 * Constraints:
 *     - m == grid.length
 *     - n == grid[i].length
 *     - 1 <= m, n <= 10
 *     - grid[i][j] is 0, 1, or 2.
 *
 * Template (python3):
 *     class Solution:
 *         def orangesRotting(self, grid: List[List[int]]) -> int:
 *
 * Hint: Use BFS starting from all rotten oranges simultaneously.
 */

#include "io.h"
#include <stdlib.h>

int solve(int **grid, int rows, int cols) {
    int *queue = malloc(200 * sizeof(int));
    int front = 0, back = 0;
    int fresh = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 2) { queue[back++] = r; queue[back++] = c; }
            else if (grid[r][c] == 1) fresh++;
        }
    }
    if (fresh == 0) { free(queue); return 0; }
    int minutes = 0;
    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};
    while (front < back) {
        int level_items = (back - front) / 2;
        for (int i = 0; i < level_items; i++) {
            int r = queue[front++]; int c = queue[front++];
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d]; int nc = c + dc[d];
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == 1) {
                    grid[nr][nc] = 2;
                    fresh--;
                    queue[back++] = nr; queue[back++] = nc;
                }
            }
        }
        if (front < back) minutes++;
    }
    free(queue);
    return fresh == 0 ? minutes : -1;
}

int main(void)
{
    int n;
    int *size_line = read_ints(&n);
    int cols = size_line[0];
    free(size_line);
    int **grid = (int **)malloc(sizeof(int *) * 20);
    int rows = 0;
    while (1) {
        int row_n;
        grid[rows] = read_ints(&row_n);
        if (row_n == 0) { free(grid[rows]); break; }
        rows++;
    }
    int result = solve(grid, rows, cols);
    write_int(result);
    for (int i = 0; i < rows; i++) free(grid[i]);
    free(grid);
    return 0;
}
