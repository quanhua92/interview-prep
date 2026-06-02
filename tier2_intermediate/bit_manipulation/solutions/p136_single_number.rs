/*
 * P136: Single Number (Easy)
 * https://leetcode.com/problems/single-number/
 * Topics: Array, Bit Manipulation
 *
 * Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.
 * You must implement a solution with a linear runtime complexity and use only constant extra space.
 *
 * Example 1:
 *     Input: nums = [2,2,1]
 *     Output: 1
 *
 * Example 2:
 *     Input: nums = [4,1,2,1,2]
 *     Output: 4
 *
 * Example 3:
 *     Input: nums = [1]
 *     Output: 1
 *
 * Constraints:
 *     - 1 <= nums.length <= 3 * 10^4
 *     - -3 * 10^4 <= nums[i] <= 3 * 10^4
 *     - Each element in the array appears twice except for one element which appears only once.
 *
 * Hints:
 *     - Think about the XOR (^) operator's property.
 *
 * Template (python3):
 *     class Solution:
 *         def singleNumber(self, nums: List[int]) -> int:
 *
 * Hint: XOR all numbers — pairs cancel out, leaving the single number.
 */

use wasm_libs::*;

fn single_number(nums: &[i32]) -> i32 {
    let mut result = 0;
    for &num in nums {
        result ^= num;
    }
    result
}

fn main() {
    let nums = read_ints();
    let result = single_number(&nums);
    write_int(result);
    std::process::exit(0);
}
