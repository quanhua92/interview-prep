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
 *     - 1 <= m, n <= 104
 *     - 1 <= m * n <= 104
 *     - -105 <= mat[i][j] <= 105
 * 
 * Template (python3):
 *     class Solution:
 *         def findDiagonalOrder(self, mat: List[List[int]]) -> List[int]:
 * 
 * Hint: Group by i+j diagonal index. If d is even, reverse to simulate up-right direction.
 */
use std::process::exit;

fn find_diagonal_order(mat: &Vec<Vec<i32>>) -> Vec<i32>
{
    todo!()
}

struct DiagTC {
    label: &'static str,
    input: Vec<Vec<i32>>,
    expected: Vec<i32>,
}

fn main()
{
    let tests: Vec<DiagTC> = vec![
        DiagTC { label: "example 1", input: vec![vec![1,2,3],vec![4,5,6],vec![7,8,9]], expected: vec![1,2,4,7,5,3,6,8,9] },
        DiagTC { label: "example 2", input: vec![vec![1,2],vec![3,4],vec![5,6]], expected: vec![1,2,3,5,4,6] },
        DiagTC { label: "single element", input: vec![vec![1]], expected: vec![1] },
        DiagTC { label: "single row", input: vec![vec![1,2,3,4]], expected: vec![1,2,3,4] },
        DiagTC { label: "single column", input: vec![vec![1],vec![2],vec![3],vec![4]], expected: vec![1,2,3,4] },
        DiagTC { label: "2x4 rectangular", input: vec![vec![1,2,3,4],vec![5,6,7,8]], expected: vec![1,2,5,6,3,4,7,8] },
        DiagTC { label: "negative values 2x2", input: vec![vec![-1,-2],vec![3,4]], expected: vec![-1,-2,3,4] },
    ];

    println!("\n============================================================");
    println!("  498. Diagonal Traverse");
    println!("============================================================");
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = find_diagonal_order(&tc.input);
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
