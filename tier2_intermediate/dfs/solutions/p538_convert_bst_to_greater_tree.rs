/*
 * P538: Convert BST to Greater Tree [PREMIUM] (Medium)
 * https://leetcode.com/problems/convert-bst-to-greater-tree/
 * Topics: Tree, Depth-First Search, Binary Search Tree, Binary Tree
 */

use wasm_libs::*;
use std::collections::VecDeque;
use std::io::Write;

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

fn reverse_inorder(node: &Option<Box<TreeNode>>, total: &mut i32) {
    if let Some(n) = node {
        reverse_inorder(&n.right, total);
        *total += n.val;
        n.val = *total;
        reverse_inorder(&n.left, total);
    }
}

fn main() {
    let line = read_line();
    if line.trim().is_empty() { return; }
    let nl = 2147483647i32;
    let vals: Vec<i32> = line.split_whitespace()
        .map(|t| if t == "null" { nl } else { t.parse().unwrap() })
        .collect();
    if vals.is_empty() || vals[0] == nl { return; }
    let mut root = from_list(&vals);
    let mut total = 0;
    reverse_inorder(&mut root, &mut total);
    let mut all: Vec<Option<i32>> = Vec::new();
    let mut q = VecDeque::new();
    q.push_back(root.as_ref().map(|n| n.val));
    while let Some(node_opt) = q.pop_front() {
        all.push(node_opt);
    }
    let root = root.unwrap();
    let mut q = VecDeque::new();
    q.push_back(Some(root.as_ref()));
    while let Some(node_opt) = q.pop_front() {
        match node_opt {
            None => all.push(None),
            Some(n) => {
                all.push(n.left.as_ref().map(|l| l.val));
                all.push(n.right.as_ref().map(|r| r.val));
                q.push_back(n.left.as_ref());
                q.push_back(n.right.as_ref());
            }
        }
    }
    while all.last() == Some(&None) && all.len() > 1 { all.pop(); }
    let mut out = io::stdout().lock();
    let mut first = true;
    for v in &all {
        if !first { write!(out, " ").unwrap(); }
        first = false;
        match v {
            None => write!(out, "null").unwrap(),
            Some(val) => write!(out, "{}", val).unwrap(),
        }
    }
    writeln!(out).unwrap();
}
