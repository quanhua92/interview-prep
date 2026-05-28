/*
 * P427: Construct Quad Tree [PREMIUM] (Medium)
 * https://leetcode.com/problems/construct-quad-tree/
 * Topics: Array, Divide and Conquer, Tree, Matrix
 *
 * Given a n * n matrix grid of 0's and 1's only. We want to represent grid with a Quad-Tree.
 * Return the root of the Quad-Tree representing grid.
 *
 * Example 1:
 *     Input: grid = [[0,1],[1,0]]
 *     Output: [[0,1],[1,0],[1,1],[1,1],[1,0]]
 *
 * Constraints:
 *     - n == grid.length == grid[i].length
 *     - n == 2x where 0 <= x <= 6
 *
 * Hint: Recursively divide grid into 4 quadrants, make leaf if all same value.
 */

use wasm_libs::*;

fn all_same(grid: &[Vec<i32>], row: usize, col: usize, size: usize) -> bool {
    todo!();
}

enum QNode {
    Leaf(i32),
    Internal(i32, usize),
}

fn main() {
    let header = read_ints();
    let cols = header[0] as usize;
    let mut grid: Vec<Vec<i32>> = Vec::with_capacity(cols);
    for _ in 0..cols {
        grid.push(read_ints());
    }

    let mut flat: Vec<i32> = Vec::new();
    fn build_flat(grid: &[Vec<i32>], row: usize, col: usize, size: usize, flat: &mut Vec<i32>) -> usize {
        if all_same(grid, row, col, size) {
            flat.push(1);
            flat.push(grid[row][col]);
            flat.len() - 2
        } else {
            let half = size / 2;
            let idx = flat.len();
            flat.push(0);
            flat.push(1);
            build_flat(grid, row, col, half, flat);
            build_flat(grid, row, col + half, half, flat);
            build_flat(grid, row + half, col, half, flat);
            build_flat(grid, row + half, col + half, half, flat);
            idx
        }
    }
    build_flat(&grid, 0, 0, cols, &mut flat);

    use std::io::Write;
    let mut out = std::io::stdout().lock();

    fn compute_child_sizes(flat: &[i32], pos: usize) -> usize {
        if flat[pos] == 1 { return 2; }
        let mut total = 2;
        let mut p = pos + 2;
        for _ in 0..4 {
            let cs = compute_child_sizes(flat, p);
            p += cs;
            total += cs;
        }
        total
    }

    fn bfs_print(flat: &[i32], root_pos: usize, out: &mut std::io::StdoutLock) {
        let mut queue = std::collections::VecDeque::new();
        queue.push_back(root_pos);
        while let Some(pos) = queue.pop_front() {
            if flat[pos] == 1 {
                writeln!(out, "{} {}", flat[pos], flat[pos + 1]).unwrap();
            } else {
                writeln!(out, "{} {}", flat[pos], flat[pos + 1]).unwrap();
                let mut child_pos = pos + 2;
                for _ in 0..4 {
                    queue.push_back(child_pos);
                    child_pos += compute_child_sizes(flat, child_pos);
                }
            }
        }
    }

    bfs_print(&flat, 0, &mut out);
    std::process::exit(0);
}
