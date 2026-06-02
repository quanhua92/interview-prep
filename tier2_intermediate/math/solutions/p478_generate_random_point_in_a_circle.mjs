/**
 * P478: Generate Random Point in a Circle [PREMIUM] (Medium)
 * https://leetcode.com/problems/generate-random-point-in-a-circle/
 * Topics: Math, Geometry, Rejection Sampling, Randomized
 *
 * Given the radius and the position of the center of a circle, implement the function randPoint which generates a uniform random point inside the circle.
 * Implement the Solution class:
 * Example 1:
 *     Input
 * Example 1:
 *     ["Solution", "randPoint", "randPoint", "randPoint"]
 *     [[1.0, 0.0, 0.0], [], [], []]
 *     Output
 *     [null, [-0.02493, -0.38077], [0.82314, 0.38945], [0.36572, 0.17248]]
 *
 *     Explanation
 *     Solution solution = new Solution(1.0, 0.0, 0.0);
 *     solution.randPoint(); // return [-0.02493, -0.38077]
 *     solution.randPoint(); // return [0.82314, 0.38945]
 *     solution.randPoint(); // return [0.36572, 0.17248]
 *
 * Constraints:
 *     - 0 < radius <= 10^8
 *     - -10^7 <= x_center, y_center <= 10^7
 *     - At most 3 * 10^4 calls will be made to randPoint.
 *
 * Template (python3):
 *     class Solution:
 *
 *         def __init__(self, radius: float, x_center: float, y_center: float):
 *
 *
 *         def randPoint(self) -> List[float]:
 *
 *
 *
 *     # Your Solution object will be instantiated and called as such:
 *     # obj = Solution(radius, x_center, y_center)
 *     # param_1 = obj.randPoint()
 */

import { readLine, readInt } from '../../wasm_libs/js/io.mjs';

const params = readLine().split(/\s+/).map(Number);
const radius = params[0];
const xCenter = params[1];
const yCenter = params[2];
const count = readInt();

const out = [];
for (let i = 0; i < count; i++) {
  while (true) {
    const x = Math.random() * 2 - 1;
    const y = Math.random() * 2 - 1;
    if (x * x + y * y <= 1) {
      out.push(`${xCenter + x * radius} ${yCenter + y * radius}`);
      break;
    }
  }
}
if (typeof Javy !== "undefined" && Javy.IO && Javy.IO.write) {
  Javy.IO.write(out.join("\n") + "\n");
} else {
  console.log(out.join("\n"));
}
