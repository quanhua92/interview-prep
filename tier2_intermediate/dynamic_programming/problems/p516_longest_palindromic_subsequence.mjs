/**
 * P516: Longest Palindromic Subsequence [PREMIUM] (Medium)
 * https://leetcode.com/problems/longest-palindromic-subsequence/
 * Topics: String, Dynamic Programming
 *
 * Given a string s, find the longest palindromic subsequence's length in s.
 * A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.
 * Example 1:
 *     Input: s = "bbbab"
 *     Output: 4
 *     Explanation: One possible longest palindromic subsequence is "bbbb".
 *
 * Example 2:
 *     Input: s = "cbbd"
 *     Output: 2
 *     Explanation: One possible longest palindromic subsequence is "bb".
 *
 * Constraints:
 *     - 1 <= s.length <= 1000
 *     - s consists only of lowercase English letters.
 *
 * Template (python3):
 *     class Solution:
 *         def longestPalindromeSubseq(self, s: str) -> int:
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../wasm_libs/js/io.mjs';

function solve(s) {
  throw new Error("NotImplementedError");
}

const s = readLine();
writeInt(solve(s));
