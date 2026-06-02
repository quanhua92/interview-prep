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
 *     - 1 <= n <= 2 * 10^5
 *     - -10^9 <= nums[i] <= 10^9
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../../wasm_libs/js/io.mjs';

function solve(nums) {
  let third = -Infinity;
  const stack = [];
  for (let i = nums.length - 1; i >= 0; i--) {
    const num = nums[i];
    if (num < third) return true;
    while (stack.length > 0 && stack[stack.length - 1] < num) {
      third = stack.pop();
    }
    stack.push(num);
  }
  return false;
}

const nums = readInts();
writeBool(solve(nums));
