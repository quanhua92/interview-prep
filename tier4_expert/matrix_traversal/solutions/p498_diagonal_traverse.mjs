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
 *     - 1 <= m, n <= 10^4
 *     - 1 <= m * n <= 10^4
 *     - -10^5 <= mat[i][j] <= 10^5
 *
 * Hint: Group by i+j diagonal index. If d is even, reverse to simulate up-right direction.
 */

import { readInts, readInt, writeInts } from '../../../wasm_libs/js/io.mjs';

function readIntMatrix() {
  readInt();
  const matrix = [];
  while (true) {
    const row = readInts();
    if (row.length === 0) break;
    matrix.push(row);
  }
  return matrix;
}

function solve(mat) {
  if (!mat || !mat[0]) return [];
  const m = mat.length, n = mat[0].length;
  const result = [];
  const diagonals = new Map();
  for (let i = 0; i < m; i++) {
    for (let j = 0; j < n; j++) {
      const d = i + j;
      if (!diagonals.has(d)) diagonals.set(d, []);
      diagonals.get(d).push(mat[i][j]);
    }
  }
  for (let d = 0; d < m + n - 1; d++) {
    const diag = diagonals.get(d);
    if (d % 2 === 0) {
      result.push(...diag.reverse());
    } else {
      result.push(...diag);
    }
  }
  return result;
}

const mat = readIntMatrix();
const result = solve(mat);
writeInts(result);
