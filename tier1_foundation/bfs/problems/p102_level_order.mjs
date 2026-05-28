/**
 * P102: Binary Tree Level Order Traversal (Medium)
 * https://leetcode.com/problems/binary-tree-level-order-traversal/
 * Topics: Tree, Breadth-First Search, Binary Tree
 *
 * Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).
 *
 * Example 1:
 *     Input: root = [3,9,20,null,null,15,7]
 *     Output: [[3],[9,20],[15,7]]
 *
 * Example 2:
 *     Input: root = [1]
 *     Output: [[1]]
 *
 * Example 3:
 *     Input: root = []
 *     Output: []
 *
 * Constraints:
 *     - The number of nodes in the tree is in the range [0, 2000].
 *     - -1000 <= Node.val <= 1000
 *
 * Hints:
 *     - Use a queue to perform BFS.
 *
 * Hint: Use a queue to process nodes level by level.
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../wasm_libs/js/io.mjs';

const NULL_VAL = -2147483648;

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
    throw new Error("NotImplementedError");
}

const n = readInt();
if (n !== 0) {
  const tokens = readLine().split(' ');
  const vals = tokens.map(t => t === 'null' ? null : parseInt(t, 10));
  const result = solve(vals);
  for (const row of result) writeInts(row);
}
