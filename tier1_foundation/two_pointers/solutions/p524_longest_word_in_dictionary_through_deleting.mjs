/**
 * P524: Longest Word in Dictionary through Deleting [PREMIUM] (Medium)
 * https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/
 * Topics: Array, Two Pointers, String, Sorting
 * 
 * Given a string s and a string array dictionary, return the longest string in the dictionary that can be formed by deleting some of the given string characters. If there is more than one possible result, return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.
 * Example 1:
 *     Input: s = "abpcplea", dictionary = ["ale","apple","monkey","plea"]
 *     Output: "apple"
 * 
 * Example 2:
 *     Input: s = "abpcplea", dictionary = ["a","b","c"]
 *     Output: "a"
 * 
 * Constraints:
 *     - 1 <= s.length <= 1000
 *     - 1 <= dictionary.length <= 1000
 *     - 1 <= dictionary[i].length <= 1000
 *     - s and dictionary[i] consist of lowercase English letters.
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../wasm_libs/js/io.mjs';

function solve(s, dictionary) {
  function isSubseq(word, target) {
    let i = 0;
    for (const ch of target) {
      if (i < word.length && word[i] === ch) {
        i++;
      }
    }
    return i === word.length;
  }

  let best = "";
  for (const word of dictionary) {
    if (isSubseq(word, s)) {
      if (word.length > best.length || (word.length === best.length && word < best)) {
        best = word;
      }
    }
  }
  return best;
}

const s = readLine();
const dictSize = readInt();
const dictionary = [];
for (let i = 0; i < dictSize; i++) dictionary.push(readLine());
writeString(solve(s, dictionary));
