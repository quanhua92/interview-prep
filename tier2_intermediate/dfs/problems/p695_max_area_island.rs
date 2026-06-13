/*
 * P695: Max Area of Island (Medium)
 * https://leetcode.com/problems/max-area-of-island/
 * Topics: Array, Depth-First Search, Breadth-First Search, Union Find, Matrix
 */

use wasm_libs::*;

fn solve(grid: &mut Vec<Vec<i32>>) -> i32 {
    todo!()
}

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
    let result = solve(&mut grid);
    write_int(result);
}
