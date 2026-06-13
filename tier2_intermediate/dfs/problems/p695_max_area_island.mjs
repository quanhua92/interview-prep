/**
 * P695: Max Area of Island (Medium)
 * https://leetcode.com/problems/max-area-of-island/
 * Topics: Array, Depth-First Search, Breadth-First Search, Union Find, Matrix
 *
 * You are given an m x n binary matrix grid. Return the maximum area of an island.
 *
 * Example 1:
 *     Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
 *     Output: 6
 *
 * Example 2:
 *     Input: grid = [[0,0,0,0,0,0,0,0]]
 *     Output: 0
 *
 * Constraints:
 *     - m == grid.length
 *     - n == grid[i].length
 *     - 1 <= m, n <= 50
 *
 * Template (javascript):
 *     function maxAreaOfIsland(grid: number[][]): number
 *
 * Hint: Use DFS to explore each island and track the maximum area found.
 */

import { readInts, writeInt } from '../../../wasm_libs/js/io.mjs';

function solve(grid) {
  throw new Error("NotImplementedError");
}

const meta = readInts();
const rows = meta[0];
const cols = meta.length > 1 ? meta[1] : 0;
if (rows === 0 || cols === 0) {
  writeInt(0);
} else {
  const grid = [];
  for (let i = 0; i < rows; i++) {
    grid.push(readInts());
  }
  writeInt(solve(grid));
}
