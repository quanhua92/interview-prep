/**
 * P552: Student Attendance Record II [PREMIUM] (Hard)
 * https://leetcode.com/problems/student-attendance-record-ii/
 * Topics: Dynamic Programming
 *
 * An attendance record for a student can be represented as a string where each character signifies whether the student was absent, late, or present on that day. The record only contains the following three characters:
 * Any student is eligible for an attendance award if they meet both of the following criteria:
 * Given an integer n, return the number of possible attendance records of length n that make a student eligible for an attendance award. The answer may be very large, so return it modulo 109 + 7.
 * Example 1:
 *     Input: n = 2
 *     Output: 8
 *     Explanation: There are 8 records with length 2 that are eligible for an award:
 *     "PP", "AP", "PA", "LP", "PL", "AL", "LA", "LL"
 *     Only "AA" is not eligible because there are 2 absences (there need to be fewer than 2).
 *
 * Example 2:
 *     Input: n = 1
 *     Output: 3
 *
 * Example 3:
 *     Input: n = 10101
 *     Output: 183236316
 *
 * Constraints:
 *     - 1 <= n <= 105
 *
 * Template (python3):
 *     class Solution:
 *         def checkRecord(self, n: int) -> int:
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../wasm_libs/js/io.mjs';

function solve(n) {
  const mod = 1000000007n;
  const dp = Array.from({length: 2}, () => Array.from({length: 2}, () => new Array(3).fill(0n)));
  dp[0][0][0] = 1n;
  for (let i = 0; i < n; i++) {
    const cur = i % 2, nxt = 1 - cur;
    for (let a = 0; a < 2; a++) for (let l = 0; l < 3; l++) dp[nxt][a][l] = 0n;
    for (let a = 0; a < 2; a++) {
      for (let l = 0; l < 3; l++) {
        const val = dp[cur][a][l];
        if (val === 0n) continue;
        dp[nxt][a][0] = (dp[nxt][a][0] + val) % mod;
        if (a < 1) dp[nxt][a + 1][0] = (dp[nxt][a + 1][0] + val) % mod;
        if (l < 2) dp[nxt][a][l + 1] = (dp[nxt][a][l + 1] + val) % mod;
      }
    }
  }
  const last = n % 2;
  let result = 0n;
  for (let a = 0; a < 2; a++) for (let l = 0; l < 3; l++) result = (result + dp[last][a][l]) % mod;
  return Number(result);
}

const n = readInt();
writeInt(solve(n));
