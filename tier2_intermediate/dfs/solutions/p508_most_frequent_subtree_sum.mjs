/**
 * P508: Most Frequent Subtree Sum [PREMIUM] (Medium)
 * https://leetcode.com/problems/most-frequent-subtree-sum/
 * Topics: Hash Table, Tree, Depth-First Search, Binary Tree
 *
 * Given the root of a binary tree, return the most frequent subtree sum. If there is a tie, return all the values with the highest frequency in any order.
 * The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself).
 * Example 1:
 *     Input: root = [5,2,-3]
 *     Output: [2,-3,4]
 *
 * Example 2:
 *     Input: root = [5,2,-5]
 *     Output: [2]
 *
 * Constraints:
 *     - The number of nodes in the tree is in the range [1, 10^4].
 *     - -10^5 <= Node.val <= 10^5
 */

import { readLine, writeInts } from '../../../wasm_libs/js/io.mjs';

function buildTree(arr) {
  if (arr === null || arr.length === 0) return null;
  const root = { val: arr[0], left: null, right: null };
  const queue = [root];
  let i = 1;
  while (i < arr.length && queue.length > 0) {
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

function solve(root) {
  const freq = new Map();
  function subtreeSum(node) {
    const s = node.val + (node.left ? subtreeSum(node.left) : 0) + (node.right ? subtreeSum(node.right) : 0);
    freq.set(s, (freq.get(s) || 0) + 1);
    return s;
  }
  subtreeSum(root);
  let maxCount = 0;
  for (const count of freq.values()) { if (count > maxCount) maxCount = count; }
  const result = [];
  for (const [s, c] of freq) { if (c === maxCount) result.push(s); }
  return result.sort((a, b) => a - b);
}

const line = readLine();
const vals = line.split(' ').map(x => x === 'null' ? null : parseInt(x, 10));
const root = buildTree(vals);
writeInts(solve(root));
