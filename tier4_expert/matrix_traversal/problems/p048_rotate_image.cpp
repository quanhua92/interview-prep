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
#include "cpptest.h"
#pragma GCC diagnostic pop
#include <algorithm>

static void rotate(std::vector<std::vector<int>> &matrix)
{
    abort();
}

typedef struct {
    const char *label;
    std::vector<std::vector<int>> input;
    std::vector<std::vector<int>> expected;
} MatTC;

int main(void)
{
    MatTC tests[] = {
        {"example 1", {{1,2,3},{4,5,6},{7,8,9}}, {{7,4,1},{8,5,2},{9,6,3}}},
        {"example 2", {{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}}, {{15,13,2,5},{14,3,4,1},{12,6,8,9},{16,7,10,11}}},
        {"single element", {{1}}, {{1}}},
        {"2x2 matrix", {{1,2},{3,4}}, {{3,1},{4,2}}},
        {"negative values", {{-1,-2,-3},{-4,-5,-6},{-7,-8,-9}}, {{-7,-4,-1},{-8,-5,-2},{-9,-6,-3}}},
    };

    int n_tests = (int)(sizeof(tests) / sizeof(tests[0]));
    printf("\n============================================================\n");
    printf("  48. Rotate Image\n");
    printf("============================================================\n");
    int passed = 0;
    for (int t = 0; t < n_tests; t++) {
        MatTC &tc = tests[t];
        rotate(tc.input);
        bool ok = tc.input == tc.expected;
        if (ok) {
            passed++;
            printf("  Test %d (%s): PASS\n", t + 1, tc.label);
        } else {
            printf("  Test %d (%s): FAIL\n", t + 1, tc.label);
        }
    }
    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
