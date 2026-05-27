/**
 * P565: Array Nesting [PREMIUM] (Medium)
 * https://leetcode.com/problems/array-nesting/
 * Topics: Array, Depth-First Search
 */

import { readInts, writeInt } from '../../../wasm_libs/js/io.mjs';

function solve(nums) {
  let maxLen = 0;
  const visited = new Array(nums.length).fill(false);
  for (let i = 0; i < nums.length; i++) {
    if (!visited[i]) {
      let count = 0;
      let j = i;
      while (!visited[j]) {
        visited[j] = true;
        j = nums[j];
        count++;
      }
      if (count > maxLen) maxLen = count;
    }
  }
  return maxLen;
}

const nums = readInts();
writeInt(solve(nums));
