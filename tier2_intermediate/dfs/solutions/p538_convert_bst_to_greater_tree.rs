/*
 * P538: Convert BST to Greater Tree [PREMIUM] (Medium)
 * https://leetcode.com/problems/convert-bst-to-greater-tree/
 * Topics: Tree, Depth-First Search, Binary Search Tree, Binary Tree
 *
 * Given the root of a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST is changed to the original key plus the sum of all keys greater than the original key in BST.
 * As a reminder, a binary search tree is a tree that satisfies these constraints:
 * Example 2:
 * Note: This question is the same as 1038: https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/
 * Example 1:
 *     Input: root = [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
 *     Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]
 *
 * Example 2:
 *     Input: root = [0,null,1]
 *     Output: [1,null,1]
 *
 * Constraints:
 *     - The number of nodes in the tree is in the range [0, 10^4].
 *     - -10^4 <= Node.val <= 10^4
 *     - All the values in the tree are unique.
 *     - root is guaranteed to be a valid binary search tree.
 *
 * Template (python3):
 *     # Definition for a binary tree node.
 *     # class TreeNode:
 *     #     def __init__(self, val=0, left=None, right=None):
 *     #         self.val = val
 *     #         self.left = left
 *     #         self.right = right
 *     class Solution:
 *         def convertBST(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
 */

use wasm_libs::*;
use std::io::{self, Write};
use std::collections::VecDeque;

fn build_tree(vals: &[i32], nl: i32) -> (Vec<i32>, Vec<i32>) {
    let n = vals.len();
    if n == 0 || vals[0] == nl { return (vec![], vec![]); }
    let mut left = vec![-1i32; n];
    let mut right = vec![-1i32; n];
    let mut qi = 1usize;
    let mut queue = VecDeque::new();
    queue.push_back(0usize);
    while let Some(i) = queue.pop_front() {
        if qi < n {
            left[i] = if vals[qi] == nl { -1 } else { qi as i32 };
            if vals[qi] != nl { queue.push_back(qi); }
            qi += 1;
        }
        if qi < n {
            right[i] = if vals[qi] == nl { -1 } else { qi as i32 };
            if vals[qi] != nl { queue.push_back(qi); }
            qi += 1;
        }
    }
    (left, right)
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
