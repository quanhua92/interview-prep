/**
 * P84: Largest Rectangle in Histogram (Hard)
 * https://leetcode.com/problems/largest-rectangle-in-histogram/
 * Topics: Array, Stack, Monotonic Stack
 *
 * Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.
 *
 * Example 1:
 *     Input: heights = [2,1,5,6,2,3]
 *     Output: 10
 *
 * Example 2:
 *     Input: heights = [2,4]
 *     Output: 4
 *
 * Constraints:
 *     - 1 <= heights.length <= 105
 *     - 0 <= heights[i] <= 104
 *
 * Hint: Use a monotonic increasing stack with a sentinel to compute max rectangle area.
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../../wasm_libs/js/io.mjs';

function solve(heights) {
  throw new Error("NotImplementedError");
}

const heights = readInts();
writeInt(solve(heights));
