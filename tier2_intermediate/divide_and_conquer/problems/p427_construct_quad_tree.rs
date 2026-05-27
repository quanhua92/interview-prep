/*
 * P427: Construct Quad Tree [PREMIUM] (Medium)
 * https://leetcode.com/problems/construct-quad-tree/
 * Topics: Array, Divide and Conquer, Tree, Matrix
 *
 * Given a n * n matrix grid of 0's and 1's only. We want to represent grid with a Quad-Tree.
 * Return the root of the Quad-Tree representing grid.
 *
 * Constraints:
 *     - n == grid.length == grid[i].length
 *     - n == 2x where 0 <= x <= 6
 *
 * Hint: Recursively divide grid into 4 quadrants, make leaf if all same value.
 */

use wasm_libs::*;

fn solve(grid: &[Vec<i32>]) {
    todo!()
}

fn main() {
    let header = read_ints();
    let cols = header[0] as usize;
    let mut grid: Vec<Vec<i32>> = Vec::with_capacity(cols);
    for _ in 0..cols {
        grid.push(read_ints());
    }
    solve(&grid);
    std::process::exit(0);
}
