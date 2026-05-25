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
 *     Explanation:
 *     2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
 *     7 is a candidate, and 7 = 7.
 *     These are the only two combinations.
 *
 * Example 2:
 *     Input: candidates = [2,3,5], target = 8
 *     Output: [[2,2,2,2],[2,3,3],[3,5]]
 *
 * Example 3:
 *     Input: candidates = [2], target = 1
 *     Output: []
 *
 * Constraints:
 *     - 1 <= candidates.length <= 30
 *     - 2 <= candidates[i] <= 40
 *     - All elements of candidates are distinct.
 *     - 1 <= target <= 40
 *
 * Template (python3):
 *     class Solution:
 *         def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
 *
 * Hint: Use backtracking with early pruning when the remaining sum goes negative.
 */


#include "ctest.h"
#include <stdlib.h>
#include <string.h>

static int g_cands[30];
static int g_path[40];
static int g_path_len;
static int **g_res;
static int *g_cs;
static int g_cnt;
static int g_cap;

static void add_res(void) {
    if (g_cnt >= g_cap) {
        g_cap = g_cap ? g_cap * 2 : 16;
        g_res = realloc(g_res, g_cap * sizeof(int *));
        g_cs = realloc(g_cs, g_cap * sizeof(int));
    }
    g_res[g_cnt] = malloc(g_path_len * sizeof(int));
    memcpy(g_res[g_cnt], g_path, g_path_len * sizeof(int));
    g_cs[g_cnt] = g_path_len;
    g_cnt++;
}

static void bt(int start, int rem) {
    if (rem == 0) { add_res(); return; }
    for (int i = start; i < 30 && g_cands[i] > 0; i++) {
        if (g_cands[i] > rem) break;
        g_path[g_path_len++] = g_cands[i];
        bt(i, rem - g_cands[i]);
        g_path_len--;
    }
}

static int sort_cands(const void *a, const void *b) {
    return *(const int *)a - *(const int *)b;
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

static int **combinationSum(int *candidates, int candidatesSize, int target, int *returnSize, int **returnColumnSizes) {
    memset(g_cands, 0, sizeof(g_cands));
    memcpy(g_cands, candidates, candidatesSize * sizeof(int));
    qsort(g_cands, candidatesSize, sizeof(int), sort_cands);
    g_cnt = 0; g_cap = 0; g_path_len = 0;
    g_res = NULL; g_cs = NULL;
    bt(0, target);
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
    printf("  39. Combination Sum\n");
    printf("============================================================\n");

    int passed = 0;

    {
        int c[] = {2,3,6,7};
        int ed[][3] = {{2,2,3},{7}};
        int ecs[] = {3,1}; int *e[] = {ed[0],ed[1]};
        int rs, *rcs; int **g = combinationSum(c,4,7,&rs,&rcs);
        if (check(g,rs,rcs,e,2,ecs)) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n"); }
        for (int i=0;i<rs;i++) free(g[i]); free(g); free(rcs);
    }
    {
        int c[] = {2,3,5};
        int ed[][4] = {{2,2,2,2},{2,3,3},{3,5}};
        int ecs[] = {4,3,2}; int *e[] = {ed[0],ed[1],ed[2]};
        int rs, *rcs; int **g = combinationSum(c,3,8,&rs,&rcs);
        if (check(g,rs,rcs,e,3,ecs)) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n"); }
        for (int i=0;i<rs;i++) free(g[i]); free(g); free(rcs);
    }
    {
        int c[] = {2};
        int rs, *rcs; int **g = combinationSum(c,1,1,&rs,&rcs);
        if (rs==0) { passed++; printf("  Test 3 (no solution): PASS\n"); }
        else { printf("  Test 3 (no solution): FAIL\n"); }
        for (int i=0;i<rs;i++) free(g[i]); free(g); free(rcs);
    }
    {
        int c[] = {5};
        int ed[][1] = {{5}};
        int ecs[] = {1}; int *e[] = {ed[0]};
        int rs, *rcs; int **g = combinationSum(c,1,5,&rs,&rcs);
        if (check(g,rs,rcs,e,1,ecs)) { passed++; printf("  Test 4 (single candidate equals target): PASS\n"); }
        else { printf("  Test 4 (single candidate equals target): FAIL\n"); }
        for (int i=0;i<rs;i++) free(g[i]); free(g); free(rcs);
    }
    {
        int c[] = {2};
        int ed[][2] = {{2,2}};
        int ecs[] = {2}; int *e[] = {ed[0]};
        int rs, *rcs; int **g = combinationSum(c,1,4,&rs,&rcs);
        if (check(g,rs,rcs,e,1,ecs)) { passed++; printf("  Test 5 (reuse single candidate): PASS\n"); }
        else { printf("  Test 5 (reuse single candidate): FAIL\n"); }
        for (int i=0;i<rs;i++) free(g[i]); free(g); free(rcs);
    }
    {
        int c[] = {8,7,4,3};
        int ed[][3] = {{3,4,4},{3,8},{4,7}};
        int ecs[] = {3,2,2}; int *e[] = {ed[0],ed[1],ed[2]};
        int rs, *rcs; int **g = combinationSum(c,4,11,&rs,&rcs);
        if (check(g,rs,rcs,e,3,ecs)) { passed++; printf("  Test 6 (unsorted candidates multiple combos): PASS\n"); }
        else { printf("  Test 6 (unsorted candidates multiple combos): FAIL\n"); }
        for (int i=0;i<rs;i++) free(g[i]); free(g); free(rcs);
    }
    {
        int c[] = {3,5};
        int rs, *rcs; int **g = combinationSum(c,2,7,&rs,&rcs);
        if (rs==0) { passed++; printf("  Test 7 (no valid combination): PASS\n"); }
        else { printf("  Test 7 (no valid combination): FAIL\n"); }
        for (int i=0;i<rs;i++) free(g[i]); free(g); free(rcs);
    }
    {
        int c[] = {3};
        int ed[][3] = {{3,3,3}};
        int ecs[] = {3}; int *e[] = {ed[0]};
        int rs, *rcs; int **g = combinationSum(c,1,9,&rs,&rcs);
        if (check(g,rs,rcs,e,1,ecs)) { passed++; printf("  Test 8 (triple reuse): PASS\n"); }
        else { printf("  Test 8 (triple reuse): FAIL\n"); }
        for (int i=0;i<rs;i++) free(g[i]); free(g); free(rcs);
    }

    printf("\n  %d/8 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 8 ? 0 : 1;
}
