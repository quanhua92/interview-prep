/*
 * P576: Out of Boundary Paths [PREMIUM] (Medium)
 * https://leetcode.com/problems/out-of-boundary-paths/
 * Topics: Dynamic Programming
 *
 * There is an m x n grid with a ball. The ball is initially at the position [startRow, startColumn]. You are allowed to move the ball to one of the four adjacent cells in the grid (possibly out of the grid crossing the grid boundary). You can apply at most maxMove moves to the ball.
 * Given the five integers m, n, maxMove, startRow, startColumn, return the number of paths to move the ball out of the grid boundary. Since the answer can be very large, return it modulo 109 + 7.
 * Example 1:
 *     Input: m = 2, n = 2, maxMove = 2, startRow = 0, startColumn = 0
 *     Output: 6
 *
 * Example 2:
 *     Input: m = 1, n = 3, maxMove = 3, startRow = 0, startColumn = 1
 *     Output: 12
 *
 * Constraints:
 *     - 1 <= m, n <= 50
 *     - 0 <= maxMove <= 50
 *     - 0 <= startRow < m
 *     - 0 <= startColumn < n
 *
 * Hint: Is traversing every path feasible? There are many possible paths for a small matrix. Try to optimize it.
 * Hint: Can we use some space to store the number of paths and update them after every move?
 * Hint: One obvious thing: the ball will go out of the boundary only by crossing it. Also, there is only one possible way the ball can go out of the boundary from the boundary cell except for corner cells. From the corner cell, the ball can go out in two different ways.
 *
 * Can you use this thing to solve the problem?
 *
 * Template (python3):
 *     class Solution:
 *         def findPaths(self, m: int, n: int, maxMove: int, startRow: int, startColumn: int) -> int:
 */

use wasm_libs::*;

impl Solution {
    fn find_paths(m: i32, n: i32, max_move: i32, start_row: i32, start_column: i32) -> i32 {
        let m = m as usize;
    let n = n as usize;
    let mm = max_move as usize;
    let mod_val = 1_000_000_007i64;
    let dirs: [(i32, i32); 4] = [(-1, 0), (1, 0), (0, -1), (0, 1)];
    let mut dp = vec![0i64; m * n];
    let mut nxt = vec![0i64; m * n];
    dp[start_row as usize * n + start_column as usize] = 1;
    let mut result: i64 = 0;
    for _move in 0..mm {
        for v in nxt.iter_mut() { *v = 0; }
        for r in 0..m {
            for c in 0..n {
                let val = dp[r * n + c];
                if val == 0 { continue; }
                for &(dr, dc) in &dirs {
                    let nr = r as i32 + dr;
                    let nc = c as i32 + dc;
                    if nr >= 0 && nr < m as i32 && nc >= 0 && nc < n as i32 {
                        nxt[nr as usize * n + nc as usize] = (nxt[nr as usize * n + nc as usize] + val) % mod_val;
                    } else {
                        result = (result + val) % mod_val;
                    }
                }
            }
        }
        std::mem::swap(&mut dp, &mut nxt);
    }
    result as i32
    }
}

struct Solution;

fn main() {
    let m = read_int();
    let n = read_int();
    let mm = read_int();
    let sr = read_int();
    let sc = read_int();
    write_int(find_paths(m, n, mm, sr, sc));
}
