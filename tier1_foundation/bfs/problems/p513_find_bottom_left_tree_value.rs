/*
 * P513: Find Bottom Left Tree Value [PREMIUM] (Medium)
 * https://leetcode.com/problems/find-bottom-left-tree-value/
 * Topics: Tree, Depth-First Search, Breadth-First Search, Binary Tree
 * 
 * Given the root of a binary tree, return the leftmost value in the last row of the tree.
 * Example 1:
 *     Input: root = [2,1,3]
 *     Output: 1
 * 
 * Example 2:
 *     Input: root = [1,2,3,4,null,5,6,null,null,7]
 *     Output: 7
 * 
 * Constraints:
 *     - The number of nodes in the tree is in the range [1, 104].
 *     - -231 <= Node.val <= 231 - 1
 * 
 * Template (python3):
 *     # Definition for a binary tree node.
 *     # class TreeNode:
 *     #     def __init__(self, val=0, left=None, right=None):
 *     #         self.val = val
 *     #         self.left = left
 *     #         self.right = right
 *     class Solution:
 *         def findBottomLeftValue(self, root: Optional[TreeNode]) -> int:
 */
use std::cell::RefCell;
use std::collections::VecDeque;
use std::rc::Rc;

struct TreeNode {
    val: i32,
    left: Option<Rc<RefCell<TreeNode>>>,
    right: Option<Rc<RefCell<TreeNode>>>,
}

const NULL_VAL: i32 = i32::MIN;

fn build_tree(vals: &[i32]) -> Option<Rc<RefCell<TreeNode>>> {
    todo!()
}

fn find_bottom_left_value(root: Rc<RefCell<TreeNode>>) -> i32 {
    todo!()
}

fn main() {
    let tests: Vec<(&str, Vec<i32>, i32)> = vec![
        ("example 1", vec![2, 1, 3], 1),
        ("example 2", vec![1, 2, 3, 4, NULL_VAL, 5, 6, NULL_VAL, NULL_VAL, 7], 7),
        ("single node", vec![1], 1),
        ("left child only", vec![1, 2], 2),
        ("right child only", vec![1, NULL_VAL, 2], 2),
        ("left skewed deep", vec![1, 2, NULL_VAL, 3, NULL_VAL, 4], 4),
    ];
    let mut passed = 0;
    for (i, (label, vals, expected)) in tests.iter().enumerate() {
        let root = build_tree(vals).unwrap();
        let got = find_bottom_left_value(root);
        if got == *expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, label);
            println!("    Expected: {}", expected);
            println!("    Got:      {}", got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
