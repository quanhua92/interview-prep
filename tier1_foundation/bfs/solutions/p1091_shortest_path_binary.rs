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


use std::collections::VecDeque;

fn shortest_path_binary_matrix(grid: &mut Vec<Vec<i32>>) -> i32 {
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
    let tests: Vec<(&str, Vec<Vec<i32>>, i32)> = vec![
        ("example 1", vec![vec![0,1],vec![1,0]], 2),
        ("example 2", vec![vec![0,0,0],vec![1,1,0],vec![1,1,0]], 4),
        ("blocked", vec![vec![1,0],vec![0,1]], -1),
        ("single cell", vec![vec![0]], 1),
        ("3x3 all open (diagonal)", vec![vec![0,0,0],vec![0,0,0],vec![0,0,0]], 3),
        ("2x2 all open (diagonal)", vec![vec![0,0],vec![0,0]], 2),
        ("3x3 only corners open", vec![vec![0,1,1],vec![1,1,1],vec![1,1,0]], -1),
    ];
    let mut passed = 0;
    for (i, (label, grid, expected)) in tests.iter().enumerate() {
        let mut g = grid.clone();
        let got = shortest_path_binary_matrix(&mut g);
        if got == *expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, label);
            println!("    Expected: {}", expected);
            println!("    Got:      {}", got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
