/*
 * P508: Most Frequent Subtree Sum [PREMIUM] (Medium)
 * https://leetcode.com/problems/most-frequent-subtree-sum/
 * Topics: Hash Table, Tree, Depth-First Search, Binary Tree
 * 
 * Given the root of a binary tree, return the most frequent subtree sum. If there is a tie, return all the values with the highest frequency in any order.
 * The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself).
 * Example 1:
 *     Input: root = [5,2,-3]
 *     Output: [2,-3,4]
 * 
 * Example 2:
 *     Input: root = [5,2,-5]
 *     Output: [2]
 * 
 * Constraints:
 *     - The number of nodes in the tree is in the range [1, 104].
 *     - -105 <= Node.val <= 105
 * 
 * Template (python3):
 *     # Definition for a binary tree node.
 *     # class TreeNode:
 *     #     def __init__(self, val=0, left=None, right=None):
 *     #         self.val = val
 *     #         self.left = left
 *     #         self.right = right
 *     class Solution:
 *         def findFrequentTreeSum(self, root: Optional[TreeNode]) -> List[int]:
 */
#[allow(unused_imports)]
use rstest;
use std::cell::RefCell;
use std::rc::Rc;
use std::collections::HashMap;

#[derive(Clone)]
struct TreeNode {
    val: i32,
    left: Option<Rc<RefCell<TreeNode>>>,
    right: Option<Rc<RefCell<TreeNode>>>,
}

fn from_list(vals: &[i32]) -> Option<Rc<RefCell<TreeNode>>> {
    todo!()
}

fn subtree_sum(node: &Option<Rc<RefCell<TreeNode>>>, freq: &mut HashMap<i32, i32>) -> i32 {
    todo!()
}

fn find_frequent_tree_sum(root: &Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {
    todo!()
}

fn main() {
    println!("\n============================================================");
    println!("  508. Most Frequent Subtree Sum");
    println!("============================================================");

    struct TestCase { label: &'static str, vals: &'static [i32], expected: &'static [i32] }
    let tests: &[TestCase] = &[
        TestCase { label: "example 1", vals: &[5, 2, -3], expected: &[-3, 2, 4] },
        TestCase { label: "example 2", vals: &[5, 2, -5], expected: &[2] },
        TestCase { label: "single node", vals: &[1], expected: &[1] },
        TestCase { label: "balanced tree", vals: &[1, 2, 3], expected: &[2, 3, 6] },
        TestCase { label: "all negative values", vals: &[-1, -2, -3], expected: &[-6, -3, -2] },
    ];

    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let root = from_list(tc.vals);
        let got = find_frequent_tree_sum(&root);
        let mut expected = tc.expected.to_vec();
        expected.sort();
        if got == expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {:?}", expected);
            println!("    Got:      {:?}", got);
        }
    }

    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");

    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
