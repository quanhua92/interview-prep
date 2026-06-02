/**
 * P3: Longest Substring Without Repeating Characters (Medium)
 * https://leetcode.com/problems/longest-substring-without-repeating-characters/
 * Topics: Hash Table, String, Sliding Window
 *
 * Given a string s, find the length of the longest substring without duplicate characters.
 *
 * Example 1:
 *     Input: s = "abcabcbb"
 *     Output: 3
 *     Explanation: The answer is "abc", with the length of 3.
 *
 * Example 2:
 *     Input: s = "bbbbb"
 *     Output: 1
 *     Explanation: The answer is "b", with the length of 1.
 *
 * Example 3:
 *     Input: s = "pwwkew"
 *     Output: 3
 *     Explanation: The answer is "wke", with the length of 3.
 *     Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
 *
 * Constraints:
 *     - 0 <= s.length <= 5 * 10^4
 *     - s consists of English letters, digits, symbols and spaces.
 *
 * Hints:
 *     - Generate all possible substrings & check for each substring if it's valid and keep updating maxLen accordingly.
 *
 * Template (python3):
 *     class Solution:
 *         def lengthOfLongestSubstring(self, s: str) -> int:
 *
 * Hint: Use a hash map to track the last index of each character.
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../wasm_libs/js/io.mjs';

function solve(s) {
  const charIndex = new Map();
  let left = 0;
  let maxLen = 0;
  for (let right = 0; right < s.length; right++) {
    const ch = s[right];
    if (charIndex.has(ch) && charIndex.get(ch) >= left) {
      left = charIndex.get(ch) + 1;
    }
    charIndex.set(ch, right);
    maxLen = Math.max(maxLen, right - left + 1);
  }
  return maxLen;
}

const s = readLine();
writeInt(solve(s));
