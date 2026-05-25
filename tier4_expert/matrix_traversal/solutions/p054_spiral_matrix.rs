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


use std::process::exit;

fn spiral_order(matrix: &Vec<Vec<i32>>) -> Vec<i32>
{
    if matrix.is_empty() || matrix[0].is_empty() {
        return vec![];
    }
    let m = matrix.len();
    let n = matrix[0].len();
    let mut result = Vec::with_capacity(m * n);
    let (mut top, mut bottom) = (0, m - 1);
    let (mut left, mut right) = (0, n - 1);

    while top <= bottom && left <= right {
        for c in left..=right {
            result.push(matrix[top][c]);
        }
        top += 1;
        for r in top..=bottom {
            result.push(matrix[r][right]);
        }
        if right > 0 { right -= 1; } else { break; }
        if top <= bottom {
            for c in (left..=right).rev() {
                result.push(matrix[bottom][c]);
            }
            bottom -= 1;
        }
        if left <= right {
            for r in (top..=bottom).rev() {
                result.push(matrix[r][left]);
            }
            left += 1;
        }
    }
    result
}

struct SpirTC {
    label: &'static str,
    input: Vec<Vec<i32>>,
    expected: Vec<i32>,
}

fn main()
{
    let tests: Vec<SpirTC> = vec![
        SpirTC { label: "example 1", input: vec![vec![1,2,3],vec![4,5,6],vec![7,8,9]], expected: vec![1,2,3,6,9,8,7,4,5] },
        SpirTC { label: "example 2", input: vec![vec![1,2,3,4],vec![5,6,7,8],vec![9,10,11,12]], expected: vec![1,2,3,4,8,12,11,10,9,5,6,7] },
        SpirTC { label: "single element", input: vec![vec![7]], expected: vec![7] },
        SpirTC { label: "single row", input: vec![vec![1,2,3,4]], expected: vec![1,2,3,4] },
        SpirTC { label: "single column", input: vec![vec![1],vec![2],vec![3],vec![4]], expected: vec![1,2,3,4] },
        SpirTC { label: "2x2 matrix", input: vec![vec![1,2],vec![3,4]], expected: vec![1,2,4,3] },
        SpirTC { label: "2 rows many columns", input: vec![vec![1,2,3,4,5],vec![6,7,8,9,10]], expected: vec![1,2,3,4,5,10,9,8,7,6] },
    ];

    println!("\n============================================================");
    println!("  54. Spiral Matrix");
    println!("============================================================");
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = spiral_order(&tc.input);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {:?}", tc.expected);
            println!("    Got:      {:?}", got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");

    if passed == tests.len() { exit(0); } else { exit(1); }
}
