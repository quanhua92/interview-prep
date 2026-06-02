/**
 * P1306: Jump Game III (Medium)
 * https://leetcode.com/problems/jump-game-iii/
 * Topics: Array, Depth-First Search, Breadth-First Search
 *
 * Given an array of non-negative integers arr, you are initially positioned at start index of the array. When you are at index i, you can jump to i + arr[i] or i - arr[i], check if you can reach any index with value 0.
 * Notice that you can not jump outside of the array at any time.
 *
 * Example 1:
 *     Input: arr = [4,2,3,0,3,1,2], start = 5
 *     Output: true
 *     Explanation:
 *     All possible ways to reach at index 3 with value 0 are:
 *     index 5 -> index 4 -> index 1 -> index 3
 *     index 5 -> index 6 -> index 4 -> index 1 -> index 3
 *
 * Example 2:
 *     Input: arr = [4,2,3,0,3,1,2], start = 0
 *     Output: true
 *     Explanation:
 *     One possible way to reach at index 3 with value 0 is:
 *     index 0 -> index 4 -> index 1 -> index 3
 *
 * Example 3:
 *     Input: arr = [3,0,2,1,2], start = 2
 *     Output: false
 *     Explanation: There is no way to reach at index 1 with value 0.
 *
 * Constraints:
 *     - 1 <= arr.length <= 5 * 10^4
 *     - 0 <= arr[i] < arr.length
 *     - 0 <= start < arr.length
 *
 * Hints:
 *     - Think of BFS to solve the problem.
 *     - When you reach a position with a value = 0 then return true.
 *
 * Hint: DFS with a visited set; explore start+arr[start] and start-arr[start], checking bounds and visited.
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
