/**
 * P449: Serialize and Deserialize BST [PREMIUM] (Medium)
 * https://leetcode.com/problems/serialize-and-deserialize-bst/
 * Topics: String, Tree, Depth-First Search, Breadth-First Search, Design, Binary Search Tree, Binary Tree
 *
 * Serialization is converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.
 * Design an algorithm to serialize and deserialize a binary search tree. There is no restriction on how your serialization/deserialization algorithm should work. You need to ensure that a binary search tree can be serialized to a string, and this string can be deserialized to the original tree structure.
 * The encoded string should be as compact as possible.
 * Example 1:
 *     Input: root = [2,1,3]
 *     Output: [2,1,3]
 *
 * Example 2:
 *     Input: root = []
 *     Output: []
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
 * Codec Class (Using Compact BST Boundaries)
 * ===================================================================== */

class Codec {
    serialize(root) {
        throw new Error("NotImplementedError");
    }

    deserialize(data) {
        throw new Error("NotImplementedError");
    }
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

function convertTreeToList(root) {
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

/* =====================================================================
 * Solve
 * ===================================================================== */

function solve(root) {
    const codec = new Codec();
    const data = codec.serialize(root);
    return codec.deserialize(data);
}

/* =====================================================================
 * Main
 * ===================================================================== */

const n = readInt();
if (n === 0) {
} else {
    const tokens = readLine().split(' ');
    const vals = tokens.map(t => t === 'null' ? null : parseInt(t, 10));
    const tree = buildTreeFromList(vals);
    const result = solve(tree);
    const result_list = convertTreeToList(result);
    const parts = result_list.map(v => v === null ? 'null' : String(v));
    writeString(parts.join(' '));
}
