/**
 * P395: Longest Substring with At Least K Repeating Characters [PREMIUM] (Medium)
 * https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/
 * Topics: Hash Table, String, Divide and Conquer, Sliding Window
 *
 * Given a string s and an integer k, return the length of the longest substring of s such that the frequency of each character in this substring is greater than or equal to k.
 * if no such substring exists, return 0.
 * Example 1:
 *     Input: s = "aaabb", k = 3
 *     Output: 3
 *     Explanation: The longest substring is "aaa", as 'a' is repeated 3 times.
 *
 * Example 2:
 *     Input: s = "ababbc", k = 2
 *     Output: 5
 *     Explanation: The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.
 *
 * Constraints:
 *     - 1 <= s.length <= 10^4
 *     - s consists of only lowercase English letters.
 *     - 1 <= k <= 10^5
 *
 * Template (python3):
 *     class Solution:
 *         def longestSubstring(self, s: str, k: int) -> int:
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../wasm_libs/js/io.mjs';

function solve(s, k) {
  let maxLen = 0;
  for (let t = 1; t <= 26; t++) {
    const freq = new Map();
    let left = 0;
    let unique = 0;
    let atLeastK = 0;
    for (let right = 0; right < s.length; right++) {
      const ch = s[right];
      freq.set(ch, (freq.get(ch) || 0) + 1);
      if (freq.get(ch) === 1) unique++;
      if (freq.get(ch) === k) atLeastK++;
      while (unique > t) {
        const lc = s[left];
        if (freq.get(lc) === k) atLeastK--;
        freq.set(lc, freq.get(lc) - 1);
        if (freq.get(lc) === 0) unique--;
        left++;
      }
      if (unique === t && atLeastK === t) {
        maxLen = Math.max(maxLen, right - left + 1);
      }
    }
  }
  return maxLen;
}

// Divide and Conquer approach (added for reference — not used by judge)
function longestSubstringDC(s, k) {
  if (s.length < k) return 0;
  const freq = {};
  for (const ch of s) freq[ch] = (freq[ch] || 0) + 1;
  for (const [char, count] of Object.entries(freq)) {
    if (count < k) {
      return Math.max(...s.split(char).map(sub => longestSubstringDC(sub, k)));
    }
  }
  return s.length;
}

const s = readLine();
const k = readInt();
writeInt(solve(s, k));
