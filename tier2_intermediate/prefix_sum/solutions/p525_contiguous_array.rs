/*
 * P525: Contiguous Array [PREMIUM] (Medium)
 * https://leetcode.com/problems/contiguous-array/
 * Topics: Array, Hash Table, Prefix Sum
 *
 * Given a binary array nums, return the maximum length of a contiguous subarray with an equal number of 0 and 1.
 * Example 1:
 *     Input: nums = [0,1]
 *     Output: 2
 *     Explanation: [0, 1] is the longest contiguous subarray with an equal number of 0 and 1.
 *
 * Example 2:
 *     Input: nums = [0,1,0]
 *     Output: 2
 *     Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.
 *
 * Example 3:
 *     Input: nums = [0,1,1,1,1,1,0,0,0]
 *     Output: 6
 *     Explanation: [1,1,1,0,0,0] is the longest contiguous subarray with equal number of 0 and 1.
 *
 * Constraints:
 *     - 1 <= nums.length <= 105
 *     - nums[i] is either 0 or 1.
 *
 * Template (python3):
 *     class Solution:
 *         def findMaxLength(self, nums: List[int]) -> int:
 */

use std::collections::HashMap;
use rstest::TestCase;
use rstest::run_tests;

fn find_max_length(nums: &[i32], _target: i32) -> Vec<i32> {
    let mut first: HashMap<i32, i32> = HashMap::new();
    first.insert(0, -1);
    let mut max_len = 0;
    let mut count = 0i32;
    for i in 0..nums.len() {
        count += if nums[i] == 1 { 1 } else { -1 };
        if let Some(&idx) = first.get(&count) {
            let len = (i as i32 - idx) as i32;
            if len > max_len {
                max_len = len;
            }
        } else {
            first.insert(count, i as i32);
        }
    }
    vec![max_len]
}

fn main() {
    let tests: &[TestCase] = &[
        TestCase { label: "example 1", input_arr: &[0, 1], target: 0, expected: &[2] },
        TestCase { label: "example 2", input_arr: &[0, 1, 0], target: 0, expected: &[2] },
        TestCase { label: "example 3", input_arr: &[0, 1, 1, 1, 1, 1, 0, 0, 0], target: 0, expected: &[6] },
        TestCase { label: "single element", input_arr: &[1], target: 0, expected: &[0] },
        TestCase { label: "balanced halves", input_arr: &[0, 0, 0, 0, 1, 1, 1, 1], target: 0, expected: &[8] },
        TestCase { label: "middle balanced", input_arr: &[0, 0, 1, 0, 0, 0, 1, 1], target: 0, expected: &[6] },
    ];
    std::process::exit(run_tests!("525. Contiguous Array", find_max_length, tests));
}
