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
 * Hint: Sort first, then skip duplicates at the same recursion level during backtracking.
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

static void add_result(int *path, int depth) {
    abort();
}

static void backtrack(int start, int *path, int depth) {
    abort();
}

static int cmp_int(const void *a, const void *b) {
    abort();
}

static void sort_results(int **rows, int *cs, int n) {
    abort();
}

int main(void)
{
    int n;
    int *nums = read_ints(&n);
    nums_buf = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) nums_buf[i] = nums[i];
    qsort(nums_buf, n, sizeof(int), cmp_int);
    nums_len = n;
    result = NULL;
    col_sizes = NULL;
    result_count = 0;
    result_cap = 0;
    int path[11];
    backtrack(0, path, 0);
    sort_results(result, col_sizes, result_count);
    for (int i = 0; i < result_count; i++) {
        if (col_sizes[i] > 0) {
            write_ints(result[i], col_sizes[i]);
        } else {
            write_ints(NULL, 0);
        }
    }
    for (int i = 0; i < result_count; i++) {
        if (result[i]) free(result[i]);
    }
    free(result);
    free(col_sizes);
    free(nums_buf);
    free(nums);
    return 0;
}
