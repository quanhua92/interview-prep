/*
 * P572: Subtree of Another Tree [PREMIUM] (Easy)
 * https://leetcode.com/problems/subtree-of-another-tree/
 * Topics: Tree, Depth-First Search, String Matching, Binary Tree, Hash Function
 * 
 * Given the roots of two binary trees root and subRoot, return true if there is a subtree of root with the same structure and node values of subRoot and false otherwise.
 * A subtree of a binary tree tree is a tree that consists of a node in tree and all of this node's descendants. The tree tree could also be considered as a subtree of itself.
 * Example 1:
 *     Input: root = [3,4,5,1,2], subRoot = [4,1,2]
 *     Output: true
 * 
 * Example 2:
 *     Input: root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
 *     Output: false
 * 
 * Constraints:
 *     - The number of nodes in the root tree is in the range [1, 2000].
 *     - The number of nodes in the subRoot tree is in the range [1, 1000].
 *     - -104 <= root.val <= 104
 *     - -104 <= subRoot.val <= 104
 * 
 * Hint: Which approach is better here- recursive or iterative?
 * Hint: If recursive approach is better, can you write recursive function with its parameters?
 * Hint: Two trees <b>s</b> and <b>t</b> are said to be identical if their root values are same and their left and right subtrees are identical. Can you write this in form of recursive formulae?
 * Hint: Recursive formulae can be:
 * isIdentical(s,t)= s.val==t.val AND isIdentical(s.left,t.left) AND isIdentical(s.right,t.right)
 * 
 * Template (python3):
 *     # Definition for a binary tree node.
 *     # class TreeNode:
 *     #     def __init__(self, val=0, left=None, right=None):
 *     #         self.val = val
 *     #         self.left = left
 *     #         self.right = right
 *     class Solution:
 *         def isSubtree(self, root: Optional[TreeNode], subRoot: Optional[TreeNode]) -> bool:
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
    todo!()
}

fn is_same(a: &Option<Rc<RefCell<TreeNode>>>, b: &Option<Rc<RefCell<TreeNode>>>) -> bool {
    todo!()
}

fn is_subtree(root: &Option<Rc<RefCell<TreeNode>>>, sub_root: &Option<Rc<RefCell<TreeNode>>>) -> bool {
    todo!()
}

fn main() {
    println!("\n============================================================");
    println!("  572. Subtree of Another Tree");
    println!("============================================================");

    struct TestCase { label: &'static str, root: &'static [i32], sub: &'static [i32], expected: bool }
    let tests: &[TestCase] = &[
        TestCase { label: "example 1", root: &[3,4,5,1,2], sub: &[4,1,2], expected: true },
        TestCase { label: "example 2", root: &[3,4,5,1,2,100001,100001,100001,100001,0], sub: &[4,1,2], expected: false },
        TestCase { label: "identical trees", root: &[1,2,3], sub: &[1,2,3], expected: true },
        TestCase { label: "single node match", root: &[1], sub: &[1], expected: true },
        TestCase { label: "right-skewed subtree", root: &[1,100001,2,100001,3], sub: &[2,100001,3], expected: true },
        TestCase { label: "no matching value", root: &[1,2], sub: &[3], expected: false },
    ];

    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let root = from_list(tc.root);
        let sub = from_list(tc.sub);
        let got = is_subtree(&root, &sub);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {}", tc.expected);
            println!("    Got:      {}", got);
        }
    }

    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");

    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
