/*
 * P994: Rotting Oranges (Medium)
 * https://leetcode.com/problems/rotting-oranges/
 * Topics: Array, Breadth-First Search, Matrix
 *
 * You are given an m x n grid where each cell can have one of three values:
 * Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.
 * Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.
 *
 * Example 1:
 *     Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
 *     Output: 4
 *
 * Example 2:
 *     Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
 *     Output: -1
 *     Explanation: The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.
 *
 * Example 3:
 *     Input: grid = [[0,2]]
 *     Output: 0
 *     Explanation: Since there are already no fresh oranges at minute 0, the answer is just 0.
 *
 * Constraints:
 *     - m == grid.length
 *     - n == grid[i].length
 *     - 1 <= m, n <= 10
 *     - grid[i][j] is 0, 1, or 2.
 *
 * Template (python3):
 *     class Solution:
 *         def orangesRotting(self, grid: List[List[int]]) -> int:
 *
 * Hint: Use BFS starting from all rotten oranges simultaneously.
 */


use std::collections::VecDeque;

fn oranges_rotting(grid: &mut Vec<Vec<i32>>) -> i32 {
    let rows = grid.len();
    let cols = grid[0].len();
    let mut queue: VecDeque<(usize, usize)> = VecDeque::new();
    let mut fresh = 0i32;
    for r in 0..rows {
        for c in 0..cols {
            if grid[r][c] == 2 {
                queue.push_back((r, c));
            } else if grid[r][c] == 1 {
                fresh += 1;
            }
        }
    }
    if fresh == 0 {
        return 0;
    }
    let dirs: [(i32, i32); 4] = [(0, 1), (0, -1), (1, 0), (-1, 0)];
    let mut minutes = 0i32;
    while !queue.is_empty() {
        let sz = queue.len();
        for _ in 0..sz {
            let (r, c) = queue.pop_front().unwrap();
            for (dr, dc) in dirs.iter() {
                let nr = r as i32 + dr;
                let nc = c as i32 + dc;
                if nr >= 0 && nr < rows as i32 && nc >= 0 && nc < cols as i32 {
                    let (nr, nc) = (nr as usize, nc as usize);
                    if grid[nr][nc] == 1 {
                        grid[nr][nc] = 2;
                        fresh -= 1;
                        queue.push_back((nr, nc));
                    }
                }
            }
        }
        if !queue.is_empty() {
            minutes += 1;
        }
    }
    if fresh == 0 { minutes } else { -1 }
}

fn main() {
    let tests: Vec<(&str, Vec<Vec<i32>>, i32)> = vec![
        ("example 1", vec![vec![2,1,1], vec![1,1,0], vec![0,1,1]], 4),
        ("example 2", vec![vec![2,1,1], vec![0,1,1], vec![1,0,1]], -1),
        ("no fresh", vec![vec![0,2]], 0),
        ("single fresh no rotten", vec![vec![1]], -1),
        ("single rotten", vec![vec![2]], 0),
        ("all fresh no rotten", vec![vec![1,1,1], vec![1,1,1], vec![1,1,1]], -1),
        ("multiple rotten sources", vec![vec![2,2], vec![1,1], vec![0,1]], 2),
    ];
    let mut passed = 0;
    for (i, (label, grid, expected)) in tests.iter().enumerate() {
        let mut g = grid.clone();
        let got = oranges_rotting(&mut g);
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
