/**
 * P473: Matchsticks to Square [PREMIUM] (Medium)
 * https://leetcode.com/problems/matchsticks-to-square/
 * Topics: Array, Dynamic Programming, Backtracking, Bit Manipulation, Bitmask
 *
 * You are given an integer array matchsticks where matchsticks[i] is the length of the ith matchstick.
 * Return true if you can make this square and false otherwise.
 *
 * Example 1:
 *     Input: matchsticks = [1,1,2,2,2]
 *     Output: true
 *
 * Example 2:
 *     Input: matchsticks = [3,3,3,3,4]
 *     Output: false
 *
 * Hint: Treat the matchsticks as an array. Can we split the array into 4 equal parts?
 */

import { readInts, writeBool } from '../../../wasm_libs/js/io.mjs';

function solve(matchsticks) {
  if (!matchsticks || matchsticks.length === 0) return false;
  const total = matchsticks.reduce((a, b) => a + b, 0);
  if (total % 4 !== 0) return false;
  const side = total / 4;
  matchsticks.sort((a, b) => b - a);
  if (matchsticks[0] > side) return false;
  const sides = [0, 0, 0, 0];

  function backtrack(idx) {
    if (idx === matchsticks.length) {
      return sides[0] === sides[1] && sides[1] === sides[2] && sides[2] === side;
    }
    for (let i = 0; i < 4; i++) {
      if (sides[i] + matchsticks[idx] <= side) {
        sides[i] += matchsticks[idx];
        if (backtrack(idx + 1)) return true;
        sides[i] -= matchsticks[idx];
      }
    }
    return false;
  }

  return backtrack(0);
}

const matchsticks = readInts();
writeBool(solve(matchsticks));
