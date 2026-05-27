/**
 * P200: Number of Islands (Medium)
 * https://leetcode.com/problems/number-of-islands/
 * Topics: Array, Depth-First Search, Breadth-First Search, Union Find, Matrix
 */

import { readLine, readInts, writeInt } from '../../../wasm_libs/js/io.mjs';

function solve(grid) {
  if (!grid || grid.length === 0 || grid[0].length === 0) return 0;
  const rows = grid.length;
  const cols = grid[0].length;
  let count = 0;

  function dfs(r, c) {
    if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] !== "1") return;
    grid[r][c] = "0";
    dfs(r + 1, c);
    dfs(r - 1, c);
    dfs(r, c + 1);
    dfs(r, c - 1);
  }

  for (let r = 0; r < rows; r++) {
    for (let c = 0; c < cols; c++) {
      if (grid[r][c] === "1") {
        count++;
        dfs(r, c);
      }
    }
  }
  return count;
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
