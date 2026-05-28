/**
 * P572: Subtree of Another Tree [PREMIUM] (Easy)
 * https://leetcode.com/problems/subtree-of-another-tree/
 * Topics: Tree, Depth-First Search, String Matching, Binary Tree, Hash Function
 *
 * Given the roots of two binary trees root and subRoot, return true if there is a subtree of root with the same structure and node values of subRoot and false otherwise.
 * A subtree of a binary tree tree is a tree that consists of a node in tree and all of this node's descendants. The tree tree could also be considered as a subtree of itself.
 * Example 1:
 *     Input: root = [3,4,5,1,2], subRoot = [4,1,2]
 *     Output: true
 *
 * Example 2:
 *     Input: root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
 *     Output: false
 *
 * Constraints:
 *     - The number of nodes in the root tree is in the range [1, 2000].
 *     - The number of nodes in the subRoot tree is in the range [1, 1000].
 *     - -104 <= root.val <= 104
 *     - -104 <= subRoot.val <= 104
 *
 * Hint: Which approach is better here- recursive or iterative?
 * Hint: If recursive approach is better, can you write recursive function with its parameters?
 * Hint: Two trees s and t are said to be identical if their root values are same and their left and right subtrees are identical. Can you write this in form of recursive formulae?
 * Hint: Recursive formulae can be:
 * isIdentical(s,t)= s.val==t.val AND isIdentical(s.left,t.left) AND isIdentical(s.right,t.right)
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
