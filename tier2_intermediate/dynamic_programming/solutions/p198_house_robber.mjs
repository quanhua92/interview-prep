/**
 * P198: House Robber (Medium)
 * https://leetcode.com/problems/house-robber/
 * Topics: Array, Dynamic Programming
 *
 * You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and it will automatically contact the police if two adjacent houses were broken into on the same night.
 * Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.
 *
 * Example 1:
 *     Input: nums = [1,2,3,1]
 *     Output: 4
 *     Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
 *     Total amount you can rob = 1 + 3 = 4.
 *
 * Example 2:
 *     Input: nums = [2,7,9,3,1]
 *     Output: 12
 *     Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
 *     Total amount you can rob = 2 + 9 + 1 = 12.
 *
 * Constraints:
 *     - 1 <= nums.length <= 100
 *     - 0 <= nums[i] <= 400
 *
 * Template (python3):
 *     class Solution:
 *         def rob(self, nums: List[int]) -> int:
 *
 * Hint: Use two variables (prev, curr) -- for each house decide to rob or skip.
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../wasm_libs/js/io.mjs';

function solve(nums) {
  let prev = 0, curr = 0;
  for (const num of nums) {
    const temp = curr;
    curr = Math.max(curr, prev + num);
    prev = temp;
  }
  return curr;
}

const nums = readInts();
writeInt(solve(nums));
