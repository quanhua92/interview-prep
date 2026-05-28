/*
 * P90: Subsets II (Medium)
 * https://leetcode.com/problems/subsets-ii/
 * Topics: Array, Backtracking, Bit Manipulation
 *
 * Given an integer array nums that may contain duplicates, return all possible subsets (the power set).
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 *
 * Example 1:
 *     Input: nums = [1,2,2]
 *     Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
 *
 * Example 2:
 *     Input: nums = [0]
 *     Output: [[],[0]]
 *
 * Constraints:
 *     - 1 <= nums.length <= 10
 *     - -10 <= nums[i] <= 10
 *
 * Hint: Sort first, then skip duplicates at the same recursion level during backtracking.
 */

use wasm_libs::*;

fn subsets_with_dup(mut nums: Vec<i32>) -> Vec<Vec<i32>> {
    todo!()
}

fn main() {
    let nums = read_ints();
    let result = subsets_with_dup(nums);
    for row in &result {
        write_ints(row);
    }
    std::process::exit(0);
}
