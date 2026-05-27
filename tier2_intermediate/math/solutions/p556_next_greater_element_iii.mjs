/**
 * P556: Next Greater Element III [PREMIUM] (Medium)
 * https://leetcode.com/problems/next-greater-element-iii/
 * Topics: Math, Two Pointers, String
 *
 * Given a positive integer n, find the smallest integer which has exactly the same digits existing in the integer n and is greater in value than n. If no such positive integer exists, return -1.
 * Note that the returned integer should fit in 32-bit integer, if there is a valid answer but it does not fit in 32-bit integer, return -1.
 * Example 1:
 *     Input: n = 12
 *     Output: 21
 *
 * Example 2:
 *     Input: n = 21
 *     Output: -1
 *
 * Constraints:
 *     - 1 <= n <= 231 - 1
 *
 * Template (python3):
 *     class Solution:
 *         def nextGreaterElement(self, n: int) -> int:
 */

import { readInts, writeInt } from '../../wasm_libs/js/io.mjs';

function solve(n) {
  const digits = String(n).split("");
  let i = digits.length - 2;
  while (i >= 0 && digits[i] >= digits[i + 1]) {
    i--;
  }
  if (i < 0) return -1;
  let j = digits.length - 1;
  while (digits[j] <= digits[i]) {
    j--;
  }
  [digits[i], digits[j]] = [digits[j], digits[i]];
  const right = digits.splice(i + 1).reverse();
  digits.push(...right);
  const result = parseInt(digits.join(""), 10);
  return result <= 2 ** 31 - 1 ? result : -1;
}

const vals = readInts();
writeInt(solve(vals[0]));
