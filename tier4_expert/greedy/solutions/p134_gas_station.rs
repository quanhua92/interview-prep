/*
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

use wasm_libs::*;

fn can_complete_circuit(gas: &[i32], cost: &[i32]) -> i32 {
    let mut total_surplus = 0i32;
    let mut current_surplus = 0i32;
    let mut start = 0i32;
    for i in 0..gas.len() {
        let diff = gas[i] - cost[i];
        total_surplus += diff;
        current_surplus += diff;
        if current_surplus < 0 {
            start = (i + 1) as i32;
            current_surplus = 0;
        }
    }
    if total_surplus >= 0 { start } else { -1 }
}

fn main() {
    let gas = read_ints();
    let cost = read_ints();
    let result = can_complete_circuit(&gas, &cost);
    write_int(result);
}
