/*
 * P542: 01 Matrix [PREMIUM] (Medium)
 * https://leetcode.com/problems/01-matrix/
 * Topics: Array, Dynamic Programming, Breadth-First Search, Matrix
 *
 * Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.
 * The distance between two cells sharing a common edge is 1.
 * Example 2:
 * Note: This question is the same as 1765: https://leetcode.com/problems/map-of-highest-peak/
 * Example 1:
 *     Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
 *     Output: [[0,0,0],[0,1,0],[0,0,0]]
 *
 * Example 2:
 *     Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
 *     Output: [[0,0,0],[0,1,0],[1,2,1]]
 *
 * Constraints:
 *     - m == mat.length
 *     - n == mat[i].length
 *     - 1 <= m, n <= 104
 *     - 1 <= m * n <= 104
 *     - mat[i][j] is either 0 or 1.
 *     - There is at least one 0 in mat.
 *
 * Template (python3):
 *     class Solution:
 *         def updateMatrix(self, mat: List[List[int]]) -> List[List[int]]:
 */


#include "io.h"
#include <stdlib.h>

static int *updateMatrix(const int *flat, int rows, int cols, int *out_size)
{
    int total = rows * cols;
    *out_size = total;
    int *dist = malloc(total * sizeof(int));
    int *queue = malloc(total * 2 * sizeof(int));
    int front = 0, back = 0;

    for (int i = 0; i < total; i++) {
        if (flat[i] == 0) {
            dist[i] = 0;
            queue[back++] = i / cols;
            queue[back++] = i % cols;
        } else {
            dist[i] = -1;
        }
    }

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (front < back) {
        int r = queue[front++];
        int c = queue[front++];
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && dist[nr * cols + nc] == -1) {
                dist[nr * cols + nc] = dist[r * cols + c] + 1;
                queue[back++] = nr;
                queue[back++] = nc;
            }
        }
    }

    free(queue);
    return dist;
}

int main(void)
{
    int n;
    int *size_line = read_ints(&n);
    int cols = size_line[0];
    free(size_line);
    int *flat = malloc(10000 * sizeof(int));
    int rows = 0;
    while (1) {
        int count;
        int *row = read_ints(&count);
        if (count == 0) { free(row); break; }
        for (int j = 0; j < count; j++)
            flat[rows * cols + j] = row[j];
        free(row);
        rows++;
    }
    int out_size = 0;
    int *result = updateMatrix(flat, rows, cols, &out_size);
    for (int i = 0; i < rows; i++)
        write_ints(result + i * cols, cols);
    free(flat);
    free(result);
    return 0;
}
