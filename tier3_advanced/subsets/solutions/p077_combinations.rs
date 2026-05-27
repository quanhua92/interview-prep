/*
 * P77: Combinations (Medium)
 * https://leetcode.com/problems/combinations/
 * Topics: Backtracking
 *
 * Given two integers n and k, return all possible combinations of k numbers chosen from the range [1, n].
 * You may return the answer in any order.
 *
 * Example 1:
 *     Input: n = 4, k = 2
 *     Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
 *
 * Example 2:
 *     Input: n = 1, k = 1
 *     Output: [[1]]
 *
 * Constraints:
 *     - 1 <= n <= 20
 *     - 1 <= k <= n
 *
 * Hint: Use backtracking with a start index to generate all k-length combinations from 1..n.
 */

use wasm_libs::*;

fn combine(n: i32, k: i32) -> Vec<Vec<i32>> {
    let mut res: Vec<Vec<i32>> = Vec::new();
    let mut path: Vec<i32> = Vec::new();
    fn backtrack(start: i32, n: i32, k: i32, path: &mut Vec<i32>, res: &mut Vec<Vec<i32>>) {
        if path.len() == k as usize {
            res.push(path.clone());
            return;
        }
        for i in start..=n {
            path.push(i);
            backtrack(i + 1, n, k, path, res);
            path.pop();
        }
    }
    backtrack(1, n, k, &mut path, &mut res);
    res
}

fn main() {
    let n = read_int();
    let k = read_int();
    let result = combine(n, k);
    for row in &result {
        write_ints(row);
    }
    std::process::exit(0);
}
