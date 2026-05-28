/**
 * P1306: Jump Game III (Medium)
 * https://leetcode.com/problems/jump-game-iii/
 * Topics: Array, Depth-First Search, Breadth-First Search
 *
 * Given an array of non-negative integers arr, you are initially positioned at start index.
 * Check if you can reach any index with value 0 by jumping to i + arr[i] or i - arr[i].
 *
 * Example 1:
 *     Input: arr = [4,2,3,0,3,1,2], start = 5
 *     Output: true
 *
 * Example 2:
 *     Input: arr = [4,2,3,0,3,1,2], start = 0
 *     Output: true
 *
 * Example 3:
 *     Input: arr = [3,0,2,1,2], start = 2
 *     Output: false
 *
 * Constraints:
 *     - 1 <= arr.length <= 5 * 10^4
 *     - 0 <= arr[i] < arr.length
 *
 * Template (javascript):
 *     function canReach(arr: number[], start: number): boolean
 *
 * Hint: DFS with a visited set; explore start+arr[start] and start-arr[start], checking bounds and visited.
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../wasm_libs/js/io.mjs';

function solve() {
  throw new Error("NotImplementedError");
}

solve();
