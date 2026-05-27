/**
 * P70: Climbing Stairs (Easy)
 * https://leetcode.com/problems/climbing-stairs/
 * Topics: Math, Dynamic Programming, Memoization
 * 
 * You are climbing a staircase. It takes n steps to reach the top.
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
 * 
 * Example 1:
 *     Input: n = 2
 *     Output: 2
 *     Explanation: There are two ways to climb to the top.
 *     1. 1 step + 1 step
 *     2. 2 steps
 * 
 * Example 2:
 *     Input: n = 3
 *     Output: 3
 *     Explanation: There are three ways to climb to the top.
 *     1. 1 step + 1 step + 1 step
 *     2. 1 step + 2 steps
 *     3. 2 steps + 1 step
 * 
 * Constraints:
 *     - 1 <= n <= 45
 * 
 * Hints:
 *     - To reach nth step, what could have been your previous steps? (Think about the step sizes)
 * 
 * Template (python3):
 *     class Solution:
 *         def climbStairs(self, n: int) -> int:
 * 
 * Hint: This is essentially Fibonacci -- each step depends on the two before it.
 */
import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../wasm_libs/js/io.mjs';

function solve(n) {
  throw new Error("NotImplementedError");
}

const n = readInt();
writeInt(solve(n));
