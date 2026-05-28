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

use wasm_libs::*;
use std::collections::HashMap;

fn build_tree(vals: &[i32], nl: i32) -> (Vec<i32>, Vec<i32>) {
    let n = vals.len();
    if n == 0 || vals[0] == nl { return (vec![], vec![]); }
    let mut left = vec![-1i32; n];
    let mut right = vec![-1i32; n];
    let mut qi = 1usize;
    let mut queue = std::collections::VecDeque::new();
    queue.push_back(0usize);
    while let Some(i) = queue.pop_front() {
        if qi < n {
            left[i] = if vals[qi] == nl { -1 } else { qi as i32 };
            if vals[qi] != nl { queue.push_back(qi); }
            qi += 1;
        }
        if qi < n {
            right[i] = if vals[qi] == nl { -1 } else { qi as i32 };
            if vals[qi] != nl { queue.push_back(qi); }
            qi += 1;
        }
    }
    (left, right)
}

fn main() {
    let line = read_line();
    let nl = 2147483647i32;
    let vals: Vec<i32> = line.split_whitespace()
        .map(|t| if t == "null" { nl } else { t.parse().unwrap() })
        .collect();

    if vals.is_empty() || vals[0] == nl {
        write_ints(&[]);
        return;
    }

    let (left, right) = build_tree(&vals, nl);
    let mut freq: HashMap<i32, i32> = HashMap::new();

    fn subtree_sum(idx: i32, vals: &[i32], left: &[i32], right: &[i32], freq: &mut HashMap<i32, i32>) -> i32 {
        if idx < 0 { return 0; }
        let s = vals[idx as usize]
            + subtree_sum(left[idx as usize], vals, left, right, freq)
            + subtree_sum(right[idx as usize], vals, left, right, freq);
        *freq.entry(s).or_insert(0) += 1;
        s
    }

    subtree_sum(0, &vals, &left, &right, &mut freq);

    let max_freq = *freq.values().max().unwrap_or(&0);
    let mut result: Vec<i32> = freq.into_iter().filter(|&(_, v)| v == max_freq).map(|(k, _)| k).collect();
    result.sort();
    write_ints(&result);
}
