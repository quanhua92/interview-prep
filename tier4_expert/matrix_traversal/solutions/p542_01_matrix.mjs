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
 *     - 1 <= m, n <= 10^4
 *     - 1 <= m * n <= 10^4
 *     - mat[i][j] is either 0 or 1.
 *     - There is at least one 0 in mat.
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

function writeMatrix(mat) {
  for (const row of mat) {
    writeInts(row);
  }
}

function solve(mat) {
  const m = mat.length, n = mat[0].length;
  const dist = Array.from({ length: m }, () => new Array(n).fill(0));
  const queue = [];
  for (let r = 0; r < m; r++) {
    for (let c = 0; c < n; c++) {
      if (mat[r][c] === 0) {
        queue.push([r, c]);
      } else {
        dist[r][c] = -1;
      }
    }
  }
  const dirs = [[-1, 0], [1, 0], [0, -1], [0, 1]];
  let head = 0;
  while (head < queue.length) {
    const [r, c] = queue[head++];
    for (const [dr, dc] of dirs) {
      const nr = r + dr, nc = c + dc;
      if (nr >= 0 && nr < m && nc >= 0 && nc < n && dist[nr][nc] === -1) {
        dist[nr][nc] = dist[r][c] + 1;
        queue.push([nr, nc]);
      }
    }
  }
  return dist;
}

const mat = readIntMatrix();
const result = solve(mat);
writeMatrix(result);
