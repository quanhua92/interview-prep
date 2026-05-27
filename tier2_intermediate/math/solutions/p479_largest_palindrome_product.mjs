/**
 * P479: Largest Palindrome Product [PREMIUM] (Hard)
 * https://leetcode.com/problems/largest-palindrome-product/
 * Topics: Math, Enumeration
 *
 * Given an integer n, return the largest palindromic integer that can be represented as the product of two n-digits integers. Since the answer can be very large, return it modulo 1337.
 * Example 1:
 *     Input: n = 2
 *     Output: 987
 *     Explanation: 99 x 91 = 9009, 9009 % 1337 = 987
 *
 * Example 2:
 *     Input: n = 1
 *     Output: 9
 *
 * Constraints:
 *     - 1 <= n <= 8
 *
 * Template (python3):
 *     class Solution:
 *         def largestPalindrome(self, n: int) -> int:
 */

import { readInts, writeInt } from '../../wasm_libs/js/io.mjs';

function solve(n) {
  if (n === 1) return 9;
  const upper = 10 ** n - 1;
  const lower = 10 ** (n - 1);
  const MOD = 1337n;
  for (let left = upper; left >= lower; left--) {
    const s = String(left);
    const palindrome = BigInt(s + s.split("").reverse().join(""));
    for (let right = upper; right >= lower; right--) {
      const rightBig = BigInt(right);
      if (rightBig * rightBig < palindrome) break;
      if (palindrome % rightBig === 0n) {
        return Number(palindrome % MOD);
      }
    }
  }
  return 0;
}

const vals = readInts();
writeInt(solve(vals[0]));
