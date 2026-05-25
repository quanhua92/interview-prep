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
 * Constraints:
 *     - 1 <= nums.length <= 10
 *     - -10 <= nums[i] <= 10
 *     - All the numbers of nums are unique.
 *
 * Template (python3):
 *     class Solution:
 *         def subsets(self, nums: List[int]) -> List[List[int]]:
 *
 * Hint: Use backtracking to generate all possible subsets by including/excluding each element.
 */


#include "ctest.h"
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

static int **subsets(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
    g_nums = nums;
    g_n = numsSize;
    g_cnt = 0; g_cap = 0; g_plen = 0;
    g_res = NULL; g_cs = NULL;
    g_path = malloc(numsSize * sizeof(int));
    bt(0);
    free(g_path);
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
    printf("  78. Subsets\n");
    printf("============================================================\n");

    int passed = 0;

    {
        int n[] = {1,2,3};
        int ed[][3] = {{},{1},{1,2},{1,2,3},{1,3},{2},{2,3},{3}};
        int ecs[] = {0,1,2,3,2,1,2,1};
        int *e[8]; for (int i=0;i<8;i++) e[i]=ed[i];
        int rs, *rcs; int **g = subsets(n,3,&rs,&rcs);
        if (check(g,rs,rcs,e,8,ecs)) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n"); }
        for (int i=0;i<rs;i++) free(g[i]); free(g); free(rcs);
    }
    {
        int n[] = {0};
        int ed[][1] = {{},{0}};
        int ecs[] = {0,1};
        int *e[2] = {ed[0],ed[1]};
        int rs, *rcs; int **g = subsets(n,1,&rs,&rcs);
        if (check(g,rs,rcs,e,2,ecs)) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n"); }
        for (int i=0;i<rs;i++) free(g[i]); free(g); free(rcs);
    }
    {
        int n[] = {1,2};
        int ed[][2] = {{},{1},{1,2},{2}};
        int ecs[] = {0,1,2,1};
        int *e[4]; for (int i=0;i<4;i++) e[i]=ed[i];
        int rs, *rcs; int **g = subsets(n,2,&rs,&rcs);
        if (check(g,rs,rcs,e,4,ecs)) { passed++; printf("  Test 3 (two elements): PASS\n"); }
        else { printf("  Test 3 (two elements): FAIL\n"); }
        for (int i=0;i<rs;i++) free(g[i]); free(g); free(rcs);
    }
    {
        int n[] = {-1,0,1};
        int ed[][3] = {{},{-1},{-1,0},{-1,0,1},{-1,1},{0},{0,1},{1}};
        int ecs[] = {0,1,2,3,2,1,2,1};
        int *e[8]; for (int i=0;i<8;i++) e[i]=ed[i];
        int rs, *rcs; int **g = subsets(n,3,&rs,&rcs);
        if (check(g,rs,rcs,e,8,ecs)) { passed++; printf("  Test 4 (negative numbers): PASS\n"); }
        else { printf("  Test 4 (negative numbers): FAIL\n"); }
        for (int i=0;i<rs;i++) free(g[i]); free(g); free(rcs);
    }
    {
        int n[] = {1,2,3,4};
        int ed[][4] = {
            {},{1},{1,2},{1,2,3},{1,2,3,4},{1,2,4},{1,3},{1,3,4},
            {1,4},{2},{2,3},{2,3,4},{2,4},{3},{3,4},{4}
        };
        int ecs[] = {0,1,2,3,4,3,2,3,2,1,2,3,2,1,2,1};
        int *e[16]; for (int i=0;i<16;i++) e[i]=ed[i];
        int rs, *rcs; int **g = subsets(n,4,&rs,&rcs);
        if (check(g,rs,rcs,e,16,ecs)) { passed++; printf("  Test 5 (four elements): PASS\n"); }
        else { printf("  Test 5 (four elements): FAIL\n"); }
        for (int i=0;i<rs;i++) free(g[i]); free(g); free(rcs);
    }
    {
        int n[] = {3,1};
        int ed[][2] = {{},{3},{3,1},{1}};
        int ecs[] = {0,1,2,1};
        int *e[4]; for (int i=0;i<4;i++) e[i]=ed[i];
        int rs, *rcs; int **g = subsets(n,2,&rs,&rcs);
        if (check(g,rs,rcs,e,4,ecs)) { passed++; printf("  Test 6 (unsorted input): PASS\n"); }
        else { printf("  Test 6 (unsorted input): FAIL\n"); }
        for (int i=0;i<rs;i++) free(g[i]); free(g); free(rcs);
    }

    printf("\n  %d/6 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 6 ? 0 : 1;
}
