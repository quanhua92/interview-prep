/**
 * P695: Max Area of Island (Medium)
 * https://leetcode.com/problems/max-area-of-island/
 * Topics: Array, Depth-First Search, Breadth-First Search, Union Find, Matrix
 *
 * You are given an m x n binary matrix grid. An island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.
 * The area of an island is the number of cells with a value 1 in the island.
 * Return the maximum area of an island in grid. If there is no island, return 0.
 *
 * Example 1:
 *     Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
 *     Output: 6
 *     Explanation: The answer is not 11, because the island must be connected 4-directionally.
 *
 * Example 2:
 *     Input: grid = [[0,0,0,0,0,0,0,0]]
 *     Output: 0
 *
 * Constraints:
 *     - m == grid.length
 *     - n == grid[i].length
 *     - 1 <= m, n <= 50
 *     - grid[i][j] is either 0 or 1.
 *
 * Hint: Use DFS to explore each island and track the maximum area found.
 */

import { readInts, writeInt } from '../../../wasm_libs/js/io.mjs';

function solve(grid) {
  if (!grid || !grid[0]) return 0;
  const rows = grid.length;
  const cols = grid[0].length;
  let maxArea = 0;

  function dfs(r, c) {
    if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] !== 1) return 0;
    grid[r][c] = 0;
    return 1 + dfs(r + 1, c) + dfs(r - 1, c) + dfs(r, c + 1) + dfs(r, c - 1);
  }

  for (let r = 0; r < rows; r++) {
    for (let c = 0; c < cols; c++) {
      if (grid[r][c] === 1) {
        maxArea = Math.max(maxArea, dfs(r, c));
      }
    }
  }
  return maxArea;
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
