/*
 * P448: Find All Numbers Disappeared in an Array (Easy)
 * https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
 * Topics: Array, Hash Table
 *
 * Given an array nums of n integers where nums[i] is in the range [1, n], return an array of all the integers in the range [1, n] that do not appear in nums.
 *
 * Example 1:
 *     Input: nums = [4,3,2,7,8,2,3,1]
 *     Output: [5,6]
 *
 * Example 2:
 *     Input: nums = [1,1]
 *     Output: [2]
 *
 * Constraints:
 *     - n == nums.length
 *     - 1 <= n <= 105
 *     - 1 <= nums[i] <= n
 *
 * Hint: Negate the value at index abs(n)-1 for each number. Indices with positive values are missing.
 */

use wasm_libs::*;

impl Solution {
    fn find_disappeared_numbers(nums: &mut [i32]) -> Vec<i32> {
        todo!()
    }
}

struct Solution;

fn main() {
    let mut nums = read_ints();
    let result = Solution::find_disappeared_numbers(&mut nums);
    write_ints(&result);
    std::process::exit(0);
}
