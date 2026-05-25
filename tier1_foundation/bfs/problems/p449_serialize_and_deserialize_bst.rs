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
 *     - The number of nodes in the tree is in the range [0, 104].
 *     - 0 <= Node.val <= 104
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

fn solve(vals: &[i32]) -> Vec<i32> {
    todo!()
}

fn main() {
    let tests: Vec<(&str, Vec<i32>, Vec<i32>)> = vec![
        ("example 1", vec![2,1,3], vec![2,1,3]),
        ("empty tree", vec![], vec![]),
        ("single node", vec![1], vec![1]),
        ("bst with left subtree", vec![3,1,4,NULL_VAL,2], vec![3,1,4,NULL_VAL,2]),
        ("balanced bst 3 levels", vec![5,3,8,1,4,7,9], vec![5,3,8,1,4,7,9]),
        ("complete bst", vec![4,2,5,1,3], vec![4,2,5,1,3]),
    ];
    let mut passed = 0;
    for (i, (label, vals, expected)) in tests.iter().enumerate() {
        let got = solve(vals);
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
