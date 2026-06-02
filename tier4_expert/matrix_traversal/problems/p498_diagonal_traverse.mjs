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
 * Template (python3):
 *     class Solution:
 *         def findDiagonalOrder(self, mat: List[List[int]]) -> List[int]:
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
    throw new Error("NotImplementedError");
}

const mat = readIntMatrix();
const result = solve(mat);
writeInts(result);
