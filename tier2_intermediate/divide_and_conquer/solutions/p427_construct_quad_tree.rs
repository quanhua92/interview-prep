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

fn all_same(grid: &[Vec<i32>], row: usize, col: usize, size: usize) -> bool {
    let v = grid[row][col];
    for i in row..row + size {
        for j in col..col + size {
            if grid[i][j] != v { return false; }
        }
    }
    true
}

fn build(grid: &[Vec<i32>], row: usize, col: usize, size: usize) -> Vec<i32> {
    if all_same(grid, row, col, size) {
        return vec![1, grid[row][col]];
    }
    let half = size / 2;
    let mut node = vec![0, 1];
    node.extend(build(grid, row, col, half));
    node.extend(build(grid, row, col + half, half));
    node.extend(build(grid, row + half, col, half));
    node.extend(build(grid, row + half, col + half, half));
    node
}

fn main() {
    let header = read_ints();
    let cols = header[0] as usize;
    let mut grid: Vec<Vec<i32>> = Vec::with_capacity(cols);
    for _ in 0..cols {
        grid.push(read_ints());
    }
    let tree = build(&grid, 0, 0, cols);
    let mut queue = std::collections::VecDeque::new();
    queue.push_back(tree);
    use std::io::Write;
    let mut out = std::io::stdout().lock();
    while let Some(node) = queue.pop_front() {
        if node.is_empty() {
            writeln!(out, "null").unwrap();
            continue;
        }
        writeln!(out, "{} {}", node[0], node[1]).unwrap();
        if node[0] == 0 {
            let children: Vec<Vec<i32>> = node[2..].chunks(2 + 4).map(|c| c.to_vec()).collect();
            for child in &children {
                queue.push_back(child.clone());
            }
        }
    }
    std::process::exit(0);
}
