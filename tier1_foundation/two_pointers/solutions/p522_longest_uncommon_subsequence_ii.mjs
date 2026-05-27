/**
 * P522: Longest Uncommon Subsequence II [PREMIUM] (Medium)
 * https://leetcode.com/problems/longest-uncommon-subsequence-ii/
 * Topics: Array, Hash Table, Two Pointers, String, Sorting
 * 
 * Given an array of strings strs, return the length of the longest uncommon subsequence between them. If the longest uncommon subsequence does not exist, return -1.
 * An uncommon subsequence between an array of strings is a string that is a subsequence of one string but not the others.
 * A subsequence of a string s is a string that can be obtained after deleting any number of characters from s.
 * Example 1:
 *     Input: strs = ["aba","cdc","eae"]
 *     Output: 3
 * 
 * Example 2:
 *     Input: strs = ["aaa","aaa","aa"]
 *     Output: -1
 * 
 * Constraints:
 *     - 2 <= strs.length <= 50
 *     - 1 <= strs[i].length <= 10
 *     - strs[i] consists of lowercase English letters.
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../wasm_libs/js/io.mjs';

function solve(strs) {
  function isSubseq(a, b) {
    let i = 0;
    for (const ch of b) {
      if (i < a.length && a[i] === ch) {
        i++;
      }
    }
    return i === a.length;
  }

  strs.sort((a, b) => b.length - a.length);
  for (let i = 0; i < strs.length; i++) {
    const candidate = strs[i];
    let isUncommon = true;
    for (let j = 0; j < strs.length; j++) {
      if (i !== j && isSubseq(candidate, strs[j])) {
        isUncommon = false;
        break;
      }
    }
    if (isUncommon) return candidate.length;
  }
  return -1;
}

const n = readInt();
const strs = [];
for (let i = 0; i < n; i++) strs.push(readLine());
writeInt(solve(strs));
