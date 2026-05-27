/*
 * P169: Majority Element (Easy)
 * https://leetcode.com/problems/majority-element/
 * Topics: Array, Hash Table, Divide and Conquer, Sorting, Counting
 *
 * Given an array nums of size n, return the majority element.
 * The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.
 *
 * Example 1:
 *     Input: nums = [3,2,3]
 *     Output: 3
 *
 * Example 2:
 *     Input: nums = [2,2,1,1,1,2,2]
 *     Output: 2
 *
 * Constraints:
 *     - n == nums.length
 *     - 1 <= n <= 5 * 104
 *     - -109 <= nums[i] <= 109
 *
 * Hint: Use Boyer-Moore voting algorithm — maintain a candidate and count.
 */

use wasm_libs::*;

impl Solution {
    fn majority_element(nums: &[i32]) -> i32 {
        let mut candidate = nums[0];
        let mut count = 1i32;
        for i in 1..nums.len() {
            if count == 0 {
                candidate = nums[i];
                count = 1;
            } else if nums[i] == candidate {
                count += 1;
            } else {
                count -= 1;
            }
        }
        candidate
    }
}

struct Solution;

fn main() {
    let nums = read_ints();
    write_int(Solution::majority_element(&nums));
    std::process::exit(0);
}
