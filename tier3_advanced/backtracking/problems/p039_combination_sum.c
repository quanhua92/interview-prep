/*
 * P39: Combination Sum (Medium)
 * https://leetcode.com/problems/combination-sum/
 * Topics: Array, Backtracking
 *
 * Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.
 * The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.
 * The test cases are generated such that the number of unique combinations that sum up to target is less than 150 combinations for the given input.
 *
 * Example 1:
 *     Input: candidates = [2,3,6,7], target = 7
 *     Output: [[2,2,3],[7]]
 *
 * Example 2:
 *     Input: candidates = [2,3,5], target = 8
 *     Output: [[2,2,2,2],[2,3,3],[3,5]]
 *
 * Example 3:
 *     Input: candidates = [2], target = 1
 *     Output: []
 *
 * Hint: Use backtracking with early pruning when the remaining sum goes negative.
 */

#include "io.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int g_cands[30];
static int g_path[40];
static int g_path_len;
static int **g_res;
static int *g_cs;
static int g_cnt;
static int g_cap;

static void add_res(void) {
    abort();
}

static void bt(int start, int rem) {
    abort();
}

static int sort_cands(const void *a, const void *b) {
    abort();
}

int main(void) {
    int n;
    int *candidates = read_ints(&n);
    int target;
    scanf("%d", &target);

    memset(g_cands, 0, sizeof(g_cands));
    memcpy(g_cands, candidates, n * sizeof(int));
    qsort(g_cands, n, sizeof(int), sort_cands);
    g_cnt = 0; g_cap = 0; g_path_len = 0;
    g_res = NULL; g_cs = NULL;
    bt(0, target);

    for (int i = 0; i < g_cnt; i++) {
        write_ints(g_res[i], g_cs[i]);
        free(g_res[i]);
    }
    free(g_res); free(g_cs); free(candidates);
    return 0;
}
