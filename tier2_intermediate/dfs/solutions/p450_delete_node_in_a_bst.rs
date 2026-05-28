/*
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
 * Template (python3):
 *     # Definition for a binary tree node.
 *     # class TreeNode:
 *     #     def __init__(self, val=0, left=None, right=None):
 *     #         self.val = val
 *     #         self.left = left
 *     #         self.right = right
 *     class Solution:
 *         def deleteNode(self, root: Optional[TreeNode], key: int) -> Optional[TreeNode]:
 *
 * Hint: Recurse down the BST to find the target. When found with two children,
 * find the leftmost node in the right subtree (inorder successor), attach the left
 * subtree to it, and return the right subtree as the new root.
 */

use wasm_libs::*;
use std::io::{self, Write};

#[derive(Debug, Clone)]
struct TreeNode {
    val: i32,
    left: Option<Box<TreeNode>>,
    right: Option<Box<TreeNode>>,
}

fn insert(root: Option<Box<TreeNode>>, val: i32) -> Option<Box<TreeNode>> {
    match root {
        None => Some(Box::new(TreeNode { val, left: None, right: None })),
        Some(mut r) => {
            if val < r.val { r.left = insert(r.left, val); }
            else { r.right = insert(r.right, val); }
            Some(r)
        }
    }
}

fn find_min(node: &Box<TreeNode>) -> i32 {
    let mut cur = node;
    while let Some(ref left) = cur.left { cur = left; }
    cur.val
}

fn delete_node(root: Option<Box<TreeNode>>, key: i32) -> Option<Box<TreeNode>> {
    match root {
        None => None,
        Some(mut r) => {
            if key < r.val {
                r.left = delete_node(r.left, key);
                Some(r)
            } else if key > r.val {
                r.right = delete_node(r.right, key);
                Some(r)
            } else {
                let left = r.left.take();
                let right = r.right.take();
                match (left, right) {
                    (None, Some(ri)) => Some(ri),
                    (Some(le), None) => Some(le),
                    (Some(le), Some(ri)) => {
                        let min_val = find_min(&ri);
                        let new_right = delete_node(Some(ri), min_val);
                        r.val = min_val;
                        r.left = Some(le);
                        r.right = new_right;
                        Some(r)
                    }
                    (None, None) => None,
                }
            }
        }
    }
}

fn main() {
    let tree_line = read_line();
    let key: i32 = read_line().trim().parse().unwrap();
    let nl = "null";
    let mut root: Option<Box<TreeNode>> = None;
    for tok in tree_line.split_whitespace() {
        if tok == nl { continue; }
        let v: i32 = tok.parse().unwrap();
        root = insert(root, v);
    }
    let root = delete_node(root, key);
    match root {
        None => { let mut out = io::stdout().lock(); writeln!(out, "null").unwrap(); },
        Some(r) => {
            let mut q = std::collections::VecDeque::new();
            q.push_back(Some(r));
            let mut first = true;
            let mut all: Vec<Option<Box<TreeNode>>> = Vec::new();
            while let Some(node) = q.pop_front() {
                all.push(node);
                if let Some(n) = all.last().unwrap() {
                    q.push_back(n.left.clone());
                    q.push_back(n.right.clone());
                }
            }
            while all.last().is_some() && all.last().unwrap().is_none() { all.pop(); }
            let mut out = io::stdout().lock();
            let mut first = true;
            for n in &all {
                if !first { write!(out, " ").unwrap(); }
                first = false;
                match n {
                    None => write!(out, "null").unwrap(),
                    Some(node) => write!(out, "{}", node.val).unwrap(),
                }
            }
            writeln!(out).unwrap();
        }
    }
}
