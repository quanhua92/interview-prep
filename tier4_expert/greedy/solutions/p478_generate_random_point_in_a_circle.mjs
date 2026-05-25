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
 *     - 0 < radius <= 108
 *     - -107 <= x_center, y_center <= 107
 *     - At most 3 * 104 calls will be made to randPoint.
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

function solve(radius, xCenter, yCenter, count) {
  const points = [];
  for (let i = 0; i < count; i++) {
    while (true) {
      const x = Math.random() * 2 - 1;
      const y = Math.random() * 2 - 1;
      if (x * x + y * y <= 1) {
        points.push([xCenter + x * radius, yCenter + y * radius]);
        break;
      }
    }
  }
  return points;
}

const tests = [
  { label: "points within unit circle", input: [1.0, 0.0, 0.0, 1000], expected: "in_circle" },
  { label: "points within offset circle", input: [0.5, 1.0, 2.0, 1000], expected: "in_circle" },
  { label: "tiny circle", input: [0.01, 0.0, 0.0, 100], expected: "in_circle" },
  { label: "large offset center", input: [5.0, -100.0, 200.0, 500], expected: "in_circle" },
  { label: "single point", input: [1.0, 0.0, 0.0, 1], expected: "in_circle" },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const [radius, cx, cy, count] = t.input;
  const points = solve(radius, cx, cy, count);
  const inCircle = points.every(
    (p) => (p[0] - cx) ** 2 + (p[1] - cy) ** 2 <= radius * radius + 1e-9
  );
  const ok = inCircle && points.length === count;
  if (ok) {
    passed++;
    console.log(`  Test ${i + 1} (${t.label}): PASS`);
  } else {
    console.log(`  Test ${i + 1} (${t.label}): FAIL`);
    if (!inCircle) console.log("    Some points outside circle!");
    if (points.length !== count) console.log(`    Expected ${count} points, got ${points.length}`);
  }
}
console.log(`\n  ${passed}/${tests.length} passed`);
process.exit(passed === tests.length ? 0 : 1);
