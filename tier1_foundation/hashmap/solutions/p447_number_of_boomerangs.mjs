/**
 * P447: Number of Boomerangs [PREMIUM] (Medium)
 * https://leetcode.com/problems/number-of-boomerangs/
 * Topics: Array, Hash Table, Math
 *
 * You are given n points in the plane that are all distinct, where points[i] = [xi, yi]. A boomerang is a tuple of points (i, j, k) such that the distance between i and j equals the distance between i and k (the order of the tuple matters).
 * Return the number of boomerangs.
 * Example 1:
 *     Input: points = [[0,0],[1,0],[2,0]]
 *     Output: 2
 *     Explanation: The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]].
 *
 * Example 2:
 *     Input: points = [[1,1],[2,2],[3,3]]
 *     Output: 2
 *
 * Example 3:
 *     Input: points = [[1,1]]
 *     Output: 0
 *
 * Constraints:
 *     - n == points.length
 *     - 1 <= n <= 500
 *     - points[i].length == 2
 *     - -10^4 <= xi, yi <= 10^4
 *     - All the points are unique.
 */

import { readInt, readInts, writeInt } from '../../wasm_libs/js/io.mjs';

function solve(points) {
  let result = 0;
  for (let i = 0; i < points.length; i++) {
    const p = points[i];
    const distCount = new Map();
    for (let j = 0; j < points.length; j++) {
      if (i === j) continue;
      const q = points[j];
      const dx = p[0] - q[0];
      const dy = p[1] - q[1];
      const dist = dx * dx + dy * dy;
      distCount.set(dist, (distCount.get(dist) || 0) + 1);
    }
    for (const count of distCount.values()) {
      result += count * (count - 1);
    }
  }
  return result;
}

const n = readInt();
const points = [];
for (let i = 0; i < n; i++) {
  points.push(readInts());
}
writeInt(solve(points));
