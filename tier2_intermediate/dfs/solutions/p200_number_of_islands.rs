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

use wasm_libs::*;

fn main() {
    let meta = read_ints();
    let rows = meta[0] as usize;
    let cols = if meta.len() > 1 { meta[1] as usize } else { 0 };
    if rows == 0 || cols == 0 {
        write_int(0);
        return;
    }
    let mut grid: Vec<Vec<char>> = Vec::new();
    for _ in 0..rows {
        let line = read_line();
        grid.push(line.chars().collect());
    }
    let mut count = 0i32;

    fn dfs(grid: &mut [Vec<char>], r: i32, c: i32, rows: usize, cols: usize) {
        if r < 0 || r as usize >= rows || c < 0 || c as usize >= cols || grid[r as usize][c as usize] != '1' {
            return;
        }
        grid[r as usize][c as usize] = '0';
        dfs(grid, r + 1, c, rows, cols);
        dfs(grid, r - 1, c, rows, cols);
        dfs(grid, r, c + 1, rows, cols);
        dfs(grid, r, c - 1, rows, cols);
    }

    for r in 0..rows {
        for c in 0..cols {
            if grid[r][c] == '1' {
                count += 1;
                dfs(&mut grid, r as i32, c as i32, rows, cols);
            }
        }
    }
    write_int(count);
}
