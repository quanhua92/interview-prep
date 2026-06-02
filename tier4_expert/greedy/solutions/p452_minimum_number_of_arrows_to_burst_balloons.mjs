/**
 * P452: Minimum Number of Arrows to Burst Balloons [PREMIUM] (Medium)
 * https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/
 * Topics: Array, Greedy, Sorting
 *
 * There are some spherical balloons taped onto a flat wall that represents the XY-plane. The balloons are represented as a 2D integer array points where points[i] = [xstart, xend] denotes a balloon whose horizontal diameter stretches between xstart and xend.
 * Given the array points, return the minimum number of arrows that must be shot to burst all balloons.
 *
 * Example 1:
 *     Input: points = [[10,16],[2,8],[1,6],[7,12]]
 *     Output: 2
 *
 * Example 2:
 *     Input: points = [[1,2],[3,4],[5,6],[7,8]]
 *     Output: 4
 *
 * Example 3:
 *     Input: points = [[1,2],[2,3],[3,4],[4,5]]
 *     Output: 2
 *
 * Constraints:
 *     - 1 <= points.length <= 10^5
 *     - points[i].length == 2
 *     - -2^31 <= xstart < xend <= 2^31 - 1
 *
 * Template (python3):
 *     class Solution:
 *         def findMinArrowShots(self, points: List[List[int]]) -> int:
 */

import { readInt, readInts, readLine, writeInt } from "src/wasm_libs/js/io.mjs";

function solve(points) {
  if (points.length === 0) return 0;
  points.sort((a, b) => a[1] - b[1]);
  let arrows = 1;
  let end = points[0][1];
  for (let i = 1; i < points.length; i++) {
    const [start, finish] = points[i];
    if (start > end) {
      arrows++;
      end = finish;
    }
  }
  return arrows;
}

readInt(); // cols (not needed)
const points = [];
for (let line = readLine(); line; line = readLine()) {
  const row = line.trim().split(/\s+/).map(Number);
  if (row.length >= 2) points.push(row);
}
writeInt(solve(points));
