/*
 * P1091: Shortest Path in Binary Matrix (Medium)
 * https://leetcode.com/problems/shortest-path-in-binary-matrix/
 * Topics: Array, Breadth-First Search, Matrix
 *
 * Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. If there is no clear path, return -1.
 * A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:
 * The length of a clear path is the number of visited cells of this path.
 *
 * Example 1:
 *     Input: grid = [[0,1],[1,0]]
 *     Output: 2
 *
 * Example 2:
 *     Input: grid = [[0,0,0],[1,1,0],[1,1,0]]
 *     Output: 4
 *
 * Example 3:
 *     Input: grid = [[1,0,0],[1,1,0],[1,1,0]]
 *     Output: -1
 *
 * Constraints:
 *     - n == grid.length
 *     - n == grid[i].length
 *     - 1 <= n <= 100
 *     - grid[i][j] is 0 or 1
 *
 * Hints:
 *     - Do a breadth first search to find the shortest path.
 *
 * Template (python3):
 *     class Solution:
 *         def shortestPathBinaryMatrix(self, grid: List[List[int]]) -> int:
 *
 * Hint: BFS from (0,0) with 8 directions, return distance to (n-1,n-1) or -1.
 */

use wasm_libs::*;
use std::collections::VecDeque;

fn solve(grid: &mut Vec<Vec<i32>>) -> i32 {
    let n = grid.len();
    if grid[0][0] == 1 || grid[n - 1][n - 1] == 1 { return -1; }
    if n == 1 { return 1; }
    let dirs: [(i32, i32); 8] = [(-1,-1),(-1,0),(-1,1),(0,-1),(0,1),(1,-1),(1,0),(1,1)];
    let mut queue: VecDeque<(i32, i32, i32)> = VecDeque::new();
    queue.push_back((0, 0, 1));
    grid[0][0] = 1;
    while !queue.is_empty() {
        let (r, c, dist) = queue.pop_front().unwrap();
        for &(dr, dc) in dirs.iter() {
            let nr = r + dr;
            let nc = c + dc;
            if nr >= 0 && nr < n as i32 && nc >= 0 && nc < n as i32 {
                let (nr, nc) = (nr as usize, nc as usize);
                if grid[nr][nc] == 0 {
                    if nr == n - 1 && nc == n - 1 { return dist + 1; }
                    grid[nr][nc] = 1;
                    queue.push_back((nr as i32, nc as i32, dist + 1));
                }
            }
        }
    }
    -1
}

fn main() {
    let n = read_int();
    let mut grid = Vec::new();
    for _ in 0..n {
        grid.push(read_ints());
    }
    write_int(solve(&mut grid));
    std::process::exit(0);
}
