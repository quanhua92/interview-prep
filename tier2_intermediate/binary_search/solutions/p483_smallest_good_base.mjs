/**
 * P483: Smallest Good Base [PREMIUM] (Hard)
 * https://leetcode.com/problems/smallest-good-base/
 * Topics: Math, Binary Search
 *
 * Given an integer n represented as a string, return the smallest good base of n.
 * We call k >= 2 a good base of n, if all digits of n base k are 1's.
 * Example 1:
 *     Input: n = "13"
 *     Output: "3"
 *     Explanation: 13 base 3 is 111.
 *
 * Example 2:
 *     Input: n = "4681"
 *     Output: "8"
 *     Explanation: 4681 base 8 is 11111.
 *
 * Example 3:
 *     Input: n = "1000000000000000000"
 *     Output: "999999999999999999"
 *     Explanation: 1000000000000000000 base 999999999999999999 is 11.
 *
 * Constraints:
 *     - n is an integer in the range [3, 1018].
 *     - n does not contain any leading zeros.
 *
 * Template (python3):
 *     class Solution:
 *         def smallestGoodBase(self, n: str) -> str:
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../../wasm_libs/js/io.mjs';

function solve(n) {
  const num = BigInt(n);

  const calc = (k, m) => {
    let total = 0n;
    for (let i = 0; i < m; i++) {
      total = total * k + 1n;
      if (total > num) return total;
    }
    return total;
  };

  const maxM = Number(num.toString(2).length);
  let result = String(num - 1n);

  for (let m = maxM; m >= 2; m--) {
    let lo = 2n;
    let hi = num - 1n;
    while (lo <= hi) {
      const mid = (lo + hi) / 2n;
      const s = calc(mid, m);
      if (s === num) return String(mid);
      if (s < num) {
        lo = mid + 1n;
      } else {
        hi = mid - 1n;
      }
    }
  }
  return result;
}

const n = readLine();
writeString(solve(n));
