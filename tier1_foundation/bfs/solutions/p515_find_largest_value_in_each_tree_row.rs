/*
 * P515: Find Largest Value in Each Tree Row [PREMIUM] (Medium)
 * https://leetcode.com/problems/find-largest-value-in-each-tree-row/
 * Topics: Tree, Depth-First Search, Breadth-First Search, Binary Tree
 *
 * Given the root of a binary tree, return an array of the largest value in each row of the tree (0-indexed).
 * Example 1:
 *     Input: root = [1,3,2,5,3,null,9]
 *     Output: [1,3,9]
 *
 * Example 2:
 *     Input: root = [1,2,3]
 *     Output: [1,3]
 *
 * Constraints:
 *     - The number of nodes in the tree will be in the range [0, 104].
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
 *         def largestValues(self, root: Optional[TreeNode]) -> List[int]:
 */


use std::cell::RefCell;
use std::collections::VecDeque;
use std::rc::Rc;
use rstest::print_arr;

struct TreeNode {
    val: i32,
    left: Option<Rc<RefCell<TreeNode>>>,
    right: Option<Rc<RefCell<TreeNode>>>,
}

const NULL_VAL: i32 = i32::MIN;

fn build_tree(vals: &[i32]) -> Option<Rc<RefCell<TreeNode>>> {
    if vals.is_empty() || vals[0] == NULL_VAL {
        return None;
    }
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

fn largest_values(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {
    let mut result = Vec::new();
    let root = match root {
        Some(r) => r,
        None => return result,
    };
    let mut queue: VecDeque<Rc<RefCell<TreeNode>>> = VecDeque::new();
    queue.push_back(root);
    while !queue.is_empty() {
        let sz = queue.len();
        let mut max_val = i32::MIN;
        for _ in 0..sz {
            let node = queue.pop_front().unwrap();
            let v = node.borrow().val;
            if v > max_val {
                max_val = v;
            }
            let (left, right) = {
                let n = node.borrow();
                (n.left.clone(), n.right.clone())
            };
            if let Some(l) = left {
                queue.push_back(l);
            }
            if let Some(r) = right {
                queue.push_back(r);
            }
        }
        result.push(max_val);
    }
    result
}

fn main() {
    let tests: Vec<(&str, Vec<i32>, Vec<i32>)> = vec![
        ("example 1", vec![1, 3, 2, 5, 3, NULL_VAL, 9], vec![1, 3, 9]),
        ("example 2", vec![1, 2, 3], vec![1, 3]),
        ("empty tree", vec![], vec![]),
        ("negative values", vec![-1, -2, -3, -4], vec![-1, -2, -4]),
        ("left chain", vec![1, 2, NULL_VAL, 3], vec![1, 2, 3]),
        ("single node", vec![5], vec![5]),
    ];
    let mut passed = 0;
    for (i, (label, vals, expected)) in tests.iter().enumerate() {
        let root = build_tree(vals);
        let got = largest_values(root);
        if got == *expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, label);
            print!("    Expected: ");
            print_arr(expected);
            print!("\n    Got:      ");
            print_arr(&got);
            println!();
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
