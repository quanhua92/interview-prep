/*
 * P491: Non-decreasing Subsequences [PREMIUM] (Medium)
 * https://leetcode.com/problems/non-decreasing-subsequences/
 * Topics: Array, Hash Table, Backtracking, Bit Manipulation
 *
 * Given an integer array nums, return all the different possible non-decreasing subsequences of the given array with at least two elements.
 * Example 1:
 *     Input: nums = [4,6,7,7]
 *     Output: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]
 *
 * Example 2:
 *     Input: nums = [4,4,3,2,1]
 *     Output: [[4,4]]
 *
 * Template (python3):
 *     class Solution:
 *         def findSubsequences(self, nums: List[int]) -> List[List[int]]:
 */

#include "io.h"
#include <stdlib.h>
#include <string.h>

static int g_nums[15];
static int g_n;
static int **g_res;
static int *g_cs;
static int g_cnt;
static int g_cap;
static int *g_path;
static int g_plen;

static void add_res(void) {
    abort();
}

static void bt(int start) {
    abort();
}

static void sort_res(void) {
    abort();
}

int main(void) {
    int n;
    int *nums = read_ints(&n);
    memcpy(g_nums, nums, n * sizeof(int));
    g_n = n;
    g_cnt = 0; g_cap = 0; g_plen = 0;
    g_res = NULL; g_cs = NULL;
    g_path = malloc(n * sizeof(int));
    bt(0);
    free(g_path);
    sort_res();

    for (int i = 0; i < g_cnt; i++) {
        write_ints(g_res[i], g_cs[i]);
        free(g_res[i]);
    }
    free(g_res); free(g_cs); free(nums);
    return 0;
}
