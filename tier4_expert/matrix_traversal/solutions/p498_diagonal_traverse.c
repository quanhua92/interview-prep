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
 *     - 1 <= m, n <= 104
 *     - 1 <= m * n <= 104
 *     - -105 <= mat[i][j] <= 105
 *
 * Template (python3):
 *     class Solution:
 *         def findDiagonalOrder(self, mat: List[List[int]]) -> List[int]:
 *
 * Hint: Group by i+j diagonal index. If d is even, reverse to simulate up-right direction.
 */


#include "ctest.h"
#include <stdlib.h>

static int *findDiagonalOrder(const int *flat, int rows, int cols, int *ret_size)
{
    *ret_size = rows * cols;
    int *result = malloc(*ret_size * sizeof(int));
    if (rows == 0 || cols == 0) return result;

    int idx = 0;
    for (int d = 0; d < rows + cols - 1; d++) {
        if (d % 2 == 0) {
            int ir = d < rows ? d : rows - 1;
            int ic = d < rows ? 0 : d - rows + 1;
            while (ir >= 0 && ic < cols) {
                result[idx++] = flat[ir * cols + ic];
                ir--; ic++;
            }
        } else {
            int ir = d < cols ? 0 : d - cols + 1;
            int ic = d < cols ? d : cols - 1;
            while (ir < rows && ic >= 0) {
                result[idx++] = flat[ir * cols + ic];
                ir++; ic--;
            }
        }
    }
    return result;
}

typedef struct {
    const char *label;
    const int *input;
    int rows, cols;
    const int *expected;
    int expected_n;
} DiagTC;

int main(void)
{
    int in1[] = {1,2,3, 4,5,6, 7,8,9};
    int ex1[] = {1,2,4,7,5,3,6,8,9};
    int in2[] = {1,2, 3,4, 5,6};
    int ex2[] = {1,2,3,5,4,6};
    int in3[] = {1};
    int ex3[] = {1};
    int in4[] = {1,2,3,4};
    int ex4[] = {1,2,3,4};
    int in5[] = {1, 2, 3, 4};
    int ex5[] = {1,2,3,4};
    int in6[] = {1,2,3,4, 5,6,7,8};
    int ex6[] = {1,2,5,6,3,4,7,8};
    int in7[] = {-1,-2, 3,4};
    int ex7[] = {-1,-2,3,4};

    DiagTC tests[] = {
        {"example 1", in1, 3, 3, ex1, 9},
        {"example 2", in2, 3, 2, ex2, 6},
        {"single element", in3, 1, 1, ex3, 1},
        {"single row", in4, 1, 4, ex4, 4},
        {"single column", in5, 4, 1, ex5, 4},
        {"2x4 rectangular", in6, 2, 4, ex6, 8},
        {"negative values 2x2", in7, 2, 2, ex7, 4},
    };

    int n_tests = (int)(sizeof(tests) / sizeof(tests[0]));
    printf("\n============================================================\n");
    printf("  498. Diagonal Traverse\n");
    printf("============================================================\n");
    int passed = 0;
    for (int t = 0; t < n_tests; t++) {
        DiagTC *tc = &tests[t];
        int ret_size = 0;
        int *got = findDiagonalOrder(tc->input, tc->rows, tc->cols, &ret_size);
        int ok = th_arr_eq(got, ret_size, tc->expected, tc->expected_n);
        if (ok) {
            passed++;
            printf("  Test %d (%s): PASS\n", t + 1, tc->label);
        } else {
            printf("  Test %d (%s): FAIL\n", t + 1, tc->label);
            printf("    Expected: "); th_print_arr(tc->expected, tc->expected_n);
            printf("\n    Got:      "); th_print_arr(got, ret_size);
            printf("\n");
        }
        free(got);
    }
    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
