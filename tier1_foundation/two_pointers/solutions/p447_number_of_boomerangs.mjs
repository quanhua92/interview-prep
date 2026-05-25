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
 *     - -104 <= xi, yi <= 104
 *     - All the points are unique.
 */

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

// --- tests ---
const tests = [
  { label: "example 1", input: [[[0, 0], [1, 0], [2, 0]]], expected: 2 },
  { label: "example 2", input: [[[1, 1], [2, 2], [3, 3]]], expected: 2 },
  { label: "example 3", input: [[[1, 1]]], expected: 0 },
  { label: "only 2 points", input: [[[0, 0], [1, 0]]], expected: 0 },
  { label: "square 4 points", input: [[[0, 0], [0, 1], [1, 0], [1, 1]]], expected: 8 },
  { label: "isoceles triangle", input: [[[0, 0], [1, 1], [1, -1]]], expected: 2 },
  { label: "isoceles different heights", input: [[[0, 0], [3, 4], [3, -4]]], expected: 2 },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(t.input[0]);
  if (JSON.stringify(got) === JSON.stringify(t.expected)) {
    passed++;
    console.log(`  Test ${i + 1} (${t.label}): PASS`);
  } else {
    console.log(`  Test ${i + 1} (${t.label}): FAIL`);
    console.log(`    Expected: ${JSON.stringify(t.expected)}\n    Got:      ${JSON.stringify(got)}`);
  }
}
console.log(`\n  ${passed}/${tests.length} passed`);
process.exit(passed === tests.length ? 0 : 1);
