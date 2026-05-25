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


#include "cpptest.h"
#include <vector>
#include <algorithm>

static int dfs(std::vector<std::vector<int>>& grid, int r, int c, int rows, int cols) {
    if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] != 1) return 0;
    grid[r][c] = 0;
    return 1 + dfs(grid, r+1, c, rows, cols) + dfs(grid, r-1, c, rows, cols)
             + dfs(grid, r, c+1, rows, cols) + dfs(grid, r, c-1, rows, cols);
}

static int maxAreaOfIsland(std::vector<std::vector<int>> grid) {
    if (grid.empty() || grid[0].empty()) return 0;
    int rows = grid.size(), cols = grid[0].size();
    int max_area = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 1) {
                max_area = std::max(max_area, dfs(grid, r, c, rows, cols));
            }
        }
    }
    return max_area;
}

int main() {
    (void)print_arr;

    printf("\n============================================================\n");
    printf("  695. Max Area of Island\n");
    printf("============================================================\n");

    int passed = 0;

    {
        std::vector<std::vector<int>> g = {{0,0,1,0,0,0,0,1,0,0,0,0,0},{0,0,0,0,0,0,0,1,1,1,0,0,0},{0,1,1,0,1,0,0,0,0,0,0,0,0},{0,1,0,0,1,1,0,0,1,0,1,0,0},{0,1,0,0,1,1,0,0,1,1,1,0,0},{0,0,0,0,0,0,0,0,0,0,1,0,0},{0,0,0,0,0,0,0,1,1,1,0,0,0},{0,0,0,0,0,0,0,1,1,0,0,0,0}};
        int got = maxAreaOfIsland(g);
        if (got == 6) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n    Expected: 6\n    Got:      %d\n", got); }
    }
    {
        std::vector<std::vector<int>> g = {{0,0,0,0,0,0,0,0}};
        int got = maxAreaOfIsland(g);
        if (got == 0) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n    Expected: 0\n    Got:      %d\n", got); }
    }
    {
        std::vector<std::vector<int>> g = {{1}};
        int got = maxAreaOfIsland(g);
        if (got == 1) { passed++; printf("  Test 3 (single cell land): PASS\n"); }
        else { printf("  Test 3 (single cell land): FAIL\n    Expected: 1\n    Got:      %d\n", got); }
    }
    {
        std::vector<std::vector<int>> g = {{0}};
        int got = maxAreaOfIsland(g);
        if (got == 0) { passed++; printf("  Test 4 (single cell water): PASS\n"); }
        else { printf("  Test 4 (single cell water): FAIL\n    Expected: 0\n    Got:      %d\n", got); }
    }
    {
        std::vector<std::vector<int>> g = {{1,1,1},{1,1,1},{1,1,1}};
        int got = maxAreaOfIsland(g);
        if (got == 9) { passed++; printf("  Test 5 (all land 3x3): PASS\n"); }
        else { printf("  Test 5 (all land 3x3): FAIL\n    Expected: 9\n    Got:      %d\n", got); }
    }
    {
        std::vector<std::vector<int>> g = {{1,0,1,0,1}};
        int got = maxAreaOfIsland(g);
        if (got == 1) { passed++; printf("  Test 6 (single row alternating): PASS\n"); }
        else { printf("  Test 6 (single row alternating): FAIL\n    Expected: 1\n    Got:      %d\n", got); }
    }
    {
        std::vector<std::vector<int>> g = {{1},{0},{1},{0},{1}};
        int got = maxAreaOfIsland(g);
        if (got == 1) { passed++; printf("  Test 7 (single column alternating): PASS\n"); }
        else { printf("  Test 7 (single column alternating): FAIL\n    Expected: 1\n    Got:      %d\n", got); }
    }

    printf("\n  %d/7 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 7 ? 0 : 1;
}
