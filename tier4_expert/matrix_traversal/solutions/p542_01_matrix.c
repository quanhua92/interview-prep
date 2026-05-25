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


#include "ctest.h"
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

typedef struct {
    const char *label;
    const int *input;
    int rows, cols;
    const int *expected;
} MatDistTC;

int main(void)
{
    int in1[] = {0,0,0, 0,1,0, 0,0,0};
    int ex1[] = {0,0,0, 0,1,0, 0,0,0};
    int in2[] = {0,0,0, 0,1,0, 1,1,1};
    int ex2[] = {0,0,0, 0,1,0, 1,2,1};
    int in3[] = {0};
    int ex3[] = {0};
    int in4[] = {1, 0, 1};
    int ex4[] = {1, 0, 1};
    int in5[] = {0,1,1,1};
    int ex5[] = {0,1,2,3};
    int in6[] = {1,1,1, 1,0,1, 1,1,1};
    int ex6[] = {2,1,2, 1,0,1, 2,1,2};
    int in7[] = {1,1,0, 1,1,1, 0,1,1};
    int ex7[] = {2,1,0, 1,2,1, 0,1,2};

    MatDistTC tests[] = {
        {"example 1", in1, 3, 3, ex1},
        {"example 2", in2, 3, 3, ex2},
        {"single zero", in3, 1, 1, ex3},
        {"single column", in4, 3, 1, ex4},
        {"single row", in5, 1, 4, ex5},
        {"cross of ones around center zero", in6, 3, 3, ex6},
        {"corner zeros", in7, 3, 3, ex7},
    };

    int n_tests = (int)(sizeof(tests) / sizeof(tests[0]));
    printf("\n============================================================\n");
    printf("  542. 01 Matrix\n");
    printf("============================================================\n");
    int passed = 0;
    for (int t = 0; t < n_tests; t++) {
        MatDistTC *tc = &tests[t];
        int out_size = 0;
        int *got = updateMatrix(tc->input, tc->rows, tc->cols, &out_size);
        int total = tc->rows * tc->cols;
        int ok = th_arr_eq(got, out_size, tc->expected, total);
        if (ok) {
            passed++;
            printf("  Test %d (%s): PASS\n", t + 1, tc->label);
        } else {
            printf("  Test %d (%s): FAIL\n", t + 1, tc->label);
            printf("    Expected: "); th_print_arr(tc->expected, total);
            printf("\n    Got:      "); th_print_arr(got, out_size);
            printf("\n");
        }
        free(got);
    }
    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
