/**
 * P456: 132 Pattern [PREMIUM] (Medium)
 * https://leetcode.com/problems/132-pattern/
 * Topics: Array, Binary Search, Stack, Monotonic Stack, Ordered Set
 *
 * Given an array of n integers nums, a 132 pattern is a subsequence of three integers nums[i], nums[j] and nums[k] such that i < j < k and nums[i] < nums[k] < nums[j].
 * Return true if there is a 132 pattern in nums, otherwise, return false.
 * Example 1:
 *     Input: nums = [1,2,3,4]
 *     Output: false
 *
 * Example 2:
 *     Input: nums = [3,1,4,2]
 *     Output: true
 *
 * Example 3:
 *     Input: nums = [-1,3,2,0]
 *     Output: true
 *
 * Constraints:
 *     - n == nums.length
 *     - 1 <= n <= 2 * 105
 *     - -109 <= nums[i] <= 109
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../../wasm_libs/js/io.mjs';

function solve(nums) {
  throw new Error("NotImplementedError");
}

const nums = readInts();
writeBool(solve(nums));
