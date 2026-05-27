/**
 * P57: Insert Interval (Medium)
 * https://leetcode.com/problems/insert-interval/
 * Topics: Array
 *
 * You are given an array of non-overlapping intervals intervals where intervals[i] = [starti, endi] represent the start and the end of the ith interval and intervals is sorted in ascending order by starti. You are also given an interval newInterval = [start, end] that represents the start and end of another interval.
 * Insert newInterval into intervals such that intervals is still sorted in ascending order by starti and intervals still does not have any overlapping intervals (merge overlapping intervals if necessary).
 * Return intervals after the insertion.
 *
 * Hint: Add non-overlapping before, merge overlapping, add non-overlapping after.
 */

import { readInts, readInt, writeInts } from '../../wasm_libs/js/io.mjs';

function solve(intervals, newInterval) {
  throw new Error("NotImplementedError");
}

const n = readInt();
const intervals = [];
for (let i = 0; i < n; i++) {
  intervals.push(readInts());
}
const newInterval = readInts();
const result = solve(intervals, newInterval);
for (const row of result) {
  writeInts(row);
}
