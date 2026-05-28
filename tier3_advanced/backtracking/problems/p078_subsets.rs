/*
 * P78: Subsets (Medium)
 * https://leetcode.com/problems/subsets/
 * Topics: Array, Backtracking, Bit Manipulation
 *
 * Given an integer array nums of unique elements, return all possible subsets (the power set).
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 *
 * Example 1:
 *     Input: nums = [1,2,3]
 *     Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
 *
 * Hint: Use backtracking to generate all possible subsets by including/excluding each element.
 */

use wasm_libs::*;

fn subsets(nums: Vec<i32>) -> Vec<Vec<i32>> {
    todo!()
}

fn main() {
    let nums = read_ints();
    let result = subsets(nums);
    for s in result {
        if s.is_empty() {
            write_string("");
        } else {
            write_ints(&s);
        }
    }
}
