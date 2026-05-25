/**
 * P48: Rotate Image (Medium)
 * https://leetcode.com/problems/rotate-image/
 * Topics: Array, Math, Matrix
 *
 * You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).
 * You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.
 *
 * Example 1:
 *     Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
 *     Output: [[7,4,1],[8,5,2],[9,6,3]]
 *
 * Example 2:
 *     Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
 *     Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
 *
 * Constraints:
 *     - n == matrix.length == matrix[i].length
 *     - 1 <= n <= 20
 *     - -1000 <= matrix[i][j] <= 1000
 *
 * Template (python3):
 *     class Solution:
 *         def rotate(self, matrix: List[List[int]]) -> None:
 *             '''
 *             Do not return anything, modify matrix in-place instead.
 *             '''
 *
 * Hint: Transpose the matrix first, then reverse each row.
 */

function solve(matrix) {
  const n = matrix.length;
  for (let i = 0; i < n; i++) {
    for (let j = i + 1; j < n; j++) {
      [matrix[i][j], matrix[j][i]] = [matrix[j][i], matrix[i][j]];
    }
  }
  for (const row of matrix) {
    row.reverse();
  }
  return matrix;
}

const tests = [
  { label: "example 1", input: [[[1, 2, 3], [4, 5, 6], [7, 8, 9]]], expected: [[7, 4, 1], [8, 5, 2], [9, 6, 3]] },
  { label: "example 2", input: [[[5, 1, 9, 11], [2, 4, 8, 10], [13, 3, 6, 7], [15, 14, 12, 16]]], expected: [[15, 13, 2, 5], [14, 3, 4, 1], [12, 6, 8, 9], [16, 7, 10, 11]] },
  { label: "single element", input: [[[1]]], expected: [[1]] },
  { label: "2x2 matrix", input: [[[1, 2], [3, 4]]], expected: [[3, 1], [4, 2]] },
  { label: "negative values", input: [[[-1, -2, -3], [-4, -5, -6], [-7, -8, -9]]], expected: [[-7, -4, -1], [-8, -5, -2], [-9, -6, -3]] },
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
