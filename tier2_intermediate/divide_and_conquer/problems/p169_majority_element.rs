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
 * Hint: Use Boyer-Moore voting algorithm — maintain a candidate and count.
 */

use wasm_libs::*;

impl Solution {
    fn majority_element(nums: &[i32]) -> i32 {
        todo!()
    }
}

struct Solution;

fn main() {
    let nums = read_ints();
    write_int(Solution::majority_element(&nums));
    std::process::exit(0);
}
