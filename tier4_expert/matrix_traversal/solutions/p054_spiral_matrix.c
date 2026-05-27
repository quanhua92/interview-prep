/*
 * P54: Spiral Matrix (Medium)
 * https://leetcode.com/problems/spiral-matrix/
 * Topics: Array, Matrix, Simulation
 *
 * Given an m x n matrix, return all elements of the matrix in spiral order.
 *
 * Example 1:
 *     Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
 *     Output: [1,2,3,6,9,8,7,4,5]
 *
 * Example 2:
 *     Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
 *     Output: [1,2,3,4,8,12,11,10,9,5,6,7]
 *
 * Constraints:
 *     - m == matrix.length
 *     - n == matrix[i].length
 *     - 1 <= m, n <= 10
 *     - -100 <= matrix[i][j] <= 100
 *
 * Hints:
 *     - Well for some problems, the best way really is to come up with some algorithms for simulation. Basically, you need to simulate what the problem asks us to do.
 *     - We go boundary by boundary and move inwards. That is the essential operation. First row, last column, last row, first column, and then we move inwards by 1 and repeat. That's all. That is all the simulation that we need.
 *     - Think about when you want to switch the progress on one of the indexes. If you progress on i out of [i, j], you'll shift in the same column. Similarly, by changing values for j, you'd be shifting in the same row.
 * Also, keep track of the end of a boundary so that you can move inwards and then keep repeating. It's always best to simulate edge cases like a single column or a single row to see if anything breaks or not.
 *
 * Template (python3):
 *     class Solution:
 *         def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
 *
 * Hint: Use four boundary pointers (top, bottom, left, right) and shrink them as you traverse.
 */


#include "io.h"
#include <stdlib.h>

static int *spiralOrder(const int *flat, int rows, int cols, int *ret_size)
{
    int cap = rows * cols;
    int *result = malloc(cap * sizeof(int));
    *ret_size = 0;
    int top = 0, bottom = rows - 1, left = 0, right = cols - 1;

    while (top <= bottom && left <= right) {
        for (int c = left; c <= right; c++)
            result[(*ret_size)++] = flat[top * cols + c];
        top++;
        for (int r = top; r <= bottom; r++)
            result[(*ret_size)++] = flat[r * cols + right];
        right--;
        if (top <= bottom) {
            for (int c = right; c >= left; c--)
                result[(*ret_size)++] = flat[bottom * cols + c];
            bottom--;
        }
        if (left <= right) {
            for (int r = bottom; r >= top; r--)
                result[(*ret_size)++] = flat[r * cols + left];
            left++;
        }
    }
    return result;
}

int main(void)
{
    int n;
    int *size_line = read_ints(&n);
    int cols = size_line[0];
    free(size_line);
    int rows = cols;
    int total = rows * cols;
    int *flat = malloc(total * sizeof(int));
    for (int i = 0; i < rows; i++) {
        int count;
        int *row = read_ints(&count);
        for (int j = 0; j < cols; j++)
            flat[i * cols + j] = row[j];
        free(row);
    }
    int ret_size = 0;
    int *result = spiralOrder(flat, rows, cols, &ret_size);
    write_ints(result, ret_size);
    free(flat);
    free(result);
    return 0;
}
