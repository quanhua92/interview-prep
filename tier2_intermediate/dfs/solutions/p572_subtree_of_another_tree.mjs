/**
 * P572: Subtree of Another Tree [PREMIUM] (Easy)
 * https://leetcode.com/problems/subtree-of-another-tree/
 * Topics: Tree, Depth-First Search, String Matching, Binary Tree, Hash Function
 */

import { readLine, writeBool } from '../../../wasm_libs/js/io.mjs';

function buildTree(arr) {
  if (arr.length === 0) return null;
  const root = { val: arr[0], left: null, right: null };
  const queue = [root];
  let i = 1;
  while (queue.length > 0 && i < arr.length) {
    const node = queue.shift();
    if (i < arr.length && arr[i] !== null) { node.left = { val: arr[i], left: null, right: null }; queue.push(node.left); }
    i++;
    if (i < arr.length && arr[i] !== null) { node.right = { val: arr[i], left: null, right: null }; queue.push(node.right); }
    i++;
  }
  return root;
}

function isSame(a, b) {
  if (!a && !b) return true;
  if (!a || !b) return false;
  return a.val === b.val && isSame(a.left, b.left) && isSame(a.right, b.right);
}

function solve(root, subRoot) {
  if (!subRoot) return true;
  if (!root) return false;
  if (isSame(root, subRoot)) return true;
  return solve(root.left, subRoot) || solve(root.right, subRoot);
}

const rootLine = readLine();
const subLine = readLine();
const rootVals = rootLine.split(' ').map(x => x === 'null' ? null : parseInt(x, 10));
const subVals = subLine.split(' ').map(x => x === 'null' ? null : parseInt(x, 10));
writeBool(solve(buildTree(rootVals), buildTree(subVals)));
