/*
 * P491: Non-decreasing Subsequences [PREMIUM] (Medium)
 * https://leetcode.com/problems/non-decreasing-subsequences/
 * Topics: Array, Hash Table, Backtracking, Bit Manipulation
 *
 * Given an integer array nums, return all the different possible non-decreasing subsequences of the given array with at least two elements. You may return the answer in any order.
 * Example 1:
 *     Input: nums = [4,6,7,7]
 *     Output: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]
 *
 * Example 2:
 *     Input: nums = [4,4,3,2,1]
 *     Output: [[4,4]]
 *
 * Constraints:
 *     - 1 <= nums.length <= 15
 *     - -100 <= nums[i] <= 100
 *
 * Template (python3):
 *     class Solution:
 *         def findSubsequences(self, nums: List[int]) -> List[List[int]]:
 */


#include "ctest.h"
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

static int **findSubsequences(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
    memcpy(g_nums, nums, numsSize * sizeof(int));
    g_n = numsSize;
    g_cnt = 0; g_cap = 0; g_plen = 0;
    g_res = NULL; g_cs = NULL;
    g_path = malloc(numsSize * sizeof(int));
    bt(0);
    free(g_path);
    sort_res();
    *returnSize = g_cnt;
    *returnColumnSizes = g_cs;
    return g_res;
}

static int check(int **got, int gn, int *gcs, int **exp, int en, int *ecs) {
    if (gn != en) return 0;
    for (int i = 0; i < gn; i++) {
        if (gcs[i] != ecs[i]) return 0;
        for (int j = 0; j < gcs[i]; j++)
            if (got[i][j] != exp[i][j]) return 0;
    }
    return 1;
}

int main(void) {
    (void)th_print_arr;
    (void)th_arr_eq;

    printf("\n============================================================\n");
    printf("  491. Non-decreasing Subsequences\n");
    printf("============================================================\n");

    int passed = 0;

    {
        int n[] = {4,6,7,7};
        int ed[][4] = {{4,6},{4,6,7},{4,6,7,7},{4,7},{4,7,7},{6,7},{6,7,7},{7,7}};
        int ecs[] = {2,3,4,2,3,2,3,2};
        int *e[8]; for (int i=0;i<8;i++) e[i]=ed[i];
        int rs, *rcs; int **g = findSubsequences(n,4,&rs,&rcs);
        if (check(g,rs,rcs,e,8,ecs)) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n"); }
        for (int i=0;i<rs;i++) free(g[i]); free(g); free(rcs);
    }
    {
        int n[] = {4,4,3,2,1};
        int ed[][2] = {{4,4}};
        int ecs[] = {2};
        int *e[1] = {ed[0]};
        int rs, *rcs; int **g = findSubsequences(n,5,&rs,&rcs);
        if (check(g,rs,rcs,e,1,ecs)) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n"); }
        for (int i=0;i<rs;i++) free(g[i]); free(g); free(rcs);
    }
    {
        int n[] = {2,2,2};
        int ed[][3] = {{2,2},{2,2,2}};
        int ecs[] = {2,3};
        int *e[2] = {ed[0],ed[1]};
        int rs, *rcs; int **g = findSubsequences(n,3,&rs,&rcs);
        if (check(g,rs,rcs,e,2,ecs)) { passed++; printf("  Test 3 (all same elements): PASS\n"); }
        else { printf("  Test 3 (all same elements): FAIL\n"); }
        for (int i=0;i<rs;i++) free(g[i]); free(g); free(rcs);
    }
    {
        int n[] = {5,4,3,2,1};
        int rs, *rcs; int **g = findSubsequences(n,5,&rs,&rcs);
        if (rs==0) { passed++; printf("  Test 4 (strictly decreasing): PASS\n"); }
        else { printf("  Test 4 (strictly decreasing): FAIL\n"); }
        for (int i=0;i<rs;i++) free(g[i]); free(g); free(rcs);
    }
    {
        int n[] = {1,2,3};
        int ed[][3] = {{1,2},{1,2,3},{1,3},{2,3}};
        int ecs[] = {2,3,2,2};
        int *e[4]; for (int i=0;i<4;i++) e[i]=ed[i];
        int rs, *rcs; int **g = findSubsequences(n,3,&rs,&rcs);
        if (check(g,rs,rcs,e,4,ecs)) { passed++; printf("  Test 5 (strictly increasing): PASS\n"); }
        else { printf("  Test 5 (strictly increasing): FAIL\n"); }
        for (int i=0;i<rs;i++) free(g[i]); free(g); free(rcs);
    }
    {
        int n[] = {1};
        int rs, *rcs; int **g = findSubsequences(n,1,&rs,&rcs);
        if (rs==0) { passed++; printf("  Test 6 (single element): PASS\n"); }
        else { printf("  Test 6 (single element): FAIL\n"); }
        for (int i=0;i<rs;i++) free(g[i]); free(g); free(rcs);
    }

    printf("\n  %d/6 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 6 ? 0 : 1;
}
