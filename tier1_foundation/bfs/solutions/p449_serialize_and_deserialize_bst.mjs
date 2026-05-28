/**
 * P449: Serialize and Deserialize BST [PREMIUM] (Medium)
 * https://leetcode.com/problems/serialize-and-deserialize-bst/
 * Topics: String, Tree, Depth-First Search, Breadth-First Search, Design, Binary Search Tree, Binary Tree
 *
 * Serialization is converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.
 * Design an algorithm to serialize and deserialize a binary search tree. There is no restriction on how your serialization/deserialization algorithm should work. You need to ensure that a binary search tree can be serialized to a string, and this string can be deserialized to the original tree structure.
 * The encoded string should be as compact as possible.
 * Example 1:
 *     Input: root = [2,1,3]
 *     Output: [2,1,3]
 *
 * Example 2:
 *     Input: root = []
 *     Output: []
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../wasm_libs/js/io.mjs';

function buildTree(arr) {
  if (arr.length === 0) return null;
  const root = { val: arr[0], left: null, right: null };
  const queue = [root];
  let i = 1;
  while (queue.length > 0 && i < arr.length) {
    const node = queue.shift();
    if (i < arr.length && arr[i] !== null) {
      node.left = { val: arr[i], left: null, right: null };
      queue.push(node.left);
    }
    i++;
    if (i < arr.length && arr[i] !== null) {
      node.right = { val: arr[i], left: null, right: null };
      queue.push(node.right);
    }
    i++;
  }
  return root;
}

function solve(vals) {
  if (!vals || vals.length === 0) return [];
  const root = buildTree(vals);
  const serialized = [];
  const queue = [root];
  while (queue.length > 0) {
    const node = queue.shift();
    if (node) {
      serialized.push(node.val);
      if (node.left || node.right) {
        queue.push(node.left);
        queue.push(node.right);
      }
    } else {
      serialized.push(null);
    }
  }
  while (serialized.length > 0 && serialized[serialized.length - 1] === null) {
    serialized.pop();
  }
  return serialized;
}

const n = readInt();
if (n === 0) {
} else {
  const tokens = readLine().split(' ');
  const vals = tokens.map(t => t === 'null' ? null : parseInt(t, 10));
  const result = solve(vals);
  const parts = result.map(v => v === null ? 'null' : String(v));
  writeString(parts.join(' '));
}
