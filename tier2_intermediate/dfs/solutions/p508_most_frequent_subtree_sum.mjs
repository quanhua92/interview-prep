/**
 * P508: Most Frequent Subtree Sum [PREMIUM] (Medium)
 * https://leetcode.com/problems/most-frequent-subtree-sum/
 * Topics: Hash Table, Tree, Depth-First Search, Binary Tree
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
