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
    abort();
}

static void bt(int start) {
    abort();
}

static void sort_res(void) {
    abort();
}

static int **findSubsequences(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
    abort();
}

static int check(int **got, int gn, int *gcs, int **exp, int en, int *ecs) {
    abort();
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
