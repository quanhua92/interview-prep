/**
 * P78: Subsets (Medium)
 * https://leetcode.com/problems/subsets/
 * Topics: Array, Backtracking, Bit Manipulation
 *
 * Given an integer array nums of unique elements, return all possible subsets (the power set).
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 *
 * Example 1:
 *     Input: nums = [1,2,3]
 *     Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
 *
 * Hint: Use backtracking to generate all possible subsets by including/excluding each element.
 */

import { readInts, writeInts, writeString } from '../../../wasm_libs/js/io.mjs';

function solve(nums) {
    throw new Error("NotImplementedError");
}

const nums = readInts();
const result = solve(nums);
for (const s of result) {
  if (s.length > 0) {
    writeInts(s);
  } else {
    writeString("");
  }
}
