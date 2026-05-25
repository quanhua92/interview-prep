/*
 * P450: Delete Node in a BST [PREMIUM] (Medium)
 * https://leetcode.com/problems/delete-node-in-a-bst/
 * Topics: Tree, Binary Search Tree, Binary Tree
 *
 * Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.
 * Basically, the deletion can be divided into two stages:
 * Example 3:
 * Follow up: Could you solve it with time complexity O(height of tree)?
 * Example 1:
 *     Input: root = [5,3,6,2,4,null,7], key = 3
 *     Output: [5,4,6,2,null,null,7]
 *     Explanation: Given key to delete is 3. So we find the node with value 3 and delete it.
 *     One valid answer is [5,4,6,2,null,null,7], shown in the above BST.
 *     Please notice that another valid answer is [5,2,6,null,4,null,7] and it's also accepted.
 *
 * Example 2:
 *     Input: root = [5,3,6,2,4,null,7], key = 0
 *     Output: [5,3,6,2,4,null,7]
 *     Explanation: The tree does not contain a node with value = 0.
 *
 * Example 3:
 *     Input: root = [], key = 0
 *     Output: []
 *
 * Constraints:
 *     - The number of nodes in the tree is in the range [0, 104].
 *     - -105 <= Node.val <= 105
 *     - Each node has a unique value.
 *     - root is a valid binary search tree.
 *     - -105 <= key <= 105
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
 */


use std::collections::VecDeque;

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

fn tree_to_bfs(root: &Option<Box<TreeNode>>) -> Vec<i32> {
    let nil = i32::MAX;
    let mut result = Vec::new();
    let mut q = VecDeque::new();
    q.push_back(root.as_ref().map(|n| n as &TreeNode));
    while let Some(node_opt) = q.pop_front() {
        match node_opt {
            None => result.push(nil),
            Some(n) => {
                result.push(n.val);
                q.push_back(n.left.as_ref().map(|n| n as &TreeNode));
                q.push_back(n.right.as_ref().map(|n| n as &TreeNode));
            }
        }
    }
    while result.len() > 1 && *result.last().unwrap() == nil { result.pop(); }
    result
}

fn build_from_list(vals: &[i32]) -> Option<Box<TreeNode>> {
    let nil = i32::MAX;
    let mut root: Option<Box<TreeNode>> = None;
    for &v in vals {
        if v != nil { root = insert(root, v); }
    }
    root
}

fn main() {
    let nil = i32::MAX;
    let tests: Vec<(&str, Vec<i32>, i32, Vec<i32>)> = vec![
        ("example 1", vec![5,3,6,2,4,nil,7], 3, vec![5,4,6,2,nil,nil,7]),
        ("example 2", vec![5,3,6,2,4,nil,7], 0, vec![5,3,6,2,4,nil,7]),
        ("example 3", vec![nil], 0, vec![nil]),
        ("delete single node root", vec![5], 5, vec![nil]),
        ("delete root with two children", vec![3,1,4], 3, vec![4,1]),
        ("delete left leaf", vec![2,1,3], 1, vec![2,nil,3]),
        ("delete node with only left child", vec![5,3,nil,2,nil,1], 3, vec![5,2,nil,1]),
    ];

    let mut passed = 0;
    println!("\n============================================================");
    println!("  450. Delete Node in a BST");
    println!("============================================================");
    for (i, (label, input, key, expected)) in tests.iter().enumerate() {
        let root = build_from_list(input);
        let root = delete_node(root, *key);
        let got = tree_to_bfs(&root);
        let ok = got == *expected;
        if ok { passed += 1; }
        println!("  Test {} ({}): {}", i + 1, label, if ok { "PASS" } else { "FAIL" });
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
