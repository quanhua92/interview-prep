/**
 * P576: Out of Boundary Paths [PREMIUM] (Medium)
 * https://leetcode.com/problems/out-of-boundary-paths/
 * Topics: Dynamic Programming
 *
 * There is an m x n grid with a ball. The ball is initially at the position [startRow, startColumn]. You are allowed to move the ball to one of the four adjacent cells in the grid (possibly out of the grid crossing the grid boundary). You can apply at most maxMove moves to the ball.
 * Given the five integers m, n, maxMove, startRow, startColumn, return the number of paths to move the ball out of the grid boundary. Since the answer can be very large, return it modulo 10^9 + 7.
 * Example 1:
 *     Input: m = 2, n = 2, maxMove = 2, startRow = 0, startColumn = 0
 *     Output: 6
 *
 * Example 2:
 *     Input: m = 1, n = 3, maxMove = 3, startRow = 0, startColumn = 1
 *     Output: 12
 *
 * Constraints:
 *     - 1 <= m, n <= 50
 *     - 0 <= maxMove <= 50
 *     - 0 <= startRow < m
 *     - 0 <= startColumn < n
 *
 * Hint: Is traversing every path feasible? There are many possible paths for a small matrix. Try to optimize it.
 * Hint: Can we use some space to store the number of paths and update them after every move?
 * Hint: One obvious thing: the ball will go out of the boundary only by crossing it. Also, there is only one possible way the ball can go out of the boundary from the boundary cell except for corner cells. From the corner cell, the ball can go out in two different ways.
 *
 * Can you use this thing to solve the problem?
 *
 * Template (python3):
 *     class Solution:
 *         def findPaths(self, m: int, n: int, maxMove: int, startRow: int, startColumn: int) -> int:
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../wasm_libs/js/io.mjs';

function solve(m, n, maxMove, startRow, startColumn) {
  const mod = 1000000007n;
  const dirs = [[-1,0],[1,0],[0,-1],[0,1]];
  let dp = new Array(m * n).fill(0n);
  let nxt = new Array(m * n).fill(0n);
  dp[startRow * n + startColumn] = 1n;
  let result = 0n;
  for (let move = 0; move < maxMove; move++) {
    nxt.fill(0n);
    for (let r = 0; r < m; r++) {
      for (let c = 0; c < n; c++) {
        const val = dp[r * n + c];
        if (val === 0n) continue;
        for (const [dr, dc] of dirs) {
          const nr = r + dr, nc = c + dc;
          if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
            nxt[nr * n + nc] = (nxt[nr * n + nc] + val) % mod;
          } else {
            result = (result + val) % mod;
          }
        }
      }
    }
    [dp, nxt] = [nxt, dp];
  }
  return Number(result);
}

const m = readInt();
const n = readInt();
const mm = readInt();
const sr = readInt();
const sc = readInt();
writeInt(solve(m, n, mm, sr, sc));
