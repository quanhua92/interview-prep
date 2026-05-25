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

fn level_order(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<Vec<i32>> {
    todo!()
}

fn main() {
    let tests: Vec<(&str, Vec<i32>, Vec<Vec<i32>>)> = vec![
        ("example 1", vec![3,9,20,NULL_VAL,NULL_VAL,15,7], vec![vec![3],vec![9,20],vec![15,7]]),
        ("example 2", vec![1], vec![vec![1]]),
        ("empty", vec![], vec![]),
        ("right child only", vec![1,NULL_VAL,2], vec![vec![1],vec![2]]),
        ("left child only", vec![1,2], vec![vec![1],vec![2]]),
        ("full binary tree depth 2", vec![5,3,8,1,4,7,9], vec![vec![5],vec![3,8],vec![1,4,7,9]]),
        ("negative values", vec![-1,-2,-3], vec![vec![-1],vec![-2,-3]]),
        ("all same value", vec![1,1,1,1,1,1,1], vec![vec![1],vec![1,1],vec![1,1,1,1]]),
    ];
    let mut passed = 0;
    for (i, (label, vals, expected)) in tests.iter().enumerate() {
        let root = build_tree(vals);
        let got = level_order(root);
        if got == *expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, label);
            println!("    Expected: {:?}", expected);
            println!("    Got:      {:?}", got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
