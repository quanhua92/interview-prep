/*
 * P713: Subarray Product Less Than K (Medium)
 * https://leetcode.com/problems/subarray-product-less-than-k/
 * Topics: Array, Binary Search, Sliding Window, Prefix Sum
 *
 * Given an array of integers nums and an integer k, return the number of contiguous subarrays where the product of all the elements in the subarray is strictly less than k.
 *
 * Example 1:
 *     Input: nums = [10,5,2,6], k = 100
 *     Output: 8
 *     Explanation: The 8 subarrays that have product less than 100 are:
 *     [10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6]
 *     Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.
 *
 * Example 2:
 *     Input: nums = [1,2,3], k = 0
 *     Output: 0
 *
 * Constraints:
 *     - 1 <= nums.length <= 3 * 104
 *     - 1 <= nums[i] <= 1000
 *     - 0 <= k <= 106
 *
 * Hints:
 *     - For each j, let opt(j) be the smallest i so that nums[i] * nums[i+1] * ... * nums[j] is less than k.  opt is an increasing function.
 *
 * Template (python3):
 *     class Solution:
 *         def numSubarrayProductLessThanK(self, nums: List[int], k: int) -> int:
 *
 * Hint: Use a sliding window where you shrink from the left when product >= k.
 */

use wasm_libs::*;

impl Solution {
    fn num_subarray_product_less_than_k(nums: &[i32], k: i32) -> i32 {
        todo!()
    }
}

struct Solution;

fn main() {
    let nums = read_ints();
    let k = read_int();
    let result = Solution::num_subarray_product_less_than_k(&nums, k);
    write_int(result);
    std::process::exit(0);
}
