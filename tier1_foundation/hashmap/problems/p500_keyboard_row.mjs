/**
 * P500: Keyboard Row [PREMIUM] (Easy)
 * https://leetcode.com/problems/keyboard-row/
 * Topics: Array, Hash Table, String
 *
 * Given an array of strings words, return the words that can be typed using letters of the alphabet on only one row of American keyboard like the image below.
 * Note that the strings are case-insensitive, both lowercased and uppercased of the same letter are treated as if they are at the same row.
 * In the American keyboard:
 * Example 1:
 *     Input: words = ["Hello","Alaska","Dad","Peace"]
 *     Output: ["Alaska","Dad"]
 *     Explanation:
 *     Both "a" and "A" are in the 2nd row of the American keyboard due to case insensitivity.
 *
 * Example 2:
 *     Input: words = ["omk"]
 *     Output: []
 *
 * Example 3:
 *     Input: words = ["adsdf","sfd"]
 *     Output: ["adsdf","sfd"]
 *
 * Constraints:
 *     - 1 <= words.length <= 20
 *     - 1 <= words[i].length <= 100
 *     - words[i] consists of English letters (both lowercase and uppercase).
 */

import { readInt, readLine, writeString } from '../../wasm_libs/js/io.mjs';

function solve(words) {
  const rows = [
    new Set("qwertyuiop".split("")),
    new Set("asdfghjkl".split("")),
    new Set("zxcvbnm".split("")),
  ];
  const result = [];
  for (const w of words) {
    const lower = new Set(w.toLowerCase().split(""));
    if (rows.some(row => [...lower].every(ch => row.has(ch)))) {
      result.push(w);
    }
  }
  return result;
}

const n = readInt();
const words = [];
for (let i = 0; i < n; i++) {
  words.push(readLine());
}
const result = solve(words);
for (const w of result) {
  writeString(w);
}
