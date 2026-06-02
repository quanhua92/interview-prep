/**
 * P472: Concatenated Words [PREMIUM] (Hard)
 * https://leetcode.com/problems/concatenated-words/
 * Topics: Array, String, Dynamic Programming, Depth-First Search, Trie, Sorting
 *
 * Given an array of strings words (without duplicates), return all the concatenated words in the given list of words.
 * A concatenated word is defined as a string that is comprised entirely of at least two shorter words (not necessarily distinct) in the given array.
 * Example 1:
 *     Input: words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
 *     Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]
 *     Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats";
 *     "dogcatsdog" can be concatenated by "dog", "cats" and "dog";
 *     "ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".
 *
 * Example 2:
 *     Input: words = ["cat","dog","catdog"]
 *     Output: ["catdog"]
 *
 * Constraints:
 *     - 1 <= words.length <= 10^4
 *     - 1 <= words[i].length <= 30
 *     - words[i] consists of only lowercase English letters.
 *     - All the strings of words are unique.
 *     - 1 <= sum(words[i].length) <= 10^5
 *
 * Template (python3):
 *     class Solution:
 *         def findAllConcatenatedWordsInADict(self, words: List[str]) -> List[str]:
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../../wasm_libs/js/io.mjs';

class TrieNode {
  constructor() {
    this.children = {};
    this.isEnd = false;
  }
}

function solve(words) {
  const root = new TrieNode();

  function insert(word) {
    let node = root;
    for (const ch of word) {
      if (!(ch in node.children)) {
        node.children[ch] = new TrieNode();
      }
      node = node.children[ch];
    }
    node.isEnd = true;
  }

  function canConcatenate(word, start, count) {
    let node = root;
    for (let i = start; i < word.length; i++) {
      const ch = word[i];
      if (!(ch in node.children)) return false;
      node = node.children[ch];
      if (node.isEnd) {
        if (i === word.length - 1) return count >= 1;
        if (canConcatenate(word, i + 1, count + 1)) return true;
      }
    }
    return false;
  }

  const wordsSorted = [...words].sort((a, b) => a.length - b.length);
  const result = [];
  for (const word of wordsSorted) {
    if (canConcatenate(word, 0, 0)) {
      result.push(word);
    }
    insert(word);
  }
  return result.sort();
}

const nWords = readInt();
const words = [];
for (let i = 0; i < nWords; i++) {
  words.push(readLine());
}
const result = solve(words);
writeInt(result.length);
for (const w of result) {
  writeString(w);
}
