/**
 * P488: Zuma Game [PREMIUM] (Hard)
 * https://leetcode.com/problems/zuma-game/
 * Topics: String, Dynamic Programming, Stack, Breadth-First Search, Memoization
 *
 * Given a string board and a string hand, return the minimum number of balls you have to insert to clear all the balls from the board.
 * Example 1:
 *     Input: board = "WRRBBW", hand = "RB"
 *     Output: -1
 *
 * Example 2:
 *     Input: board = "WWRRBBWW", hand = "WRBRW"
 *     Output: 2
 *
 * Template (python3):
 *     class Solution:
 *         def findMinStep(self, board: str, hand: str) -> int:
 */

import { readLine, writeInt } from '../../../wasm_libs/js/io.mjs';

function solve(board, hand) {
  function collapse(s) {
    let changed = true;
    while (changed) {
      changed = false;
      let i = 0;
      while (i < s.length) {
        let j = i;
        while (j < s.length && s[j] === s[i]) j++;
        if (j - i >= 3) {
          s = s.slice(0, i) + s.slice(j);
          changed = true;
        } else {
          i = j;
        }
      }
    }
    return s;
  }

  const memo = new Map();

  function dfs(boardStr, handSorted) {
    boardStr = collapse(boardStr);
    if (boardStr === "") return 0;
    if (handSorted.length === 0) return -1;
    const key = boardStr + "|" + handSorted.join("");
    if (memo.has(key)) return memo.get(key);
    let minBalls = -1;
    for (let i = 0; i <= boardStr.length; i++) {
      for (let hi = 0; hi < handSorted.length; hi++) {
        if (hi > 0 && handSorted[hi] === handSorted[hi - 1]) continue;
        const color = handSorted[hi];
        const newBoard = boardStr.slice(0, i) + color + boardStr.slice(i);
        const newHand = [...handSorted.slice(0, hi), ...handSorted.slice(hi + 1)];
        const result = dfs(newBoard, newHand);
        if (result !== -1) {
          if (minBalls === -1 || result + 1 < minBalls) {
            minBalls = result + 1;
          }
        }
      }
    }
    memo.set(key, minBalls);
    return minBalls;
  }

  return dfs(board, [...hand].sort());
}

const board = readLine();
const hand = readLine();
writeInt(solve(board, hand));
