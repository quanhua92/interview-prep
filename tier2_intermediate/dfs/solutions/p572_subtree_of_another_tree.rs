/*
 * P572: Subtree of Another Tree [PREMIUM] (Easy)
 * https://leetcode.com/problems/subtree-of-another-tree/
 * Topics: Tree, Depth-First Search, String Matching, Binary Tree, Hash Function
 */

use wasm_libs::*;
use std::collections::VecDeque;

#[derive(Clone)]
struct TreeNode {
    val: i32,
    left: Option<Box<TreeNode>>,
    right: Option<Box<TreeNode>>,
}

fn from_list(vals: &[i32]) -> Option<Box<TreeNode>> {
    let nl = 2147483647i32;
    if vals.is_empty() || vals[0] == nl { return None; }
    let root = Box::new(TreeNode { val: vals[0], left: None, right: None });
    let mut queue = VecDeque::new();
    queue.push_back(root.clone());
    let mut vi = 1;
    while !queue.is_empty() && vi < vals.len() {
        let mut node = queue.pop_front().unwrap();
        if vi < vals.len() {
            if vals[vi] != nl {
                let child = Box::new(TreeNode { val: vals[vi], left: None, right: None });
                node.left = Some(child.clone());
                queue.push_back(child);
            }
            vi += 1;
        }
        if vi < vals.len() {
            if vals[vi] != nl {
                let child = Box::new(TreeNode { val: vals[vi], left: None, right: None });
                node.right = Some(child.clone());
                queue.push_back(child);
            }
            vi += 1;
        }
    }
    Some(root)
}

fn is_same(a: &Option<Box<TreeNode>>, b: &Option<Box<TreeNode>>) -> bool {
    match (a, b) {
        (None, None) => true,
        (None, _) | (_, None) => false,
        (Some(an), Some(bn)) => {
            an.val == bn.val && is_same(&an.left, &bn.left) && is_same(&an.right, &bn.right)
        }
    }
}

fn is_subtree(root: &Option<Box<TreeNode>>, sub_root: &Option<Box<TreeNode>>) -> bool {
    if sub_root.is_none() { return true; }
    if root.is_none() { return false; }
    if is_same(root, sub_root) { return true; }
    let r = root.as_ref().unwrap();
    is_subtree(&r.left, sub_root) || is_subtree(&r.right, sub_root)
}

fn main() {
    let root_line = read_line();
    let sub_line = read_line();
    let nl = 2147483647i32;
    let parse = |line: &str| -> Vec<i32> {
        line.split_whitespace()
            .map(|t| if t == "null" { nl } else { t.parse().unwrap() })
            .collect()
    };
    let root = from_list(&parse(&root_line));
    let sub = from_list(&parse(&sub_line));
    write_bool(is_subtree(&root, &sub));
}
