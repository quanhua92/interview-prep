/**
 * P212: Word Search II (Hard)
 * https://leetcode.com/problems/word-search-ii/
 * Topics: Array, String, Backtracking, Trie, Matrix
 *
 * Given an m x n board of characters and a list of strings words, return all words on the board.
 * Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.
 *
 * Example 1:
 *     Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
 *     Output: ["eat","oath"]
 *
 * Example 2:
 *     Input: board = [["a","b"],["c","d"]], words = ["abcb"]
 *     Output: []
 *
 * Hint: Build a Trie from the word list, then use DFS on the board to find matching words.
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../../wasm_libs/js/io.mjs';

function solve(board, words) {
  throw new Error("NotImplementedError");
}

const rows = readInt();
const cols = readInt();
const board = [];
for (let r = 0; r < rows; r++) {
  const line = readLine();
  board.push(line.split(""));
}
const nWords = readInt();
const words = [];
for (let i = 0; i < nWords; i++) {
  words.push(readLine());
}
const result = solve(board, words);
writeInt(result.length);
for (const w of result) {
  writeString(w);
}
