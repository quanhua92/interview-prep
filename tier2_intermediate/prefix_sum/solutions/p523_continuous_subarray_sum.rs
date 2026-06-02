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
 *     - 1 <= nums.length <= 10^5
 *     - 0 <= nums[i] <= 10^9
 *     - 0 <= sum(nums[i]) <= 2^31 - 1
 *     - 1 <= k <= 2^31 - 1
 *
 * Template (python3):
 *     class Solution:
 *         def checkSubarraySum(self, nums: List[int], k: int) -> bool:
 */

use std::collections::HashMap;
use wasm_libs::*;

fn check_subarray_sum(nums: &[i32], k: i32) -> bool {
    let mut mod_index: HashMap<i32, i32> = HashMap::new();
    mod_index.insert(0, -1);
    let mut prefix = 0i32;
    for i in 0..nums.len() {
        prefix = (prefix + nums[i]) % k;
        if let Some(&idx) = mod_index.get(&prefix) {
            if (i as i32 - idx) > 1 {
                return true;
            }
        } else {
            mod_index.insert(prefix, i as i32);
        }
    }
    false
}

fn main() {
    let nums = read_ints();
    let k = read_int();
    write_bool(check_subarray_sum(&nums, k));
    std::process::exit(0);
}
