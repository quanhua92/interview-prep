/**
 * P450: Delete Node in a BST [PREMIUM] (Medium)
 * https://leetcode.com/problems/delete-node-in-a-bst/
 * Topics: Tree, Binary Search Tree, Binary Tree
 *
 * Given the root of a Binary Search Tree (BST) and a key, delete the node with the given key in the BST.
 * Return the root node reference (possibly updated) of the BST.
 *
 * The deletion process involves finding the node and handling three cases:
 * - Node has no children: simply remove it.
 * - Node has one child: replace the node with its child.
 * - Node has two children: find the inorder successor (smallest in the right subtree),
 *   attach the deleted node's left subtree to the successor, and replace with the right subtree.
 *
 * Example 1:
 *     Input: root = [5,3,6,2,4,null,7], key = 3
 *     Output: [5,4,6,2,null,null,7]
 *     Explanation: The node with value 3 is deleted. One valid answer is [5,4,6,2,null,null,7],
 *     another is [5,2,6,null,4,null,7].
 *
 * Example 2:
 *     Input: root = [5,3,6,2,4,null,7], key = 0
 *     Output: [5,3,6,2,4,null,7]
 *     Explanation: The key 0 is not found, so the tree is unchanged.
 *
 * Example 3:
 *     Input: root = [], key = 0
 *     Output: []
 *
 * Constraints:
 *     - The number of nodes in the tree is in the range [0, 10^4].
 *     - -10^5 <= Node.val <= 10^5
 *     - Each node has a unique value.
 *     - root is a valid binary search tree.
 *
 * Hint: Recurse down the BST to find the target. When found with two children,
 * find the leftmost node in the right subtree (inorder successor), attach the left
 * subtree to it, and return the right subtree as the new root.
 */

import { readLine, writeString } from '../../../wasm_libs/js/io.mjs';

class TreeNode {
    constructor(val) {
        this.val = val;
        this.left = null;
        this.right = null;
    }
}

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

function solve(root, key) {
    if (!root) return null;
    if (key < root.val) {
        root.left = solve(root.left, key);
    } else if (key > root.val) {
        root.right = solve(root.right, key);
    } else {
        if (!root.left) return root.right;
        if (!root.right) return root.left;
        let minNode = root.right;
        while (minNode.left) {
            minNode = minNode.left;
        }
        root.val = minNode.val;
        root.right = solve(root.right, minNode.val);
    }
    return root;
}

const treeLine = readLine();
const key = parseInt(readLine(), 10);
const vals = treeLine.split(' ').map(x => x === 'null' ? null : parseInt(x, 10));
const root = buildTreeFromList(vals);
const result = treeToList(solve(root, key));
writeString(result.length === 0 ? 'null' : result.map(v => v === null ? 'null' : String(v)).join(' '));
