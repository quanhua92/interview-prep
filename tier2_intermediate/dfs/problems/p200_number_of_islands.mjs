/**
 * P200: Number of Islands (Medium)
 * https://leetcode.com/problems/number-of-islands/
 * Topics: Array, Depth-First Search, Breadth-First Search, Union Find, Matrix
 *
 * Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.
 * An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.
 *
 * Example 1:
 *     Input: grid = [
 *       ["1","1","1","1","0"],
 *       ["1","1","0","1","0"],
 *       ["1","1","0","0","0"],
 *       ["0","0","0","0","0"]
 *     ]
 *     Output: 1
 *
 * Example 2:
 *     Input: grid = [
 *       ["1","1","0","0","0"],
 *       ["1","1","0","0","0"],
 *       ["0","0","1","0","0"],
 *       ["0","0","0","1","1"]
 *     ]
 *     Output: 3
 *
 * Constraints:
 *     - m == grid.length
 *     - n == grid[i].length
 *     - 1 <= m, n <= 300
 *     - grid[i][j] is '0' or '1'.
 *
 * Template (javascript):
 *     function solve(grid: string[][]): number
 *
 * Hint: Use DFS to mark visited land cells, counting each new island.
 */

import { readLine, readInts, writeInt } from '../../../wasm_libs/js/io.mjs';

function solve(grid) {
  throw new Error("NotImplementedError");
}

const meta = readInts();
const rows = meta[0];
const cols = meta.length > 1 ? meta[1] : 0;
if (rows === 0) {
  writeInt(0);
} else {
  const grid = [];
  for (let i = 0; i < rows; i++) {
    grid.push(readLine().split(''));
  }
  writeInt(solve(grid));
}
