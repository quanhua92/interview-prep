/*
 * P54: Spiral Matrix (Medium)
 * https://leetcode.com/problems/spiral-matrix/
 * Topics: Array, Matrix, Simulation
 *
 * Given an m x n matrix, return all elements of the matrix in spiral order.
 *
 * Example 1:
 *     Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
 *     Output: [1,2,3,6,9,8,7,4,5]
 *
 * Example 2:
 *     Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
 *     Output: [1,2,3,4,8,12,11,10,9,5,6,7]
 *
 * Constraints:
 *     - m == matrix.length
 *     - n == matrix[i].length
 *     - 1 <= m, n <= 10
 *     - -100 <= matrix[i][j] <= 100
 *
 * Hints:
 *     - Well for some problems, the best way really is to come up with some algorithms for simulation. Basically, you need to simulate what the problem asks us to do.
 *     - We go boundary by boundary and move inwards. That is the essential operation. First row, last column, last row, first column, and then we move inwards by 1 and repeat. That's all. That is all the simulation that we need.
 *     - Think about when you want to switch the progress on one of the indexes. If you progress on i out of [i, j], you'll shift in the same column. Similarly, by changing values for j, you'd be shifting in the same row.
 * Also, keep track of the end of a boundary so that you can move inwards and then keep repeating. It's always best to simulate edge cases like a single column or a single row to see if anything breaks or not.
 *
 * Template (python3):
 *     class Solution:
 *         def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
 *
 * Hint: Use four boundary pointers (top, bottom, left, right) and shrink them as you traverse.
 */


use wasm_libs::*;
use std::io::{self, BufRead};

fn spiral_order(matrix: &Vec<Vec<i32>>) -> Vec<i32>
{
    if matrix.is_empty() || matrix[0].is_empty() {
        return vec![];
    }
    let m = matrix.len();
    let n = matrix[0].len();
    let mut result = Vec::with_capacity(m * n);
    let (mut top, mut bottom) = (0isize, (m - 1) as isize);
    let (mut left, mut right) = (0isize, (n - 1) as isize);

    while top <= bottom && left <= right {
        for c in left..=right {
            result.push(matrix[top as usize][c as usize]);
        }
        top += 1;
        for r in top..=bottom {
            result.push(matrix[r as usize][right as usize]);
        }
        right -= 1;
        if top <= bottom {
            for c in (left..=right).rev() {
                result.push(matrix[bottom as usize][c as usize]);
            }
            bottom -= 1;
        }
        if left <= right {
            for r in (top..=bottom).rev() {
                result.push(matrix[r as usize][left as usize]);
            }
            left += 1;
        }
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
    let matrix = read_int_matrix();
    let result = spiral_order(&matrix);
    write_ints(&result);
}
