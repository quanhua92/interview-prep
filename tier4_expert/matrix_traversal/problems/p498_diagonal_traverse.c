/*
 * P498: Diagonal Traverse (Medium)
 * https://leetcode.com/problems/diagonal-traverse/
 * Topics: Array, Matrix, Simulation
 *
 * Given an m x n matrix mat, return an array of all the elements of the array in a diagonal order.
 *
 * Example 1:
 *     Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
 *     Output: [1,2,4,7,5,3,6,8,9]
 *
 * Example 2:
 *     Input: mat = [[1,2],[3,4]]
 *     Output: [1,2,3,4]
 *
 * Constraints:
 *     - m == mat.length
 *     - n == mat[i].length
 *     - 1 <= m, n <= 10^4
 *     - 1 <= m * n <= 10^4
 *     - -10^5 <= mat[i][j] <= 10^5
 *
 * Template (python3):
 *     class Solution:
 *         def findDiagonalOrder(self, mat: List[List[int]]) -> List[int]:
 *
 * Hint: Group by i+j diagonal index. If d is even, reverse to simulate up-right direction.
 */


#include "io.h"
#include <stdlib.h>

static int *findDiagonalOrder(const int *flat, int rows, int cols, int *ret_size)
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
    int *result = findDiagonalOrder(flat, rows, cols, &ret_size);
    write_ints(result, ret_size);
    free(flat);
    free(result);
    return 0;
}
