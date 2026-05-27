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

use interview_prep::{read_ints, write_ints, write_string};

fn subsets(nums: Vec<i32>) -> Vec<Vec<i32>> {
    let mut result: Vec<Vec<i32>> = Vec::new();
    let mut path: Vec<i32> = Vec::new();

    fn bt(nums: &[i32], start: usize, path: &mut Vec<i32>, result: &mut Vec<Vec<i32>>) {
        result.push(path.clone());
        for i in start..nums.len() {
            path.push(nums[i]);
            bt(nums, i + 1, path, result);
            path.pop();
        }
    }

    bt(&nums, 0, &mut path, &mut result);
    result
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
