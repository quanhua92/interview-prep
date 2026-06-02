/**
 * P391: Perfect Rectangle [PREMIUM] (Hard)
 * https://leetcode.com/problems/perfect-rectangle/
 * Topics: Array, Hash Table, Math, Geometry, Line Sweep
 *
 * Given an array rectangles where rectangles[i] = [xi, yi, ai, bi] represents an axis-aligned rectangle. The bottom-left point of the rectangle is (xi, yi) and the top-right point of it is (ai, bi).
 * Return true if all the rectangles together form an exact cover of a rectangular region.
 * Example 1:
 *     Input: rectangles = [[1,1,3,3],[3,1,4,2],[3,2,4,4],[1,3,2,4],[2,3,3,4]]
 *     Output: true
 *     Explanation: All 5 rectangles together form an exact cover of a rectangular region.
 *
 * Example 2:
 *     Input: rectangles = [[1,1,2,3],[1,3,2,4],[3,1,4,2],[3,2,4,4]]
 *     Output: false
 *     Explanation: Because there is a gap between the two rectangular regions.
 *
 * Example 3:
 *     Input: rectangles = [[1,1,3,3],[3,1,4,2],[1,3,2,4],[2,2,4,4]]
 *     Output: false
 *     Explanation: Because two of the rectangles overlap with each other.
 *
 * Constraints:
 *     - 1 <= rectangles.length <= 2 * 10^4
 *     - rectangles[i].length == 4
 *     - -10^5 <= xi < ai <= 10^5
 *     - -10^5 <= yi < bi <= 10^5
 *
 * Template (python3):
 *     class Solution:
 *         def isRectangleCover(self, rectangles: List[List[int]]) -> bool:
 */

import { readInts, readInt, writeBool } from '../../wasm_libs/js/io.mjs';

function solve(rectangles) {
  const corners = new Set();
  let totalArea = 0;
  let minX = Infinity, minY = Infinity;
  let maxX = -Infinity, maxY = -Infinity;
  for (const [x1, y1, x2, y2] of rectangles) {
    minX = Math.min(minX, x1);
    minY = Math.min(minY, y1);
    maxX = Math.max(maxX, x2);
    maxY = Math.max(maxY, y2);
    totalArea += (x2 - x1) * (y2 - y1);
    for (const corner of [[x1, y1], [x1, y2], [x2, y1], [x2, y2]]) {
      const key = `${corner[0]},${corner[1]}`;
      if (corners.has(key)) {
        corners.delete(key);
      } else {
        corners.add(key);
      }
    }
  }
  if (corners.size !== 4) return false;
  const expectedCorners = new Set([
    `${minX},${minY}`, `${minX},${maxY}`, `${maxX},${minY}`, `${maxX},${maxY}`
  ]);
  for (const c of corners) {
    if (!expectedCorners.has(c)) return false;
  }
  return totalArea === (maxX - minX) * (maxY - minY);
}

const n = readInt();
const rectangles = [];
for (let i = 0; i < n; i++) {
  rectangles.push(readInts());
}
writeBool(solve(rectangles));
