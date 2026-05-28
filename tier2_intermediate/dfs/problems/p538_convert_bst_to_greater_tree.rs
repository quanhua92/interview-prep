/*
 * P538: Convert BST to Greater Tree [PREMIUM] (Medium)
 * https://leetcode.com/problems/convert-bst-to-greater-tree/
 * Topics: Tree, Depth-First Search, Binary Search Tree, Binary Tree
 */

use wasm_libs::*;
use std::io::{self, Write};
use std::collections::VecDeque;

fn build_tree(vals: &[i32], nl: i32) -> (Vec<i32>, Vec<i32>) {
    todo!();
}

fn main() {
    let line = read_line();
    if line.trim().is_empty() {
        writeln!(io::stdout(), "").unwrap();
        return;
    }
    let nl = 2147483647i32;
    let vals: Vec<i32> = line.split_whitespace()
        .map(|t| if t == "null" { nl } else { t.parse().unwrap() })
        .collect();
    if vals.is_empty() || vals[0] == nl {
        writeln!(io::stdout(), "").unwrap();
        return;
    }

    let (left, right) = build_tree(&vals, nl);
    let mut tree_vals = vals.clone();

    fn reverse_inorder(idx: i32, tree_vals: &mut [i32], left: &[i32], right: &[i32], total: &mut i32) {
        if idx < 0 { return; }
        reverse_inorder(right[idx as usize], tree_vals, left, right, total);
        *total += tree_vals[idx as usize];
        tree_vals[idx as usize] = *total;
        reverse_inorder(left[idx as usize], tree_vals, left, right, total);
    }

    let mut total = 0i32;
    reverse_inorder(0, &mut tree_vals, &left, &right, &mut total);

    let mut result: Vec<Option<i32>> = Vec::new();
    let mut queue = VecDeque::new();
    queue.push_back(0i32);
    while !queue.is_empty() {
        let idx = queue.pop_front().unwrap();
        if idx < 0 {
            result.push(None);
        } else {
            result.push(Some(tree_vals[idx as usize]));
            queue.push_back(left[idx as usize]);
            queue.push_back(right[idx as usize]);
        }
    }
    while result.last() == Some(&None) && result.len() > 1 { result.pop(); }

    let mut out = io::stdout().lock();
    let mut first = true;
    for v in &result {
        if !first { write!(out, " ").unwrap(); }
        first = false;
        match v {
            None => write!(out, "null").unwrap(),
            Some(val) => write!(out, "{}", val).unwrap(),
        }
    }
    writeln!(out).unwrap();
}
