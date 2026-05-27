/*
 * P695: Max Area of Island (Medium)
 * https://leetcode.com/problems/max-area-of-island/
 * Topics: Array, Depth-First Search, Breadth-First Search, Union Find, Matrix
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
    let mut grid: Vec<Vec<i32>> = Vec::new();
    for _ in 0..rows {
        grid.push(read_ints());
    }

    fn dfs(grid: &mut [Vec<i32>], r: i32, c: i32, rows: usize, cols: usize) -> i32 {
        if r < 0 || r as usize >= rows || c < 0 || c as usize >= cols || grid[r as usize][c as usize] != 1 {
            return 0;
        }
        grid[r as usize][c as usize] = 0;
        1 + dfs(grid, r + 1, c, rows, cols) + dfs(grid, r - 1, c, rows, cols)
            + dfs(grid, r, c + 1, rows, cols) + dfs(grid, r, c - 1, rows, cols)
    }

    let mut max_area = 0;
    for r in 0..rows {
        for c in 0..cols {
            if grid[r][c] == 1 {
                max_area = max_area.max(dfs(&mut grid, r as i32, c as i32, rows, cols));
            }
        }
    }
    write_int(max_area);
}
