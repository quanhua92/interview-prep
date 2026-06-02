/*
 * P498: Diagonal Traverse (Medium)
 * https://leetcode.com/problems/diagonal-traverse/
 * Topics: Array, Matrix, Simulation
 *
 * Given an m x n matrix mat, return an array of all the elements of the array in a diagonal order.
 *
 * Example 1:
 *     Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
 *     Output: [1,2,4,7,5,3,6,8,9]
 *
 * Example 2:
 *     Input: mat = [[1,2],[3,4]]
 *     Output: [1,2,3,4]
 *
 * Constraints:
 *     - m == mat.length
 *     - n == mat[i].length
 *     - 1 <= m, n <= 10^4
 *     - 1 <= m * n <= 10^4
 *     - -10^5 <= mat[i][j] <= 10^5
 *
 * Template (python3):
 *     class Solution:
 *         def findDiagonalOrder(self, mat: List[List[int]]) -> List[int]:
 *
 * Hint: Group by i+j diagonal index. If d is even, reverse to simulate up-right direction.
 */

use wasm_libs::*;
use std::io::{self, BufRead};

fn find_diagonal_order(mat: &Vec<Vec<i32>>) -> Vec<i32>
{
    if mat.is_empty() || mat[0].is_empty() {
        return vec![];
    }
    let m = mat.len();
    let n = mat[0].len();
    let mut result = Vec::with_capacity(m * n);

    for d in 0..(m + n - 1) {
        let mut diag = Vec::new();
        let (mut r, mut c): (usize, i32) = if d < n {
            (0, d as i32)
        } else {
            (d - n + 1, (n - 1) as i32)
        };
        while r < m && c >= 0 && (c as usize) < n {
            diag.push(mat[r][c as usize]);
            r += 1;
            c -= 1;
        }
        if d % 2 == 0 {
            diag.reverse();
        }
        result.extend(&diag);
    }
    result
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

fn main()
{
    let mat = read_int_matrix();
    let result = find_diagonal_order(&mat);
    write_ints(&result);
}
