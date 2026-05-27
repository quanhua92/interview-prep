/**
 * P695: Max Area of Island (Medium)
 * https://leetcode.com/problems/max-area-of-island/
 * Topics: Array, Depth-First Search, Breadth-First Search, Union Find, Matrix
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
