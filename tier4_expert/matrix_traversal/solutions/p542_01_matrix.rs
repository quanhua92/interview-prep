/*
 * P542: 01 Matrix [PREMIUM] (Medium)
 * https://leetcode.com/problems/01-matrix/
 * Topics: Array, Dynamic Programming, Breadth-First Search, Matrix
 *
 * Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.
 * The distance between two cells sharing a common edge is 1.
 * Example 2:
 * Note: This question is the same as 1765: https://leetcode.com/problems/map-of-highest-peak/
 * Example 1:
 *     Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
 *     Output: [[0,0,0],[0,1,0],[0,0,0]]
 *
 * Example 2:
 *     Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
 *     Output: [[0,0,0],[0,1,0],[1,2,1]]
 *
 * Constraints:
 *     - m == mat.length
 *     - n == mat[i].length
 *     - 1 <= m, n <= 10^4
 *     - 1 <= m * n <= 10^4
 *     - mat[i][j] is either 0 or 1.
 *     - There is at least one 0 in mat.
 *
 * Template (python3):
 *     class Solution:
 *         def updateMatrix(self, mat: List[List[int]]) -> List[List[int]]:
 */

use std::collections::VecDeque;
use wasm_libs::*;
use std::io::{self, BufRead};

fn update_matrix(mat: &Vec<Vec<i32>>) -> Vec<Vec<i32>>
{
    if mat.is_empty() || mat[0].is_empty() {
        return vec![];
    }
    let m = mat.len();
    let n = mat[0].len();
    let mut dist = vec![vec![-1; n]; m];
    let mut queue = VecDeque::new();

    for i in 0..m {
        for j in 0..n {
            if mat[i][j] == 0 {
                dist[i][j] = 0;
                queue.push_back((i, j));
            }
        }
    }

    let dirs: [(i32, i32); 4] = [(-1, 0), (1, 0), (0, -1), (0, 1)];

    while let Some((r, c)) = queue.pop_front() {
        let r = r as i32;
        let c = c as i32;
        for (dr, dc) in &dirs {
            let nr = r + dr;
            let nc = c + dc;
            if nr >= 0 && nr < m as i32 && nc >= 0 && nc < n as i32 {
                let nr = nr as usize;
                let nc = nc as usize;
                if dist[nr][nc] == -1 {
                    dist[nr][nc] = dist[r as usize][c as usize] + 1;
                    queue.push_back((nr, nc));
                }
            }
        }
    }
    dist
}

fn read_int_matrix() -> Vec<Vec<i32>> {
    let _cols = read_int();
    let stdin = io::stdin();
    let lines: Vec<String> = stdin.lock().lines().map(|l| l.unwrap()).collect();
    lines.iter()
        .filter(|l| !l.trim().is_empty())
        .map(|l| l.split_whitespace().map(|s| s.parse().unwrap()).collect())
        .collect()
}

fn write_matrix(mat: &[Vec<i32>]) {
    for row in mat {
        write_ints(row);
    }
}

fn main()
{
    let mat = read_int_matrix();
    let result = update_matrix(&mat);
    write_matrix(&result);
}
