/**
 * P907: Sum of Subarray Minimums (Medium)
 * https://leetcode.com/problems/sum-of-subarray-minimums/
 * Topics: Array, Dynamic Programming, Stack, Monotonic Stack
 *
 * Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous) subarray of arr. Since the answer may be large, return the answer modulo 10^9 + 7.
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
 *     - 1 <= arr.length <= 3 * 10^4
 *     - 1 <= arr[i] <= 3 * 10^4
 *
 * Hint: Use a monotonic stack to find the number of subarrays where each element is the minimum.
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../../wasm_libs/js/io.mjs';

function solve(arr) {
  const MOD = 10 ** 9 + 7;
  const n = arr.length;
  const left = new Array(n).fill(-1);
  const right = new Array(n).fill(n);
  const stack = [];

  for (let i = 0; i < n; i++) {
    while (stack.length > 0 && arr[stack[stack.length - 1]] >= arr[i]) {
      stack.pop();
    }
    left[i] = stack.length > 0 ? stack[stack.length - 1] : -1;
    stack.push(i);
  }

  stack.length = 0;
  for (let i = n - 1; i >= 0; i--) {
    while (stack.length > 0 && arr[stack[stack.length - 1]] > arr[i]) {
      stack.pop();
    }
    right[i] = stack.length > 0 ? stack[stack.length - 1] : n;
    stack.push(i);
  }

  let total = 0;
  for (let i = 0; i < n; i++) {
    const countLeft = i - left[i];
    const countRight = right[i] - i;
    total = (total + arr[i] * countLeft * countRight) % MOD;
  }
  return total;
}

const arr = readInts();
writeInt(solve(arr));
