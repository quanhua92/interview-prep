/*
 * P450: Delete Node in a BST [PREMIUM] (Medium)
 * https://leetcode.com/problems/delete-node-in-a-bst/
 * Topics: Tree, Binary Search Tree, Binary Tree
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
    todo!();
}

fn find_min(node: &Box<TreeNode>) -> i32 {
    todo!();
}

fn delete_node(root: Option<Box<TreeNode>>, key: i32) -> Option<Box<TreeNode>> {
    todo!();
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
