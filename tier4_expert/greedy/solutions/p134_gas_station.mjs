/**
 * P134: Gas Station (Medium)
 * https://leetcode.com/problems/gas-station/
 * Topics: Array, Greedy
 *
 * There are n gas stations along a circular route, where the amount of gas at the ith station is gas[i].
 * You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from the ith station to its next (i + 1)th station. You begin the journey with an empty tank at one of the gas stations.
 * Given two integer arrays gas and cost, return the starting gas station's index if you can travel around the circuit once in the clockwise direction, otherwise return -1. If there exists a solution, it is guaranteed to be unique.
 *
 * Example 1:
 *     Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
 *     Output: 3
 *
 * Example 2:
 *     Input: gas = [2,3,4], cost = [3,4,3]
 *     Output: -1
 *
 * Constraints:
 *     - n == gas.length == cost.length
 *     - 1 <= n <= 105
 *     - 0 <= gas[i], cost[i] <= 104
 *     - The input is generated such that the answer is unique.
 *
 * Template (python3):
 *     class Solution:
 *         def canCompleteCircuit(self, gas: List[int], cost: List[int]) -> int:
 *
 * Hint: Track total_surplus and current_surplus. If current_surplus < 0, reset start to next station.
 */

import { readInts, writeInt } from "src/wasm_libs/js/io.mjs";

function solve(gas, cost) {
  let totalSurplus = 0;
  let currentSurplus = 0;
  let start = 0;

  for (let i = 0; i < gas.length; i++) {
    totalSurplus += gas[i] - cost[i];
    currentSurplus += gas[i] - cost[i];
    if (currentSurplus < 0) {
      start = i + 1;
      currentSurplus = 0;
    }
  }

  return totalSurplus >= 0 ? start : -1;
}

const gas = readInts();
const cost = readInts();
writeInt(solve(gas, cost));
