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
 *     - 1 <= m, n <= 104
 *     - 1 <= m * n <= 104
 *     - mat[i][j] is either 0 or 1.
 *     - There is at least one 0 in mat.
 * 
 * Template (python3):
 *     class Solution:
 *         def updateMatrix(self, mat: List[List[int]]) -> List[List[int]]:
 */
use std::collections::VecDeque;
use std::process::exit;

fn update_matrix(mat: &Vec<Vec<i32>>) -> Vec<Vec<i32>>
{
    todo!()
}

struct MatDistTC {
    label: &'static str,
    input: Vec<Vec<i32>>,
    expected: Vec<Vec<i32>>,
}

fn main()
{
    let tests: Vec<MatDistTC> = vec![
        MatDistTC { label: "example 1", input: vec![vec![0,0,0],vec![0,1,0],vec![0,0,0]], expected: vec![vec![0,0,0],vec![0,1,0],vec![0,0,0]] },
        MatDistTC { label: "example 2", input: vec![vec![0,0,0],vec![0,1,0],vec![1,1,1]], expected: vec![vec![0,0,0],vec![0,1,0],vec![1,2,1]] },
        MatDistTC { label: "single zero", input: vec![vec![0]], expected: vec![vec![0]] },
        MatDistTC { label: "single column", input: vec![vec![1],vec![0],vec![1]], expected: vec![vec![1],vec![0],vec![1]] },
        MatDistTC { label: "single row", input: vec![vec![0,1,1,1]], expected: vec![vec![0,1,2,3]] },
        MatDistTC { label: "cross of ones around center zero", input: vec![vec![1,1,1],vec![1,0,1],vec![1,1,1]], expected: vec![vec![2,1,2],vec![1,0,1],vec![2,1,2]] },
        MatDistTC { label: "corner zeros", input: vec![vec![1,1,0],vec![1,1,1],vec![0,1,1]], expected: vec![vec![2,1,0],vec![1,2,1],vec![0,1,2]] },
    ];

    println!("\n============================================================");
    println!("  542. 01 Matrix");
    println!("============================================================");
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = update_matrix(&tc.input);
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
