/*
 * P695: Max Area of Island (Medium)
 * https://leetcode.com/problems/max-area-of-island/
 * Topics: Array, Depth-First Search, Breadth-First Search, Union Find, Matrix
 * 
 * You are given an m x n binary matrix grid. An island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.
 * The area of an island is the number of cells with a value 1 in the island.
 * Return the maximum area of an island in grid. If there is no island, return 0.
 * 
 * Example 1:
 *     Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
 *     Output: 6
 *     Explanation: The answer is not 11, because the island must be connected 4-directionally.
 * 
 * Example 2:
 *     Input: grid = [[0,0,0,0,0,0,0,0]]
 *     Output: 0
 * 
 * Constraints:
 *     - m == grid.length
 *     - n == grid[i].length
 *     - 1 <= m, n <= 50
 *     - grid[i][j] is either 0 or 1.
 * 
 * Template (python3):
 *     class Solution:
 *         def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
 * 
 * Hint: Use DFS to explore each island and track the maximum area found.
 */
#include "ctest.h"

static int dfs(int **grid, int r, int c, int rows, int cols) {
    /* TODO: Implement */
    return 0;
}

static int maxAreaOfIsland(int **grid, int gridSize, int *gridColSize) {
    /* TODO: Implement */
    return 0;
}

int main(void) {
    (void)th_print_arr;
    (void)th_arr_eq;

    printf("\n============================================================\n");
    printf("  695. Max Area of Island\n");
    printf("============================================================\n");

    int passed = 0;

    {
        int r0[] = {0,0,1,0,0,0,0,1,0,0,0,0,0};
        int r1[] = {0,0,0,0,0,0,0,1,1,1,0,0,0};
        int r2[] = {0,1,1,0,1,0,0,0,0,0,0,0,0};
        int r3[] = {0,1,0,0,1,1,0,0,1,0,1,0,0};
        int r4[] = {0,1,0,0,1,1,0,0,1,1,1,0,0};
        int r5[] = {0,0,0,0,0,0,0,0,0,0,1,0,0};
        int r6[] = {0,0,0,0,0,0,0,1,1,1,0,0,0};
        int r7[] = {0,0,0,0,0,0,0,1,1,0,0,0,0};
        int *g[] = {r0,r1,r2,r3,r4,r5,r6,r7};
        int cs[] = {13,13,13,13,13,13,13,13};
        int got = maxAreaOfIsland(g, 8, cs);
        if (got == 6) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n    Expected: 6\n    Got:      %d\n", got); }
    }
    {
        int r0[] = {0,0,0,0,0,0,0,0};
        int *g[] = {r0};
        int cs[] = {8};
        int got = maxAreaOfIsland(g, 1, cs);
        if (got == 0) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n    Expected: 0\n    Got:      %d\n", got); }
    }
    {
        int r0[] = {1};
        int *g[] = {r0};
        int cs[] = {1};
        int got = maxAreaOfIsland(g, 1, cs);
        if (got == 1) { passed++; printf("  Test 3 (single cell land): PASS\n"); }
        else { printf("  Test 3 (single cell land): FAIL\n    Expected: 1\n    Got:      %d\n", got); }
    }
    {
        int r0[] = {0};
        int *g[] = {r0};
        int cs[] = {1};
        int got = maxAreaOfIsland(g, 1, cs);
        if (got == 0) { passed++; printf("  Test 4 (single cell water): PASS\n"); }
        else { printf("  Test 4 (single cell water): FAIL\n    Expected: 0\n    Got:      %d\n", got); }
    }
    {
        int r0[] = {1,1,1}, r1[] = {1,1,1}, r2[] = {1,1,1};
        int *g[] = {r0,r1,r2};
        int cs[] = {3,3,3};
        int got = maxAreaOfIsland(g, 3, cs);
        if (got == 9) { passed++; printf("  Test 5 (all land 3x3): PASS\n"); }
        else { printf("  Test 5 (all land 3x3): FAIL\n    Expected: 9\n    Got:      %d\n", got); }
    }
    {
        int r0[] = {1,0,1,0,1};
        int *g[] = {r0};
        int cs[] = {5};
        int got = maxAreaOfIsland(g, 1, cs);
        if (got == 1) { passed++; printf("  Test 6 (single row alternating): PASS\n"); }
        else { printf("  Test 6 (single row alternating): FAIL\n    Expected: 1\n    Got:      %d\n", got); }
    }
    {
        int r0[] = {1}, r1[] = {0}, r2[] = {1}, r3[] = {0}, r4[] = {1};
        int *g[] = {r0,r1,r2,r3,r4};
        int cs[] = {1,1,1,1,1};
        int got = maxAreaOfIsland(g, 5, cs);
        if (got == 1) { passed++; printf("  Test 7 (single column alternating): PASS\n"); }
        else { printf("  Test 7 (single column alternating): FAIL\n    Expected: 1\n    Got:      %d\n", got); }
    }

    printf("\n  %d/7 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 7 ? 0 : 1;
}
