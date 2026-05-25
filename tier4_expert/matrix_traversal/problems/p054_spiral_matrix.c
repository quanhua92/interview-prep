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
#include "ctest.h"
#include <stdlib.h>

static int *spiralOrder(const int *flat, int rows, int cols, int *ret_size)
{
    /* TODO: Implement */
    return 0;
}

typedef struct {
    const char *label;
    const int *input;
    int rows, cols;
    const int *expected;
    int expected_n;
} SpirTC;

int main(void)
{
    int in1[] = {1,2,3, 4,5,6, 7,8,9};
    int ex1[] = {1,2,3,6,9,8,7,4,5};
    int in2[] = {1,2,3,4, 5,6,7,8, 9,10,11,12};
    int ex2[] = {1,2,3,4,8,12,11,10,9,5,6,7};
    int in3[] = {7};
    int ex3[] = {7};
    int in4[] = {1,2,3,4};
    int ex4[] = {1,2,3,4};
    int in5[] = {1, 2, 3, 4};
    int ex5[] = {1,2,3,4};
    int in6[] = {1,2, 3,4};
    int ex6[] = {1,2,4,3};
    int in7[] = {1,2,3,4,5, 6,7,8,9,10};
    int ex7[] = {1,2,3,4,5,10,9,8,7,6};

    SpirTC tests[] = {
        {"example 1", in1, 3, 3, ex1, 9},
        {"example 2", in2, 3, 4, ex2, 12},
        {"single element", in3, 1, 1, ex3, 1},
        {"single row", in4, 1, 4, ex4, 4},
        {"single column", in5, 4, 1, ex5, 4},
        {"2x2 matrix", in6, 2, 2, ex6, 4},
        {"2 rows many columns", in7, 2, 5, ex7, 10},
    };

    int n_tests = (int)(sizeof(tests) / sizeof(tests[0]));
    printf("\n============================================================\n");
    printf("  54. Spiral Matrix\n");
    printf("============================================================\n");
    int passed = 0;
    for (int t = 0; t < n_tests; t++) {
        SpirTC *tc = &tests[t];
        int ret_size = 0;
        int *got = spiralOrder(tc->input, tc->rows, tc->cols, &ret_size);
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
