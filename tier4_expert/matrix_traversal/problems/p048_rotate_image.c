/*
 * P48: Rotate Image (Medium)
 * https://leetcode.com/problems/rotate-image/
 * Topics: Array, Math, Matrix
 *
 * You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).
 * You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.
 *
 * Example 1:
 *     Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
 *     Output: [[7,4,1],[8,5,2],[9,6,3]]
 *
 * Example 2:
 *     Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
 *     Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
 *
 * Constraints:
 *     - n == matrix.length == matrix[i].length
 *     - 1 <= n <= 20
 *     - -1000 <= matrix[i][j] <= 1000
 *
 * Template (python3):
 *     class Solution:
 *         def rotate(self, matrix: List[List[int]]) -> None:
 *             \'\'\'
 *             Do not return anything, modify matrix in-place instead.
 *             \'\'\'
 *
 * Hint: Transpose the matrix first, then reverse each row.
 */


#include "io.h"
#include <stdlib.h>

static void rotate(int n, int matrix[n][n])
{
    abort();
}

int main(void)
{
    int n;
    int *size_line = read_ints(&n);
    int rows = size_line[0];
    free(size_line);
    int *matrix_flat = malloc(rows * rows * sizeof(int));
    for (int i = 0; i < rows; i++) {
        int count;
        int *row = read_ints(&count);
        for (int j = 0; j < rows; j++)
            matrix_flat[i * rows + j] = row[j];
        free(row);
    }
    rotate(rows, (int (*)[rows])matrix_flat);
    for (int i = 0; i < rows; i++)
        write_ints(matrix_flat + i * rows, rows);
    free(matrix_flat);
    return 0;
}
