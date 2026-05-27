/*
 * P508: Most Frequent Subtree Sum [PREMIUM] (Medium)
 * https://leetcode.com/problems/most-frequent-subtree-sum/
 * Topics: Hash Table, Tree, Depth-First Search, Binary Tree
 */

use wasm_libs::*;
use std::collections::{HashMap, VecDeque};

#[derive(Clone)]
struct TreeNode {
    val: i32,
    left: Option<Box<TreeNode>>,
    right: Option<Box<TreeNode>>,
}

fn from_list(vals: &[i32]) -> Option<Box<TreeNode>> {
    if vals.is_empty() || vals[0] == 2147483647 { return None; }
    let root = Box::new(TreeNode { val: vals[0], left: None, right: None });
    let mut queue = VecDeque::new();
    queue.push_back(root.clone());
    let mut vi = 1;
    while !queue.is_empty() && vi < vals.len() {
        let mut node = queue.pop_front().unwrap();
        if vi < vals.len() {
            if vals[vi] != 2147483647 {
                let child = Box::new(TreeNode { val: vals[vi], left: None, right: None });
                node.left = Some(child.clone());
                queue.push_back(child);
            }
            vi += 1;
        }
        if vi < vals.len() {
            if vals[vi] != 2147483647 {
                let child = Box::new(TreeNode { val: vals[vi], left: None, right: None });
                node.right = Some(child.clone());
                queue.push_back(child);
            }
            vi += 1;
        }
    }
    Some(root)
}

fn subtree_sum(node: &Option<Box<TreeNode>>, freq: &mut HashMap<i32, i32>) -> i32 {
    match node {
        None => 0,
        Some(n) => {
            let s = n.val + subtree_sum(&n.left, freq) + subtree_sum(&n.right, freq);
            *freq.entry(s).or_insert(0) += 1;
            s
        }
    }
}

fn main() {
    let line = read_line();
    let nl = 2147483647i32;
    let vals: Vec<i32> = line.split_whitespace()
        .map(|t| if t == "null" { nl } else { t.parse().unwrap() })
        .collect();
    let root = from_list(&vals);
    let mut freq = HashMap::new();
    subtree_sum(&root, &mut freq);
    let max_freq = *freq.values().max().unwrap_or(&0);
    let mut result: Vec<i32> = freq.into_iter().filter(|&(_, v)| v == max_freq).map(|(k, _)| k).collect();
    result.sort();
    write_ints(&result);
}
