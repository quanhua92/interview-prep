/**
 * P491: Non-decreasing Subsequences [PREMIUM] (Medium)
 * https://leetcode.com/problems/non-decreasing-subsequences/
 * Topics: Array, Hash Table, Backtracking, Bit Manipulation
 *
 * Given an integer array nums, return all the different possible non-decreasing subsequences of the given array with at least two elements.
 * Example 1:
 *     Input: nums = [4,6,7,7]
 *     Output: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]
 *
 * Example 2:
 *     Input: nums = [4,4,3,2,1]
 *     Output: [[4,4]]
 *
 * Template (python3):
 *     class Solution:
 *         def findSubsequences(self, nums: List[int]) -> List[List[int]]:
 */

import { readInts, writeInts } from '../../../wasm_libs/js/io.mjs';

function solve(nums) {
  const result = [];

  function backtrack(start, path) {
    if (path.length >= 2) {
      result.push([...path]);
    }
    const used = new Set();
    for (let i = start; i < nums.length; i++) {
      if (used.has(nums[i])) continue;
      if (path.length === 0 || nums[i] >= path[path.length - 1]) {
        used.add(nums[i]);
        path.push(nums[i]);
        backtrack(i + 1, path);
        path.pop();
      }
    }
  }

  backtrack(0, []);
  return result.sort((a, b) => {
    for (let i = 0; i < Math.min(a.length, b.length); i++) {
      if (a[i] !== b[i]) return a[i] - b[i];
    }
    return a.length - b.length;
  });
}

const nums = readInts();
const result = solve(nums);
for (const seq of result) {
  writeInts(seq);
}
