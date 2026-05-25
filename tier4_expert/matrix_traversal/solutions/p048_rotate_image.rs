/*
 * P48: Rotate Image (Medium)
 * https://leetcode.com/problems/rotate-image/
 * Topics: Array, Math, Matrix
 *
 * You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).
 * You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.
 *
 * Example 1:
 *     Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
 *     Output: [[7,4,1],[8,5,2],[9,6,3]]
 *
 * Example 2:
 *     Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
 *     Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
 *
 * Constraints:
 *     - n == matrix.length == matrix[i].length
 *     - 1 <= n <= 20
 *     - -1000 <= matrix[i][j] <= 1000
 *
 * Template (python3):
 *     class Solution:
 *         def rotate(self, matrix: List[List[int]]) -> None:
 *             \'\'\'
 *             Do not return anything, modify matrix in-place instead.
 *             \'\'\'
 *
 * Hint: Transpose the matrix first, then reverse each row.
 */


use std::process::exit;

fn rotate(matrix: &mut [Vec<i32>])
{
    let n = matrix.len();
    for i in 0..n {
        for j in i + 1..n {
            let t = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = t;
        }
    }
    for row in matrix.iter_mut() {
        row.reverse();
    }
}

struct MatTC {
    label: &'static str,
    input: Vec<Vec<i32>>,
    expected: Vec<Vec<i32>>,
}

fn main()
{
    let tests: Vec<MatTC> = vec![
        MatTC { label: "example 1", input: vec![vec![1,2,3],vec![4,5,6],vec![7,8,9]], expected: vec![vec![7,4,1],vec![8,5,2],vec![9,6,3]] },
        MatTC { label: "example 2", input: vec![vec![5,1,9,11],vec![2,4,8,10],vec![13,3,6,7],vec![15,14,12,16]], expected: vec![vec![15,13,2,5],vec![14,3,4,1],vec![12,6,8,9],vec![16,7,10,11]] },
        MatTC { label: "single element", input: vec![vec![1]], expected: vec![vec![1]] },
        MatTC { label: "2x2 matrix", input: vec![vec![1,2],vec![3,4]], expected: vec![vec![3,1],vec![4,2]] },
        MatTC { label: "negative values", input: vec![vec![-1,-2,-3],vec![-4,-5,-6],vec![-7,-8,-9]], expected: vec![vec![-7,-4,-1],vec![-8,-5,-2],vec![-9,-6,-3]] },
    ];

    println!("\n============================================================");
    println!("  48. Rotate Image");
    println!("============================================================");
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let mut work = tc.input.clone();
        rotate(&mut work);
        let ok = work == tc.expected;
        if ok {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");

    if passed == tests.len() { exit(0); } else { exit(1); }
}
