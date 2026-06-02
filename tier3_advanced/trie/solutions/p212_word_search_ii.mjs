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
 * Constraints:
 *     - m == board.length
 *     - n == board[i].length
 *     - 1 <= m, n <= 12
 *     - board[i][j] is a lowercase English letter.
 *     - 1 <= words.length <= 3 * 10^4
 *     - 1 <= words[i].length <= 10
 *     - words[i] consists of lowercase English letters.
 *     - All the strings of words are unique.
 *
 * Hints:
 *     - You would need to optimize your backtracking to pass the larger test. Could you stop backtracking earlier?
 *     - If the current candidate does not exist in all words' prefix, you could stop backtracking immediately. What kind of data structure could answer such query efficiently? Does a hash table work? Why or why not? How about a Trie? If you would like to learn how to implement a basic trie, please work on this problem: <a href="https://leetcode.com/problems/implement-trie-prefix-tree/">Implement Trie (Prefix Tree)</a> first.
 *
 * Hint: Build a Trie from the word list, then use DFS on the board to find matching words.
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../../wasm_libs/js/io.mjs';

class TrieNode {
  constructor() {
    this.children = {};
    this.word = null;
  }
}

function solve(board, words) {
  const rows = board.length;
  const cols = board[0].length;
  const result = [];

  function buildTrie(words) {
    const root = new TrieNode();
    for (const w of words) {
      let node = root;
      for (const ch of w) {
        if (!(ch in node.children)) {
          node.children[ch] = new TrieNode();
        }
        node = node.children[ch];
      }
      node.word = w;
    }
    return root;
  }

  function dfs(r, c, parent) {
    const ch = board[r][c];
    const curr = parent.children[ch];
    if (!curr) return;
    if (curr.word) {
      result.push(curr.word);
      curr.word = null;
    }
    board[r][c] = "#";
    for (const [dr, dc] of [[0, 1], [0, -1], [1, 0], [-1, 0]]) {
      const nr = r + dr;
      const nc = c + dc;
      if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && board[nr][nc] !== "#") {
        dfs(nr, nc, curr);
      }
    }
    board[r][c] = ch;
    if (Object.keys(curr.children).length === 0) {
      delete parent.children[ch];
    }
  }

  const root = buildTrie(words);
  for (let r = 0; r < rows; r++) {
    for (let c = 0; c < cols; c++) {
      dfs(r, c, root);
    }
  }
  return result.sort();
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
