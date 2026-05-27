/**
 * P70: Climbing Stairs (Easy)
 * https://leetcode.com/problems/climbing-stairs/
 * Topics: Math, Dynamic Programming, Memoization
 *
 * You are climbing a staircase. It takes n steps to reach the top.
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
 *
 * Constraints:
 *     - 1 <= n <= 45
 *
 * Hint: This is essentially Fibonacci -- each step depends on the two before it.
 */

import { readInt, writeInt } from '../../wasm_libs/js/io.mjs';

function solve(n) {
  if (n <= 2) return n;
  let a = 1, b = 2;
  for (let i = 3; i <= n; i++) {
    const temp = b;
    b = a + b;
    a = temp;
  }
  return b;
}

const n = readInt();
writeInt(solve(n));
