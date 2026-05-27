/**
 * P520: Detect Capital [PREMIUM] (Easy)
 * https://leetcode.com/problems/detect-capital/
 * Topics: String
 *
 * We define the usage of capitals in a word to be right when one of the following cases holds:
 * Given a string word, return true if the usage of capitals in it is right.
 * Example 1:
 *     Input: word = "USA"
 *     Output: true
 *
 * Example 2:
 *     Input: word = "FlaG"
 *     Output: false
 *
 * Constraints:
 *     - 1 <= word.length <= 100
 *     - word consists of lowercase and uppercase English letters.
 *
 * Template (python3):
 *     class Solution:
 *         def detectCapitalUse(self, word: str) -> bool:
 */

import { readLine, writeBool } from '../../wasm_libs/js/io.mjs';

function solve(word) {
  return word === word.toUpperCase() || word === word.toLowerCase() || word.slice(1) === word.slice(1).toLowerCase();
}

const word = readLine();
writeBool(solve(word));
