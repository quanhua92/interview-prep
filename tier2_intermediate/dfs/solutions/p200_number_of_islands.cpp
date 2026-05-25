/*
 * P200: Number of Islands (Medium)
 * https://leetcode.com/problems/number-of-islands/
 * Topics: Array, Depth-First Search, Breadth-First Search, Union Find, Matrix
 *
 * Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.
 * An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.
 *
 * Example 1:
 *     Input: grid = [
 *       ["1","1","1","1","0"],
 *       ["1","1","0","1","0"],
 *       ["1","1","0","0","0"],
 *       ["0","0","0","0","0"]
 *     ]
 *     Output: 1
 *
 * Example 2:
 *     Input: grid = [
 *       ["1","1","0","0","0"],
 *       ["1","1","0","0","0"],
 *       ["0","0","1","0","0"],
 *       ["0","0","0","1","1"]
 *     ]
 *     Output: 3
 *
 * Constraints:
 *     - m == grid.length
 *     - n == grid[i].length
 *     - 1 <= m, n <= 300
 *     - grid[i][j] is '0' or '1'.
 *
 * Template (python3):
 *     class Solution:
 *         def numIslands(self, grid: List[List[str]]) -> int:
 *
 * Hint: Use DFS to mark visited land cells, counting each new island.
 */


#include "cpptest.h"
#include <vector>
#include <string>

static void dfs(std::vector<std::vector<char>>& grid, int r, int c, int rows, int cols) {
    if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] != '1') return;
    grid[r][c] = '0';
    dfs(grid, r + 1, c, rows, cols);
    dfs(grid, r - 1, c, rows, cols);
    dfs(grid, r, c + 1, rows, cols);
    dfs(grid, r, c - 1, rows, cols);
}

static int numIslands(std::vector<std::vector<char>> grid) {
    if (grid.empty() || grid[0].empty()) return 0;
    int rows = grid.size(), cols = grid[0].size();
    int count = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == '1') {
                count++;
                dfs(grid, r, c, rows, cols);
            }
        }
    }
    return count;
}

int main() {
    (void)print_arr;

    printf("\n============================================================\n");
    printf("  200. Number of Islands\n");
    printf("============================================================\n");

    int passed = 0;

    {
        std::vector<std::vector<char>> g = {{'1','1','1','1','0'},{'1','1','0','1','0'},{'1','1','0','0','0'},{'0','0','0','0','0'}};
        int got = numIslands(g);
        if (got == 1) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n    Expected: 1\n    Got:      %d\n", got); }
    }
    {
        std::vector<std::vector<char>> g = {{'1','1','0','0','0'},{'1','1','0','0','0'},{'0','0','1','0','0'},{'0','0','0','1','1'}};
        int got = numIslands(g);
        if (got == 3) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n    Expected: 3\n    Got:      %d\n", got); }
    }
    {
        std::vector<std::vector<char>> g;
        int got = numIslands(g);
        if (got == 0) { passed++; printf("  Test 3 (empty grid): PASS\n"); }
        else { printf("  Test 3 (empty grid): FAIL\n    Expected: 0\n    Got:      %d\n", got); }
    }
    {
        std::vector<std::vector<char>> g = {{'0'}};
        int got = numIslands(g);
        if (got == 0) { passed++; printf("  Test 4 (single cell water): PASS\n"); }
        else { printf("  Test 4 (single cell water): FAIL\n    Expected: 0\n    Got:      %d\n", got); }
    }
    {
        std::vector<std::vector<char>> g = {{'1'}};
        int got = numIslands(g);
        if (got == 1) { passed++; printf("  Test 5 (single cell land): PASS\n"); }
        else { printf("  Test 5 (single cell land): FAIL\n    Expected: 1\n    Got:      %d\n", got); }
    }
    {
        std::vector<std::vector<char>> g = {{'1','0','1','0','1'}};
        int got = numIslands(g);
        if (got == 3) { passed++; printf("  Test 6 (single row): PASS\n"); }
        else { printf("  Test 6 (single row): FAIL\n    Expected: 3\n    Got:      %d\n", got); }
    }
    {
        std::vector<std::vector<char>> g = {{'1'},{'0'},{'1'},{'0'},{'1'}};
        int got = numIslands(g);
        if (got == 3) { passed++; printf("  Test 7 (single column): PASS\n"); }
        else { printf("  Test 7 (single column): FAIL\n    Expected: 3\n    Got:      %d\n", got); }
    }
    {
        std::vector<std::vector<char>> g = {{'1','1','1'},{'1','1','1'},{'1','1','1'}};
        int got = numIslands(g);
        if (got == 1) { passed++; printf("  Test 8 (all land 3x3): PASS\n"); }
        else { printf("  Test 8 (all land 3x3): FAIL\n    Expected: 1\n    Got:      %d\n", got); }
    }

    printf("\n  %d/8 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 8 ? 0 : 1;
}
