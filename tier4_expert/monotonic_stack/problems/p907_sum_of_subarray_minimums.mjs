/**
 * P907: Sum of Subarray Minimums (Medium)
 * https://leetcode.com/problems/sum-of-subarray-minimums/
 * Topics: Array, Dynamic Programming, Stack, Monotonic Stack
 *
 * Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous) subarray of arr. Since the answer may be large, return the answer modulo 109 + 7.
 *
 * Example 1:
 *     Input: arr = [3,1,2,4]
 *     Output: 17
 *
 * Example 2:
 *     Input: arr = [11,81,94,43,3]
 *     Output: 444
 *
 * Constraints:
 *     - 1 <= arr.length <= 3 * 104
 *     - 1 <= arr[i] <= 3 * 104
 *
 * Hint: Use a monotonic stack to find the number of subarrays where each element is the minimum.
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../../wasm_libs/js/io.mjs';

function solve(arr) {
  throw new Error("NotImplementedError");
}

const arr = readInts();
writeInt(solve(arr));
