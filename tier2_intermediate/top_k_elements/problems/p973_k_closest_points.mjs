/**
 * P973: K Closest Points to Origin (Medium)
 * https://leetcode.com/problems/k-closest-points-to-origin/
 * Topics: Array, Math, Divide and Conquer, Geometry, Sorting, Heap (Priority Queue), Quickselect
 *
 * Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane and an integer k, return the k closest points to the origin (0, 0).
 * The distance between two points on the X-Y plane is the Euclidean distance (i.e., √(x1 - x2)2 + (y1 - y2)2).
 * You may return the answer in any order. The answer is guaranteed to be unique (except for the order that it is in).
 *
 * Example 1:
 *     Input: points = [[1,3],[-2,2]], k = 1
 *     Output: [[-2,2]]
 *     Explanation:
 *     The distance between (1, 3) and the origin is sqrt(10).
 *     The distance between (-2, 2) and the origin is sqrt(8).
 *     Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
 *     We only want the closest k = 1 points from the origin, so the answer is just [[-2,2]].
 *
 * Example 2:
 *     Input: points = [[3,3],[5,-1],[-2,4]], k = 2
 *     Output: [[3,3],[-2,4]]
 *     Explanation: The answer [[-2,4],[3,3]] would also be accepted.
 *
 * Constraints:
 *     - 1 <= k <= points.length <= 104
 *     - -104 <= xi, yi <= 104
 *
 * Template (python3):
 *     class Solution:
 *         def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
 *
 * Hint: Use a max-heap of size k keyed by negative distance squared.
 */

function solve(points, k) {
  throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [[[1, 3], [-2, 2]], 1], expected: [[-2, 2]] },
  { label: "example 2 (sorted)", input: [[[3, 3], [5, -1], [-2, 4]], 2], expected: [[-2, 4], [3, 3]] },
  { label: "origin itself", input: [[[0, 0]], 1], expected: [[0, 0]] },
  { label: "tie on distance", input: [[[1, 0], [0, 1], [2, 0]], 2], expected: [[0, 1], [1, 0]] },
  { label: "negative coords", input: [[[-1, -1], [2, 2], [3, 3]], 1], expected: [[-1, -1]] },
  { label: "two tied closest", input: [[[1, 0], [0, 1], [2, 0]], 2], expected: [[0, 1], [1, 0]] },
  { label: "all same point", input: [[[1, 1], [1, 1], [1, 1]], 2], expected: [[1, 1], [1, 1]] },
  { label: "origin is closest", input: [[[3, 4], [0, 0], [1, 1]], 1], expected: [[0, 0]] },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(...t.input);
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
