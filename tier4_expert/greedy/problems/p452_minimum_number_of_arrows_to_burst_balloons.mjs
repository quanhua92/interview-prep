/**
 * P452: Minimum Number of Arrows to Burst Balloons [PREMIUM] (Medium)
 * https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/
 * Topics: Array, Greedy, Sorting
 *
 * Given the array points, return the minimum number of arrows that must be shot to burst all balloons.
 */

import { readInt, readInts, readLine, writeInt } from "src/wasm_libs/js/io.mjs";

function solve(points) {
  throw new Error("NotImplementedError");
}

readInt(); // cols (not needed)
const points = [];
for (let line = readLine(); line; line = readLine()) {
  const row = line.trim().split(/\s+/).map(Number);
  if (row.length >= 2) points.push(row);
}
writeInt(solve(points));
