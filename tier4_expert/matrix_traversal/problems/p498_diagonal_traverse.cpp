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
#include "cpptest.h"
#include <algorithm>

static std::vector<int> findDiagonalOrder(const std::vector<std::vector<int>> &mat)
{
    /* TODO: Implement */
    return 0;
}

typedef struct {
    const char *label;
    std::vector<std::vector<int>> input;
    std::vector<int> expected;
} DiagTC;

int main(void)
{
    DiagTC tests[] = {
        {"example 1", {{1,2,3},{4,5,6},{7,8,9}}, {1,2,4,7,5,3,6,8,9}},
        {"example 2", {{1,2},{3,4},{5,6}}, {1,2,3,5,4,6}},
        {"single element", {{1}}, {1}},
        {"single row", {{1,2,3,4}}, {1,2,3,4}},
        {"single column", {{1},{2},{3},{4}}, {1,2,3,4}},
        {"2x4 rectangular", {{1,2,3,4},{5,6,7,8}}, {1,2,5,6,3,4,7,8}},
        {"negative values 2x2", {{-1,-2},{3,4}}, {-1,-2,3,4}},
    };

    int n_tests = (int)(sizeof(tests) / sizeof(tests[0]));
    printf("\n============================================================\n");
    printf("  498. Diagonal Traverse\n");
    printf("============================================================\n");
    int passed = 0;
    for (int t = 0; t < n_tests; t++) {
        DiagTC &tc = tests[t];
        std::vector<int> got = findDiagonalOrder(tc.input);
        if (got == tc.expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", t + 1, tc.label);
        } else {
            printf("  Test %d (%s): FAIL\n", t + 1, tc.label);
            printf("    Expected: "); print_arr(tc.expected); printf("\n");
            printf("    Got:      "); print_arr(got); printf("\n");
        }
    }
    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
