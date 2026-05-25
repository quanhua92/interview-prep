/**
 * P542: 01 Matrix [PREMIUM] (Medium)
 * https://leetcode.com/problems/01-matrix/
 * Topics: Array, Dynamic Programming, Breadth-First Search, Matrix
 *
 * Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.
 * The distance between two cells sharing a common edge is 1.
 * Example 2:
 * Note: This question is the same as 1765: https://leetcode.com/problems/map-of-highest-peak/
 * Example 1:
 *     Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
 *     Output: [[0,0,0],[0,1,0],[0,0,0]]
 *
 * Example 2:
 *     Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
 *     Output: [[0,0,0],[0,1,0],[1,2,1]]
 *
 * Constraints:
 *     - m == mat.length
 *     - n == mat[i].length
 *     - 1 <= m, n <= 104
 *     - 1 <= m * n <= 104
 *     - mat[i][j] is either 0 or 1.
 *     - There is at least one 0 in mat.
 *
 * Template (python3):
 *     class Solution:
 *         def updateMatrix(self, mat: List[List[int]]) -> List[List[int]]:
 */

function solve(mat) {
  throw new Error("NotImplementedError");
}

const tests = [
  { input: [[0,0,0],[0,1,0],[0,0,0]], expected: [[0,0,0],[0,1,0],[0,0,0]], label: "example 1" },
  { input: [[0,0,0],[0,1,0],[1,1,1]], expected: [[0,0,0],[0,1,0],[1,2,1]], label: "example 2" },
  { input: [[0]], expected: [[0]], label: "single zero" },
  { input: [[1],[0],[1]], expected: [[1],[0],[1]], label: "single column" },
  { input: [[0,1,1,1]], expected: [[0,1,2,3]], label: "single row" },
  { input: [[1,1,1],[1,0,1],[1,1,1]], expected: [[2,1,2],[1,0,1],[2,1,2]], label: "cross of ones around center zero" },
  { input: [[1,1,0],[1,1,1],[0,1,1]], expected: [[2,1,0],[1,2,1],[0,1,2]], label: "corner zeros" },
];

let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(t.input);
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
