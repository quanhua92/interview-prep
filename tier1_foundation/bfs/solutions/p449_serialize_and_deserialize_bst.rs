/*
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
 *
 * Constraints:
 *     - The number of nodes in the tree is in the range [0, 10^4].
 *     - 0 <= Node.val <= 10^4
 *     - The input tree is guaranteed to be a binary search tree.
 *
 * Template (python3):
 *     # Definition for a binary tree node.
 *     # class TreeNode:
 *     #     def __init__(self, x):
 *     #         self.val = x
 *     #         self.left = None
 *     #         self.right = None
 *
 *     class Codec:
 *
 *         def serialize(self, root: Optional[TreeNode]) -> str:
 *             '''Encodes a tree to a single string.
 *             '''
 *
 *
 *         def deserialize(self, data: str) -> Optional[TreeNode]:
 *             '''Decodes your encoded data to tree.
 *             '''
 *
 *     # Your Codec object will be instantiated and called as such:
 *     # Your Codec object will be instantiated and called as such:
 *     # ser = Codec()
 *     # deser = Codec()
 *     # tree = ser.serialize(root)
 *     # ans = deser.deserialize(tree)
 *     # return ans
 */

use wasm_libs::*;
use std::cell::RefCell;
use std::collections::VecDeque;
use std::rc::Rc;

const NULL_VAL: i32 = i32::MIN;

struct TreeNode {
    val: i32,
    left: Option<Rc<RefCell<TreeNode>>>,
    right: Option<Rc<RefCell<TreeNode>>>,
}

fn parse_tree_line(line: &str) -> Vec<i32> {
    line.split_whitespace()
        .map(|s| if s == "null" { NULL_VAL } else { s.parse().unwrap() })
        .collect()
}

fn build_tree(vals: &[i32]) -> Option<Rc<RefCell<TreeNode>>> {
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

impl Solution {
    fn solve(vals: &[i32]) -> Vec<i32> {
        if vals.is_empty() || vals[0] == NULL_VAL { return vec![]; }
        let root = build_tree(vals).unwrap();
        let mut result = Vec::new();
        let mut queue: VecDeque<Option<Rc<RefCell<TreeNode>>>> = VecDeque::new();
        queue.push_back(Some(Rc::clone(&root)));
        while !queue.is_empty() {
            let node = queue.pop_front().unwrap();
            match node {
                Some(n) => {
                    let n_ref = n.borrow();
                    result.push(n_ref.val);
                    let left = n_ref.left.clone();
                    let right = n_ref.right.clone();
                    drop(n_ref);
                    if left.is_some() || right.is_some() {
                        queue.push_back(left);
                        queue.push_back(right);
                    }
                }
                None => { result.push(NULL_VAL); }
            }
        }
        while !result.is_empty() && *result.last().unwrap() == NULL_VAL { result.pop(); }
        result
    }
}

struct Solution;

fn main() {
    let n = read_int();
    if n == 0 { return; }
    let line = read_line();
    let vals = parse_tree_line(&line);
    let result = Solution::solve(&vals);
    let parts: Vec<String> = result.iter().map(|&v| if v == NULL_VAL { "null".to_string() } else { v.to_string() }).collect();
    write_string(&parts.join(" "));
    std::process::exit(0);
}
