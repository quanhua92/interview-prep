/**
 * P739: Daily Temperatures (Medium)
 * https://leetcode.com/problems/daily-temperatures/
 * Topics: Array, Stack, Monotonic Stack
 *
 * Given an array of integers temperatures represents the daily temperatures, return an array answer such that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature. If there is no future day for which this is possible, keep answer[i] == 0 instead.
 *
 * Example 1:
 *     Input: temperatures = [73,74,75,71,69,72,76,73]
 *     Output: [1,1,4,2,1,1,0,0]
 *
 * Example 2:
 *     Input: temperatures = [30,40,50,60]
 *     Output: [1,1,1,0]
 *
 * Example 3:
 *     Input: temperatures = [30,60,90]
 *     Output: [1,1,0]
 *
 * Constraints:
 *     - 1 <= temperatures.length <= 105
 *     - 30 <= temperatures[i] <= 100
 *
 * Hint: Use a monotonic decreasing stack to track indices of warmer days.
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../../wasm_libs/js/io.mjs';

function solve(temperatures) {
  const n = temperatures.length;
  const answer = new Array(n).fill(0);
  const stack = [];
  for (let i = 0; i < n; i++) {
    while (stack.length > 0 && temperatures[i] > temperatures[stack[stack.length - 1]]) {
      const j = stack.pop();
      answer[j] = i - j;
    }
    stack.push(i);
  }
  return answer;
}

const temperatures = readInts();
writeInts(solve(temperatures));
