/*
 * P907: Sum of Subarray Minimums (Medium)
 * https://leetcode.com/problems/sum-of-subarray-minimums/
 * Topics: Array, Dynamic Programming, Stack, Monotonic Stack
 *
 * Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous) subarray of arr. Since the answer may be large, return the answer modulo 10^9 + 7.
 *
 * Example 1:
 *     Input: arr = [3,1,2,4]
 *     Output: 17
 *     Explanation:
 *     Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4].
 *     Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.
 *     Sum is 17.
 *
 * Example 2:
 *     Input: arr = [11,81,94,43,3]
 *     Output: 444
 *
 * Constraints:
 *     - 1 <= arr.length <= 3 * 10^4
 *     - 1 <= arr[i] <= 3 * 10^4
 *
 * Template (python3):
 *     class Solution:
 *         def sumSubarrayMins(self, arr: List[int]) -> int:
 *
 * Hint: Use a monotonic stack to find the number of subarrays where each element is the minimum.
 */

use wasm_libs::*;

const MOD: i64 = 1_000_000_007;

impl Solution {
    fn sum_subarray_mins(arr: &[i32]) -> i32 {
    todo!();
}
}

struct Solution;

fn main() {
    let arr = read_ints();
    write_int(Solution::sum_subarray_mins(&arr));
    std::process::exit(0);
}
