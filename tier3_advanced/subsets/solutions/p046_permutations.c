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
 * Hint: Use backtracking with swapping to generate all permutations in-place.
 */

#include "io.h"
#include <stdlib.h>
#include <string.h>

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

int main(void)
{
    int n;
    int *nums = read_ints(&n);
    result = NULL;
    col_sizes = NULL;
    result_count = 0;
    result_cap = 0;
    nums_buf = nums;
    nums_len = n;
    backtrack(0);
    qsort(result, result_count, sizeof(int *), cmp_rows);
    for (int i = 0; i < result_count; i++) {
        write_ints(result[i], col_sizes[i]);
    }
    for (int i = 0; i < result_count; i++) free(result[i]);
    free(result);
    free(col_sizes);
    free(nums);
    return 0;
}
