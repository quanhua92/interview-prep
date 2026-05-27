/*
 * P410: Split Array Largest Sum (Hard)
 * https://leetcode.com/problems/split-array-largest-sum/
 * Topics: Array, Binary Search, Dynamic Programming, Greedy, Prefix Sum
 *
 * Given an integer array nums and an integer k, split nums into k non-empty subarrays such that the largest sum of any subarray is minimized.
 * Return the minimized largest sum of the split.
 * A subarray is a contiguous part of the array.
 *
 * Example 1:
 *     Input: nums = [7,2,5,10,8], k = 2
 *     Output: 18
 *     Explanation: There are four ways to split nums into two subarrays.
 *     The best way is to split it into [7,2,5] and [10,8], where the largest sum among the two subarrays is only 18.
 *
 * Example 2:
 *     Input: nums = [1,2,3,4,5], k = 2
 *     Output: 9
 *     Explanation: There are four ways to split nums into two subarrays.
 *     The best way is to split it into [1,2,3] and [4,5], where the largest sum among the two subarrays is only 9.
 *
 * Constraints:
 *     - 1 <= nums.length <= 1000
 *     - 0 <= nums[i] <= 106
 *     - 1 <= k <= min(50, nums.length)
 *
 * Template (python3):
 *     class Solution:
 *         def splitArray(self, nums: List[int], k: int) -> int:
 *
 * Hint: Binary search the answer in [max(nums), sum(nums)] and check feasibility greedily.
 */

use wasm_libs::*;

fn feasible(nums: &[i32], max_sum: i64, k: i32) -> bool {
    let mut count = 1;
    let mut current: i64 = 0;
    for &v in nums {
        current += v as i64;
        if current > max_sum {
            count += 1;
            current = v as i64;
            if count > k {
                return false;
            }
        }
    }
    true
}

fn split_array(nums: &[i32], k: i32) -> i64 {
    let left = *nums.iter().max().unwrap() as i64;
    let right: i64 = nums.iter().map(|&v| v as i64).sum();
    let mut left = left;
    let mut right = right;
    while left < right {
        let mid = left + (right - left) / 2;
        if feasible(nums, mid, k) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    left
}

fn main() {
    let nums = read_ints();
    let k = read_int();
    write_int(split_array(&nums, k) as i32);
    std::process::exit(0);
}
