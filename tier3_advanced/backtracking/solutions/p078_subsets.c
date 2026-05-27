/*
 * P78: Subsets (Medium)
 * https://leetcode.com/problems/subsets/
 * Topics: Array, Backtracking, Bit Manipulation
 *
 * Given an integer array nums of unique elements, return all possible subsets (the power set).
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 *
 * Example 1:
 *     Input: nums = [1,2,3]
 *     Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
 *
 * Example 2:
 *     Input: nums = [0]
 *     Output: [[],[0]]
 *
 * Hint: Use backtracking to generate all possible subsets by including/excluding each element.
 */

#include "io.h"
#include <stdlib.h>
#include <string.h>

static int *g_nums;
static int g_n;
static int **g_res;
static int *g_cs;
static int g_cnt;
static int g_cap;
static int *g_path;
static int g_plen;

static void add_res(void) {
    if (g_cnt >= g_cap) {
        g_cap = g_cap ? g_cap * 2 : 16;
        g_res = realloc(g_res, g_cap * sizeof(int *));
        g_cs = realloc(g_cs, g_cap * sizeof(int));
    }
    g_res[g_cnt] = malloc(g_plen * sizeof(int));
    memcpy(g_res[g_cnt], g_path, g_plen * sizeof(int));
    g_cs[g_cnt] = g_plen;
    g_cnt++;
}

static void bt(int start) {
    add_res();
    for (int i = start; i < g_n; i++) {
        g_path[g_plen++] = g_nums[i];
        bt(i + 1);
        g_plen--;
    }
}

int main(void) {
    int n;
    int *nums = read_ints(&n);
    g_nums = nums;
    g_n = n;
    g_cnt = 0; g_cap = 0; g_plen = 0;
    g_res = NULL; g_cs = NULL;
    g_path = malloc(n * sizeof(int));
    bt(0);
    free(g_path);

    for (int i = 0; i < g_cnt; i++) {
        if (g_cs[i] > 0) {
            write_ints(g_res[i], g_cs[i]);
        } else {
            write_string("");
        }
        free(g_res[i]);
    }
    free(g_res); free(g_cs); free(nums);
    return 0;
}
