/*
 * P46: Permutations (Medium)
 * https://leetcode.com/problems/permutations/
 * Topics: Array, Backtracking
 *
 * Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.
 *
 * Example 1:
 *     Input: nums = [1,2,3]
 *     Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 *
 * Example 2:
 *     Input: nums = [0,1]
 *     Output: [[0,1],[1,0]]
 *
 * Example 3:
 *     Input: nums = [1]
 *     Output: [[1]]
 *
 * Constraints:
 *     - 1 <= nums.length <= 6
 *     - -10 <= nums[i] <= 10
 *     - All the integers of nums are unique.
 *
 * Hint: Use backtracking with swapping to generate all permutations in-place.
 */

use wasm_libs::*;

fn permute(mut nums: Vec<i32>) -> Vec<Vec<i32>> {
    let mut res: Vec<Vec<i32>> = Vec::new();
    fn backtrack(nums: &mut Vec<i32>, first: usize, res: &mut Vec<Vec<i32>>) {
        if first == nums.len() {
            res.push(nums.clone());
            return;
        }
        for i in first..nums.len() {
            nums.swap(first, i);
            backtrack(nums, first + 1, res);
            nums.swap(first, i);
        }
    }
    backtrack(&mut nums, 0, &mut res);
    res.sort();
    res
}

fn main() {
    let nums = read_ints();
    let result = permute(nums);
    for row in &result {
        write_ints(row);
    }
    std::process::exit(0);
}
