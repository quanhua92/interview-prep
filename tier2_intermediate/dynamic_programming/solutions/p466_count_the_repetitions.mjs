/**
 * P466: Count The Repetitions [PREMIUM] (Hard)
 * https://leetcode.com/problems/count-the-repetitions/
 * Topics: String, Dynamic Programming
 *
 * We define str = [s, n] as the string str which consists of the string s concatenated n times.
 * We define that string s1 can be obtained from string s2 if we can remove some characters from s2 such that it becomes s1.
 * You are given two strings s1 and s2 and two integers n1 and n2. You have the two strings str1 = [s1, n1] and str2 = [s2, n2].
 * Return the maximum integer m such that str = [str2, m] can be obtained from str1.
 * Example 1:
 *     Input: s1 = "acb", n1 = 4, s2 = "ab", n2 = 2
 *     Output: 2
 *
 * Example 2:
 *     Input: s1 = "acb", n1 = 1, s2 = "acb", n2 = 1
 *     Output: 1
 *
 * Constraints:
 *     - 1 <= s1.length, s2.length <= 100
 *     - s1 and s2 consist of lowercase English letters.
 *     - 1 <= n1, n2 <= 106
 *
 * Template (python3):
 *     class Solution:
 *         def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../wasm_libs/js/io.mjs';

function solve(s1, n1, s2, n2) {
  if (n1 === 0) return 0;
  const s2Len = s2.length, s1Len = s1.length;
  const s1Set = new Set(s1);
  for (const ch of s2) { if (!s1Set.has(ch)) return 0; }
  const indexMap = new Map();
  let count = 0, s2Index = 0;
  for (let i = 0; i < n1; i++) {
    for (let j = 0; j < s1Len; j++) {
      if (s1[j] === s2[s2Index]) { s2Index++; if (s2Index === s2Len) { count++; s2Index = 0; } }
    }
    if (indexMap.has(s2Index)) {
      const [prevI, prevCount] = indexMap.get(s2Index);
      const cycleLen = i - prevI, cycleCount = count - prevCount;
      const remaining = n1 - 1 - i, fullCycles = Math.floor(remaining / cycleLen);
      count += fullCycles * cycleCount;
      const processed = i + fullCycles * cycleLen + 1;
      for (let ii = processed; ii < n1; ii++) {
        for (let jj = 0; jj < s1Len; jj++) {
          if (s1[jj] === s2[s2Index]) { s2Index++; if (s2Index === s2Len) { count++; s2Index = 0; } }
        }
      }
      break;
    } else { indexMap.set(s2Index, [i, count]); }
  }
  return Math.floor(count / n2);
}

const s1 = readLine();
const n1 = readInt();
const s2 = readLine();
const n2 = readInt();
writeInt(solve(s1, n1, s2, n2));
