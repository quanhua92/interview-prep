/**
 * P498: Diagonal Traverse (Medium)
 * https://leetcode.com/problems/diagonal-traverse/
 * Topics: Array, Matrix, Simulation
 *
 * Given an m x n matrix mat, return an array of all the elements of the array in a diagonal order.
 *
 * Example 1:
 *     Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
 *     Output: [1,2,4,7,5,3,6,8,9]
 *
 * Example 2:
 *     Input: mat = [[1,2],[3,4]]
 *     Output: [1,2,3,4]
 *
 * Constraints:
 *     - m == mat.length
 *     - n == mat[i].length
 *     - 1 <= m, n <= 104
 *     - 1 <= m * n <= 104
 *     - -105 <= mat[i][j] <= 105
 *
 * Template (python3):
 *     class Solution:
 *         def findDiagonalOrder(self, mat: List[List[int]]) -> List[int]:
 *
 * Hint: Group by i+j diagonal index. If d is even, reverse to simulate up-right direction.
 */

function solve(mat) {
  throw new Error("NotImplementedError");
}

const tests = [
  { input: [[1,2,3],[4,5,6],[7,8,9]], expected: [1,2,4,7,5,3,6,8,9], label: "example 1" },
  { input: [[1,2],[3,4],[5,6]], expected: [1,2,3,5,4,6], label: "example 2" },
  { input: [[1]], expected: [1], label: "single element" },
  { input: [[1,2,3,4]], expected: [1,2,3,4], label: "single row" },
  { input: [[1],[2],[3],[4]], expected: [1,2,3,4], label: "single column" },
  { input: [[1,2,3,4],[5,6,7,8]], expected: [1,2,5,6,3,4,7,8], label: "2x4 rectangular" },
  { input: [[-1,-2],[3,4]], expected: [-1,-2,3,4], label: "negative values 2x2" },
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
