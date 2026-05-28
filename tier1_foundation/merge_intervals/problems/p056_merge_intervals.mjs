/**
 * P56: Merge Intervals (Medium)
 * https://leetcode.com/problems/merge-intervals/
 * Topics: Array, Sorting
 *
 * Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.
 *
 * Example 1:
 *     Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
 *     Output: [[1,6],[8,10],[15,18]]
 *     Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].
 *
 * Example 2:
 *     Input: intervals = [[1,4],[4,5]]
 *     Output: [[1,5]]
 *     Explanation: Intervals [1,4] and [4,5] are considered overlapping.
 *
 * Constraints:
 *     - 1 <= intervals.length <= 104
 *     - intervals[i].length == 2
 *     - 0 <= starti <= endi <= 104
 *
 * Hint: Sort intervals by start time, then merge overlapping ones.
 */

import { readInts, readInt, writeInts } from '../../wasm_libs/js/io.mjs';

function solve(intervals) {
    throw new Error("NotImplementedError");
}

const n = readInt();
const intervals = [];
for (let i = 0; i < n; i++) {
  intervals.push(readInts());
}
const result = solve(intervals);
for (const row of result) {
  writeInts(row);
}
