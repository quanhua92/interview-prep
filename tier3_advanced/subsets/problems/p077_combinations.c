/*
 * P77: Combinations (Medium)
 * https://leetcode.com/problems/combinations/
 * Topics: Backtracking
 * 
 * Given two integers n and k, return all possible combinations of k numbers chosen from the range [1, n].
 * You may return the answer in any order.
 * 
 * Example 1:
 *     Input: n = 4, k = 2
 *     Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
 *     Explanation: There are 4 choose 2 = 6 total combinations.
 *     Note that combinations are unordered, i.e., [1,2] and [2,1] are considered to be the same combination.
 * 
 * Example 2:
 *     Input: n = 1, k = 1
 *     Output: [[1]]
 *     Explanation: There is 1 choose 1 = 1 total combination.
 * 
 * Constraints:
 *     - 1 <= n <= 20
 *     - 1 <= k <= n
 * 
 * Template (python3):
 *     class Solution:
 *         def combine(self, n: int, k: int) -> List[List[int]]:
 * 
 * Hint: Use backtracking with a start index to generate all k-length combinations from 1..n.
 */
#include "ctest.h"
#include <stdlib.h>

static int **result;
static int *col_sizes;
static int result_count;
static int result_cap;
static int k_val;

static void add_result(int *path) {
    /* TODO: Implement */
    return 0;
}

static void backtrack(int start, int n, int *path, int depth) {
    /* TODO: Implement */
    return 0;
}

static int **combine(int n, int k, int *returnSize, int **returnColumnSizes) {
    /* TODO: Implement */
    return 0;
}

static int check(int **got, int got_rows, int *got_cs, int **exp, int exp_rows, int *exp_cs) {
    /* TODO: Implement */
    return 0;
}

int main(void) {
    (void)th_print_arr;
    (void)th_arr_eq;

    printf("\n============================================================\n");
    printf("  77. Combinations\n");
    printf("============================================================\n");

    int passed = 0;

    {
        int ret_sz, *ret_cs;
        int **got = combine(4, 2, &ret_sz, &ret_cs);
        int exp_data[][2] = {{1,2},{1,3},{1,4},{2,3},{2,4},{3,4}};
        int *exp[6]; int exp_cs[6];
        for (int i = 0; i < 6; i++) { exp[i] = exp_data[i]; exp_cs[i] = 2; }
        if (check(got, ret_sz, ret_cs, exp, 6, exp_cs)) {
            passed++; printf("  Test 1 (example 1): PASS\n");
        } else {
            printf("  Test 1 (example 1): FAIL\n");
        }
        for (int i = 0; i < ret_sz; i++) free(got[i]);
        free(got); free(ret_cs);
    }
    {
        int ret_sz, *ret_cs;
        int **got = combine(1, 1, &ret_sz, &ret_cs);
        int exp_data[][1] = {{1}};
        int *exp[1]; int exp_cs[1];
        exp[0] = exp_data[0]; exp_cs[0] = 1;
        if (check(got, ret_sz, ret_cs, exp, 1, exp_cs)) {
            passed++; printf("  Test 2 (example 2): PASS\n");
        } else {
            printf("  Test 2 (example 2): FAIL\n");
        }
        for (int i = 0; i < ret_sz; i++) free(got[i]);
        free(got); free(ret_cs);
    }
    {
        int ret_sz, *ret_cs;
        int **got = combine(3, 1, &ret_sz, &ret_cs);
        int exp_data[][1] = {{1},{2},{3}};
        int *exp[3]; int exp_cs[3];
        for (int i = 0; i < 3; i++) { exp[i] = exp_data[i]; exp_cs[i] = 1; }
        if (check(got, ret_sz, ret_cs, exp, 3, exp_cs)) {
            passed++; printf("  Test 3 (example 3): PASS\n");
        } else {
            printf("  Test 3 (example 3): FAIL\n");
        }
        for (int i = 0; i < ret_sz; i++) free(got[i]);
        free(got); free(ret_cs);
    }
    {
        int ret_sz, *ret_cs;
        int **got = combine(5, 5, &ret_sz, &ret_cs);
        int exp_data[][5] = {{1,2,3,4,5}};
        int *exp[1]; int exp_cs[1];
        exp[0] = exp_data[0]; exp_cs[0] = 5;
        if (check(got, ret_sz, ret_cs, exp, 1, exp_cs)) {
            passed++; printf("  Test 4 (k equals n): PASS\n");
        } else {
            printf("  Test 4 (k equals n): FAIL\n");
        }
        for (int i = 0; i < ret_sz; i++) free(got[i]);
        free(got); free(ret_cs);
    }
    {
        int ret_sz, *ret_cs;
        int **got = combine(5, 3, &ret_sz, &ret_cs);
        int exp_data[][3] = {
            {1,2,3},{1,2,4},{1,2,5},{1,3,4},{1,3,5},{1,4,5},
            {2,3,4},{2,3,5},{2,4,5},{3,4,5},
        };
        int *exp[10]; int exp_cs[10];
        for (int i = 0; i < 10; i++) { exp[i] = exp_data[i]; exp_cs[i] = 3; }
        if (check(got, ret_sz, ret_cs, exp, 10, exp_cs)) {
            passed++; printf("  Test 5 (mid range): PASS\n");
        } else {
            printf("  Test 5 (mid range): FAIL\n");
        }
        for (int i = 0; i < ret_sz; i++) free(got[i]);
        free(got); free(ret_cs);
    }
    {
        int ret_sz, *ret_cs;
        int **got = combine(2, 2, &ret_sz, &ret_cs);
        int exp_data[][2] = {{1,2}};
        int *exp[1]; int exp_cs[1];
        exp[0] = exp_data[0]; exp_cs[0] = 2;
        if (check(got, ret_sz, ret_cs, exp, 1, exp_cs)) {
            passed++; printf("  Test 6 (smallest k equals n): PASS\n");
        } else {
            printf("  Test 6 (smallest k equals n): FAIL\n");
        }
        for (int i = 0; i < ret_sz; i++) free(got[i]);
        free(got); free(ret_cs);
    }
    {
        int ret_sz, *ret_cs;
        int **got = combine(6, 1, &ret_sz, &ret_cs);
        int exp_data[][1] = {{1},{2},{3},{4},{5},{6}};
        int *exp[6]; int exp_cs[6];
        for (int i = 0; i < 6; i++) { exp[i] = exp_data[i]; exp_cs[i] = 1; }
        if (check(got, ret_sz, ret_cs, exp, 6, exp_cs)) {
            passed++; printf("  Test 7 (k equals 1 larger n): PASS\n");
        } else {
            printf("  Test 7 (k equals 1 larger n): FAIL\n");
        }
        for (int i = 0; i < ret_sz; i++) free(got[i]);
        free(got); free(ret_cs);
    }

    printf("\n  %d/7 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 7 ? 0 : 1;
}
