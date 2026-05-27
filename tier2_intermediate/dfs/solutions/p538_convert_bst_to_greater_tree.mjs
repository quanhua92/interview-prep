/**
 * P538: Convert BST to Greater Tree [PREMIUM] (Medium)
 * https://leetcode.com/problems/convert-bst-to-greater-tree/
 * Topics: Tree, Depth-First Search, Binary Search Tree, Binary Tree
 */

import { readLine } from '../../../wasm_libs/js/io.mjs';

class TreeNode {
  constructor(val) { this.val = val; this.left = null; this.right = null; }
  static buildTree(arr) {
    if (!arr || arr.length === 0) return null;
    const root = new TreeNode(arr[0]);
    const queue = [root];
    let i = 1;
    while (i < arr.length && queue.length > 0) {
      const node = queue.shift();
      if (i < arr.length && arr[i] !== null) { node.left = new TreeNode(arr[i]); queue.push(node.left); }
      i++;
      if (i < arr.length && arr[i] !== null) { node.right = new TreeNode(arr[i]); queue.push(node.right); }
      i++;
    }
    return root;
  }
  toList() {
    const result = [];
    const queue = [this];
    while (queue.length > 0) {
      const node = queue.shift();
      result.push(node ? node.val : null);
      if (node) { queue.push(node.left); queue.push(node.right); }
    }
    while (result.length > 0 && result[result.length - 1] === null) result.pop();
    return result;
  }
}

function solve(root) {
  let total = 0;
  function reverseInorder(node) {
    if (!node) return;
    reverseInorder(node.right);
    total += node.val;
    node.val = total;
    reverseInorder(node.left);
  }
  reverseInorder(root);
  return root;
}

const line = readLine();
if (!line.trim()) {
  // empty tree - nothing to output
} else {
  const vals = line.split(' ').map(x => x === 'null' ? null : parseInt(x, 10));
  const root = TreeNode.buildTree(vals);
  const result = solve(root);
  if (result) {
    const list = result.toList();
    const _w = (s) => { if (typeof Javy !== 'undefined' && Javy.IO) { Javy.IO.write(s); return; } process.stdout.write(s); };
    _w(list.map(v => v === null ? 'null' : String(v)).join(' ') + '\n');
  }
}
