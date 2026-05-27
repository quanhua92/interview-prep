/**
 * P427: Construct Quad Tree [PREMIUM] (Medium)
 * https://leetcode.com/problems/construct-quad-tree/
 * Topics: Array, Divide and Conquer, Tree, Matrix
 *
 * Given a n * n matrix grid of 0's and 1's only. We want to represent grid with a Quad-Tree.
 * Return the root of the Quad-Tree representing grid.
 *
 * Constraints:
 *     - n == grid.length == grid[i].length
 *     - n == 2x where 0 <= x <= 6
 *
 * Hint: Recursively divide grid into 4 quadrants, make leaf if all same value.
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../../wasm_libs/js/io.mjs';

function solve(grid) {
  function allSame(x, y, size) {
    const val = grid[x][y];
    for (let i = x; i < x + size; i++) {
      for (let j = y; j < y + size; j++) {
        if (grid[i][j] !== val) return false;
      }
    }
    return true;
  }

  function build(x, y, size) {
    if (allSame(x, y, size)) {
      return [1, grid[x][y]];
    }
    const half = Math.floor(size / 2);
    const tl = build(x, y, half);
    const tr = build(x, y + half, half);
    const bl = build(x + half, y, half);
    const br = build(x + half, y + half, half);
    return [0, 1, tl, tr, bl, br];
  }

  const tree = build(0, 0, grid.length);
  const queue = [tree];
  while (queue.length > 0) {
    const node = queue.shift();
    if (node === null || node === undefined) {
      writeString("null");
      continue;
    }
    writeString(`${node[0]} ${node[1]}`);
    if (node[0] === 0) {
      for (let c = 2; c < node.length; c++) {
        queue.push(node[c]);
      }
    }
  }
}

const cols = readInt();
const grid = [];
for (let i = 0; i < cols; i++) {
  grid.push(readInts());
}
solve(grid);
