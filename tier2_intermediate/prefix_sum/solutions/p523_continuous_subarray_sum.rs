/*
 * P523: Continuous Subarray Sum [PREMIUM] (Medium)
 * https://leetcode.com/problems/continuous-subarray-sum/
 * Topics: Array, Hash Table, Math, Prefix Sum
 *
 * Given an integer array nums and an integer k, return true if nums has a good subarray or false otherwise.
 * A good subarray is a subarray where:
 * Note that:
 * Example 1:
 *     Input: nums = [23,2,4,6,7], k = 6
 *     Output: true
 *     Explanation: [2, 4] is a continuous subarray of size 2 whose elements sum up to 6.
 *
 * Example 2:
 *     Input: nums = [23,2,6,4,7], k = 6
 *     Output: true
 *     Explanation: [23, 2, 6, 4, 7] is an continuous subarray of size 5 whose elements sum up to 42.
 *     42 is a multiple of 6 because 42 = 7 * 6 and 7 is an integer.
 *
 * Example 3:
 *     Input: nums = [23,2,6,4,7], k = 13
 *     Output: false
 *
 * Constraints:
 *     - 1 <= nums.length <= 105
 *     - 0 <= nums[i] <= 109
 *     - 0 <= sum(nums[i]) <= 231 - 1
 *     - 1 <= k <= 231 - 1
 *
 * Template (python3):
 *     class Solution:
 *         def checkSubarraySum(self, nums: List[int], k: int) -> bool:
 */

use std::collections::HashMap;
use rstest::TestCase;
use rstest::run_tests;

fn check_subarray_sum(nums: &[i32], k: i32) -> Vec<i32> {
    let mut mod_index: HashMap<i32, i32> = HashMap::new();
    mod_index.insert(0, -1);
    let mut prefix = 0i32;
    for i in 0..nums.len() {
        prefix = (prefix + nums[i]) % k;
        if let Some(&idx) = mod_index.get(&prefix) {
            if (i as i32 - idx) > 1 {
                return vec![1];
            }
        } else {
            mod_index.insert(prefix, i as i32);
        }
    }
    vec![0]
}

fn main() {
    let tests: &[TestCase] = &[
        TestCase { label: "example 1", input_arr: &[23, 2, 4, 6, 7], target: 6, expected: &[1] },
        TestCase { label: "example 2", input_arr: &[23, 2, 6, 4, 7], target: 6, expected: &[1] },
        TestCase { label: "example 3", input_arr: &[23, 2, 6, 4, 7], target: 13, expected: &[0] },
        TestCase { label: "two zeros sum to 0", input_arr: &[5, 0, 0], target: 3, expected: &[1] },
        TestCase { label: "no valid subarray", input_arr: &[1, 2], target: 4, expected: &[0] },
        TestCase { label: "two zeros always valid", input_arr: &[0, 0], target: 1, expected: &[1] },
    ];
    std::process::exit(run_tests!("523. Continuous Subarray Sum", check_subarray_sum, tests));
}
