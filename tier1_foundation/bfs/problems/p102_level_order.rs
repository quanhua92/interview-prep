/*
 * P102: Binary Tree Level Order Traversal (Medium)
 * https://leetcode.com/problems/binary-tree-level-order-traversal/
 * Topics: Tree, Breadth-First Search, Binary Tree
 *
 * Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).
 *
 * Example 1:
 *     Input: root = [3,9,20,null,null,15,7]
 *     Output: [[3],[9,20],[15,7]]
 *
 * Example 2:
 *     Input: root = [1]
 *     Output: [[1]]
 *
 * Example 3:
 *     Input: root = []
 *     Output: []
 *
 * Constraints:
 *     - The number of nodes in the tree is in the range [0, 2000].
 *     - -1000 <= Node.val <= 1000
 *
 * Hints:
 *     - Use a queue to perform BFS.
 *
 * Template (python3):
 *     # Definition for a binary tree node.
 *     # class TreeNode:
 *     #     def __init__(self, val=0, left=None, right=None):
 *     #         self.val = val
 *     #         self.left = left
 *     #         self.right = right
 *     class Solution:
 *         def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
 *
 * Hint: Use a queue to process nodes level by level.
 */

use wasm_libs::*;
use std::collections::VecDeque;

const NULL_VAL: i32 = i32::MIN;

fn parse_tree_line(line: &str) -> Vec<i32> {
    line.split_whitespace()
        .map(|s| if s == "null" { NULL_VAL } else { s.parse().unwrap() })
        .collect()
}

fn build_tree(vals: &[i32]) -> Option<Rc<TreeNode>> {
    if vals.is_empty() || vals[0] == NULL_VAL { return None; }
    let root = Rc::new(RefCell::new(TreeNode { val: vals[0], left: None, right: None }));
    let mut queue: VecDeque<Rc<RefCell<TreeNode>>> = VecDeque::new();
    queue.push_back(Rc::clone(&root));
    let mut i = 1;
    while !queue.is_empty() && i < vals.len() {
        let node = queue.pop_front().unwrap();
        if i < vals.len() {
            if vals[i] != NULL_VAL {
                let child = Rc::new(RefCell::new(TreeNode { val: vals[i], left: None, right: None }));
                node.borrow_mut().left = Some(Rc::clone(&child));
                queue.push_back(child);
            }
            i += 1;
        }
        if i < vals.len() {
            if vals[i] != NULL_VAL {
                let child = Rc::new(RefCell::new(TreeNode { val: vals[i], left: None, right: None }));
                node.borrow_mut().right = Some(Rc::clone(&child));
                queue.push_back(child);
            }
            i += 1;
        }
    }
    Some(root)
}

struct TreeNode {
    val: i32,
    left: Option<Rc<RefCell<TreeNode>>>,
    right: Option<Rc<RefCell<TreeNode>>>,
}

use std::cell::RefCell;
use std::rc::Rc;

impl Solution {
    fn level_order(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<Vec<i32>> {
    todo!()
}
}

struct Solution;

fn main() {
    let n = read_int();
    if n == 0 { return; }
    let line = read_line();
    let vals = parse_tree_line(&line);
    let root = build_tree(&vals);
    let result = Solution::level_order(root);
    for row in &result { write_ints(row); }
    std::process::exit(0);
}
