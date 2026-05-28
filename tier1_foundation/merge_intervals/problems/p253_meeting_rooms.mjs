/**
 * P253: Meeting Rooms II (Medium)
 * https://leetcode.com/problems/meeting-rooms-ii/
 * Topics: Array, Two Pointers, Sorting, Heap (Priority Queue), Prefix Sum
 *
 * Given an array of meeting time intervals intervals where intervals[i] = [starti, endi], return the minimum number of conference rooms required.
 *
 * Example 1:
 *     Input: intervals = [[0,30],[5,10],[15,20]]
 *     Output: 2
 *
 * Example 2:
 *     Input: intervals = [[7,10],[2,4]]
 *     Output: 1
 *
 * Hint: Sort start and end times separately, then use two pointers to count concurrent meetings.
 */

import { readInts, readInt, writeInt } from '../../wasm_libs/js/io.mjs';

function solve(intervals) {
    throw new Error("NotImplementedError");
}

const n = readInt();
const intervals = [];
for (let i = 0; i < n; i++) {
  intervals.push(readInts());
}
writeInt(solve(intervals));
