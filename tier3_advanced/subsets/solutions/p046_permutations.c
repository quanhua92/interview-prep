/*
 * P46: Permutations (Medium)
 * https://leetcode.com/problems/permutations/
 * Topics: Array, Backtracking
 *
 * Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.
 *
 * Example 1:
 *     Input: nums = [1,2,3]
 *     Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 *
 * Example 2:
 *     Input: nums = [0,1]
 *     Output: [[0,1],[1,0]]
 *
 * Example 3:
 *     Input: nums = [1]
 *     Output: [[1]]
 *
 * Constraints:
 *     - 1 <= nums.length <= 6
 *     - -10 <= nums[i] <= 10
 *     - All the integers of nums are unique.
 *
 * Template (python3):
 *     class Solution:
 *         def permute(self, nums: List[int]) -> List[List[int]]:
 *
 * Hint: Use backtracking with swapping to generate all permutations in-place.
 */


#include "ctest.h"
#include <stdlib.h>

static int **result;
static int *col_sizes;
static int result_count;
static int result_cap;
static int *nums_buf;
static int nums_len;

static void add_result(void) {
    if (result_count >= result_cap) {
        result_cap = result_cap ? result_cap * 2 : 16;
        result = realloc(result, result_cap * sizeof(int *));
        col_sizes = realloc(col_sizes, result_cap * sizeof(int));
    }
    result[result_count] = malloc(nums_len * sizeof(int));
    for (int i = 0; i < nums_len; i++) result[result_count][i] = nums_buf[i];
    col_sizes[result_count] = nums_len;
    result_count++;
}

static void backtrack(int first) {
    if (first == nums_len) {
        add_result();
        return;
    }
    for (int i = first; i < nums_len; i++) {
        int tmp = nums_buf[first];
        nums_buf[first] = nums_buf[i];
        nums_buf[i] = tmp;
        backtrack(first + 1);
        tmp = nums_buf[first];
        nums_buf[first] = nums_buf[i];
        nums_buf[i] = tmp;
    }
}

static int cmp_rows(const void *a, const void *b) {
    int *ra = *(int **)a, *rb = *(int **)b;
    for (int i = 0; i < nums_len; i++) {
        if (ra[i] != rb[i]) return ra[i] - rb[i];
    }
    return 0;
}

static int **permute(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
    result = NULL;
    col_sizes = NULL;
    result_count = 0;
    result_cap = 0;
    nums_buf = nums;
    nums_len = numsSize;
    backtrack(0);
    qsort(result, result_count, sizeof(int *), cmp_rows);
    *returnSize = result_count;
    *returnColumnSizes = col_sizes;
    return result;
}

static int perm_cmp(const void *a, const void *b) {
    const int *ra = *(const int *const *)a, *rb = *(const int *const *)b;
    for (int i = 0; i < nums_len; i++) {
        if (ra[i] != rb[i]) return ra[i] - rb[i];
    }
    return 0;
}

static int check(int **got, int got_rows, int *got_cs, int **exp, int exp_rows, int *exp_cs, int n) {
    if (got_rows != exp_rows) return 0;
    nums_len = n;
    qsort(got, got_rows, sizeof(int *), perm_cmp);
    qsort(exp, exp_rows, sizeof(int *), perm_cmp);
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
    printf("  46. Permutations\n");
    printf("============================================================\n");

    int passed = 0;

    {
        int nums[] = {1,2,3};
        int exp_data[][3] = {{1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,1,2},{3,2,1}};
        int *exp[6]; int exp_cs[6];
        for (int i = 0; i < 6; i++) { exp[i] = exp_data[i]; exp_cs[i] = 3; }
        int ret_sz, *ret_cs;
        int **got = permute(nums, 3, &ret_sz, &ret_cs);
        if (check(got, ret_sz, ret_cs, exp, 6, exp_cs, 3)) {
            passed++; printf("  Test 1 (example 1): PASS\n");
        } else {
            printf("  Test 1 (example 1): FAIL\n");
        }
        for (int i = 0; i < ret_sz; i++) free(got[i]);
        free(got); free(ret_cs);
    }
    {
        int nums[] = {0,1};
        int exp_data[][2] = {{0,1},{1,0}};
        int *exp[2]; int exp_cs[2];
        for (int i = 0; i < 2; i++) { exp[i] = exp_data[i]; exp_cs[i] = 2; }
        int ret_sz, *ret_cs;
        int **got = permute(nums, 2, &ret_sz, &ret_cs);
        if (check(got, ret_sz, ret_cs, exp, 2, exp_cs, 2)) {
            passed++; printf("  Test 2 (example 2): PASS\n");
        } else {
            printf("  Test 2 (example 2): FAIL\n");
        }
        for (int i = 0; i < ret_sz; i++) free(got[i]);
        free(got); free(ret_cs);
    }
    {
        int nums[] = {1};
        int exp_data[][1] = {{1}};
        int *exp[1]; int exp_cs[1];
        exp[0] = exp_data[0]; exp_cs[0] = 1;
        int ret_sz, *ret_cs;
        int **got = permute(nums, 1, &ret_sz, &ret_cs);
        if (check(got, ret_sz, ret_cs, exp, 1, exp_cs, 1)) {
            passed++; printf("  Test 3 (single element): PASS\n");
        } else {
            printf("  Test 3 (single element): FAIL\n");
        }
        for (int i = 0; i < ret_sz; i++) free(got[i]);
        free(got); free(ret_cs);
    }
    {
        int nums[] = {-1,0,1};
        int exp_data[][3] = {{-1,0,1},{-1,1,0},{0,-1,1},{0,1,-1},{1,-1,0},{1,0,-1}};
        int *exp[6]; int exp_cs[6];
        for (int i = 0; i < 6; i++) { exp[i] = exp_data[i]; exp_cs[i] = 3; }
        int ret_sz, *ret_cs;
        int **got = permute(nums, 3, &ret_sz, &ret_cs);
        if (check(got, ret_sz, ret_cs, exp, 6, exp_cs, 3)) {
            passed++; printf("  Test 4 (negative and zero mix): PASS\n");
        } else {
            printf("  Test 4 (negative and zero mix): FAIL\n");
        }
        for (int i = 0; i < ret_sz; i++) free(got[i]);
        free(got); free(ret_cs);
    }
    {
        int nums[] = {-3,-1};
        int exp_data[][2] = {{-3,-1},{-1,-3}};
        int *exp[2]; int exp_cs[2];
        for (int i = 0; i < 2; i++) { exp[i] = exp_data[i]; exp_cs[i] = 2; }
        int ret_sz, *ret_cs;
        int **got = permute(nums, 2, &ret_sz, &ret_cs);
        if (check(got, ret_sz, ret_cs, exp, 2, exp_cs, 2)) {
            passed++; printf("  Test 5 (two negative elements): PASS\n");
        } else {
            printf("  Test 5 (two negative elements): FAIL\n");
        }
        for (int i = 0; i < ret_sz; i++) free(got[i]);
        free(got); free(ret_cs);
    }
    {
        int nums[] = {1,2,3,4};
        int exp_data[][4] = {
            {1,2,3,4},{1,2,4,3},{1,3,2,4},{1,3,4,2},{1,4,2,3},{1,4,3,2},
            {2,1,3,4},{2,1,4,3},{2,3,1,4},{2,3,4,1},{2,4,1,3},{2,4,3,1},
            {3,1,2,4},{3,1,4,2},{3,2,1,4},{3,2,4,1},{3,4,1,2},{3,4,2,1},
            {4,1,2,3},{4,1,3,2},{4,2,1,3},{4,2,3,1},{4,3,1,2},{4,3,2,1},
        };
        int *exp[24]; int exp_cs[24];
        for (int i = 0; i < 24; i++) { exp[i] = exp_data[i]; exp_cs[i] = 4; }
        int ret_sz, *ret_cs;
        int **got = permute(nums, 4, &ret_sz, &ret_cs);
        if (check(got, ret_sz, ret_cs, exp, 24, exp_cs, 4)) {
            passed++; printf("  Test 6 (four elements): PASS\n");
        } else {
            printf("  Test 6 (four elements): FAIL\n");
        }
        for (int i = 0; i < ret_sz; i++) free(got[i]);
        free(got); free(ret_cs);
    }
    {
        int nums[] = {-5};
        int exp_data[][1] = {{-5}};
        int *exp[1]; int exp_cs[1];
        exp[0] = exp_data[0]; exp_cs[0] = 1;
        int ret_sz, *ret_cs;
        int **got = permute(nums, 1, &ret_sz, &ret_cs);
        if (check(got, ret_sz, ret_cs, exp, 1, exp_cs, 1)) {
            passed++; printf("  Test 7 (single negative element): PASS\n");
        } else {
            printf("  Test 7 (single negative element): FAIL\n");
        }
        for (int i = 0; i < ret_sz; i++) free(got[i]);
        free(got); free(ret_cs);
    }

    printf("\n  %d/7 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 7 ? 0 : 1;
}
