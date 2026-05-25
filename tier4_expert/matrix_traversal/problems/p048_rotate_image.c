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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "ctest.h"
#pragma GCC diagnostic pop
#include <stdbool.h>
#include <string.h>

static void rotate(int n, int matrix[n][n])
{
    abort();
}

typedef struct {
    const char *label;
    int n;
    const int *input;
    const int *expected;
} MatTC;

int main(void)
{
    int in1[] = {1,2,3, 4,5,6, 7,8,9};
    int ex1[] = {7,4,1, 8,5,2, 9,6,3};
    int in2[] = {5,1,9,11, 2,4,8,10, 13,3,6,7, 15,14,12,16};
    int ex2[] = {15,13,2,5, 14,3,4,1, 12,6,8,9, 16,7,10,11};
    int in3[] = {1};
    int ex3[] = {1};
    int in4[] = {1,2, 3,4};
    int ex4[] = {3,1, 4,2};
    int in5[] = {-1,-2,-3, -4,-5,-6, -7,-8,-9};
    int ex5[] = {-7,-4,-1, -8,-5,-2, -9,-6,-3};

    MatTC tests[] = {
        {"example 1", 3, in1, ex1},
        {"example 2", 4, in2, ex2},
        {"single element", 1, in3, ex3},
        {"2x2 matrix", 2, in4, ex4},
        {"negative values", 3, in5, ex5},
    };

    int n_tests = (int)(sizeof(tests) / sizeof(tests[0]));
    printf("\n============================================================\n");
    printf("  48. Rotate Image\n");
    printf("============================================================\n");
    int passed = 0;
    for (int t = 0; t < n_tests; t++) {
        MatTC *tc = &tests[t];
        int n = tc->n;
        int *work = malloc(n * n * sizeof(int));
        memcpy(work, tc->input, n * n * sizeof(int));
        rotate(n, (int (*)[n])work);
        bool ok = memcmp(work, tc->expected, n * n * sizeof(int)) == 0;
        if (ok) {
            passed++;
            printf("  Test %d (%s): PASS\n", t + 1, tc->label);
        } else {
            printf("  Test %d (%s): FAIL\n", t + 1, tc->label);
            printf("    Expected: "); th_print_arr(tc->expected, n * n);
            printf("\n    Got:      "); th_print_arr(work, n * n);
            printf("\n");
        }
        free(work);
    }
    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
