/**
 * P480: Sliding Window Median (Hard)
 * https://leetcode.com/problems/sliding-window-median/
 * Topics: Array, Hash Table, Sliding Window, Heap (Priority Queue)
 *
 * You are given an integer array nums and an integer k. There is a sliding window of size k.
 * Return the median array for each window.
 *
 * Constraints:
 *     - 1 <= k <= nums.length <= 105
 *     - -231 <= nums[i] <= 231 - 1
 *
 * Hint: Use a max-heap for the small half and a min-heap for the large half with lazy deletion.
 */

import { readInts, readInt } from '../../wasm_libs/js/io.mjs';

function solve(nums, k) {
  throw new Error("NotImplementedError");
}

const nums = readInts();
const k = readInt();
const result = solve(nums, k);
for (const m of result) {
  console.log(m);
}
