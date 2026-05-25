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
 *     - The number of nodes in the tree is in the range [0, 104].
 *     - -104 <= Node.val <= 104
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


#[allow(unused_imports)]
use rstest;
use std::cell::RefCell;
use std::rc::Rc;

#[derive(Clone)]
struct TreeNode {
    val: i32,
    left: Option<Rc<RefCell<TreeNode>>>,
    right: Option<Rc<RefCell<TreeNode>>>,
}

fn from_list(vals: &[i32]) -> Option<Rc<RefCell<TreeNode>>> {
    if vals.is_empty() || vals[0] == 100_001 { return None; }
    let root = Rc::new(RefCell::new(TreeNode { val: vals[0], left: None, right: None }));
    let mut queue = std::collections::VecDeque::new();
    queue.push_back(root.clone());
    let mut vi = 1;
    while !queue.is_empty() && vi < vals.len() {
        let node = queue.pop_front().unwrap();
        if vi < vals.len() {
            if vals[vi] != 100_001 {
                let child = Rc::new(RefCell::new(TreeNode { val: vals[vi], left: None, right: None }));
                node.borrow_mut().left = Some(child.clone());
                queue.push_back(child);
            }
            vi += 1;
        }
        if vi < vals.len() {
            if vals[vi] != 100_001 {
                let child = Rc::new(RefCell::new(TreeNode { val: vals[vi], left: None, right: None }));
                node.borrow_mut().right = Some(child.clone());
                queue.push_back(child);
            }
            vi += 1;
        }
    }
    Some(root)
}

fn trees_equal(a: &Option<Rc<RefCell<TreeNode>>>, b: &Option<Rc<RefCell<TreeNode>>>) -> bool {
    match (a, b) {
        (None, None) => true,
        (None, _) | (_, None) => false,
        (Some(an), Some(bn)) => {
            an.borrow().val == bn.borrow().val
                && trees_equal(&an.borrow().left, &bn.borrow().left)
                && trees_equal(&an.borrow().right, &bn.borrow().right)
        }
    }
}

fn convert_bst(root: &Option<Rc<RefCell<TreeNode>>>) {
    fn reverse_inorder(node: &Option<Rc<RefCell<TreeNode>>>, total: &mut i32) {
        if let Some(n) = node {
            reverse_inorder(&n.borrow().right, total);
            *total += n.borrow().val;
            n.borrow_mut().val = *total;
            reverse_inorder(&n.borrow().left, total);
        }
    }
    let mut total = 0;
    reverse_inorder(root, &mut total);
}

fn main() {
    println!("\n============================================================");
    println!("  538. Convert BST to Greater Tree");
    println!("============================================================");

    struct TestCase { label: &'static str, input: &'static [i32], expected: &'static [i32] }
    let tests: &[TestCase] = &[
        TestCase { label: "example 1", input: &[4,1,6,0,2,5,7,100001,100001,100001,3,100001,100001,100001,8], expected: &[30,36,21,36,35,26,15,100001,100001,100001,33,100001,100001,100001,8] },
        TestCase { label: "example 2", input: &[0,100001,1], expected: &[1,100001,1] },
        TestCase { label: "small balanced BST", input: &[2,1,3], expected: &[5,6,3] },
        TestCase { label: "single node", input: &[1], expected: &[1] },
        TestCase { label: "right-skewed BST", input: &[1,100001,2,100001,3], expected: &[6,100001,5,100001,3] },
    ];

    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let root = from_list(tc.input);
        let expected = from_list(tc.expected);
        convert_bst(&root);
        if trees_equal(&root, &expected) {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
        }
    }

    {
        convert_bst(&None);
        passed += 1;
        println!("  Test 6 (empty tree): PASS");
    }

    println!("\n  {}/6 passed", passed);
    println!("============================================================\n");

    std::process::exit(if passed == 6 { 0 } else { 1 });
}
