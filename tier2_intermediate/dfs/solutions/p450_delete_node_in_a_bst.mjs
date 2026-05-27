/**
 * P450: Delete Node in a BST [PREMIUM] (Medium)
 * https://leetcode.com/problems/delete-node-in-a-bst/
 * Topics: Tree, Binary Search Tree, Binary Tree
 */

import { readLine, readInts } from '../../../wasm_libs/js/io.mjs';

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

function treeToList(root) {
  if (!root) return [];
  const result = [];
  const queue = [root];
  while (queue.length > 0) {
    const node = queue.shift();
    if (node) {
      result.push(node.val);
      queue.push(node.left);
      queue.push(node.right);
    } else {
      result.push(null);
    }
  }
  while (result.length > 0 && result[result.length - 1] === null) {
    result.pop();
  }
  return result;
}

function deleteNode(root, key) {
  if (!root) return null;
  if (key < root.val) {
    root.left = deleteNode(root.left, key);
  } else if (key > root.val) {
    root.right = deleteNode(root.right, key);
  } else {
    if (!root.left) return root.right;
    if (!root.right) return root.left;
    let minNode = root.right;
    while (minNode.left) {
      minNode = minNode.left;
    }
    root.val = minNode.val;
    root.right = deleteNode(root.right, minNode.val);
  }
  return root;
}

const treeLine = readLine();
const key = parseInt(readLine(), 10);
const vals = treeLine.split(' ').map(x => x === 'null' ? null : parseInt(x, 10));
const root = buildTree(vals);
const result = treeToList(deleteNode(root, key));
const _w = (s) => { if (typeof Javy !== 'undefined' && Javy.IO) { Javy.IO.write(s); return; } process.stdout.write(s); };
_w((result.length === 0 ? 'null' : result.map(v => v === null ? 'null' : String(v)).join(' ')) + '\n');
