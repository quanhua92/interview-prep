/*
 * P39: Combination Sum (Medium)
 * https://leetcode.com/problems/combination-sum/
 * Topics: Array, Backtracking
 *
 * Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target.
 * The same number may be chosen from candidates an unlimited number of times.
 *
 * Example 1:
 *     Input: candidates = [2,3,6,7], target = 7
 *     Output: [[2,2,3],[7]]
 *
 * Example 2:
 *     Input: candidates = [2,3,5], target = 8
 *     Output: [[2,2,2,2],[2,3,3],[3,5]]
 *
 * Hint: Use backtracking with early pruning when the remaining sum goes negative.
 */

use interview_prep::{read_int, read_ints, write_ints};

fn combination_sum(mut candidates: Vec<i32>, target: i32) -> Vec<Vec<i32>> {
    candidates.sort();
    let mut result: Vec<Vec<i32>> = Vec::new();
    let mut path: Vec<i32> = Vec::new();

    fn bt(
        cands: &[i32],
        start: usize,
        rem: i32,
        path: &mut Vec<i32>,
        result: &mut Vec<Vec<i32>>,
    ) {
        if rem == 0 {
            result.push(path.clone());
            return;
        }
        for i in start..cands.len() {
            if cands[i] > rem {
                break;
            }
            path.push(cands[i]);
            bt(cands, i, rem - cands[i], path, result);
            path.pop();
        }
    }

    bt(&candidates, 0, target, &mut path, &mut result);
    result
}

fn main() {
    let candidates = read_ints();
    let target = read_int();
    let result = combination_sum(candidates, target);
    for combo in result {
        write_ints(&combo);
    }
}
