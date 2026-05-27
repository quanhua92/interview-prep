/**
 * P211: Design Add and Search Words Data Structure (Medium)
 * https://leetcode.com/problems/design-add-and-search-words-data-structure/
 * Topics: String, Depth-First Search, Design, Trie
 *
 * Design a data structure that supports adding new words and finding if a string matches any previously added string.
 * Implement the WordDictionary class:
 * Example:
 *
 * Example 1:
 *     Input
 *     ["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
 *     [[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
 *     Output
 *     [null,null,null,null,false,true,true,true]
 *
 * Hint: Build a Trie from the word list, then search with DFS handling '.' wildcards by trying all children.
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../../wasm_libs/js/io.mjs';

function solve(words, searchWords) {
  throw new Error("NotImplementedError");
}

const nWords = readInt();
const words = [];
for (let i = 0; i < nWords; i++) {
  words.push(readLine());
}
const nSearches = readInt();
const searchWords = [];
for (let i = 0; i < nSearches; i++) {
  searchWords.push(readLine());
}
const results = solve(words, searchWords);
for (const r of results) {
  writeBool(r);
}
