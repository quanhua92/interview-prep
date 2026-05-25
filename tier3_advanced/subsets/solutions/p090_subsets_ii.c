/*
 * P90: Subsets II (Medium)
 * https://leetcode.com/problems/subsets-ii/
 * Topics: Array, Backtracking, Bit Manipulation
 *
 * Given an integer array nums that may contain duplicates, return all possible subsets (the power set).
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 *
 * Example 1:
 *     Input: nums = [1,2,2]
 *     Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
 *
 * Example 2:
 *     Input: nums = [0]
 *     Output: [[],[0]]
 *
 * Constraints:
 *     - 1 <= nums.length <= 10
 *     - -10 <= nums[i] <= 10
 *
 * Template (python3):
 *     class Solution:
 *         def subsetsWithDup(self, nums: List[int]) -> List[List[int]]:
 *
 * Hint: Sort first, then skip duplicates at the same recursion level during backtracking.
 */


#include "ctest.h"
#include <stdlib.h>

static int **result;
static int *col_sizes;
static int result_count;
static int result_cap;
static int *nums_buf;
static int nums_len;

static void add_result(int *path, int depth) {
    if (result_count >= result_cap) {
        result_cap = result_cap ? result_cap * 2 : 64;
        result = realloc(result, result_cap * sizeof(int *));
        col_sizes = realloc(col_sizes, result_cap * sizeof(int));
    }
    if (depth > 0) {
        result[result_count] = malloc(depth * sizeof(int));
        for (int i = 0; i < depth; i++) result[result_count][i] = path[i];
    } else {
        result[result_count] = NULL;
    }
    col_sizes[result_count] = depth;
    result_count++;
}

static void backtrack(int start, int *path, int depth) {
    add_result(path, depth);
    for (int i = start; i < nums_len; i++) {
        if (i > start && nums_buf[i] == nums_buf[i - 1]) continue;
        path[depth] = nums_buf[i];
        backtrack(i + 1, path, depth + 1);
    }
}

static int cmp_int(const void *a, const void *b) { return *(const int *)a - *(const int *)b; }

static int **subsetsWithDup(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
    result = NULL;
    col_sizes = NULL;
    result_count = 0;
    result_cap = 0;
    nums_buf = malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) nums_buf[i] = nums[i];
    qsort(nums_buf, numsSize, sizeof(int), cmp_int);
    nums_len = numsSize;
    int path[11];
    backtrack(0, path, 0);
    for (int i = 0; i < result_count - 1; i++) {
        for (int j = i + 1; j < result_count; j++) {
            if (col_sizes[i] != col_sizes[j]) continue;
            int swap = 0;
            for (int k = 0; k < col_sizes[i]; k++) {
                if (result[i][k] > result[j][k]) { swap = 1; break; }
                if (result[i][k] < result[j][k]) break;
            }
            if (swap) {
                int *tmp = result[i]; result[i] = result[j]; result[j] = tmp;
                int tc = col_sizes[i]; col_sizes[i] = col_sizes[j]; col_sizes[j] = tc;
            }
        }
    }
    *returnSize = result_count;
    *returnColumnSizes = col_sizes;
    free(nums_buf);
    return result;
}

static void sort_results(int **rows, int *cs, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (cs[i] != cs[j]) continue;
            int eq = 1;
            for (int k = 0; k < cs[i]; k++) {
                if (rows[i][k] != rows[j][k]) { eq = 0; break; }
            }
            if (!eq && cs[i] > 0) {
                int less = 1;
                for (int k = 0; k < cs[i]; k++) {
                    if (rows[i][k] > rows[j][k]) { less = 0; break; }
                    if (rows[i][k] < rows[j][k]) break;
                }
                if (!less) {
                    int *tmp = rows[i]; rows[i] = rows[j]; rows[j] = tmp;
                    int tc = cs[i]; cs[i] = cs[j]; cs[j] = tc;
                }
            }
        }
    }
}

static int check(int **got, int got_rows, int *got_cs, int **exp, int exp_rows, int *exp_cs) {
    if (got_rows != exp_rows) return 0;
    sort_results(got, got_cs, got_rows);
    sort_results(exp, exp_cs, exp_rows);
    for (int i = 0; i < got_rows; i++) {
        if (got_cs[i] != exp_cs[i]) return 0;
        for (int j = 0; j < got_cs[i]; j++) {
            if (got[i][j] != exp[i][j]) return 0;
        }
    }
    return 1;
}

int main(void) {
    (void)th_print_arr;
    (void)th_arr_eq;

    printf("\n============================================================\n");
    printf("  90. Subsets II\n");
    printf("============================================================\n");

    int passed = 0;

    {
        int nums[] = {1,2,2};
        int ret_sz, *ret_cs;
        int **got = subsetsWithDup(nums, 3, &ret_sz, &ret_cs);
        int exp_data[][3] = {{}, {1}, {1,2}, {1,2,2}, {2}, {2,2}};
        int exp_cs_arr[] = {0, 1, 2, 3, 1, 2};
        int *exp[6]; int exp_cs[6];
        for (int i = 0; i < 6; i++) {
            exp[i] = (exp_cs_arr[i] > 0) ? exp_data[i] : NULL;
            exp_cs[i] = exp_cs_arr[i];
        }
        if (check(got, ret_sz, ret_cs, exp, 6, exp_cs)) {
            passed++; printf("  Test 1 (example 1): PASS\n");
        } else {
            printf("  Test 1 (example 1): FAIL\n");
        }
        for (int i = 0; i < ret_sz; i++) free(got[i]);
        free(got); free(ret_cs);
    }
    {
        int nums[] = {0};
        int ret_sz, *ret_cs;
        int **got = subsetsWithDup(nums, 1, &ret_sz, &ret_cs);
        int exp_data[][1] = {{0}};
        int *exp[2]; int exp_cs[2];
        exp[0] = NULL; exp_cs[0] = 0;
        exp[1] = exp_data[0]; exp_cs[1] = 1;
        if (check(got, ret_sz, ret_cs, exp, 2, exp_cs)) {
            passed++; printf("  Test 2 (example 2): PASS\n");
        } else {
            printf("  Test 2 (example 2): FAIL\n");
        }
        for (int i = 0; i < ret_sz; i++) free(got[i]);
        free(got); free(ret_cs);
    }
    {
        int nums[] = {2,2,2};
        int ret_sz, *ret_cs;
        int **got = subsetsWithDup(nums, 3, &ret_sz, &ret_cs);
        int exp_data[][3] = {{2}, {2,2}, {2,2,2}};
        int exp_cs_local[] = {0, 1, 2, 3};
        int *exp[4]; int exp_cs[4];
        exp[0] = NULL; exp_cs[0] = 0;
        for (int i = 1; i < 4; i++) { exp[i] = exp_data[i-1]; exp_cs[i] = exp_cs_local[i]; }
        if (check(got, ret_sz, ret_cs, exp, 4, exp_cs)) {
            passed++; printf("  Test 3 (all duplicates): PASS\n");
        } else {
            printf("  Test 3 (all duplicates): FAIL\n");
        }
        for (int i = 0; i < ret_sz; i++) free(got[i]);
        free(got); free(ret_cs);
    }
    {
        int nums[] = {1,1,2,2};
        int ret_sz, *ret_cs;
        int **got = subsetsWithDup(nums, 4, &ret_sz, &ret_cs);
        int exp_data[][4] = {
            {1}, {1,1}, {1,1,2}, {1,1,2,2}, {1,2}, {1,2,2}, {2}, {2,2},
        };
        int exp_cs_local[] = {0, 1, 2, 3, 4, 2, 3, 1, 2};
        int *exp[9]; int exp_cs[9];
        exp[0] = NULL; exp_cs[0] = 0;
        for (int i = 1; i < 9; i++) { exp[i] = exp_data[i-1]; exp_cs[i] = exp_cs_local[i]; }
        if (check(got, ret_sz, ret_cs, exp, 9, exp_cs)) {
            passed++; printf("  Test 4 (multiple duplicates): PASS\n");
        } else {
            printf("  Test 4 (multiple duplicates): FAIL\n");
        }
        for (int i = 0; i < ret_sz; i++) free(got[i]);
        free(got); free(ret_cs);
    }
    {
        int nums[] = {-1,-1,0};
        int ret_sz, *ret_cs;
        int **got = subsetsWithDup(nums, 3, &ret_sz, &ret_cs);
        int exp_data[][3] = {{-1}, {-1,-1}, {-1,-1,0}, {-1,0}, {0}};
        int exp_cs_local[] = {0, 1, 2, 3, 2, 1};
        int *exp[6]; int exp_cs[6];
        exp[0] = NULL; exp_cs[0] = 0;
        for (int i = 1; i < 6; i++) { exp[i] = exp_data[i-1]; exp_cs[i] = exp_cs_local[i]; }
        if (check(got, ret_sz, ret_cs, exp, 6, exp_cs)) {
            passed++; printf("  Test 5 (negative duplicates): PASS\n");
        } else {
            printf("  Test 5 (negative duplicates): FAIL\n");
        }
        for (int i = 0; i < ret_sz; i++) free(got[i]);
        free(got); free(ret_cs);
    }
    {
        int nums[] = {1,1,1,1};
        int ret_sz, *ret_cs;
        int **got = subsetsWithDup(nums, 4, &ret_sz, &ret_cs);
        int exp_data[][4] = {{1}, {1,1}, {1,1,1}, {1,1,1,1}};
        int exp_cs_local[] = {0, 1, 2, 3, 4};
        int *exp[5]; int exp_cs[5];
        exp[0] = NULL; exp_cs[0] = 0;
        for (int i = 1; i < 5; i++) { exp[i] = exp_data[i-1]; exp_cs[i] = exp_cs_local[i]; }
        if (check(got, ret_sz, ret_cs, exp, 5, exp_cs)) {
            passed++; printf("  Test 6 (all same element): PASS\n");
        } else {
            printf("  Test 6 (all same element): FAIL\n");
        }
        for (int i = 0; i < ret_sz; i++) free(got[i]);
        free(got); free(ret_cs);
    }

    printf("\n  %d/6 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 6 ? 0 : 1;
}
