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
    abort();
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
    int ret_size = 0;
    int *result = spiralOrder(flat, rows, cols, &ret_size);
    write_ints(result, ret_size);
    free(flat);
    free(result);
    return 0;
}
