/**
 * P513: Find Bottom Left Tree Value [PREMIUM] (Medium)
 * https://leetcode.com/problems/find-bottom-left-tree-value/
 * Topics: Tree, Depth-First Search, Breadth-First Search, Binary Tree
 *
 * Given the root of a binary tree, return the leftmost value in the last row of the tree.
 * Example 1:
 *     Input: root = [2,1,3]
 *     Output: 1
 *
 * Example 2:
 *     Input: root = [1,2,3,4,null,5,6,null,null,7]
 *     Output: 7
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
    writeInt(result);
}
