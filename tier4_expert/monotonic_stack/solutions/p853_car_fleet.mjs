/**
 * P853: Car Fleet (Medium)
 * https://leetcode.com/problems/car-fleet/
 * Topics: Array, Stack, Sorting, Monotonic Stack
 *
 * There are n cars at given miles away from the starting mile 0, traveling to reach the mile target.
 * You are given two integer arrays position and speed, both of length n, where position[i] is the starting mile of the ith car and speed[i] is the speed of the ith car in miles per hour.
 * A car cannot pass another car, but it can catch up and then travel next to it at the speed of the slower car.
 * Return the number of car fleets that will arrive at the destination.
 *
 * Example 1:
 *     Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
 *     Output: 3
 *
 * Example 2:
 *     Input: target = 10, position = [3], speed = [3]
 *     Output: 1
 *
 * Example 3:
 *     Input: target = 100, position = [0,2,4], speed = [4,2,1]
 *     Output: 1
 *
 * Hint: Sort by position desc, calculate time to target. A car forms a new fleet only if it arrives before the current fleet.
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../../wasm_libs/js/io.mjs';

function solve(target, position, speed) {
  const cars = position.map((p, i) => [p, speed[i]]);
  cars.sort((a, b) => b[0] - a[0]);
  let fleets = 0;
  let slowestTime = -1;
  for (const [pos, spd] of cars) {
    const time = (target - pos) / spd;
    if (time > slowestTime) {
      fleets++;
      slowestTime = time;
    }
  }
  return fleets;
}

const target = readInt();
const position = readInts();
const speed = readInts();
writeInt(solve(target, position, speed));
