/**
 * P463: Island Perimeter [PREMIUM] (Easy)
 * https://leetcode.com/problems/island-perimeter/
 * Topics: Array, Depth-First Search, Breadth-First Search, Matrix
 *
 * You are given row x col grid representing a map where grid[i][j] = 1 represents land and grid[i][j] = 0 represents water.
 * Grid cells are connected horizontally/vertically (not diagonally). The grid is completely surrounded by water, and there is exactly one island (i.e., one or more connected land cells).
 * The island doesn't have "lakes", meaning the water inside isn't connected to the water around the island. One cell is a square with side length 1. The grid is rectangular, width and height don't exceed 100. Determine the perimeter of the island.
 * Example 1:
 *     Input: grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
 *     Output: 16
 *
 * Example 2:
 *     Input: grid = [[1]]
 *     Output: 4
 *
 * Example 3:
 *     Input: grid = [[1,0]]
 *     Output: 4
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../wasm_libs/js/io.mjs';

function solve(grid) {
  const rows = grid.length;
  const cols = grid[0].length;
  const visited = new Set();
  let perimeter = 0;
  const directions = [[0, 1], [0, -1], [1, 0], [-1, 0]];
  for (let r = 0; r < rows; r++) {
    for (let c = 0; c < cols; c++) {
      if (grid[r][c] === 1) {
        const queue = [[r, c]];
        visited.add(`${r},${c}`);
        while (queue.length > 0) {
          const [cr, cc] = queue.shift();
          for (const [dr, dc] of directions) {
            const nr = cr + dr;
            const nc = cc + dc;
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || grid[nr][nc] === 0) {
              perimeter++;
            } else if (!visited.has(`${nr},${nc}`)) {
              visited.add(`${nr},${nc}`);
              queue.push([nr, nc]);
            }
          }
        }
        return perimeter;
      }
    }
  }
  return 0;
}

const _cols = readInt();
const grid = [];
while (true) {
  const row = readInts();
  if (row.length === 0) break;
  grid.push(row);
}
writeInt(solve(grid));
