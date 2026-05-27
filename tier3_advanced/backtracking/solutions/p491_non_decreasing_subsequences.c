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
    if (g_plen >= 2) add_res();
    int used[201];
    memset(used, 0, sizeof(used));
    for (int i = start; i < g_n; i++) {
        int v = g_nums[i] + 100;
        if (used[v]) continue;
        if (g_plen == 0 || g_nums[i] >= g_path[g_plen - 1]) {
            used[v] = 1;
            g_path[g_plen++] = g_nums[i];
            bt(i + 1);
            g_plen--;
        }
    }
}

static void sort_res(void) {
    for (int i = 0; i < g_cnt - 1; i++)
        for (int j = i + 1; j < g_cnt; j++) {
            int ml = g_cs[i] < g_cs[j] ? g_cs[i] : g_cs[j];
            int gt = 0;
            for (int k = 0; k < ml; k++) {
                if (g_res[i][k] > g_res[j][k]) { gt = 1; break; }
                if (g_res[i][k] < g_res[j][k]) { gt = -1; break; }
            }
            if (gt == 0 && g_cs[i] != g_cs[j]) gt = g_cs[i] < g_cs[j] ? -1 : 1;
            if (gt > 0) {
                int *t = g_res[i]; g_res[i] = g_res[j]; g_res[j] = t;
                int c = g_cs[i]; g_cs[i] = g_cs[j]; g_cs[j] = c;
            }
        }
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
