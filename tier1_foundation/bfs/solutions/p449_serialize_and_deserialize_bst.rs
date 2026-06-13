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

/* =====================================================================
 * Core Data Structure
 * ===================================================================== */

struct TreeNode {
    val: i32,
    left: Option<Rc<RefCell<TreeNode>>>,
    right: Option<Rc<RefCell<TreeNode>>>,
}

impl TreeNode {
    fn new(val: i32) -> Rc<RefCell<TreeNode>> {
        Rc::new(RefCell::new(TreeNode { val, left: None, right: None }))
    }
}

/* =====================================================================
 * CodecDFS (Using Compact BST Bounds — Pre-order)
 * ===================================================================== */

struct CodecDFS;

impl CodecDFS {
    fn serialize(root: &Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {
        let mut vals = Vec::new();
        Self::pre_order(root, &mut vals);
        vals
    }

    fn pre_order(node: &Option<Rc<RefCell<TreeNode>>>, vals: &mut Vec<i32>) {
        if let Some(n) = node {
            vals.push(n.borrow().val);
            let left = n.borrow().left.clone();
            let right = n.borrow().right.clone();
            Self::pre_order(&left, vals);
            Self::pre_order(&right, vals);
        }
    }

    fn deserialize(data: &[i32]) -> Option<Rc<RefCell<TreeNode>>> {
        if data.is_empty() { return None; }
        let mut idx: usize = 0;
        Self::build_bst(data, &mut idx, i64::MIN, i64::MAX)
    }

    fn build_bst(data: &[i32], idx: &mut usize, lo: i64, hi: i64) -> Option<Rc<RefCell<TreeNode>>> {
        if *idx >= data.len() { return None; }
        let v = data[*idx] as i64;
        if v < lo || v > hi { return None; }
        let val = data[*idx];
        *idx += 1;
        let root = TreeNode::new(val);
        root.borrow_mut().left = Self::build_bst(data, idx, lo, v);
        root.borrow_mut().right = Self::build_bst(data, idx, v, hi);
        Some(root)
    }
}

/* =====================================================================
 * CodecBFS (BFS Level-Order with null markers)
 * ===================================================================== */

struct CodecBFS;

impl CodecBFS {
    fn serialize(root: &Option<Rc<RefCell<TreeNode>>>) -> String {
        match root {
            None => String::new(),
            Some(r) => {
                let mut queue: VecDeque<Option<Rc<RefCell<TreeNode>>>> = VecDeque::new();
                queue.push_back(Some(r.clone()));
                let mut out: Vec<String> = Vec::new();
                while !queue.is_empty() {
                    let node = queue.pop_front().unwrap();
                    match node {
                        Some(n) => {
                            out.push(n.borrow().val.to_string());
                            queue.push_back(n.borrow().left.clone());
                            queue.push_back(n.borrow().right.clone());
                        }
                        None => { out.push("null".to_string()); }
                    }
                }
                while out.last().map_or(false, |s| s == "null") { out.pop(); }
                out.join(" ")
            }
        }
    }

    fn deserialize(data: &str) -> Option<Rc<RefCell<TreeNode>>> {
        if data.is_empty() { return None; }
        let tokens: Vec<&str> = data.split_whitespace().collect();
        if tokens[0] == "null" { return None; }
        let root = TreeNode::new(tokens[0].parse().unwrap());
        let mut queue: VecDeque<Rc<RefCell<TreeNode>>> = VecDeque::new();
        queue.push_back(root.clone());
        let mut i = 1;
        while !queue.is_empty() && i < tokens.len() {
            let node = queue.pop_front().unwrap();
            if i < tokens.len() && tokens[i] != "null" {
                let child = TreeNode::new(tokens[i].parse().unwrap());
                node.borrow_mut().left = Some(child.clone());
                queue.push_back(child);
            }
            i += 1;
            if i < tokens.len() && tokens[i] != "null" {
                let child = TreeNode::new(tokens[i].parse().unwrap());
                node.borrow_mut().right = Some(child.clone());
                queue.push_back(child);
            }
            i += 1;
        }
        Some(root)
    }
}

/* =====================================================================
 * Environment Utilities
 * ===================================================================== */

fn parse_tree_line(line: &str) -> Vec<i32> {
    line.split_whitespace()
        .map(|s| if s == "null" { NULL_VAL } else { s.parse().unwrap() })
        .collect()
}

fn build_tree_from_list(vals: &[i32]) -> Option<Rc<RefCell<TreeNode>>> {
    if vals.is_empty() || vals[0] == NULL_VAL { return None; }
    let root = TreeNode::new(vals[0]);
    let mut queue: VecDeque<Rc<RefCell<TreeNode>>> = VecDeque::new();
    queue.push_back(root.clone());
    let mut i = 1;
    while !queue.is_empty() && i < vals.len() {
        let node = queue.pop_front().unwrap();
        if i < vals.len() {
            if vals[i] != NULL_VAL {
                let child = TreeNode::new(vals[i]);
                node.borrow_mut().left = Some(child.clone());
                queue.push_back(child);
            }
            i += 1;
        }
        if i < vals.len() {
            if vals[i] != NULL_VAL {
                let child = TreeNode::new(vals[i]);
                node.borrow_mut().right = Some(child.clone());
                queue.push_back(child);
            }
            i += 1;
        }
    }
    Some(root)
}

fn convert_tree_to_list(root: &Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {
    match root {
        None => vec![],
        Some(r) => {
            let mut result = Vec::new();
            let mut queue: VecDeque<Option<Rc<RefCell<TreeNode>>>> = VecDeque::new();
            queue.push_back(Some(r.clone()));
            while !queue.is_empty() {
                let node = queue.pop_front().unwrap();
                match node {
                    Some(n) => {
                        let n_ref = n.borrow();
                        result.push(n_ref.val);
                        let left = n_ref.left.clone();
                        let right = n_ref.right.clone();
                        drop(n_ref);
                        queue.push_back(left);
                        queue.push_back(right);
                    }
                    None => { result.push(NULL_VAL); }
                }
            }
            while result.last().map_or(false, |&v| v == NULL_VAL) { result.pop(); }
            result
        }
    }
}

/* =====================================================================
 * Solve
 * ===================================================================== */

fn solve(root: &Option<Rc<RefCell<TreeNode>>>) -> Option<Rc<RefCell<TreeNode>>> {
    let data = CodecBFS::serialize(root);
    CodecBFS::deserialize(&data)
}

/* =====================================================================
 * Main
 * ===================================================================== */

fn main() {
    let n = read_int();
    if n == 0 { return; }
    let line = read_line();
    let vals = parse_tree_line(&line);
    let tree = build_tree_from_list(&vals);
    let result = solve(&tree);
    let result_list = convert_tree_to_list(&result);
    let parts: Vec<String> = result_list.iter()
        .map(|&v| if v == NULL_VAL { "null".to_string() } else { v.to_string() })
        .collect();
    write_string(&parts.join(" "));
    std::process::exit(0);
}
