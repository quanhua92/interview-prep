/**
 * P1306: Jump Game III (Medium)
 * https://leetcode.com/problems/jump-game-iii/
 * Topics: Array, Depth-First Search, Breadth-First Search
 */

import { readInts, readLine, writeBool } from '../../../wasm_libs/js/io.mjs';

function solve(arr, start) {
  const n = arr.length;
  const visited = new Set();

  function dfs(i) {
    if (i < 0 || i >= n || visited.has(i)) return false;
    if (arr[i] === 0) return true;
    visited.add(i);
    const jump = arr[i];
    return dfs(i + jump) || dfs(i - jump);
  }

  return dfs(start);
}

const arr = readInts();
const start = parseInt(readLine(), 10);
writeBool(solve(arr, start));
