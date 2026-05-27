/**
 * P448: Find All Numbers Disappeared in an Array (Easy)
 * https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
 * Topics: Array, Hash Table
 *
 * Given an array nums of n integers where nums[i] is in the range [1, n], return an array of all the integers in the range [1, n] that do not appear in nums.
 *
 * Example 1:
 *     Input: nums = [4,3,2,7,8,2,3,1]
 *     Output: [5,6]
 *
 * Example 2:
 *     Input: nums = [1,1]
 *     Output: [2]
 *
 * Constraints:
 *     - n == nums.length
 *     - 1 <= n <= 105
 *     - 1 <= nums[i] <= n
 *
 * Hint: Negate the value at index abs(n)-1 for each number. Indices with positive values are missing.
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../wasm_libs/js/io.mjs';

function solve(nums) {
  for (const n of nums) {
    const index = Math.abs(n) - 1;
    if (nums[index] > 0) {
      nums[index] = -nums[index];
    }
  }
  const result = [];
  for (let i = 0; i < nums.length; i++) {
    if (nums[i] > 0) result.push(i + 1);
  }
  return result;
}

const nums = readInts();
writeInts(solve(nums));
