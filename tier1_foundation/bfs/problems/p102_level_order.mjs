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

/* =====================================================================
 * Core Data Structure
 * ===================================================================== */

class TreeNode {
    constructor(val) {
        this.val = val;
        this.left = null;
        this.right = null;
    }
}

/* =====================================================================
 * LeetCode Solution
 * ===================================================================== */

function solve(root) {
    throw new Error("NotImplementedError");
}

/* =====================================================================
 * Environment Utilities
 * ===================================================================== */

function buildTreeFromList(arr) {
    if (!arr || arr.length === 0 || arr[0] === null) return null;
    const root = new TreeNode(arr[0]);
    const queue = [root];
    let i = 1;
    while (queue.length > 0 && i < arr.length) {
        const node = queue.shift();
        if (i < arr.length) {
            if (arr[i] !== null) {
                node.left = new TreeNode(arr[i]);
                queue.push(node.left);
            }
            i++;
        }
        if (i < arr.length) {
            if (arr[i] !== null) {
                node.right = new TreeNode(arr[i]);
                queue.push(node.right);
            }
            i++;
        }
    }
    return root;
}

/* =====================================================================
 * Runtime System Execution Block
 * ===================================================================== */

const n = readInt();
if (n === 0) {
} else {
    const tokens = readLine().split(' ');
    const vals = tokens.map(t => t === 'null' ? null : parseInt(t, 10));
    const tree = buildTreeFromList(vals);
    const result = solve(tree);
    for (const row of result) writeInts(row);
}
