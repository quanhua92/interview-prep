/**
 * P572: Subtree of Another Tree [PREMIUM] (Easy)
 * https://leetcode.com/problems/subtree-of-another-tree/
 * Topics: Tree, Depth-First Search, String Matching, Binary Tree, Hash Function
 *
 * Given the roots of two binary trees root and subRoot, return true if there is a subtree of root with the same structure and node values of subRoot.
 *
 * Example 1:
 *     Input: root = [3,4,5,1,2], subRoot = [4,1,2]
 *     Output: true
 *
 * Example 2:
 *     Input: root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
 *     Output: false
 *
 * Constraints:
 *     - The number of nodes in root is in the range [1, 2000].
 *     - -10^4 <= root.val <= 10^4
 *
 * Template (javascript):
 *     function isSubtree(root: TreeNode | null, subRoot: TreeNode | null): boolean
 */

import { readLine, writeBool } from '../../../wasm_libs/js/io.mjs';

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

function solve(root, subRoot) {
  throw new Error("NotImplementedError");
}

const rootLine = readLine();
const subLine = readLine();
const rootVals = rootLine.split(' ').map(x => x === 'null' ? null : parseInt(x, 10));
const subVals = subLine.split(' ').map(x => x === 'null' ? null : parseInt(x, 10));
writeBool(solve(buildTree(rootVals), buildTree(subVals)));
