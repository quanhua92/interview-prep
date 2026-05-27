/**
 * P495: Teemo Attacking [PREMIUM] (Easy)
 * https://leetcode.com/problems/teemo-attacking/
 * Topics: Array, Simulation
 *
 * Our hero Teemo is attacking an enemy Ashe with poison attacks! When Teemo attacks Ashe, Ashe gets poisoned for a exactly duration seconds.
 * You are given a non-decreasing integer array timeSeries, and an integer duration.
 * Return the total number of seconds that Ashe is poisoned.
 *
 * Example 1:
 *     Input: timeSeries = [1,4], duration = 2
 *     Output: 4
 *
 * Example 2:
 *     Input: timeSeries = [1,2], duration = 2
 *     Output: 3
 */

import { readInts, readInt, writeInt } from '../../wasm_libs/js/io.mjs';

function solve(timeSeries, duration) {
  if (timeSeries.length === 0) return 0;
  let total = 0;
  for (let i = 0; i < timeSeries.length - 1; i++) {
    total += Math.min(duration, timeSeries[i + 1] - timeSeries[i]);
  }
  return total + duration;
}

const timeSeries = readInts();
const duration = readInt();
writeInt(solve(timeSeries, duration));
