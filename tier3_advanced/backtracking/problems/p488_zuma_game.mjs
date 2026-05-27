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
 */

import { readLine, writeInt } from '../../../wasm_libs/js/io.mjs';

function solve(board, hand) {
  throw new Error("NotImplementedError");
}

const board = readLine();
const hand = readLine();
writeInt(solve(board, hand));
